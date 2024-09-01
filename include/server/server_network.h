/*
This class is responsible for abstracting network functionality for the server.
The class has very little in common with the client implementation and therefor
they do not inherit a common class. The usage of the class is to receive and
send messages by calls from the server class.
*/
/* -------------------------------------------------------------------------- */
#pragma once
#include "common/defines.h"
#include <SFML/Network.hpp>
/* -------------------------------------------------------------------------- */
class ServerNetwork {
public:
  /* ------------------------------- Functions ------------------------------ */
  void set_port(int port);
  void set_max_number_of_players(int playerCount);
  void listen_for_connections();

private:
  /* ------------------------------- Variables ------------------------------ */
  int port_{DEFAULT_PORT};
  uint8_t playerCount_{MIN_NUMBER_OF_PLAYERS};
  sf::TcpListener socketListener_{};
  sf::TcpSocket sockets_[MAX_NUMBER_OF_PLAYERS];

  /* ------------------------------- Functions ------------------------------ */
  void send_game_started(uint8_t playerId);
};
/* -------------------------------------------------------------------------- */