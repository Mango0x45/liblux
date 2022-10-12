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

#include <stdio.h>

#include "common.h"
#include "lux.h"

int
luxget(lux_t *disp)
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
