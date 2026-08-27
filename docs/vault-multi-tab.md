# Multi-tab vault

The vault window (`CNewUIStorageInventory`, `src/source/UI/NewUI/Inventory/
NewUIStorageInventory.cpp`) now has 4 tabs instead of a single 8x15 storage
grid. Each tab is a genuinely independent storage on the server - its own
120 item slots and its own zen balance, not an offset view into one bigger
grid (that's what the pre-existing "Extended Vault" window,
`NewUIStorageInventoryExt`, already does, and it doesn't scale past ~2
pages because the slot index on the wire is a single byte).

## How it works

- 4 small tab buttons (`m_aTabBtn[VAULT_TAB_COUNT]`) sit at the top of the
  vault window. Clicking one sends `SendVaultTabSelectRequest(tabIndex)` -
  a new packet (`VaultTabSelectRequest`, C1/F3/0x60,
  `MUnique.OpenMU.Network.Packets` bumped to 0.9.11 for it).
- The client does **not** keep 4 separate item grids. There is still only
  one `CNewUIInventoryCtrl` for the window; the server always answers a tab
  switch through the exact same "here are the items of the storage you
  currently have open" mechanism it already uses when the vault dialog
  first opens (`ProcessToReceiveStorageItems` et al.), so switching tabs
  just clears and repopulates that one control in place.
- Item-move requests (drag an item in/out of the vault) are unchanged -
  still plain `ItemStorageKind.Vault`, no per-tab kind. The server tracks
  "which tab is active" itself (`Player.ActiveVaultTabIndex`) and repoints
  `Player.Vault` to match whenever a tab-select request comes in, so every
  existing move/zen code path on the server keeps working without knowing
  tabs exist at all. See `mu-chilecito-server`'s `feature/multi-tab-vault`
  branch for that half.
- `MUnique.OpenMU.Network.Packets` local package cache
  (`MuMain-main-cliente/.nuget/`) needed a manually-placed 0.9.11 build,
  since this project doesn't publish that package to a real NuGet feed -
  see `src/CMakeLists.txt`'s `OPENMU_PACKETS_VERSION` and
  `ClientLibrary/MUnique.Client.Library.csproj`'s hardcoded content-file
  paths, both of which needed the version bump too.

## What's not done here

- **Admin panel**: no client-side concern, but worth noting - the server
  side needed zero new panel code, since `Account.Vault2/3/4` are
  `[MemberOfAggregate] ItemStorage?` properties like `Vault`, and the
  panel's account-edit form already builds fields for any property shaped
  like that via reflection (`EmbeddedFormFieldBuilder`).
- **Not tested end-to-end against a live server** - built and verified to
  compile/link cleanly, but there was no local Docker/DB available to
  actually open the vault dialog and click between tabs. First real test:
  talk to the vault NPC in-game, confirm all 4 tabs show independent
  contents and money.
- Each tab's zen is independent (no shared pool across the 4) - not
  explicitly requested, just the simplest interpretation given each tab is
  a genuinely separate `ItemStorage` row.
