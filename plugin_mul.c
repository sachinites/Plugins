#include "calc_plugin.h"

static double mul(double a, double b) {
    return a * b;
}

REGISTER_PLUGIN(plugin) = {
    .name = "mul",
    .execute = mul
};
