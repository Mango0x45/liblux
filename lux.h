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

#define BACKLIGHT_DIR "/sys/class/backlight"

#ifdef __cplusplus
extern "C" {
#endif

struct luxdisp {
	int __dirfd, __max;
	FILE *__bstream;
};

void luxfree(struct luxdisp *);
int luxinit(struct luxdisp *);
int luxmax(struct luxdisp *);
int luxget(struct luxdisp *);
int luxset(struct luxdisp *, int);
int luxinc(struct luxdisp *, int);
int luxdec(struct luxdisp *, int);

double luxgetp(struct luxdisp *);
double luxsetp(struct luxdisp *, double);
double luxincp(struct luxdisp *, double);
double luxdecp(struct luxdisp *, double);

#ifdef __cplusplus
}
#endif

#endif /* !LUX_H */
