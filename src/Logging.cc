#include "Logging.h"

#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>

#include <iomanip>

// LCOV_EXCL_START

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)

namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace logging = boost::log;
namespace src = boost::log::sources;

using std::ios;
using std::left;
using std::ostream;
using std::setw;
using std::string;
using std::to_string;

size_t log_level_number = severity_level::INFO;

string get_log_dir() {
        return string("/brewer_files/log/");
}

const std::string log_levels[] = {
    "TRACE",
    "DEBUG",
    "INFO",
    "WARN",
    "ERROR",
};
const size_t log_levels_size = sizeof(log_levels) / sizeof(*log_levels);

BOOST_LOG_GLOBAL_LOGGER_INIT(global_logger, src::logger) {
    logger_t _logger;
    return _logger;
}

void init_logging() {
    logging::add_common_attributes();
    const string log_dir = get_log_dir();
    const string log_filename = log_dir + "brewer.log";
    logging::add_file_log(
            keywords::file_name = log_filename,
            keywords::open_mode = (ios::out | ios::app),
            keywords::auto_flush = true,
            keywords::format = (
                expr::stream
                << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                << " [" << expr::attr<severity_level>("Severity") << "]: "
                << expr::smessage));

    for (size_t log_level_index = 0; log_level_index < log_levels_size; ++log_level_index) {
        if (log_levels[log_level_index] == "INFO") {
            log_level_number = log_level_index;
            break;
        }
    }
    LOG_INFO << "Logging initialized with log level: " << log_levels[log_level_number];
    logging::core::get()->set_filter(severity >= log_level_number);
}


ostream& operator<<(ostream& os, severity_level level) {
    if (static_cast<size_t>(level) < log_levels_size) {
        os << left << setw(5) << log_levels[level];
    } else {
        os << static_cast<int>(level);
    }

    return os;
}

// LCOV_EXCL_STOP
