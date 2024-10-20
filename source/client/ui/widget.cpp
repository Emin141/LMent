#include "client/ui/widget.h"
#include "common/misc_util.h"
#include "spdlog/spdlog.h"
#include <SFML/Graphics/RenderTarget.hpp>
/* -------------------------------------------------------------------------- */
Widget::Widget(Widget* parentWidget) : parentWidget_(parentWidget) {}
/* -------------------------------------------------------------------------- */
void Widget::set_focused(bool value) { focused_ = value; }
/* -------------------------------------------------------------------------- */
bool Widget::is_focused() const { return focused_; }
/* -------------------------------------------------------------------------- */
void Widget::set_click_disposition(ClickDisposition value) {
  clickDisposition_ = value;
}
/* -------------------------------------------------------------------------- */
Widget::ClickDisposition Widget::get_click_disposition() const {
  return clickDisposition_;
}
/* -------------------------------------------------------------------------- */
void Widget::handle_mouse_button_pressed(const sf::Event& mouseClickEvent,
                                         const sf::Vector2i& mousePosition) {}
/* -------------------------------------------------------------------------- */
void Widget::handle_mouse_button_released(const sf::Event& mouseClickEvent,
                                          const sf::Vector2i& mousePosition) {}
/* -------------------------------------------------------------------------- */
Widget* Widget::add_child_widget(std::unique_ptr<Widget> childWidget) {
  childWidgets_.push_back(std::move(childWidget));
  return childWidgets_.back().get();
}
/* -------------------------------------------------------------------------- */
const std::vector<std::unique_ptr<Widget>>& Widget::get_child_widgets() const {
  return childWidgets_;
}
/* -------------------------------------------------------------------------- */
const Widget* Widget::get_widget_at_index(uint8_t index) const {
  if (index < childWidgets_.size()) {
    return childWidgets_[index].get();
  } else {
    spdlog::warn("Could not find child widget at index {}", index);
    return nullptr;
  }
}
/* -------------------------------------------------------------------------- */
Widget* Widget::get_widget_at_index(uint8_t index) {
  if (index < childWidgets_.size()) {
    return childWidgets_[index].get();
  } else {
    spdlog::warn("Could not find child widget at index {}", index);
    return nullptr;
  }
}
/* -------------------------------------------------------------------------- */
void Widget::remove_widget(Widget* childWidget) {
  util::erase(childWidgets_, [&](const auto& existingChildWidget) {
    return existingChildWidget.get() == childWidget;
  });
}
/* -------------------------------------------------------------------------- */
void Widget::remove_widget_at(uint8_t index) {
  util::erase_at(childWidgets_, index);
}
/* -------------------------------------------------------------------------- */
void Widget::update(float deltaTime) {}
/* -------------------------------------------------------------------------- */
void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (const auto& childWidget : childWidgets_) {
    target.draw(*childWidget, states);
  }
}
/* -------------------------------------------------------------------------- */
void Widget::on_mouse_button_pressed() {}
/* -------------------------------------------------------------------------- */
void Widget::on_mouse_button_released() {}
/* -------------------------------------------------------------------------- */