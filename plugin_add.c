#include "calc_plugin.h"

static double add(double a, double b) {
    return a + b;
}

REGISTER_PLUGIN(plugin) = {
    .name = "add",
    .execute = add
};
