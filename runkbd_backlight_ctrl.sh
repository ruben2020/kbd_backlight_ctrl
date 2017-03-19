#!/bin/bash
# This script is only for testing purposes
export DBUS_SESSION_BUS_ADDRESS=unix:path=/var/run/dbus/system_bus_socket
export KBD_BACKLIGHT_CTRL_TIMEOUT=20
kbd_backlight_ctrl

