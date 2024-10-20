/*
This class is responsible for abstracting network functionality for the server.
The class has very little in common with the client implementation and therefor
they do not inherit a common class. The usage of the class is to receive and
send messages by calls from the server class.
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "common/defines.h"
#include "common/message_type.h"
#include "common/player_id.h"
#include <SFML/Network.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/SocketSelector.hpp>
#include <memory>
#include <unordered_map>
/* -------------------------------------------------------------------------- */
class ServerNetwork {
public:
  /* ------------------------------- Functions ------------------------------ */
  void set_port(int port);
  void set_player_count(int playerCount);
  void listen_for_connections();
  void broadcast(MessageType messageType /* TODO Polymorphic message here? */);

private:
  /* ------------------------------- Variables ------------------------------ */
  int port_{DEFAULT_PORT};
  uint8_t playerCount_{MIN_NUMBER_OF_PLAYERS};
  sf::TcpListener socketListener_{};
  std::unordered_map<PlayerId, std::unique_ptr<sf::TcpSocket>> sockets_;
  std::unordered_map<PlayerId, sf::IpAddress> playerAddresses_;

  /* ------------------------------- Functions ------------------------------ */
  void broadcast_game_started();
};
/* -------------------------------------------------------------------------- */