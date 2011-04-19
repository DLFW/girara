/* See LICENSE file for license and copyright information */

#ifndef GIRARA_DATASTRUCTURES_H
#define GIRARA_DATASTRUCTURES_H

#include <stddef.h>
#include <stdbool.h>
#include "girara-types.h"

/**
 * Create a new list.
 *
 * @return The girara list object or NULL if an error occured
 */
girara_list_t* girara_list_new(void);

/**
 * Set the function which should be called if the stored data should be freed.
 *
 * @param list The girara list object
 * @param gfree Pointer to the free function
 */
void girara_list_set_free_function(girara_list_t* list, girara_free_function_t gfree);

/**
 * Destroy list.
 *
 * @param list The girara list object
 */
void girara_list_free(girara_list_t* list);

/**
 * Append an element to the list.
 *
 * @param list The girara list object
 * @param data The element
 */
void girara_list_append(girara_list_t* list, void* data);

/**
 * Prepend an element to the list.
 *
 * @param list The girara list object
 * @param data The element
 */
void girara_list_prepend(girara_list_t* list, void* data);

/**
 * Remove an element of the list
 *
 * @param list The girara list object
 * @param data The element
 */
void girara_list_remove(girara_list_t* list, void* data);

/**
 * Returns nth entry
 *
 * @param list The girara list object
 * @param n Index of the entry
 * @return The nth element or NULL if an error occured
 */
void* girara_list_nth(girara_list_t* list, unsigned int n);

/**
 * Checks if the list contains the given element
 *
 * @param list The girara list object
 * @param data The element
 * @return true if the list contains the element
 */
bool girara_list_contains(girara_list_t* list, void* data);

/**
 * Get size of the list.
 *
 * @param list The girara list object
 * @return The size of the list
 */
size_t girara_list_size(girara_list_t* list);

/**
 * Create an iterator pointing at the start of list.
 *
 * @param list The girara list object
 * @return The list iterator or NULL if an error occured
 */
girara_list_iterator_t* girara_list_iterator(girara_list_t* list);

/**
 * Move iterator to next element.
 *
 * @param list The list iterator
 * @return The moved iterator or NULL if an error occured
 */
girara_list_iterator_t* girara_list_iterator_next(girara_list_iterator_t* iter);

/**
 * Get data from the element pointed to by the iterator.
 *
 * @param list The list iterator
 * @return The data of the current element
 */
void* girara_list_iterator_data(girara_list_iterator_t* iter);

/**
 * Set data from the element pointed to by the iterator.
 *
 * @param list The list iterator
 * @param data Sets the list iterator to a specific element
 */
void girara_list_iterator_set(girara_list_iterator_t* iter, void *data);

/**
 * Destroy the iterator.
 *
 * @param list The list iterator
 */
void girara_list_iterator_free(girara_list_iterator_t* iter);

/**
 * Create a new node.
 *
 * @param data Data of the new node
 * @return A girara node object or NULL if an error occured
 */
girara_tree_node_t* girara_node_new(void* data);

/**
 * Set the function which should be called if the stored data should be freed.
 *
 * @param node The girara node object
 * @param gfree Pointer to the free function
 */
void girara_node_set_free_function(girara_tree_node_t* node, girara_free_function_t gfree);

/**
 * Free a node. This will remove the node from its' parent and will destroy all
 * its' children.
 *
 * @param node The girara node object
 */
void girara_node_free(girara_tree_node_t* node);

/**
 * Append a node to another node.
 *
 * @param parent The parent node
 * @param child The child node
 */
void girara_node_append(girara_tree_node_t* parent, girara_tree_node_t* child);

/**
 * Append data as new node to another node.
 *
 * @param parent The parent node
 * @param data The data of the node
 * @return The node object or NULL if an error occured
 */
girara_tree_node_t* girara_node_append_data(girara_tree_node_t* parent, void* data);

/**
 * Get parent node.
 *
 * @param node The girara node object
 * @return The parent node or NULL if an error occured or no parent exists
 */
girara_tree_node_t* girara_node_get_parent(girara_tree_node_t* node);

/**
 * Get root node.
 *
 * @param node The girara node object
 * @return The root node or NULL if an error occured
 */
girara_tree_node_t* girara_node_get_root(girara_tree_node_t* node);

/**
 * Get list of children.
 *
 * @param node The girara node object
 * @return List object containing all child nodes or NULL if an error occured
 */
girara_list_t* girara_node_get_children(girara_tree_node_t* node);

/**
 * Get number of children.
 *
 * @param node The girara node object
 * @return The number of child nodes
 */
size_t girara_node_get_num_children(girara_tree_node_t* node);

/**
 * Get data.
 *
 * @param node The girara node object
 * @return The data of the node
 */
void* girara_node_get_data(girara_tree_node_t* node);

/**
 * Set data.
 *
 * @param node The girara node object
 * @param data The new data of the object
 */
void girara_node_set_data(girara_tree_node_t* node, void* data);

#endif
