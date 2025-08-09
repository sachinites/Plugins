#include "calc_plugin.h"
#include <stdio.h>

static double div_fn(double param, double input) {
    if (param == 0) {
        fprintf(stderr, "Error: Division by zero!\n");
        return input;
    }
    return input / param;
}

static const calc_node_t nodes_div[] = {
    { .name = "div", .process = div_fn }
};

REGISTER_PLUGIN(plugin) = {
    .plugin_name = "div_plugin",
    .nodes = nodes_div,
    .node_count = 1
};
