#include "client/ui/user_interface.h"
#include "client/ui/widget.h"
/* ------------------------------------------------------------------------------------------------------------------ */
UserInterface::UserInterface(const sf::Vector2u& size) {
  enabled_ = true;
  horizontalAlignment_ = HorizontalAlignment::Stretch;
  verticalAlignment_ = VerticalAlignment::Stretch;
  padding_ = Padding{};
  clickDisposition_ = ClickDisposition::ChildrenClickable;
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
  for (const auto& childWidget : childWidgets_) {
    childWidget->update(deltaTime);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void UserInterface::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& childWidget : childWidgets_) {
    childWidget->draw(target, states);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */