/*
This class is responsible for most of what the player sees. It extends the basic
common functionality of the server and client and handles input, connections,
rendering, and such.
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "client/client_network.h"
#include "client/ui/widget.h"
#include "common/game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <list>
#include <memory>
/* -------------------------------------------------------------------------- */
class GameClient : public Game {
public:
  GameClient(); // Acts as a setup function as well.
  ~GameClient() = default;
  void run() override;

private:
  /* ------------------------------- Variables ------------------------------ */
  ClientNetwork network_;
  sf::RenderWindow window_;

  std::list<std::unique_ptr<Widget>> widgets_;
  /* -------------------------------- Functions ----------------------------- */
  bool initialize_network();
  void update(float deltaTime) override;
  void abort() override;

  void poll_events();
  void draw();
};
/* -------------------------------------------------------------------------- */