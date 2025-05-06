# DRL_Incremental
 
A game project for my Advanced Programming class.
--------------------

v0.4.1:
- Added "Decaying" debuff:
After a few seconds, if there are no inputs, decrease DRL.
- Added "Overload" debuff:
If you click too fast, the game will temporariy disallow you to click.
- Added failing condition:
If DRL stays before a certain thredshold for longer than a few seconds, force quit the game.

v0.5
- Added "Leech" debuff:
After a few seconds, a "leech" will spawn, subtracting DRL as long as it stays on the screen.
- Added "Bonus DRL":
After a few seconds, reward you with some DRL based on how much you got.
- Added MENU, GAMEOVER and VICTORY screen

v0.6
- Added sound effects and BGM.

In this game, you have to grind for DRL and strive for the scholarship! The more you click, the more DRL you will get!

How to play: Click on the gray box. Each click grants a number of DRL, based of which upgrade you are at.

Inspired by Cookie Clicker and similar incremental type of games.

References:
- Let's Make Games's SDL2 Tutorial series
- Assisted by ChatGPT and Github Copilot.

CREDITS:
Menu BGM: DDBY - Blue Wings (From "Cafe de Touhou 2")
Game BGM: DDBY - Sky Garden - Takayan (From "Cafe de Touhou 1")
Win BGM: rintaro soma - 系ぎて (R3 Music Box Cover) (From "maimai DX")
Game Over BGM: Fontainebleau - Just You (From "The NOexistenceN of you AND me")


TODO: Better game balancing
