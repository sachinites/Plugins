# Plugins
Demonstrate how to design and implement Plugin play architecture

How this maps to VPP’s design:
==============================

calc_core.c → VPP main engine (vlib_main_t).
Each plugin_*.c → VPP plugin (.so loaded at runtime).
REGISTER_PLUGIN → VLIB_PLUGIN_REGISTER.
execute() → Packet-processing node function in VPP.
dlopen/dlsym → VPP’s internal plugin loader.

======== Calling plugins in a chain like Fashion =================

Mapping to VPP concepts
VPP term	Our calculator example
vlib_main_t	calc_main_t (core runtime)
Node	Calculator operation (add, mul, etc.)
Frame	Input data (operands)
Plugin .so	Shared object implementing one or more operations
Node registration	Macro REGISTER_NODE


calc_plugin.h — shared API (defines calc_main_t, calc_node_t, calc_plugin_t, and REGISTER_PLUGIN)

calc_core.c — the core engine that:

loads plugins via dlopen/dlsym,

copies plugin node descriptors into an internal mutable table (so params can be overridden),

accepts the CLI chain start <value> <op> <arg> ... and executes nodes in sequence,

sets cm.current_node before calling a node (so plugin code can access current_node->param).

plugin_add.c, plugin_sub.c, plugin_mul.c, plugin_div.c — example plugins (each exports plugin).

Makefile — builds core and .so plugins.

Example Run : 

./calc_core ./plugin_add.so ./plugin_mul.so ./plugin_div.so start 0 add 10 mul 5 div 2


