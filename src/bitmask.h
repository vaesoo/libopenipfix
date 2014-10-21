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
#ifndef BITMASK_H
#define BITMASK_H

/*
 * Sparse bitmask handling
 */
struct bitmask_node {
	unsigned bn_off;
	uint32_t bn_mask;
};

struct bitmask {
	struct bitmask_node *bm_nodes;
	size_t bm_num_nodes;
	int bm_bits_set;
};

struct bitmask *bitmask_new(void);
int bitmask_set(struct bitmask *, unsigned);
int bitmask_bits_set(const struct bitmask *);
bool bitmask_eq(const struct bitmask *, const struct bitmask *);
void bitmask_reset(struct bitmask *);
void bitmask_dump(const struct bitmask *);

#endif /* BITMASK_H */
