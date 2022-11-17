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

#include <sys/types.h>

#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

#include "lux.h"

static int getdir(void);

int
luxinit(lux_t *disp)
{
	/* Set the default values for the luxdisp struct.  We want to be as lazy
	 * as possible, so we don't bother with __bstream and __max yet.  We do
	 * need __dirfd though.
	 */
	*disp = (lux_t) {
		.__bstream = NULL,
		.__max     = -1,
		.__dirfd   = getdir()
	};
	return disp->__dirfd;
}

int
getdir(void)
{
	int fd, dfd;
	struct dirent *dp;
	DIR *dir;

	/* To get the file descriptor for the directory where all the brightness
	 * files are located, we first need to open LIBLUX_BACKLIGHT_DIR which
	 * is the directory where the backlight directories are located.  Then
	 * we need to get a DIR* of that directory and get the 3rd entry.  We
	 * need the third because the fist and second are the . and .. folders.
	 * Finally we open the folder so that we have a file descriptor we can
	 * return.
	 */
	if ((dfd = open(LIBLUX_BACKLIGHT_DIR, O_RDONLY)) == -1)
		return -1;
	if ((dir = fdopendir(dfd)) == NULL) {
		close(dfd);
		return -1;
	}
	if ((dp = readdir(dir)) == NULL
			|| (dp = readdir(dir)) == NULL
			|| (dp = readdir(dir)) == NULL
			|| (fd = openat(dfd, dp->d_name, O_PATH)) == -1)
		fd = -1;

	close(dfd);
	closedir(dir);
	return fd;
}
