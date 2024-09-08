/*
This class is responsible for most of what the player sees. It extends the basic
common functionality of the server and client and
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "client/client_network.h"
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
  ClientNetwork network_;
  sf::RenderWindow window_;
  bool networkInitalized_{false};

  /* -------------------------------- Functions ----------------------------- */
  bool initialize_network();
  void update(float deltaTime) override;
  void abort() override;

  void poll_events();
  void draw();
};
/* -------------------------------------------------------------------------- */