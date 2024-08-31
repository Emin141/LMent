/*
TODO document
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "common/game.h"
#include <SFML/Graphics.hpp>
/* -------------------------------------------------------------------------- */
class GameClient : public Game {
public:
  GameClient(); // Acts as a setup function as well.
  void run() override;

private:
  /* ------------------------------- Variables ------------------------------ */
  sf::RenderWindow window_;

  /* -------------------------------- Functions ----------------------------- */
  void update() override;
  void exit() override;

  void poll_events();
  void draw();
};
/* -------------------------------------------------------------------------- */