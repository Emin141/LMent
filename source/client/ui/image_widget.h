/*
Used to display backgrounds mostly.
*/
/* ------------------------------------------------------------------------------------------------------------------ */
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "client/ui/widget.h"
/* ------------------------------------------------------------------------------------------------------------------ */
class ImageWidget : public Widget {
 public:
  ImageWidget(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Texture* texture,
              const sf::IntRect& textureRect);

  void set_position(const sf::Vector2f& value) override;
  const sf::Vector2f& get_position() const override;
  void set_size(const sf::Vector2f& value) override;
  const sf::Vector2f& get_size() const override;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
  sf::RectangleShape rectangleShape_;
};
/* ------------------------------------------------------------------------------------------------------------------ */