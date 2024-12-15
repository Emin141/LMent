#include "client/ui/widget.h"
#include "common/misc_util.h"
#include "spdlog/spdlog.h"
#include <SFML/Graphics/RenderTarget.hpp>
/* ------------------------------------------------------------------------------------------------------------------ */
Widget::Widget(Widget* parentWidget) : parentWidget_(parentWidget) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_focused(bool value) {
    focused_ = value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
bool Widget::is_focused() const {
    return focused_;
}
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
void Widget::set_position(const sf::Vector2f& value) {
    position_ = value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
sf::Vector2f Widget::get_position() const {
    return position_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_size(const sf::Vector2f& value) {
    size_ = value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
sf::Vector2f Widget::get_size() const {
    return size_;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_alignment(HorizontalAlignment value) {
    horizontalAlignment_ = value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_alignment(VerticalAlignment value) {
    verticalAlignment_ = value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_alignment(HorizontalAlignment haValue, VerticalAlignment vaValue) {
    horizontalAlignment_ = haValue;
    verticalAlignment_ = vaValue;
}
/* ------------------------------------------------------------------------------------------------------------------ */
std::pair<Widget::HorizontalAlignment, Widget::VerticalAlignment> Widget::get_alignment() const {
    return {horizontalAlignment_, verticalAlignment_};
}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::set_padding(Widget::Padding value) {
    padding_ = value;
}
/* ------------------------------------------------------------------------------------------------------------------ */
Widget::Padding Widget::get_padding() const {
    return padding_;
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
void Widget::handle_mouse_button_pressed(const sf::Event::MouseButtonEvent& mouseClickEvent,
                                         const sf::Vector2i& mousePosition) {}
/* ------------------------------------------------------------------------------------------------------------------ */
void Widget::handle_mouse_button_released(const sf::Event::MouseButtonEvent& mouseClickEvent,
                                          const sf::Vector2i& mousePosition) {}
/* ------------------------------------------------------------------------------------------------------------------ */
bool Widget::is_mouse_inside_boundaries(const sf::Vector2i& mousePosition) const {
    const auto& [anchorX, anchorY] = get_position();
    const auto& [sizeX, sizeY] = get_size();

    return (mousePosition.x > anchorX && mousePosition.x < (anchorX + sizeX)) &&
           (mousePosition.y > anchorY && mousePosition.y < (anchorY + sizeY));
}
/* ------------------------------------------------------------------------------------------------------------------ */
Widget* Widget::add_child_widget(std::unique_ptr<Widget> childWidget) {
    childWidgets_.push_back(std::move(childWidget));
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
    util::erase(childWidgets_,
                [&](const auto& existingChildWidget) { return existingChildWidget.get() == childWidget; });
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
