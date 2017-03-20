/* 
 * https://github.com/ruben2020/kbd_backlight_ctrl
 * 
 * Copyright (c) 2017, ruben2020 https://github.com/ruben2020
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * 
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef KBD_BACKLIGHT_COMMON_H
#define KBD_BACKLIGHT_COMMON_H

#define DEBUG_ON                            (0)
#define KBD_EVENTS_DEVICE_DEFAULT          "/dev/input/event0"
#define KBD_BACKLIGHT_TIMEOUT_DEFAULT       (60)

#if (DEBUG_ON)
#define DEBUG_PRINT1(x)        printf(x)
#define DEBUG_PRINT2(x,y)      printf(x,y)
#else
#define DEBUG_PRINT1(x)
#define DEBUG_PRINT2(x,y)
#endif

void kbd_light_set(int val);
void dbus_setup(void);

#endif    /* KBD_BACKLIGHT_COMMON_H */

