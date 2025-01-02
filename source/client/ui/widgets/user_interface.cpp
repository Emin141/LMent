#include "client/ui/widgets/user_interface.h"

#include <memory>

#include "client/ui/components/widget.h"
/* ------------------------------------------------------------------------------------------------------------------ */
UserInterface::UserInterface(const sf::Vector2u& windowSize) {
  clickDisposition_ = ClickDisposition::ChildrenClickable;

  mainMenu_ = dynamic_cast<MainMenu*>(childWidgets_.emplace_back(std::make_unique<MainMenu>(windowSize)).get());
  mainMenu_->bindExitCallback([] { std::exit(0); });

  activeScreen_ = mainMenu_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void UserInterface::handle_input(const sf::Event& inputEvent) {
  // ? Do I have to handle resize events
  switch (inputEvent.type) {
    case sf::Event::TextEntered: {
      // TODO I'll handle text input later.
      break;
    }
    case sf::Event::KeyPressed: {
      break;
    }
    case sf::Event::KeyReleased: {
      break;
    }
    case sf::Event::MouseWheelMoved: {
      break;
    }
    case sf::Event::MouseWheelScrolled: {
      break;
    }
    case sf::Event::MouseButtonPressed: {
      sf::Vector2i mousePosition{inputEvent.mouseButton.x, inputEvent.mouseButton.y};
      for (auto& childWidget : childWidgets_) {
        if (childWidget->contains_point(mousePosition)) {
          childWidget->handle_mouse_button_pressed(inputEvent.mouseButton);
          break;
        }
      }
      break;
    }
    case sf::Event::MouseButtonReleased: {
      sf::Vector2i mousePosition{inputEvent.mouseButton.x, inputEvent.mouseButton.y};
      for (auto& childWidget : childWidgets_) {
        if (childWidget->contains_point(mousePosition)) {
          childWidget->handle_mouse_button_released(inputEvent.mouseButton);
          break;
        }
      }
      break;
    }
    case sf::Event::MouseMoved: {
      sf::Vector2i mousePosition{inputEvent.mouseMove.x, inputEvent.mouseMove.y};

      // Checks if the hovered widget from the last frame became unhovered.
      if (hoveredWidget_ != nullptr && !hoveredWidget_->contains_point(mousePosition)) {
        hoveredWidget_->handle_hover_end();
        hoveredWidget_ = nullptr;
      }

      for (auto& childWidget : childWidgets_) {
        if (Widget* hoverCandidate = childWidget->get_hovered_widget(inputEvent.mouseMove);
            hoverCandidate != nullptr && hoverCandidate != hoveredWidget_) {
          hoveredWidget_ = hoverCandidate;
          hoveredWidget_->handle_hover_start();
          break;
        }
      }
      break;
    }
    default:
      break;
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void UserInterface::update(float deltaTime) {
  if (activeScreen_ != nullptr) {
    activeScreen_->update(deltaTime);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void UserInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (activeScreen_ != nullptr) {
    activeScreen_->draw(target, states);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */