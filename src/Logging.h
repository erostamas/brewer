#pragma once

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/trivial.hpp>

#include <iosfwd>
#include <string>

#define LOG_TRACE   BOOST_LOG_SEV(global_logger::get(), severity_level::TRACE)
#define LOG_DEBUG   BOOST_LOG_SEV(global_logger::get(), severity_level::DEBUG)
#define LOG_INFO    BOOST_LOG_SEV(global_logger::get(), severity_level::INFO)
#define LOG_WARNING BOOST_LOG_SEV(global_logger::get(), severity_level::WARNING)
#define LOG_ERROR   BOOST_LOG_SEV(global_logger::get(), severity_level::ERROR)

enum severity_level {
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

extern size_t log_level_number;

std::ostream& operator<<(std::ostream& os, severity_level level);

typedef boost::log::sources::severity_logger_mt<severity_level> logger_t;

BOOST_LOG_GLOBAL_LOGGER(global_logger, logger_t)

void init_logging();

