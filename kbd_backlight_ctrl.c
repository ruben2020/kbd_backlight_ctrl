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

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <linux/input.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "kbd_backlight_common.h"

void sighandler(int signum);
void* countdown_thread(void *unused);
void* keyevents_thread(void *unused);
void thread_create_error(char* threadname);
void init_param(void);
int main();

int countdown;
int timeout;
int threads_active = 1;
int fd;
char* kbd_events_device;
pthread_t thread_countdown;
pthread_t thread_keyevents;
pthread_mutex_t mut;

void sighandler(int signum)
{
	DEBUG_PRINT2("Received signal: %d\n", signum);
	threads_active = 0;
	exit(0);
}

void* countdown_thread(void *unused)
{
	do {
		pthread_mutex_lock(&mut);
		if (countdown > 0)
		{
			countdown--;
			if (countdown == 0)
			{
				kbd_light_set(0);
			}
		}
		pthread_mutex_unlock(&mut);
		if (threads_active) sleep(1);  /* Sleep for 1 second */
	} while (threads_active);
	pthread_exit(NULL);
}

void* keyevents_thread(void *unused)
{
	ssize_t rd;
	struct input_event ev;

	fd = open(kbd_events_device, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "ERROR: Could not open %s as read-only device. You need to be root.\n", kbd_events_device);
		exit(1);
	}
	do {
		rd = read(fd, &ev, sizeof(struct input_event));
		if (!threads_active) break;
		if (rd == -1)
		{
			fprintf(stderr, "ERROR: Reading error for device %s\n", kbd_events_device);
			exit(1);
		}
		DEBUG_PRINT2("Read something new from %s\n", kbd_events_device);
		pthread_mutex_lock(&mut);
		if (countdown < 2)
		{
			kbd_light_set(1);
		}
		countdown = timeout;
		pthread_mutex_unlock(&mut);		
	} while(threads_active);
	close(fd);
	pthread_exit(NULL);
}

void thread_create_error(char* threadname)
{
	fprintf(stderr, "ERROR: thread %s could not be created and started!\n", threadname);
	exit(1);
}

void init_param(void)
{
	char *s = NULL;	
	s = getenv("KBD_BACKLIGHT_CTRL_TIMEOUT");
	if (s != NULL)
	{
		timeout = atoi(s);
	}
	else timeout = KBD_BACKLIGHT_TIMEOUT_DEFAULT;
	if ((timeout < 2) || (timeout > 7200))
		timeout = KBD_BACKLIGHT_TIMEOUT_DEFAULT;
	DEBUG_PRINT2("Timeout set to %d\n", timeout);
	countdown = timeout;
	s = NULL;
	s = getenv("KBD_BACKLIGHT_CTRL_INDEVICE");
	if (s != NULL)
	{
		kbd_events_device = s;
	}
	else kbd_events_device = KBD_EVENTS_DEVICE_DEFAULT;
	if( access(kbd_events_device, R_OK) != -1 )
	{
		DEBUG_PRINT2("%s is readable\n", kbd_events_device);
	}
	else
	{
		fprintf(stderr, "ERROR: %s is not readable!\n", kbd_events_device);
		exit(1);
	}
}

int main()
{
	int rc;
	pthread_attr_t attr;  

	signal(SIGINT,  sighandler);
	signal(SIGTERM, sighandler);

	init_param();
	dbus_setup();
	kbd_light_set(1);
	pthread_mutex_init(&mut, NULL);
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	DEBUG_PRINT1("Creating threads\n");

	rc = pthread_create(&thread_countdown, &attr, &countdown_thread, NULL);
	if (rc) thread_create_error("thread_countdown");

	rc = pthread_create(&thread_keyevents, &attr, &keyevents_thread, NULL);
	if (rc) thread_create_error("thread_keyevents");

 	pthread_join(thread_countdown, NULL);
	DEBUG_PRINT1("Joined thread_countdown\n");
	pthread_join(thread_keyevents, NULL);
	DEBUG_PRINT1("Joined thread_keyevents\n");

	close(fd);
	pthread_attr_destroy(&attr);
	pthread_mutex_destroy(&mut);
	DEBUG_PRINT1("End program\n");
	return 0;
}

