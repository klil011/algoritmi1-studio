/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/**
 * \file bst_private.h
 *
 * \brief Private header for the Binary Search Tree abstract data type.
 *
 * \author Khalil Mounir
 *
 * \copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 *  This file is part of UPOalglib.
 *
 *  UPOalglib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  UPOalglib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UPO_BST_PRIVATE_H
#define UPO_BST_PRIVATE_H


#include <upo/bst.h>


/** \brief Alias for binary search tree node type. */
typedef struct upo_bst_node_s upo_bst_node_t;

/** \brief Type for nodes of a binary search tree. */
struct upo_bst_node_s
{
    void *key; /**< Pointer to user-provided key. */
    void *value; /**< Pointer to user-provided value. */
    upo_bst_node_t *left; /**< Pointer to the left child node. */
    upo_bst_node_t *right; /**< Pointer to the right child node. */
};

/** \brief Defines a binary tree. */
struct upo_bst_s
{
    upo_bst_node_t *root; /**< The root of the binary tree. */
    upo_bst_comparator_t key_cmp; /**< Pointer to the key comparison function. */
};


/**
 * \brief Clears the subtree rooted at the given node.
 *
 * \param node The root of the subtree where to clear nodes.
 * \param destroy_data Tells whether the memory previously allocated for the key
 *  and the associated value must be freed (value `1`) or not (value `0`).
 *
 * Memory deallocation (if requested) is performed by means of the `free()`
 * standard C function.
 */
static void upo_bst_clear_impl(upo_bst_node_t*, int destroy_data);

static void* upo_bts_get_impl(upo_bst_node_t*, const void *key, upo_bst_comparator_t key_cmp);

static void* upo_bts_put_impl(upo_bst_node_t*, void *key, void *value, void *oldValue, upo_bst_comparator_t key_cmp);

static size_t upo_bts_size_impl(upo_bst_node_t*);

static upo_bst_node_t* upo_bts_node_create(void *key, void *value);

static void* upo_bst_insert_impl(upo_bst_node_t*, void *key, void *value, upo_bst_comparator_t key_cmp);

static size_t upo_bst_height_impl(upo_bst_node_t*);

static size_t upo_bst_is_leaf_impl(upo_bst_node_t*);

static void* upo_bst_delete_impl(upo_bst_node_t*, const void *key, int destroy_data, upo_bst_comparator_t key_cmp);

static void* upo_bst_delete_1c_impl(upo_bst_node_t*, int destroy_data);

static void* upo_bst_delete_2c_impl(upo_bst_node_t*, int destroy_data, upo_bst_comparator_t key_cmp);

static void* upo_bst_max_pred_impl(upo_bst_node_t*);

static void upo_bst_traverse_in_order_impl(upo_bst_node_t*, upo_bst_visitor_t visit, void *visit_context);

static upo_bst_node_t* upo_bst_min_impl(upo_bst_node_t*);

static upo_bst_node_t* upo_bst_max_impl(upo_bst_node_t*);

static void* upo_bst_floor_impl(upo_bst_node_t*, const void *key, upo_bst_comparator_t key_cmp);

static void* upo_bst_ceiling_impl(upo_bst_node_t*, const void *key, upo_bst_comparator_t key_cmp);

static void upo_bst_key_range_impl(upo_bst_node_t *, const void *low_key, const void *high_key, upo_bst_key_list_t *list, upo_bst_comparator_t key_cmp);

static upo_bst_key_list_node_t* upo_bst_key_list_node_create();

static void upo_bst_keys_impl(upo_bst_node_t *, upo_bst_key_list_t *list);

static int upo_bst_is_bst_impl(upo_bst_node_t *n, const void *min_key, int min_key_changed, const void *max_key, int max_key_changed, upo_bst_comparator_t key_cmp);

static size_t upo_bst_rank_impl(upo_bst_node_t *n, const void *key, upo_bst_comparator_t key_cmp);

static void* upo_bst_get_value_depth_impl(upo_bst_node_t *n, const void *key, long *depth, upo_bst_comparator_t key_cmp);

static upo_bst_key_list_t upo_bst_keys_le_impl(upo_bst_node_t *n, const void *key, upo_bst_key_list_t *key_list, upo_bst_comparator_t key_cmp);

static void* upo_bst_predecessor_impl(upo_bst_node_t *n, const void *key, upo_bst_comparator_t key_cmp);

static void* upo_bst_subtree_max_impl(upo_bst_node_t *n, int found, upo_bst_comparator_t key_cmp, const *key);

#endif /* UPO_BST_PRIVATE_H */
