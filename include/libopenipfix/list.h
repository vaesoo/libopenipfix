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
#ifndef OIPF_LIST_H
#define OIPF_LIST_H

#include <stddef.h>

static inline void prefetch(const void *x) { }

#define oipf_container_of(ptr, type, member) ({						\
			const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
			(type *)( (char *)__mptr - offsetof(type,member) );})

#define OIPF_LIST_POISON1  ((void *)0x00100100)
#define OIPF_LIST_POISON2  ((void *)0x00200200)

struct oipf_list_head {
	struct oipf_list_head *next, *prev;
};

#define OIPF_LIST_HEAD_INIT(name) { &(name), &(name) }

#define OIPF_LIST_HEAD(name)									\
	struct oipf_list_head name = OIPF_LIST_HEAD_INIT(name)

#define OIPF_INIT_LIST_HEAD(ptr) do {				\
		(ptr)->next = (ptr); (ptr)->prev = (ptr);	\
	} while (0)

static inline void
__oipf_list_add(struct oipf_list_head *new, struct oipf_list_head *prev,
				struct oipf_list_head *next)
{
	next->prev = new;
	new->next = next;
	new->prev = prev;
	prev->next = new;
}

static inline void
oipf_list_add(struct oipf_list_head *new, struct oipf_list_head *head)
{
	__oipf_list_add(new, head, head->next);
}

static inline void
oipf_list_add_tail(struct oipf_list_head *new, struct oipf_list_head *head)
{
	__oipf_list_add(new, head->prev, head);
}

static inline void
__oipf_list_del(struct oipf_list_head *prev, struct oipf_list_head *next)
{
	next->prev = prev;
	prev->next = next;
}

static inline void
oipf_list_del(struct oipf_list_head *entry)
{
	__oipf_list_del(entry->prev, entry->next);
#ifdef OIPF_DEBUG_LIST
	entry->next = OIPF_LIST_POISON1;
	entry->prev = OIPF_LIST_POISON2;
#endif /* OIPF_DEBUG_LIST */
}

static inline void
oipf_list_del_init(struct oipf_list_head *entry)
{
	__oipf_list_del(entry->prev, entry->next);
	OIPF_INIT_LIST_HEAD(entry); 
}

/**
 * list_move - delete from one list and add as another's head
 *
 * @list:	the entry to move
 * @head:	the head that will precede our entry
 */
static inline void
oipf_list_move(struct oipf_list_head *list, struct oipf_list_head *head)
{
	__oipf_list_del(list->prev, list->next);
	oipf_list_add(list, head);
}

/**
 * list_move_tail - delete from one list and add as another's tail
 *
 * @list: the entry to move
 * @head: the head that will follow our entry
 */
static inline void
oipf_list_move_tail(struct oipf_list_head *list, struct oipf_list_head *head)
{
        __oipf_list_del(list->prev, list->next);
        oipf_list_add_tail(list, head);
}

/**
 * oipf_list_empty - tests whether a list is empty
 *
 * @head: the list to test.
 */
static inline int
oipf_list_empty(const struct oipf_list_head *head)
{
	return head->next == head;
}

static inline void
__oipf_list_splice(struct oipf_list_head *list, struct oipf_list_head *head)
{
	struct oipf_list_head *first = list->next;
	struct oipf_list_head *last = list->prev;
	struct oipf_list_head *at = head->next;

	first->prev = head;
	head->next = first;

	last->next = at;
	at->prev = last;
}

/**
 * oipf_list_splice - join two lists
 *
 * @list: the new list to add.
 * @head: the place to add it in the first list.
 */
static inline void
oipf_list_splice(struct oipf_list_head *list, struct oipf_list_head *head)
{
	if (!oipf_list_empty(list))
		__oipf_list_splice(list, head);
}

#define oipf_list_entry(ptr, type, member) \
	oipf_container_of((ptr), (type), (member))

/**
 * oipf_list_for_each - iterate over a list
 *
 * @pos:	the &struct oipf_list_head to use as a loop counter.
 * @head:	the head for your list.
 */
#define oipf_list_for_each(pos, head)							 \
	for (pos = (head)->next, prefetch(pos->next); pos != (head); \
        	pos = pos->next, prefetch(pos->next))

#define __oipf_list_for_each(pos, head)							\
	for (pos = (head)->next; pos != (head); pos = pos->next)

#define oipf_list_for_each_prev(pos, head)						 \
	for (pos = (head)->prev, prefetch(pos->prev); pos != (head); \
		 pos = pos->prev, prefetch(pos->prev))
        	
#define oipf_list_for_each_prev_safe(pos, n, head)		   \
    for (pos = (head)->prev, n = pos->prev; pos != (head); \
		 pos = n, n = pos->prev)

#define list_for_each_safe(pos, n, head)					\
	for (pos = (head)->next, n = pos->next; pos != (head);	\
		 pos = n, n = pos->next)

#define oipf_list_for_each_entry(pos, head, member)						\
	for (pos = oipf_list_entry((head)->next, typeof(*pos), member),		\
		     prefetch(pos->member.next);  &pos->member != (head);		\
	     pos = oipf_list_entry(pos->member.next, typeof(*pos), member),	\
		     prefetch(pos->member.next))

#define oipf_list_for_each_entry_reverse(pos, head, member)				\
	for (pos = oipf_list_entry((head)->prev, typeof(*pos), member),		\
		     prefetch(pos->member.prev); &pos->member != (head);		\
	     pos = oipf_list_entry(pos->member.prev, typeof(*pos), member),	\
		     prefetch(pos->member.prev))

#endif /* OIPF_LIST_H */
