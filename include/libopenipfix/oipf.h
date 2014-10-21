/*
 * This library is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * libopenipfix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General
 * Public License along with libopenipfix.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Holger Eitzenberger <holger@eitzenberger.org>, 2014.
 */
#ifndef OIPF_H
#define OIPF_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define __oipf_packed	__attribute__((packed))
#define __oipf_	__attribute__((packed))
#define __oipf_cold		__attribute__((cold))
#define __oipf_printf(idx, first) __attribute__((format (printf, (idx), (first))))

int oipf_init(void);

void oipf_err(const char *, ...) __oipf_printf(1, 2);

#endif /* OIPF_MSG_H */
