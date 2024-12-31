/*
This class serves as an interface to everything UI related in the game. This way we can poll, update, and draw UI
related stuff from the game client without knowing directly what the internal structure looks like.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#pragma once
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include "client/ui/components/widget.h"
#include "client/ui/widgets/main_menu.h"
/* ------------------------------------------------------------------------------------------------------------------ */
class UserInterface : public Widget {
 public:
  UserInterface(const sf::Vector2u& windowSize);

  void handle_input(const sf::Event& inputEvent);
  void update(float deltaTime) override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  MainMenu mainMenu_;

  Widget* activeScreen_{nullptr};
  Widget* focusedWidget_{nullptr};  // This will be used later for text input
  Widget* hoveredWidget_{nullptr};
};
/* ------------------------------------------------------------------------------------------------------------------ */