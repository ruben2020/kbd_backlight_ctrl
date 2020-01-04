#!/bin/bash
##############################################
## This script is only for testing purposes ##
##############################################
export DBUS_SESSION_BUS_ADDRESS=unix:path=/var/run/dbus/system_bus_socket
export KBD_BACKLIGHT_CTRL_TIMEOUT=10
export KBD_BACKLIGHT_CTRL_INDEVICE=/dev/input/by-path/platform-i8042-serio-0-event-kbd
timeout -s SIGINT 20s kbd_backlight_ctrl
rc=$?; if [[ $rc == 124 ]]; then exit 0; fi


