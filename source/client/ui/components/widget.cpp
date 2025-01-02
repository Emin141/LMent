#include "client/ui/components/widget.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

#include "common/misc_util.h"
#include "spdlog/spdlog.h"
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::enable() {
  enabled_ = true;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::disable() {
  enabled_ = false;
}
/* ------------------------------------------------------------------------------------------------------------------ */
bool Widget::enabled() const {
  return enabled_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
bool Widget::disabled() const {
  return !enabled_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_parent_widget(Widget* parentWidget) {
  parentWidget_ = parentWidget;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_position(const sf::Vector2f& value) {}
/* ------------------------------------------------------------------------------------------------------------------ */
const sf::Vector2f& Widget::get_position() const {
  static const sf::Vector2f dummy{};
  return dummy;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_size(const sf::Vector2f& value) {}
/* ------------------------------------------------------------------------------------------------------------------ */
const sf::Vector2f& Widget::get_size() const {
  static const sf::Vector2f dummy{};
  return dummy;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_click_disposition(ClickDisposition value) {
  clickDisposition_ = value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
Widget::ClickDisposition Widget::get_click_disposition() const {
  return clickDisposition_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::handle_mouse_button_pressed(const sf::Event::MouseButtonEvent& event) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::handle_mouse_button_released(const sf::Event::MouseButtonEvent& event) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::handle_hover_start() {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::handle_hover_end() {}
/* ------------------------------------------------------------------------------------------------------------------ */
bool Widget::contains_point(const sf::Vector2i& mousePosition) const {
  return false;
}
/* ------------------------------------------------------------------------------------------------------------------ */
Widget* Widget::get_hovered_widget(const sf::Event::MouseMoveEvent& event) {
  return nullptr;
}
/* ------------------------------------------------------------------------------------------------------------------ */
Widget* Widget::add_child_widget(std::unique_ptr<Widget> childWidget) {
  childWidgets_.push_back(std::move(childWidget));
  childWidgets_.back()->set_parent_widget(this);
  return childWidgets_.back().get();
}
/* ------------------------------------------------------------------------------------------------------------------ */
const std::vector<std::unique_ptr<Widget>>& Widget::get_child_widgets() const {
  return childWidgets_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
const Widget* Widget::get_widget_at_index(uint8_t index) const {
  if (index < childWidgets_.size()) {
    return childWidgets_[index].get();
  } else {
    spdlog::warn("Could not find child widget at index {}", index);
    return nullptr;
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
Widget* Widget::get_widget_at_index(uint8_t index) {
  if (index < childWidgets_.size()) {
    return childWidgets_[index].get();
  } else {
    spdlog::warn("Could not find child widget at index {}", index);
    return nullptr;
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::remove_widget(Widget* childWidget) {
  util::erase(childWidgets_, [&](const auto& existingChildWidget) { return existingChildWidget.get() == childWidget; });
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::remove_widget_at(uint8_t index) {
  util::erase_at(childWidgets_, index);
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::update(float deltaTime) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& childWidget : childWidgets_) {
    target.draw(*childWidget, states);
  }
}
/* ------------------------------------------------------------------------------------------------------------------ */
