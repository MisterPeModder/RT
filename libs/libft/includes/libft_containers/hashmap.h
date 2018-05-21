/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:59:22 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/17 18:46:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_H
# define HASHMAP_H

# include "hashmap_internal.h"

/*
** hm_make: Creates a new empty hashmap.
**
** -power: A power of two.
**         The number of buckets is the result of the operation 2**power.
**         If 0 is given, then power is set to HM_DEFAULT_POWER
**         (see "hashmap_internal.h")
**
**         A bigger number of buckets means better perfomance at the
**         cost of memory.
**
** -load_factor: used to determine the capacity of the map using this formula:
**               capacity = bucket_number * load_factor
**               when the number of elements reaches capacity, the map will
**               double its number of buckets, causing a rehash.
**               If 0 is given, then load_factor is
**               set to HM_DEFAULT_LOAD_FACTOR.
**
** returns: The hashmap instance.
*/
t_hashmap				*hm_make(size_t power, float load_factor);

/*
** hm_release: Frees the passed hashmap and sets the pointer to NULL.
**
** -d: A destructor function that will be called each time before a node is
**     freed. It takes the 'value' pointer as a parameter, this allows
**     the user to change how the memory is freed.
**     If NULL, d is set to &free.
**
**     NOTE: This function does NOT free the value of the key-value pairs,
**     you have to free it yourself using the d function pointer!
*/
void					hm_release(t_hashmap **map, void (*d)(void *));

/*
** hm_put: Puts/updates a key-value pair in the passed hashmap.
*/
void					hm_put(t_hashmap *map, const char *key, void *value);

/*
** hm_put_cpy: Same as hm_put() but the value parameter is copied instead of
**             being directly put into the map.
**
** -size: Size of the value in bytes.
*/
void					hm_put_cpy(t_hashmap *map, const char *key,
		const void *val, size_t size);

/*
** hm_get: Searches the passed hashmap instance for the given key k.
**
** returns: The value corresponding to the key if found, NULL otherwise.
*/
void					*hm_get(t_hashmap *map, const char *key);

/*
** hm_del: Deletes a key-value pair in the passed hashmap and frees it.
**
** -d: The same function pointer you would give to hm_relase(). (see above)
*/
void					hm_del(t_hashmap *m, const char *k, void (*d)(void *));

/*
** hm_collisions: Counts the number of elements that collides with each other.
**                A collision happens when two or more  elements get stored
**                in the same bucket thus decreasing the performance.
*/
size_t					hm_collisions(t_hashmap *map);

/*
** hm_length: Returns the number of elements stored in the passed hashmap.
*/
size_t					hm_length(t_hashmap *map);

/*
** hm_iter_init: Inializes the passed iterator.
**
** -it: A pointer to a t_hmiterator (preferably a stack address)
*/
void					hm_iter_init(t_hashmap *map, t_hmiterator *it);

/*
** hm_iter_next: Iterates through the map.
**
** returns: 1 if a value was found, 0 if the end of the map was reached.
**          If found use it.key to retrieve the key and it.value for the value.
**          (in this case the iterator named "it" is local)
*/
int						hm_iter_next(t_hmiterator *it);

#endif
