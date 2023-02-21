#ifndef WHYSKO_LOGGING_H
#define WHYSKO_LOGGING_H

#include <nlohmann/json.hpp>

#include <ctime>
#include <fstream>


class Logging {
public:
    static Logging& instance();

    void log(const std::string& msg);

private:
    Logging() = default;
    ~Logging() = default;

    std::ofstream ofs;

    std::string filename = "whysko.log";
    std::string loglevel = "INFO";
};


#endif//WHYSKO_LOGGING_H
