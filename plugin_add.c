#include "calc_plugin.h"

static double add_fn(double param, double input) {
    return input + param;
}

static const calc_node_t nodes_add[] = {
    { .name = "add", .process = add_fn }
};

REGISTER_PLUGIN(plugin) = {
    .plugin_name = "add_plugin",
    .nodes = nodes_add,
    .node_count = 1
};
