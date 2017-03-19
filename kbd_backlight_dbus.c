/*
 * Copyright (C) 2017 https://github.com/ruben2020
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met: 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <dbus/dbus.h>
#include "kbd_backlight_common.h"

DBusError err;
DBusConnection* conn = NULL;

void errprint(char* str)
{
	fprintf(stderr, "str\n");
	exit(1);
}

void kbd_light_set(int val)
{
	DBusMessage* msg = NULL;
	DBusMessageIter args;
	dbus_uint32_t param;

#if (DEBUG_ON)
	if (val == 0)      printf("Turn off keyboard backlight\n");
	else if (val == 1) printf("Turn on keyboard backlight\n");
	else printf("Unknown keyboard backlight parameter\n");
#endif
	param = (dbus_uint32_t) val;
	msg = dbus_message_new_method_call("org.freedesktop.UPower",
		"/org/freedesktop/UPower/KbdBacklight",
		"org.freedesktop.UPower.KbdBacklight",
		"SetBrightness");
	if (msg == NULL) errprint("DBUS msg NULL!");

	dbus_message_iter_init_append(msg, &args);
	if (!dbus_message_iter_append_basic(&args, 
		DBUS_TYPE_INT32, &param)) errprint("DBUS append err!");

	if (!dbus_connection_send(conn, msg, NULL)) errprint("DBUS send err!");
	dbus_message_unref(msg);
}

void dbus_setup(void)
{
	dbus_error_init(&err);
	conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
	if (dbus_error_is_set(&err))
	{ 
		fprintf(stderr, "DBUS Connection Error (%s)\n", err.message); 
		dbus_error_free(&err); 
	}
	if (conn == NULL) exit(1);	
}

