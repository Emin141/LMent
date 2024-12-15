#pragma once
#include <SFML/Network/Packet.hpp>
#include <cstdint>
/* ------------------------------------------------------------------------------------------------------------------ */
enum class MessageType : uint8_t {
    Error = 0,
    GameStarted,
    PlayerDisconnected,
    Update,
    TurnStep,  // 5 turn steps per player turn
    UndoStep
};
/* ------------------------------------------------------------------------------------------------------------------ */
inline sf::Packet& operator>>(sf::Packet& packet, MessageType& messageType) {
    uint8_t value;
    packet >> value;
    messageType = static_cast<MessageType>(value);
    return packet;
}
/* --------------------------------------------------------------------------
 */
inline sf::Packet& operator<<(sf::Packet& packet, const MessageType& messageType) {
    return packet << static_cast<uint8_t>(messageType);
}
/* ------------------------------------------------------------------------------------------------------------------ */