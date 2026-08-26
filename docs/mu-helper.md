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

When the character's configured attack skill is one of a short whitelist of
self-centered area skills (Twisting Slash, Cyclone, Fire Slash, and their
upgrades), enabling this option changes how the helper behaves once it's
surrounded, to match the old MU "autoclick" playstyle instead of chasing one
monster at a time:

- **Holds position and casts in place** as long as at least one known
  monster is already within the skill's radius. It does not path toward any
  specific monster's tile while this holds - the area skill hits everything
  nearby regardless of exact position.
- **Approaches like the normal helper** (the same short, incremental
  movement used for single-target skills and the basic-attack fallback)
  whenever nothing is currently within the skill's radius - e.g. only one
  monster in view and it's still a few tiles away, or the current spot ran
  dry. Once something comes into range, it goes back to holding position.
- Item pickup (gold, drops) and the return-to-origin behavior are unaffected
  by this option - the character can still move for those regardless of
  whether AoE mode is currently holding position.

Without this option, an area skill is only cast at melee range like a
single-target skill would be, so it can end up path-following one monster
instead of just standing and swinging at the cluster.

## Auto Life Buff (Elf class only)

**Option:** "Auto Life Buff (Elf class only)" checkbox, shown only for the
Elf class line.

Independently of the generic buff-skill slots, keeps "Swell Life" (HP boost)
active on the character whenever it drops, without needing a dedicated
buff-skill slot for it.

## Getting stuck when surrounded

Two related, non-obvious fixes keep the helper from stalling out under a
pile of monsters - relevant to why AoE Auto-Attack needed to exist in the
first place:

- **Skill/basic-attack range checks no longer require a walkable path to
  the target's exact tile before attacking.** When boxed in by several
  monster bodies, the pathfinding search can fail to route to a target's
  tile even though the target is already within melee or cast range - the
  helper now attacks immediately whenever it's already in range, and only
  falls back to path-and-move when it actually needs to close distance.
- **Self-defense only takes over the current target when a monster is
  actually attacking**, not on every monster that merely walks into view.
  Otherwise, being surrounded means the "current target" reassigns itself
  many times a second from incidental movement updates, and no
  attack/skill sequence ever gets a chance to land.
- **The hit-stagger animation blocks all skills, not just some** - so the
  helper skips straight to the basic-attack fallback while staggered rather
  than wasting a tick on a skill call that the game will silently ignore
  anyway.
