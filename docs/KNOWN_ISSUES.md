# Known issues and recovery

AliceFracturedMinds is not native Unreal Engine 3 multiplayer: each player runs
their own game, and the mod keeps the important parts in sync. Some situations
can still drift apart.

## Scripted encounters and bosses

Boss phases and scripted waves can advance at different times for the two
players. If one player is stuck:

1. bring both players together with `P` (or `O` on the client);
2. wait a few seconds for the host's enemy state to arrive;
3. press `L` while the yellow action is visible, only if both are stuck;
4. restart the checkpoint if the encounter still cannot progress.

## World mechanisms

Some switches, pig snouts, platforms and secret-room scripts remain local and
may have to be used by both players.

## Remote Alice

Animation, aiming, hair, dress and particles of the other player are
approximations and can differ slightly from what that player sees.

## Joining and teleporting

Joining loads the host's chapter and checkpoint. Wait until the client can move,
then use `P` (nearby) or `O` (client, long distance). Using `O` while a level or
cinematic is still loading can place Alice in an invalid spot - reload the
checkpoint then.

## Performance

The game is 32-bit. Two game processes, PhysX and long sessions use a lot of
memory. Keep the 60 FPS limit, keep diagnostics off, and restart both games
between long chapters if the game becomes unstable.

## Reporting a problem

Open an issue with the chapter and what each player did. For logs, set
`Logs = 1` in `[Debug]` of `AliceCoop.ini` on both PCs, repeat the problem and
attach the files from `AliceCoop\logs` (remove personal information first).
