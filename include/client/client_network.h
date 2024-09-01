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
#include <SFML/Network/IpAddress.hpp>
/* -------------------------------------------------------------------------- */
class ClientNetwork {
public:
  /* ------------------------------- Functions ------------------------------ */
  void set_ip_address(const sf::IpAddress &serverAddress);
  void set_port(int serverPort);
  void connect();

private:
  /* ------------------------------- Variables ------------------------------ */
  sf::IpAddress serverAddress_{};
  int serverPort_{DEFAULT_PORT};
  sf::TcpSocket socket_{};

  /* ------------------------------- Functions ------------------------------ */
};
/* -------------------------------------------------------------------------- */