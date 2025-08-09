#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "calc_plugin.h"

#define MAX_PLUGINS 10

int main(int argc, char **argv) {
    if (argc < 5) {
        printf("Usage: %s <plugin1.so> <plugin2.so> ... <op_name> <a> <b>\n", argv[0]);
        return 1;
    }

    // Load plugins
    calc_plugin_t *plugins[MAX_PLUGINS];
    int plugin_count = 0;
    int i;

    for (i = 1; i < argc - 3; i++) {
        void *handle = dlopen(argv[i], RTLD_LAZY);
        if (!handle) {
            fprintf(stderr, "Failed to load %s: %s\n", argv[i], dlerror());
            return 1;
        }

        calc_plugin_t *p = dlsym(handle, "plugin");
        if (!p) {
            fprintf(stderr, "Invalid plugin in %s\n", argv[i]);
            return 1;
        }

        plugins[plugin_count++] = p;
    }

    // Find requested operation
    char *op_name = argv[argc - 3];
    double a = atof(argv[argc - 2]);
    double b = atof(argv[argc - 1]);

    for (i = 0; i < plugin_count; i++) {
        if (strcmp(plugins[i]->name, op_name) == 0) {
            double result = plugins[i]->execute(a, b);
            printf("Result: %.2f\n", result);
            return 0;
        }
    }

    printf("Operation '%s' not found in loaded plugins.\n", op_name);
    return 1;
}
