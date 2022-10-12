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

#ifndef LUX_H
#define LUX_H

#include <stdio.h>

#define LUX_BACKLIGHT_DIR "/sys/class/backlight"
#ifdef O_PATH
	#define LUX_GDIR_FLAGS O_PATH
#else
	#define LUX_GDIR_FLAGS (O_RDONLY | O_DIRECTORY)
#endif


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	int __dirfd, __max;
	FILE *__bstream;
} lux_t;

void luxfree(lux_t *);
int luxinit(lux_t *);
int luxmax(lux_t *);
int luxget(lux_t *);
int luxset(lux_t *, int);
int luxinc(lux_t *, int);
int luxdec(lux_t *, int);

double luxgetp(lux_t *);
double luxsetp(lux_t *, double);
double luxincp(lux_t *, double);
double luxdecp(lux_t *, double);

#ifdef __cplusplus
}
#endif

#endif /* !LUX_H */
