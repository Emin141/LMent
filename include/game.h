/*
The main class which acts as the top object of the game application. This class
is responsible for holding unique references to objects such as the window and
asset loader, to route different events from input i logging management, and
similar.
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include <SFML/Graphics.hpp>
/* -------------------------------------------------------------------------- */
class Game {
public:
  // Nothing else should be in the public interface.
  Game(); // Acts as a setup function as well.
  void run();

private:
  /* ------------------------------- Variables ------------------------------ */
  bool isRunning_{false};
  sf::RenderWindow window_;

  /* -------------------------------- Functions ----------------------------- */
  bool initialize_logging();

  void poll_events();
  void update();
  void draw();
  void exit();
};
/* -------------------------------------------------------------------------- */