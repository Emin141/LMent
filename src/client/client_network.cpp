#include "client/client_network.h"
#include "common/defines.h"
#include "common/game_started_message.h"
#include "common/message_type.h"
#include "spdlog/spdlog.h"
#include <SFML/Network/Socket.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
/* -------------------------------------------------------------------------- */
void ClientNetwork::set_ip_address(const sf::IpAddress &serverAddress) {
  serverAddress_ = serverAddress;
}
/* -------------------------------------------------------------------------- */
void ClientNetwork::set_port(int serverPort) { serverPort_ = serverPort; }
/* -------------------------------------------------------------------------- */
void ClientNetwork::connect() {
  if (socket_.connect(serverAddress_, serverPort_, sf::Time(sf::seconds(10))) !=
      sf::Socket::Done) {
    spdlog::error("Failed to connect to server at {}:{}.",
                  serverAddress_.toString(), serverPort_);
    abort();
  }

  spdlog::info("Client has connected to server at {}:{}.",
               serverAddress_.toString(), serverPort_);

  socket_.setBlocking(false);
  connected_ = true;
}
/* -------------------------------------------------------------------------- */
void ClientNetwork::check_connection() {
  sf::Packet dummyPacket;
  if (socket_.receive(dummyPacket) == sf::Socket::Disconnected) {
    connected_ = false;
    spdlog::warn("Lost connection to server.");

    reconnect();
  }
}
/* -------------------------------------------------------------------------- */
void ClientNetwork::reconnect() {
  spdlog::info("Attempting to reconnect to server.");

  int attempt = 0;
  while (!connected_ && (attempt < MAX_RECONNECT_ATTEMPTS)) {
    if (socket_.connect(serverAddress_, serverPort_,
                        sf::Time(sf::seconds(5))) == sf::Socket::Done) {
      spdlog::info("Reconnected to server at {}:{}", serverAddress_.toString(),
                   serverPort_);
      connected_ = true;
    }
  }

  if (!connected_) {
    spdlog::info("Failed to reconnect to server at {}:{}",
                 serverAddress_.toString(), serverPort_);
    // TODO return to main menu.
  }
}
/* -------------------------------------------------------------------------- */