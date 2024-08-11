#include "game.h"
#include "defines.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
#include <fstream>

/* -------------------------------------------------------------------------- */
Game::Game() : window_(sf::VideoMode(800, 600), "Ceco Minesweeper") {
  // TODO(emin) should I maybe find another way of error handling?
  if (initialize_logging() == false) {
    exit();
  }
}
/* -------------------------------------------------------------------------- */
void Game::run() {
  while (window_.isOpen()) {
    sf::Event event;
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window_.close();
    }

    window_.clear();
    // Drawing code here
    window_.display();
  }
}
/* -------------------------------------------------------------------------- */
bool Game::initialize_logging() {
  // Try/catch blocks and smart pointers are used here because of the lib API
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(LOG_LEVEL);
    console_sink->set_pattern(
        "[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // TODO(emin) Maybe I should make a log directory with different log files?
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "Minesweeper.log", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::sinks_init_list sink_list = {file_sink, console_sink};

    spdlog::logger logger("multi_sink", sink_list.begin(), sink_list.end());
    logger.set_level(LOG_LEVEL);

    // or you can even set multi_sink logger as default logger
    spdlog::set_default_logger(std::make_shared<spdlog::logger>(
        "multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));

    spdlog::info("Logging library successfully initialized");

  } catch (const spdlog::spdlog_ex &ex) {
    std::ofstream outputFile("Minesweeper.log");
    if (outputFile.is_open()) {
      outputFile << "Log initialization failed: " << ex.what() << std::endl;
    }
    return false;
  }

  return true;
}
/* -------------------------------------------------------------------------- */
void Game::exit() { spdlog::info("Exiting the game."); }
/* -------------------------------------------------------------------------- */