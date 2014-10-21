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

#include <libopenipfix/oipf.h>
#include <libopenipfix/msg.h>
#include <libopenipfix/ipfix.h>

struct oipf_msg *
oipf_msg_alloc(size_t len, uint32_t oid)
{
	struct oipf_msg *msg;
	struct ipfix_hdr *hdr;

	if ((msg = malloc(sizeof(struct oipf_msg) + len)) == NULL)
		return NULL;

	memset(msg, 0, sizeof(struct oipf_msg));
	msg->tail = msg->data;
	msg->end = msg->data + len;

	hdr = ipfix_msg_reserve(msg, sizeof(struct ipfix_hdr));
	memset(hdr, 0, IPFIX_HDRLEN);
	hdr->version = htons(IPFIX_VERSION);
	hdr->oid = htonl(oid);
	pr_debug("msg=%p\n", msg);

	return msg;
	return msg;
}

void
oipf_msg_free(struct oipf_msg *msg)
{
	if (msg)
		free(msg);
}

void *
oipf_msg_data(const struct oipf_msg *msg)
{
	return msg->data;
}
