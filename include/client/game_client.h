/*
TODO document
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "common/defines.h"
#include "common/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
/* -------------------------------------------------------------------------- */
class GameClient : public Game {
public:
  GameClient(); // Acts as a setup function as well.
  void run() override;

private:
  /* ------------------------------- Variables ------------------------------ */
  // TODO move network related variables to a network manager.
  uint16_t serverPort_{DEFAULT_PORT};
  sf::IpAddress serverAddress_{"127.0.0.1"};
  sf::TcpSocket socket_{};
  sf::RenderWindow window_;

  /* -------------------------------- Functions ----------------------------- */
  bool initialize_network();
  void update(float deltaTime) override;
  void abort() override;

  void poll_events();
  void draw();
};
/* -------------------------------------------------------------------------- */