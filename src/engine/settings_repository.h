#ifndef WHYSKO_SETTINGS_REPOSITORY_H
#define WHYSKO_SETTINGS_REPOSITORY_H

#include <fstream>
#include <string>


class SettingsRepository {
public:
    SettingsRepository() = delete;
    ~SettingsRepository() = delete;

    static bool loadInputSettings();
    static bool writeInputSettings();

private:
    static bool parseInputJson(const std::string& buffer);
    static bool dumpInputJson(std::ofstream& ofs);
};


#endif//WHYSKO_SETTINGS_REPOSITORY_H
