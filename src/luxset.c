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
#include <unistd.h>

#include "common.h"
#include "lux.h"

static int intlen(int);

int
luxset(lux_t *disp, int n)
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
