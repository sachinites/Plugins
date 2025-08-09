# Plugins
Demonstrate how to design and implement Plugin play architecture

How this maps to VPP’s design:
==============================

calc_core.c → VPP main engine (vlib_main_t).
Each plugin_*.c → VPP plugin (.so loaded at runtime).
REGISTER_PLUGIN → VLIB_PLUGIN_REGISTER.
execute() → Packet-processing node function in VPP.
dlopen/dlsym → VPP’s internal plugin loader.

