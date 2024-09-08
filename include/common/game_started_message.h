#pragma once
#include "common/extensions.h"
#include <SFML/Network/Packet.hpp>
#include <vector>
/* -------------------------------------------------------------------------- */
struct GameStartedMessage {
  struct InitialPlayerInfo {
    uint8_t id;
    uint8_t position; // Based on 1D 11x11. Sadly I can't pack this into 1 byte.
  };

  uint8_t thisPlayerId;
  // TODO consider doing the whole project without a single vector?
  std::vector<InitialPlayerInfo> initialPlayerInfoList;
};
/* -------------------------------------------------------------------------- */
inline sf::Packet &
operator>>(sf::Packet &packet,
           GameStartedMessage::InitialPlayerInfo &initialPlayerInfo) {
  return packet >> initialPlayerInfo.id >> initialPlayerInfo.position;
}
/* -------------------------------------------------------------------------- */
inline sf::Packet &
operator<<(sf::Packet &packet,
           const GameStartedMessage::InitialPlayerInfo &initialPlayerInfo) {
  return packet << initialPlayerInfo.id << initialPlayerInfo.position;
}
/* -------------------------------------------------------------------------- */
inline sf::Packet &operator>>(sf::Packet &packet, GameStartedMessage &message) {
  return packet >> message.thisPlayerId >> message.initialPlayerInfoList;
}
/* -------------------------------------------------------------------------- */
inline sf::Packet &operator<<(sf::Packet &packet,
                              const GameStartedMessage &message) {
  return packet << message.thisPlayerId << message.initialPlayerInfoList;
}
/* -------------------------------------------------------------------------- */