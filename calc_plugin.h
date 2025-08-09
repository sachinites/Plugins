#ifndef CALC_PLUGIN_H
#define CALC_PLUGIN_H

typedef double (*calc_func_t)(double a, double b);

// Structure every plugin must export
typedef struct {
    const char *name;      // Plugin name (e.g., "add")
    calc_func_t execute;   // Function to perform the calculation
} calc_plugin_t;

// Registration macro (like VLIB_PLUGIN_REGISTER in VPP)
#define REGISTER_PLUGIN(plugin_var) \
    __attribute__((visibility("default"))) calc_plugin_t plugin_var

#endif
