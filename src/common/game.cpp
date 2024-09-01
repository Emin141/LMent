#include "common/game.h"
#include "common/defines.h"
#include "common/misc_util.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"
/* -------------------------------------------------------------------------- */
Game::Game() {
  // TODO should I maybe find another way of error handling?
  if (!initialize_logging()) {
    exit();
  }

  isRunning_ = true;
}
/* -------------------------------------------------------------------------- */
bool Game::initialize_logging() {
  // Try/catch blocks and smart pointers are used here because of the lib API
  try {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(LOG_LEVEL);
    console_sink->set_pattern(
        "[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        "logs/LMent_" + util::current_datetime_as_string() + ".log", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::sinks_init_list sink_list = {file_sink, console_sink};

    spdlog::logger logger("multi_sink", sink_list.begin(), sink_list.end());
    logger.set_level(LOG_LEVEL);

    // or you can even set multi_sink logger as default logger
    spdlog::set_default_logger(std::make_shared<spdlog::logger>(
        "multi_sink", spdlog::sinks_init_list({console_sink, file_sink})));

    spdlog::info("Logging library successfully initialized");

  } catch (const spdlog::spdlog_ex &ex) {
    std::fprintf(stderr, "Log initialization failed: %s\n", ex.what());
    std::fflush(stderr);
    return false;
  }

  return true;
}
/* -------------------------------------------------------------------------- */
void Game::exit() {
  spdlog::info("Exiting the game.");
  std::exit(EXIT_FAILURE); // TODO maybe specify my own codes here?
}
/* -------------------------------------------------------------------------- */
