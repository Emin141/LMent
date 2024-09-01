/*
The class representing the game server. This class is responsible for updating
and propagating the game state to all players, to start and end matches, and to
enforce game rules.
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "common/defines.h"
#include "common/game.h"
#include <SFML/Network.hpp>
/* -------------------------------------------------------------------------- */
class GameServer : public Game {
public:
  GameServer(); // Acts as a setup function as well.
  void run() override;

private:
  /* ------------------------------- Variables ------------------------------ */
  // TODO Networking may have some common functionality.
  int currentNumberOfPlayers_{0};
  int maxNumberOfPlayers_{0};
  uint16_t port_{50000};
  sf::TcpListener socketListener_{};
  sf::TcpSocket sockets_[4]; // I hate std::array and std::vector is overkill

  /* ------------------------------- Functions ------------------------------ */
  bool initialize_network();
  void update(float deltaTime) override;
  void exit() override;
};
/* -------------------------------------------------------------------------- */