# Communication round robin

The purpose of this document is to demonstrate at high level overview of how the TCP connections will work with multiple clients. The document is meant for me, for the time being, and it will be committed to  the remote repository while the functionality is being implemented. 

## Steps

### Server

- After running the server it must take two inputs: **port number** and **number of players**
- The server listens for connections on the specified port, and waits until the number of connections it received is not equal to the number of players specified
- When all clients are connected, the game begins on the server. The server notifies all clients that the game has begun. All players are notified that it is *not* their turn to play
- The server chooses one player at random to be the first player, and notifies all players that it's their turn to play
- The server begins a loop which acts as the main game loop. 
- If the player can move, gives the player 4 elemental pieces and propagates that to other players. If the player cannot move, the game is over
- The server listens for turn steps (each turn has 5 steps) or element piece discards. Each time it gets an update, it sends it to all players
- Once the player does their last turn step, the next player is chosen to be the active player
- The loop restarts

### Client

- After running the client it must take two inputs: **server address** and **port number**
- The client connects to the server and listens for the game to start
- Once the game starts, the player listens for information about which player is playing
- If they are playing, they listen to the server giving them 4 elemental pieces, and send to the server information about discards or turn steps
- If they are not playing, the listen for updates of the game state
