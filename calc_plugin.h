#ifndef CALC_PLUGIN_H
#define CALC_PLUGIN_H

#include <stddef.h>

typedef double (*calc_process_fn)(double param, double input);

typedef struct {
    const char *name;
    calc_process_fn process;
} calc_node_t;

typedef struct {
    calc_node_t nodes[128];  // registered operations
    size_t node_count;       // number of registered nodes
} calc_main_t;

typedef struct {
    const char *plugin_name;
    const calc_node_t *nodes;
    size_t node_count;
} calc_plugin_t;

#define REGISTER_PLUGIN(name) \
    __attribute__((visibility("default"))) calc_plugin_t name

#endif
