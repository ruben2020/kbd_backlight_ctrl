Keyboard Backlight Control Service
==================================

[![Build Status](https://api.travis-ci.org/ruben2020/kbd_backlight_ctrl.svg)](https://travis-ci.org/ruben2020/kbd_backlight_ctrl) 
[![Coverity Scan Build Status](https://scan.coverity.com/projects/20139/badge.svg)](https://scan.coverity.com/projects/ruben2020-kbd_backlight_ctrl)

Keyboard Backlight Control is a systemd service that turns the backlight on when any key is pressed and turns it off on timeout.

It refreshes the countdown timer if keys are still pressed.

The default countdown period is 60 seconds.

This only works on Linux and has been tested on Arch Linux and Ubuntu Linux.

For other Linux distributions, you may need to change the following:
* The executable's binary install path of `/usr/local/bin` in Makefile and `kbd_backlight_ctrl.service`
* The systemd .service file install path of `/usr/lib/systemd/system` in Makefile
* The `DBUS_SESSION_BUS_ADDRESS` environment variable in `kbd_backlight_ctrl.service`
* The keyboard input events device in `kbd_backlight_ctrl.service`, at the line which defines `KBD_BACKLIGHT_CTRL_INDEVICE`.

You can configure the timeout period in `kbd_backlight_ctrl.service`, at the line which defines `KBD_BACKLIGHT_CTRL_TIMEOUT`.

The dependencies for building are:
* dbus

To build and install the binary, run these commands:
```bash
make
sudo make install
```
To uninstall the binary, run this command:
```bash
sudo make uninstall
```

To install to systemd, run this command:
```bash
sudo make systemd_install
```

To uninstall from systemd, run this command:
```bash
sudo make systemd_uninstall
```

To clean all build products, run this command:
```bash
make clean
```

