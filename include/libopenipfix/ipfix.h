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
#ifndef OIPF_IPFIX_H
#define OIPF_IPFIX_H

struct ipfix_hdr {
#define IPFIX_VERSION			0xa
	uint16_t version;
	uint16_t len;
	uint32_t time;
	uint32_t seqno;				/* Data Records send */
	uint32_t oid;				/* Observation Domain ID */
	uint8_t data[];
} __oipf_packed;

#define IPFIX_HDRLEN	sizeof(struct ipfix_hdr)

/*
 * If the Enterprise Bit is set an additional Enterprise ID (uint32_t)
 * is attached.
 */
struct ipfix_field_spec_hdr {
	uint16_t fs_id;
	uint16_t fs_len;
	uint32_t fs_enterprise_id[];
} __oipf_packed;

/*
 * IDs 0-255 are reserved for Template Sets.  IDs of Data Sets are > 255.
 */
struct ipfix_templ_hdr {
	uint16_t id;
	uint16_t cnt;
	struct ipfix_field_spec_hdr fields[];
} __oipf_packed;

struct ipfix_set_hdr {
#define IPFIX_SET_TEMPL			2
#define IPFIX_SET_OPT_TEMPL		3
	uint16_t id;
	uint16_t len;
	uint8_t data[];
} __oipf_packed;

#endif /* OIPF_IPFIX_H */
