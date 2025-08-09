#include "calc_plugin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

#define MAX_NODES 128

static calc_main_t cm = { .node_count = 0 };

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <plugin.so>... start <initial_value> <op> <arg> ...\n", argv[0]);
        return 1;
    }

    int plugin_start_index = -1;

    // Load plugins until "start"
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "start") == 0) {
            plugin_start_index = i;
            break;
        }

        void *handle = dlopen(argv[i], RTLD_NOW);
        if (!handle) {
            fprintf(stderr, "dlopen(%s) failed: %s\n", argv[i], dlerror());
            return 1;
        }

        calc_plugin_t *plugin = dlsym(handle, "plugin");
        if (!plugin) {
            fprintf(stderr, "dlsym(plugin) failed in %s: %s\n", argv[i], dlerror());
            return 1;
        }

        for (size_t n = 0; n < plugin->node_count && cm.node_count < MAX_NODES; n++) {
            cm.nodes[cm.node_count++] = plugin->nodes[n];
        }
    }

    if (plugin_start_index == -1 || plugin_start_index + 2 > argc) {
        fprintf(stderr, "Missing 'start' token and value\n");
        return 1;
    }

    double value = atof(argv[plugin_start_index + 1]);

    // Process operations
    for (int i = plugin_start_index + 2; i < argc; i += 2) {
        if (i + 1 >= argc) {
            fprintf(stderr, "Missing argument for operation '%s'\n", argv[i]);
            return 1;
        }

        const char *op = argv[i];
        double arg = atof(argv[i + 1]);
        int found = 0;

        for (size_t n = 0; n < cm.node_count; n++) {
            if (strcmp(cm.nodes[n].name, op) == 0) {
                value = cm.nodes[n].process(arg, value);
                found = 1;
                break;
            }
        }

        if (!found) {
            fprintf(stderr, "Unknown operation '%s'\n", op);
            return 1;
        }
    }

    printf("Result: %f\n", value);
    return 0;
}