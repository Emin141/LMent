/*
The class representing the game server. This class is responsible for updating
and propagating the game state to all players, to start and end matches, and to
enforce game rules.
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "common/defines.h"
#include "common/game.h"
#include "server/server_network.h"
#include <SFML/Network.hpp>
/* -------------------------------------------------------------------------- */
class GameServer : public Game {
public:
  GameServer(); // Acts as a setup function as well.
  void init(int playerCount = MIN_NUMBER_OF_PLAYERS, int port = DEFAULT_PORT);
  void run() override;

private:
  /* ------------------------------- Variables ------------------------------ */
  ServerNetwork network_;

  /* ------------------------------- Functions ------------------------------ */
  bool initialize_network(int playerCount = DEFAULT_PORT,
                          int port = DEFAULT_PORT);
  void update(float deltaTime) override;
  void abort() override;
};
/* -------------------------------------------------------------------------- */