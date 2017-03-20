#   
#   https://github.com/ruben2020/kbd_backlight_ctrl
#   
#   Copyright (c) 2017, ruben2020 https://github.com/ruben2020
#   All rights reserved.
#   
#   Redistribution and use in source and binary forms, with or without
#   modification, are permitted provided that the following conditions are met:
#   
#   * Redistributions of source code must retain the above copyright notice, this
#     list of conditions and the following disclaimer.
#   
#   * Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#   
#   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
#   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
#   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
#   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
#   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
#   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
#   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#   

CFLAGS=-Wall -O1 -I. $(shell pkg-config --cflags dbus-1)
OBJFILES=kbd_backlight_ctrl.o kbd_backlight_dbus.o
LISTOFLIBS=-lpthread $(shell pkg-config --libs dbus-1)

kbd_backlight_ctrl: kbd_backlight_ctrl.o kbd_backlight_dbus.o
	$(CC) -o kbd_backlight_ctrl $(OBJFILES) $(LISTOFLIBS) $(CFLAGS)

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

