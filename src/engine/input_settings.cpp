#include "input_settings.h"

InputSettings& InputSettings::instance() {
    static InputSettings s;
    return s;
}
