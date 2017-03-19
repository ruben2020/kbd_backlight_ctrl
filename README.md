Keyboard Backlight Control Service
==================================

Keyboard Backlight Control is a systemd service that turns the backlight on when key is pressed and turns it off on timeout.

It refreshes the countdown timer if keys are still pressed.

The default countdown period is 20 seconds.

This only works on Linux and has been tested on Arch Linux.

For other Linux distributions, you may need to change the following:
* `/dev/input/event0` as the keyboard input device in `kbd_backlight_common.h` 
* The executable's binary install path of `/usr/local/bin` in Makefile and `kbd_backlight_ctrl.service`
* The systemd .service file install path of `/usr/lib/systemd/system` in Makefile
* The `DBUS_SESSION_BUS_ADDRESS` environment variable in `kbd_backlight_ctrl.service`
* The DBUS dependencies in the Makefile

You can configure the timeout period in `kbd_backlight_ctrl.service`, at the line which defines `KBD_BACKLIGHT_CTRL_TIMEOUT`.

The dependencies for building are:
* dbus
* pthread

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

