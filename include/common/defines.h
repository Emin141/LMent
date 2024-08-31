#pragma once
/* -------------------------------------------------------------------------- */
// This will notify during compile time that the debug build is running
#ifdef DEBUG_BUILD
#pragma message("Building DEBUG")
#endif
/* -------------------------------------------------------------------------- */
// Define logging levels using spdlog enums
#if SPDLOG_ACTIVE_LEVEL <= SPDLOG_LEVEL_DEBUG
#define LOG_LEVEL spdlog::level::debug
#else
#define LOG_LEVEL spdlog::level::info
#endif
/* -------------------------------------------------------------------------- */