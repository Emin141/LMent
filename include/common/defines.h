#pragma once
/* -------------------------------------------------------------------------- */
// Define logging levels using spdlog enums
#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#define LOG_LEVEL spdlog::level::debug
#else
#define LOG_LEVEL spdlog::level::info
#endif
/* -------------------------------------------------------------------------- */
#define MIN_NUMBER_OF_PLAYERS 2
#define MAX_NUMBER_OF_PLAYERS 4
/* -------------------------------------------------------------------------- */