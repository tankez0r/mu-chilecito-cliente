# MU Helper

The MU Helper is the client-side auto-combat/auto-loot assistant (`MUHelper::CMuHelper`,
`src/source/MUHelper/`), configured from its window in-game
(`CNewUIMuHelper`, `src/source/UI/NewUI/NewUIMuHelper.cpp`). It attacks
nearby monsters, drinks potions, buffs, picks up items, and returns to its
starting spot if it wanders too far - all while the player is present but
not actively clicking.

## AoE Auto-Attack

**Option:** "AoE Auto-Attack (AoE skills only)" checkbox, available to every
class.

Enabling this option changes how the helper behaves once it's surrounded,
to match the old MU "autoclick" playstyle instead of chasing one monster at
a time. It applies to **whatever attack skill is actually configured** -
not a fixed whitelist of area skills - plus the basic-attack fallback:

- **Holds position and attacks in place** as long as at least one known
  monster is already within range of whatever the helper is about to use
  (the configured skill, or the basic-attack fallback's range if that's
  what fires this tick). It does not path toward any specific monster's
  tile while this holds, and it doesn't matter whether that particular
  monster is the "current target" - the helper just keeps swinging at
  whatever's already close enough, self-positioned, no explicit aim.
- **Approaches like the normal helper** (the same short, incremental
  movement used for single-target skills and the basic-attack fallback)
  whenever nothing is currently within range - e.g. only one monster in
  view and it's still a few tiles away, or the current spot ran dry. Once
  something comes into range, it goes back to holding position.
- Item pickup (gold, drops) and the return-to-origin behavior are unaffected
  by this option - the character can still move for those regardless of
  whether AoE mode is currently holding position (see "Getting stuck when
  surrounded" below for what happens if that movement itself gets blocked).

Without this option, an attack is only made at melee/skill range like a
single-target skill would be, so it can end up path-following one monster
instead of just standing and swinging at the cluster.

Some skills (Nova, Hell Fire, Inferno, Evil Spirit, Storm) always hold
position regardless of this checkbox - they fire from the caster's own tile
by nature (verified against the server's `ClassAttack.cpp`-equivalent cast
code, which sends every one of these with the caster's own coordinates, not
the target's). `CMuHelper::IsSelfPositionSkill` is that fixed list; the AoE
Auto-Attack checkbox is what extends the same treatment to every other
skill once something is in range, instead of requiring a skill-specific
whitelist entry.

## Auto Life Buff (Elf class only)

**Option:** "Auto Life Buff (Elf class only)" checkbox, shown only for the
Elf class line.

Independently of the generic buff-skill slots, keeps "Swell Life" (HP boost)
active on the character whenever it drops, without needing a dedicated
buff-skill slot for it.

## Getting stuck when surrounded

`CMuHelper::Work()` runs its stages in a fixed order every tick
(`ActivatePet → AutoBuffLifeElf → Buff → RecoverHealth (Heal/DrainLife/
ConsumePotion) → ObtainItem → Regroup → Attack → RepairEquipments`), and
**any stage that returns 0 stops the whole tick right there** - stages
after it, including `Attack()`, never run. Several non-obvious fixes exist
because some stage kept returning 0 forever under specific conditions,
freezing the character in place indefinitely (not casting, not attacking,
not looting) until whatever was blocking it went away on its own:

- **Skill/basic-attack range checks no longer require a walkable path to
  the target's exact tile before attacking.** When boxed in by several
  monster bodies, the pathfinding search can fail to route to a target's
  tile even though the target is already within melee or cast range - the
  helper now attacks immediately whenever it's already in range, and only
  falls back to path-and-move when it actually needs to close distance.
  (`TryApproachTarget`'s near-check-before-pathfinding.)
- **`TryApproachTarget` also short-circuits under AoE Auto-Attack**,
  independently of the skill's own self-position status: if that option is
  on and *anything* is within the range being checked, it reports "already
  there" without moving, regardless of which specific target this
  particular call was aiming for. Without this, the basic-attack fallback
  (which always calls `TryApproachTarget` unconditionally) or a
  non-self-position skill's targeted-approach branch would walk toward
  whichever monster happened to be tracked as "current", even while
  several other monsters were already in range - the visible symptom was
  the character still wandering a little with AoE mode on, because the
  primary skill occasionally couldn't fire that tick (no mana, wrong
  timer/condition) and fell through to the chasing fallback.
- **Self-defense only takes over the current target when a monster is
  actually attacking**, not on every monster that merely walks into view.
  Otherwise, being surrounded means the "current target" reassigns itself
  many times a second from incidental movement updates, and no
  attack/skill sequence ever gets a chance to land.
- **The hit-stagger animation (`PLAYER_SHOCK`, set on every hit the hero
  takes) blocks every skill cast, not just the main attack.**
  `GameLogic::Combat::ExecuteSkill()` silently no-ops while staggered, and
  every Work() stage that casts something - `AutoBuffLifeElf`, `Buff`
  (self and party), `Heal`/`HealSelf`, `DrainLife` - routes through the
  same `SimulateSkill()` choke point. Fixed there once: `SimulateSkill`
  now reports success immediately when staggered instead of trying and
  silently failing, so Work() falls through to `Attack()` (which already
  has its own staggered fallback to a basic attack) instead of stalling on
  a buff/heal that can never land mid-hitstun anyway. The skipped buff/heal
  just retries next tick once the stagger clears.
- **Chasing a blocked drop, or a blocked path back to the original
  position, now gives up after 2 attempts instead of retrying forever.**
  `ObtainItem()` and `Regroup()`/`SimulateMove()` both call `PathFinding2`
  with no attempt limit; if the path was blocked (e.g. by the very
  monsters being fought), they returned 0 every tick indefinitely -
  `Attack()` is downstream of both in `Work()`'s order, so an unreachable
  drop or an unreachable "way back home" while mid-fight could stall
  combat completely, with no monster stagger involved at all. Both now
  give up after 2 blocked ticks (deleting the item / leaving the
  return-to-origin attempt for its next natural trigger) and let the rest
  of the tick proceed.
