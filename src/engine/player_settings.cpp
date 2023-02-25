#include "player_settings.h"

PlayerSettings& PlayerSettings::instance() {
    static PlayerSettings s;
    return s;
}
