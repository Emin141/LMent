#pragma once
#include <SFML/Network.hpp>
#include <vector>
/* -------------------------------------------------------------------------- */
template <typename T>
sf::Packet &operator>>(sf::Packet &packet, std::vector<T> &vector) {
  sf::Uint32 size;
  packet >> size;
  vector.resize(size);

  for (T &element : vector) {
    packet >> element;
  }

  return packet;
}
/* -------------------------------------------------------------------------- */
template <typename T>
sf::Packet &operator<<(sf::Packet &packet, const std::vector<T> &vector) {
  packet << static_cast<sf::Uint32>(vector.size());

  for (const T &element : vector) {
    packet << element;
  }

  return packet;
}
/* -------------------------------------------------------------------------- */