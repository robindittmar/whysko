#include "logging.h"
#include <sstream>

using json = nlohmann::json;

Logging& Logging::instance() {
    static Logging l;
    return l;
}

void Logging::log(const std::string& msg) {
    ofs.open(filename, std::ios::out | std::ios::app);
    if (!ofs) {
        return;
    }

    auto t = std::time(nullptr);
    auto tm = std::gmtime(&t);
    std::stringstream ss;
    ss << std::put_time(tm, "%Y-%m-%dT%H:%M:%SZ");

    json data;
    data["msg"] = msg;
    data["utc"] = ss.str();
    data["lvl"] = loglevel;

    ofs << data.dump() << std::endl;
    ofs.close();
}
