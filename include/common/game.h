/*
The main class which acts as the top object of the game application. This class
is responsible for holding unique references to objects such as the window and
asset loader, to route different events from input, logging management, and
similar.
The class is abstract so that it can be implemented differently for client and
server instances.
*/
/* -------------------------------------------------------------------------- */
#pragma once
/* -------------------------------------------------------------------------- */
class Game {
public:
  // Nothing else should be in the public interface.
  Game();                 // Acts as a setup function as well.
  virtual void run() = 0; // TODO maybe this shouldn't be virtual?

protected:
  /* ------------------------------- Variables ------------------------------ */
  bool isRunning_{false};

  /* -------------------------------- Functions ----------------------------- */
  virtual bool initialize_logging();
  virtual void update(float deltaTime) = 0;
  virtual void exit(); // Has some default logic.
};
/* -------------------------------------------------------------------------- */