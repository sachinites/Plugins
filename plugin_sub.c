#include "calc_plugin.h"

static double sub_fn(double param, double input) {
    return input - param;
}

static const calc_node_t nodes_sub[] = {
    { .name = "sub", .process = sub_fn }
};

REGISTER_PLUGIN(plugin) = {
    .plugin_name = "sub_plugin",
    .nodes = nodes_sub,
    .node_count = 1
};
