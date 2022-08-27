/*
 * BSD Zero Clause License
 *
 * Copyright (c) 2022 Thomas Voss
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#define _POSIX_C_SOURCE 200809L

#include <sys/types.h>

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "lux.h"

#ifdef O_PATH
	#define GETDIR_FLAGS O_PATH
#else
	#define GETDIR_FLAGS (O_RDONLY | O_DIRECTORY)
#endif

static int intlen(int);
static int getdir(void);
static FILE *getbstream(int);

void
luxfree(struct luxdisp *disp)
{
	if (disp->__dirfd != -1)
		close(disp->__dirfd);
	if (disp->__bstream != NULL)
		fclose(disp->__bstream);
}

int
luxinit(struct luxdisp *disp)
{
	/* Set the default values for the luxdisp struct.  We want to be as lazy
	 * as possible, so we don't bother with __bstream and __max yet.  We do
	 * need __dirfd though.
	 */
	*disp = (struct luxdisp) {
		.__bstream = NULL,
		.__max     = -1,
		.__dirfd   = getdir()
	};
	return disp->__dirfd;
}

int
luxmax(struct luxdisp *disp)
{
	/* The maximum brightness shouldn't change, so we can cache it in the
	 * struct.
	 */
	if (disp->__max != -1)
		return disp->__max;

	int fd = openat(disp->__dirfd, "max_brightness", O_RDONLY);
	if (fd == -1)
		return -1;
	FILE *stream = fdopen(fd, "r");
	if (stream == NULL) {
		close(fd);
		return -1;
	}

	fscanf(stream, "%d", &disp->__max);
	fclose(stream);
	return disp->__max;
}

int
luxget(struct luxdisp *disp)
{
	/* If we don't have an open stream with the brightness file yet then
	 * open one.  If we do, we instead rewind to the start of the file so
	 * that we don't just read an EOF.
	 */
	if (disp->__bstream == NULL) {
		if ((disp->__bstream = getbstream(disp->__dirfd)) == NULL)
			return -1;
	} else
		rewind(disp->__bstream);

	int n;
	fscanf(disp->__bstream, "%d", &n);
	return n;
}

int
luxset(struct luxdisp *disp, int n)
{
	/* The same deal as in luxget() */
	if (disp->__bstream == NULL) {
		if ((disp->__bstream = getbstream(disp->__dirfd)) == NULL)
			return -1;
	} else
		rewind(disp->__bstream);

	/* After writing the new brightness value to the brightness file, we
	 * need to truncate it so that luxset(disp, 1234); luxset(disp, 9);
	 * gives us a final brightness of 2 and not 9234.
	 */
	fprintf(disp->__bstream, "%d", n);
	ftruncate(fileno(disp->__bstream), intlen(n));
	return n;
}

int
luxinc(struct luxdisp *disp, int n)
{
	return luxset(disp, luxget(disp) + n);
}

int
luxdec(struct luxdisp *disp, int n)
{
	return luxinc(disp, -n);
}

double
luxgetp(struct luxdisp *disp)
{
	int cur, max;
	if ((cur = luxget(disp)) == -1 || (max = luxmax(disp)) == -1)
		return -1;
	return (double) cur / max * 100;
}

double
luxsetp(struct luxdisp *disp, double p)
{
	int max = luxmax(disp);
	return max == -1 ? -1 : luxset(disp, (int) (p / 100 * max));
}

double
luxincp(struct luxdisp *disp, double p)
{
	return luxsetp(disp, luxgetp(disp) + p);
}

double
luxdecp(struct luxdisp *disp, double p)
{
	return luxincp(disp, -p);
}

int
intlen(int n)
{
	return    n < 10         ? 1
		: n < 100        ? 2
		: n < 1000       ? 3
		: n < 10000      ? 4
		: n < 100000     ? 5
		: n < 1000000    ? 6
		: n < 10000000   ? 7
		: n < 100000000  ? 8
		: n < 1000000000 ? 9
		: 10;
}

int
getdir(void)
{
	int fd, dfd;
	struct dirent *dp;
	DIR *dir;

	/* To get the file descriptor for the directory where all the brightness
	 * files are located, we first need to open BACKLIGHT_DIR which is the
	 * directory where the backlight directories are located.  Then we need
	 * to get a DIR* of that directory and get the 3rd entry.  We need the
	 * third because the fist and second are the . and .. folders.  Finally
	 * we open the folder so that we have a file descriptor we can return.
	 */
	if ((dfd = open(BACKLIGHT_DIR, O_RDONLY)) == -1
			|| (dir = fdopendir(dfd)) == NULL
			|| (dp  = readdir(dir))   == NULL
			|| (dp  = readdir(dir))   == NULL
			|| (dp  = readdir(dir))   == NULL
			|| (fd  = openat(dfd, dp->d_name, GETDIR_FLAGS)) == -1)
		return -1;

	closedir(dir);
	return fd;
}

FILE *
getbstream(int dirfd)
{
	return fdopen(openat(dirfd, "brightness", O_RDWR), "r+");
}
