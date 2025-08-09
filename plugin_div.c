#include "calc_plugin.h"
#include <stdio.h>

static double divide(double a, double b) {
    if (b == 0) {
        fprintf(stderr, "Error: Division by zero!\n");
        return 0;
    }
    return a / b;
}

REGISTER_PLUGIN(plugin) = {
    .name = "div",
    .execute = divide
};
