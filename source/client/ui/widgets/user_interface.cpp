#include "client/ui/widgets/user_interface.h"
#include "client/ui/components/widget.h"
/* ------------------------------------------------------------------------------------------------------------------ */
UserInterface::UserInterface(const sf::Vector2u& windowSize) : mainMenu_(windowSize) {
  clickDisposition_ = ClickDisposition::ChildrenClickable;

  childWidgets_.reserve(1);  // TODO Update this when new screens are added.

  activeScreen_ = &mainMenu_;
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
          childWidget->handle_mouse_button_pressed(inputEvent.mouseButton.button);
          break;
        }
      }
      break;
    }
    case sf::Event::MouseButtonReleased: {
      sf::Vector2i mousePosition{inputEvent.mouseButton.x, inputEvent.mouseButton.y};
      for (auto& childWidget : childWidgets_) {
        if (childWidget->contains_point(mousePosition)) {
          childWidget->handle_mouse_button_released(inputEvent.mouseButton.button);
          focusedWidget_ = childWidget.get();
          break;
        }
      }
      break;
    }
    case sf::Event::MouseMoved: {
      sf::Vector2i mousePosition{inputEvent.mouseMove.x, inputEvent.mouseMove.y};
      if (hoveredWidget_ != nullptr) {
        if (hoveredWidget_->contains_point(mousePosition) == false) {
          hoveredWidget_->handle_mouse_hover_end();
          hoveredWidget_ = nullptr;
        }
      }
      for (auto& childWidget : childWidgets_) {
        if (childWidget->contains_point(mousePosition) &&
            (childWidget->get_click_disposition() == Widget::ClickDisposition::Clickable) &&
            (childWidget.get() != hoveredWidget_)) {
          hoveredWidget_ = childWidget.get();
          hoveredWidget_->handle_mouse_hover_start();
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