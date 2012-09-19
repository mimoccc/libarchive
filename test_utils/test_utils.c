/*
 * Copyright (c) 2003-2012 Tim Kientzle
 * Copyright (c) 2012 Andres Mejia
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "test_utils.h"

#include <stdlib.h>
#include <string.h>

int get_test_set(int *test_set, int limit, const char *test,
	struct test_list_t *tests)
{
	int start, end;
	int idx = 0;

	if (test == NULL) {
		/* Default: Run all tests. */
		for (;idx < limit; idx++)
			test_set[idx] = idx;
		return (limit);
	}
	if (*test >= '0' && *test <= '9') {
		const char *vp = test;
		start = 0;
		while (*vp >= '0' && *vp <= '9') {
			start *= 10;
			start += *vp - '0';
			++vp;
		}
		if (*vp == '\0') {
			end = start;
		} else if (*vp == '-') {
			++vp;
			if (*vp == '\0') {
				end = limit - 1;
			} else {
				end = 0;
				while (*vp >= '0' && *vp <= '9') {
					end *= 10;
					end += *vp - '0';
					++vp;
				}
			}
		} else
			return (-1);
		if (start < 0 || end >= limit || start > end)
			return (-1);
		while (start <= end)
			test_set[idx++] = start++;
	} else {
		size_t len = strlen(test);
		for (start = 0; start < limit; ++start) {
			const char *name = tests[start].name;
			const char *p;

			while ((p = strchr(name, test[0])) != NULL) {
				if (strncmp(p, test, len) == 0) {
					test_set[idx++] = start;
					break;
				} else
					name = p + 1;
			}

		}
	}
	return ((idx == 0)?-1:idx);
}
