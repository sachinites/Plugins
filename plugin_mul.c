#include "calc_plugin.h"

static double mul_fn(double param, double input) {
    return input * param;
}

static const calc_node_t nodes_mul[] = {
    { .name = "mul", .process = mul_fn }
};

REGISTER_PLUGIN(plugin) = {
    .plugin_name = "mul_plugin",
    .nodes = nodes_mul,
    .node_count = 1
};
