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
#ifndef OIPF_MSG_H
#define OIPF_MSG_H

#include <libopenipfix/list.h>

struct oipf_msg {
	struct oipf_list_head link;
	unsigned char *tail;
	unsigned char *end;
	unsigned int flags;
	unsigned int nrecs;
	uint8_t data[];
};

struct oipf_msg *oipf_msg_alloc(size_t len, uint32_t oid);
void oipf_msg_free(struct oipf_msg *);

void *oipf_msg_data(const struct oipf_msg *msg);

#endif /* OIPF_MSG_H */
