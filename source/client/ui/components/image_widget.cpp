#include "client/ui/components/image_widget.h"
#include <SFML/Graphics/RenderTarget.hpp>
/* ------------------------------------------------------------------------------------------------------------------ */
ImageWidget::ImageWidget(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture* texture,
                         const sf::IntRect& textureRect) {
  set_position(position);
  set_size(size);
  rectangleShape_.setTexture(texture);
  rectangleShape_.setTextureRect(textureRect);

  clickDisposition_ = ClickDisposition::Unclickable;
}
/* ------------------------------------------------------------------------------------------------------------------ */
void ImageWidget::set_position(const sf::Vector2f& value) {
  rectangleShape_.setPosition(value);
}
/* ------------------------------------------------------------------------------------------------------------------ */
const sf::Vector2f& ImageWidget::get_position() const {
  return rectangleShape_.getPosition();
}
/* ------------------------------------------------------------------------------------------------------------------ */
void ImageWidget::set_size(const sf::Vector2f& value) {
  rectangleShape_.setSize(value);
}
/* ------------------------------------------------------------------------------------------------------------------ */
const sf::Vector2f& ImageWidget::get_size() const {
  return rectangleShape_.getSize();
}
/* ------------------------------------------------------------------------------------------------------------------ */
void ImageWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  Widget::draw(target, states);

  target.draw(rectangleShape_, states);
}
/* ------------------------------------------------------------------------------------------------------------------ */