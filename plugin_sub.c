#include "calc_plugin.h"

static double sub(double a, double b) {
    return a - b;
}

REGISTER_PLUGIN(plugin) = {
    .name = "sub",
    .execute = sub
};
