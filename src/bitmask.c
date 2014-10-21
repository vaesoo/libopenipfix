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
#include "bitmask.h"

struct bitmask *
bitmask_new(void)
{
	struct bitmask *bm = calloc(1, sizeof(struct bitmask));

	return bm;
}

int
bitmask_set(struct bitmask *bm, unsigned bit)
{
	struct bitmask_node *bn;
	unsigned off = bit / 32;
	int i;

	for (i = 0; i < bm->bm_num_nodes; i++) {
		bn = &bm->bm_nodes[i];
		if (bn->bn_off == off)
			goto set;
		else if (bn->bn_off > off)
			break;
	}

	if ((bm->bm_nodes = realloc(bm->bm_nodes, (bm->bm_num_nodes + 1)
								* sizeof(struct bitmask_node))) == NULL)
		return -1;
	if (i < bm->bm_num_nodes)
		memmove(&bm->bm_nodes[i + 1], &bm->bm_nodes[i],
			    (bm->bm_num_nodes - i) * sizeof(struct bitmask_node));

	bn = &bm->bm_nodes[i];
	bn->bn_off = off;
	bn->bn_mask = 0U;
	bm->bm_num_nodes++;
set:
	if ((bn->bn_mask & (1 << (bit % 32))) == 0) {
		bn->bn_mask |= 1 << (bit % 32);
		bm->bm_bits_set++;

		return 1;
	}

	return 0;
}

int
bitmask_bits_set(const struct bitmask *bm)
{
	return bm->bm_bits_set;
}

bool
bitmask_eq(const struct bitmask *bm_a, const struct bitmask *bm_b)
{
	if (!!bm_a->bm_nodes != !!bm_b->bm_nodes)
		return false;

	return memcmp(bm_a->bm_nodes, bm_b->bm_nodes, bm_a->bm_num_nodes
				  * sizeof(struct bitmask_node)) == 0;
}

void
bitmask_reset(struct bitmask *bm)
{
	if (bm) {
		free(bm->bm_nodes);
		bm->bm_nodes = NULL;
		bm->bm_num_nodes = 0;
		bm->bm_bits_set = 0;
	}
}

void
bitmask_dump(const struct bitmask *bm)
{
	int i;

	for (i = 0; i< bm->bm_num_nodes; i++)
		printf("[%u]%08x ", bm->bm_nodes[i].bn_off, bm->bm_nodes[i].bn_mask);
	putchar('\n');
}
