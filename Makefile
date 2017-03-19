
CFLAGS=-Wall -I. $(shell pkg-config --cflags dbus-1)

kbd_backlight_ctrl: kbd_backlight_ctrl.o kbd_backlight_dbus.o
	$(CC) -o kbd_backlight_ctrl kbd_backlight_ctrl.o kbd_backlight_dbus.o -lpthread $(shell pkg-config --libs dbus-1) $(CFLAGS)

kbd_backlight_ctrl.o: kbd_backlight_ctrl.c kbd_backlight_common.h
	$(CC) -c kbd_backlight_ctrl.c $(CFLAGS)

kbd_backlight_dbus.o: kbd_backlight_dbus.c kbd_backlight_common.h
	$(CC) -c kbd_backlight_dbus.c $(CFLAGS)

.PHONY: clean install uninstall systemd_install systemd_uninstall

install: kbd_backlight_ctrl
	cp kbd_backlight_ctrl /usr/local/bin
	chmod 754 /usr/local/bin/kbd_backlight_ctrl

uninstall:
	rm -f /usr/local/bin/kbd_backlight_ctrl

systemd_install:
	cp kbd_backlight_ctrl.service /usr/lib/systemd/system/kbd_backlight_ctrl.service
	chmod 664 /usr/lib/systemd/system/kbd_backlight_ctrl.service
	systemctl enable kbd_backlight_ctrl.service
	systemctl daemon-reload
	systemctl start kbd_backlight_ctrl.service

systemd_uninstall:
	systemctl stop kbd_backlight_ctrl.service
	systemctl disable kbd_backlight_ctrl.service
	rm -f /usr/lib/systemd/system/kbd_backlight_ctrl.service
	systemctl daemon-reload

clean:
	rm -f *.o
	rm -f kbd_backlight_ctrl

