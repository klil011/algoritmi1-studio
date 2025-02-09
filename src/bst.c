/* vim: set tabstop=4 expandtab shiftwidth=4 softtabstop=4: */

/*
 * Copyright 2015 University of Piemonte Orientale, Computer Science Institute
 *
 * This file is part of UPOalglib.
 *
 * UPOalglib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * UPOalglib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with UPOalglib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "bst_private.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**** EXERCISE #1 - BEGIN of FUNDAMENTAL OPERATIONS ****/

upo_bst_t upo_bst_create(upo_bst_comparator_t key_cmp)
{
    upo_bst_t tree = malloc(sizeof(struct upo_bst_s));
    if (tree == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    tree->root = NULL;
    tree->key_cmp = key_cmp;

    return tree;
}

upo_bst_node_t *upo_bts_node_create(void *key, void *value)
{

    upo_bst_node_t *nodo = malloc(sizeof(upo_bst_node_t));
    if (nodo == NULL)
    {
        perror("Unable to create a binary search tree");
        abort();
    }

    nodo->key = key;
    nodo->value = value;
    nodo->left = NULL;
    nodo->right = NULL;

    return nodo;
}

void upo_bst_destroy(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear(tree, destroy_data);
        free(tree);
    }
}

void upo_bst_clear_impl(upo_bst_node_t *node, int destroy_data)
{
    if (node != NULL)
    {
        upo_bst_clear_impl(node->left, destroy_data);
        upo_bst_clear_impl(node->right, destroy_data);

        if (destroy_data)
        {
            free(node->key);
            free(node->value);
        }

        free(node);
    }
}

void upo_bst_clear(upo_bst_t tree, int destroy_data)
{
    if (tree != NULL)
    {
        upo_bst_clear_impl(tree->root, destroy_data);
        tree->root = NULL;
    }
}

void *upo_bst_put(upo_bst_t tree, void *key, void *value)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        void *oldValue = NULL;

        tree->root = upo_bts_put_impl(tree->root, key, value, oldValue, tree->key_cmp);

        return oldValue;
    }

    return NULL;
}

void *upo_bts_put_impl(upo_bst_node_t *n, void *key, void *value, void *oldValue, upo_bst_comparator_t key_cmp)
{

    oldValue = NULL;

    if (n == NULL)
    {
        /* implementare la funzione di creazione dei nodi */
        return upo_bts_node_create(key, value);
    }
    else if (key_cmp(key, n->key) < 0)
    {
        n->left = upo_bts_put_impl(n->left, key, value, oldValue, key_cmp);
    }
    else if (key_cmp(key, n->key) > 0)
    {
        n->right = upo_bts_put_impl(n->right, key, value, oldValue, key_cmp);
    }
    else
    {
        oldValue = n->value;
        n->value = value;
    }

    return n;
}

void upo_bst_insert(upo_bst_t tree, void *key, void *value)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        tree->root = upo_bst_insert_impl(tree->root, key, value, tree->key_cmp);
    }
}

void *upo_bst_insert_impl(upo_bst_node_t *n, void *key, void *value, upo_bst_comparator_t key_cmp)
{

    if (n == NULL)
    {
        return upo_bts_node_create(key, value);
    }
    else if (key_cmp(key, n->key) < 0)
    {
        n->left = upo_bst_insert_impl(n->left, key, value, key_cmp);
    }
    else if (key_cmp(key, n->key) > 0)
    {
        n->right = upo_bst_insert_impl(n->right, key, value, key_cmp);
    }
    else
    {
        /* Duplicate key: do nothing */
    }

    return n;
}

void *upo_bst_get(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */

    if (tree != NULL)
    {
        upo_bst_node_t *n = upo_bts_get_impl(tree->root, key, tree->key_cmp);

        if (n == NULL)
        {
            return NULL;
        }

        return n->value;
    }

    return NULL;
}

void *upo_bts_get_impl(upo_bst_node_t *n, const void *key, upo_bst_comparator_t key_cmp)
{

    if (n == NULL)
    {
        return NULL;
    }
    else if (key_cmp(key, n->key) < 0)
    {
        return upo_bts_get_impl(n->left, key, key_cmp);
    }
    else if (key_cmp(key, n->key) > 0)
    {
        return upo_bts_get_impl(n->right, key, key_cmp);
    }
    else
    {
        return n;
    }
}

int upo_bst_contains(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */

    if (tree != NULL)
    {
        upo_bst_node_t *n = upo_bts_get_impl(tree->root, key, tree->key_cmp);

        if (n == NULL)
        {
            return 0;
        }

        return 1;
    }

    return 0;

}

void upo_bst_delete(upo_bst_t tree, const void *key, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        tree->root = upo_bst_delete_impl(tree->root, key, destroy_data, tree->key_cmp);
    }
}

void *upo_bst_delete_impl(upo_bst_node_t *n, const void *key, int destroy_data, upo_bst_comparator_t key_cmp)
{

    if (n == NULL)
    {
        return NULL;
    }

    if (key_cmp(key, n->key) < 0)
    {
        n->left = upo_bst_delete_impl(n->left, key, destroy_data, key_cmp);
    }
    else if (key_cmp(key, n->key) > 0)
    {
        n->right = upo_bst_delete_impl(n->right, key, destroy_data, key_cmp);
    }
    else if (n->left != NULL && n->right != NULL)
    { /*  if left and right node are not null  */
        n = upo_bst_delete_2c_impl(n, destroy_data, key_cmp);
    }
    else
    { /*  the node can be leaf or not (at least one of them must be null)  */
        n = upo_bst_delete_1c_impl(n, destroy_data);
    }

    return n;
}

void *upo_bst_delete_1c_impl(upo_bst_node_t *n, int destroy_data)
{

    upo_bst_node_t *node = n;

    if (n->left != NULL)
    {
        n = n->left;
    }
    else
    {
        n = n->right;
    }

    if (destroy_data)
    {
        free(node->value);
    }

    free(node);

    return n;
}

/*  Larghet predecessor  */
void *upo_bst_delete_2c_impl(upo_bst_node_t *n, int destroy_data, upo_bst_comparator_t key_cmp)
{

    upo_bst_node_t *maxPredecessor = upo_bst_max_pred_impl(n->left); /* To be implemented  */

    n->key = maxPredecessor->key;
    n->value = maxPredecessor->value;

    n->left = upo_bst_delete_impl(n->left, maxPredecessor->key, destroy_data, key_cmp);

    return n;
}

void *upo_bst_max_pred_impl(upo_bst_node_t *n)
{
    if (n == NULL)
    {
        return NULL;
    }
    
    if (n->right != NULL)
    {
        upo_bst_max_pred_impl(n->right);
    }
    
    return n; 
}

size_t upo_bst_size(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */

    if (tree == NULL)
    {
        return 0;
    }

    return upo_bts_size_impl(tree->root);
}

size_t upo_bts_size_impl(upo_bst_node_t *n)
{

    if (n == NULL)
    {
        return 0;
    }

    return 1 + upo_bts_size_impl(n->left) + upo_bts_size_impl(n->right);
}

size_t upo_bst_height(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        return upo_bst_height_impl(tree->root);
    }

    return 0;
}

size_t upo_bst_height_impl(upo_bst_node_t *n)
{

    if (n == NULL || upo_bst_is_leaf_impl(n))
    {
        return 0;
    }

    return 1 + fmax(upo_bst_height_impl(n->left), upo_bst_height_impl(n->right));
}

size_t upo_bst_is_leaf_impl(upo_bst_node_t *n)
{

    if (n->left == NULL && n->right == NULL)
    {
        return 1;
    }

    return 0;
}

void upo_bst_traverse_in_order(const upo_bst_t tree, upo_bst_visitor_t visit, void *visit_context)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        upo_bst_traverse_in_order_impl(tree->root, visit, visit_context);
    }
}

void upo_bst_traverse_in_order_impl(upo_bst_node_t *n, upo_bst_visitor_t visit, void *visit_context)
{

    if (n != NULL)
    {
        upo_bst_traverse_in_order_impl(n->left, visit, visit_context);
        visit(n->key, n->value, visit_context);
        upo_bst_traverse_in_order_impl(n->right, visit, visit_context);
    }
}

int upo_bst_is_empty(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree == NULL || tree->root == NULL)
    {
        return 1;
    }

    return 0;
}

/**** EXERCISE #1 - END of FUNDAMENTAL OPERATIONS ****/

/**** EXERCISE #2 - BEGIN of EXTRA OPERATIONS ****/

void *upo_bst_min(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        upo_bst_node_t *min = upo_bst_min_impl(tree->root);
        if (min != NULL)
        {
            return min->key;
        }
        
    }

    return NULL;
}

upo_bst_node_t* upo_bst_min_impl(upo_bst_node_t *n) {

    if (n == NULL)
    {
        return NULL;
    }

    if (n->left == NULL)
    {
        return n;
    }

    return upo_bst_min_impl(n->left);  
}

void *upo_bst_max(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        upo_bst_node_t *max = upo_bst_max_impl(tree->root);
        /*  
            il controllo sul valore di max è FONDAMENTALE per evitare errori di segmentation fault,
            perchè se max_impl dovesse restituire NULL, l'istruzione max(NULL)->key genererebbe un segmentation fault  
        */
        if (max != NULL)
        {
            return max->key;
        }
    }

    return NULL;
}

upo_bst_node_t* upo_bst_max_impl(upo_bst_node_t *n) {

    if (n == NULL)
    {
        return NULL;
    }

    if (n->right == NULL)
    {
        return n;
    }

    return upo_bst_max_impl(n->right);
    
}

void upo_bst_delete_min(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        void *key_min = upo_bst_min(tree);
        upo_bst_delete(tree, key_min, destroy_data);
    }

}

void upo_bst_delete_max(upo_bst_t tree, int destroy_data)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        void *max_key = upo_bst_max(tree);
        upo_bst_delete(tree, max_key, destroy_data);
    }
    
}

void* upo_bst_floor(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        upo_bst_node_t *floor_node = NULL;
        floor_node = upo_bst_floor_impl(tree->root, key, tree->key_cmp);

        if (floor_node != NULL)
        {
            return floor_node->key;
        }
    }

    return NULL;
    
}

void* upo_bst_floor_impl(upo_bst_node_t *n, const void *key, upo_bst_comparator_t key_cmp) {

    if (n == NULL)
    {
        return NULL;
    }

    if (key_cmp(key, n->key) < 0)
    {
        return upo_bst_floor_impl(n->left, key, key_cmp);
    }
    else if (key_cmp(key, n->key) > 0)
    {
        upo_bst_node_t *floor_node = upo_bst_floor_impl(n->right, key, key_cmp);

        return (floor_node != NULL) ? floor_node : n;
    }
    else
    {
        return n;
    }
    
}


void *upo_bst_ceiling(const upo_bst_t tree, const void *key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        upo_bst_node_t *ceiling_node = upo_bst_ceiling_impl(tree->root, key, tree->key_cmp);

        if (ceiling_node != NULL)
        {
            return ceiling_node->key;
        }
        
    }

    return NULL;
    
}

void* upo_bst_ceiling_impl(upo_bst_node_t *n, const void *key, upo_bst_comparator_t key_cmp) {

    if (n == NULL)
    {
        return NULL;
    }

    if (key_cmp(key, n->key) < 0)
    {
        upo_bst_node_t *ceiling_node = upo_bst_ceiling_impl(n->left, key, key_cmp);
        return (ceiling_node != NULL) ? ceiling_node : n;
    }
    else if (key_cmp(key, n->key) > 0)
    {
        return upo_bst_ceiling_impl(n->right, key, key_cmp);              
    }
    else
    {
        return n;
    }

}

upo_bst_key_list_t upo_bst_keys_range(const upo_bst_t tree, const void *low_key, const void *high_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */

   if (tree != NULL)
   {
        upo_bst_key_list_t keys_list = NULL;
        upo_bst_key_range_impl(tree->root, low_key, high_key, &keys_list, tree->key_cmp);

        return keys_list;
   }
   
   return NULL;

}

void upo_bst_key_range_impl(upo_bst_node_t *n, const void *low_key, const void *high_key, upo_bst_key_list_t *list, upo_bst_comparator_t key_cmp) {

    if (n == NULL)
    {
        return;
    }
    
    upo_bst_key_range_impl(n->left, low_key, high_key, list, key_cmp);
    /*  operazione di aggiunta in testa alla lista  */
    //  creazione del nodo
    upo_bst_key_list_node_t *list_node = upo_bst_key_list_node_create();

    int cmp1 = key_cmp(n->key, low_key);
    int cmp2 = key_cmp(n->key, high_key);

    if (cmp1 >= 0 && cmp2 <= 0)     
    {
        //  aggiungi il nodo in testa alla lista
        list_node->key = n->key;
        list_node->next = *list;
        *list = list_node;
    }
    
    upo_bst_key_range_impl(n->right, low_key, high_key, list, key_cmp);
}

upo_bst_key_list_node_t* upo_bst_key_list_node_create() {

    upo_bst_key_list_node_t *list_node = malloc(sizeof(struct upo_bst_key_list_node_s));
    if (list_node == NULL)
    {
        perror("Unable to allocate memory for a new node of the key list");
        abort();
    }

    list_node->key = NULL;
    list_node->next = NULL;

    return list_node; 
}

upo_bst_key_list_t upo_bst_keys(const upo_bst_t tree)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (tree != NULL)
    {
        upo_bst_key_list_t list = NULL;
        upo_bst_keys_impl(tree->root, &list);

        return list;
    }
    
    return NULL;
    
}

void upo_bst_keys_impl(upo_bst_node_t *n, upo_bst_key_list_t *list) {

    if (n == NULL)
    {
        return;
    }

    upo_bst_keys_impl(n->left, list);
    
    upo_bst_key_list_node_t *list_node = upo_bst_key_list_node_create();
    
    list_node->key = n->key;
    list_node->next = *list;
    *list = list_node;

    upo_bst_keys_impl(n->right, list);
    
}

int upo_bst_is_bst(const upo_bst_t tree, const void *min_key, const void *max_key)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    if (upo_bst_is_empty(tree))
    {
        return 1;
    }

    return upo_bst_is_bst_impl(tree->root, min_key, 0, max_key, 0, tree->key_cmp);
    
}

int upo_bst_is_bst_impl(upo_bst_node_t *n, const void *min_key, int min_key_changed, const void *max_key, int max_key_changed, upo_bst_comparator_t key_cmp)
{
    if (n == NULL)
    {
        return 1;
    }

    if (key_cmp(n->key, min_key) < 0
        || (min_key_changed && key_cmp(n->key, min_key) == 0)
        || (key_cmp(n->key, max_key) > 0)
        || (max_key_changed && key_cmp(n->key, max_key) == 0))
    {
        return 0;
    }
    
    return upo_bst_is_bst_impl(n->left, min_key, min_key_changed, n->key, 1, key_cmp)
            && upo_bst_is_bst_impl(n->right, n->key, 1, max_key, max_key_changed, key_cmp);
}


size_t upo_bst_rank(const upo_bst_t bst, const void *k) {

    if (bst == NULL)
    {
        return 0;
    }

    return upo_bst_rank_impl(bst->root, k, bst->key_cmp);
    
}

size_t upo_bst_rank_impl(upo_bst_node_t *n, const void *key, upo_bst_comparator_t key_cmp) {

    if (n == NULL)
    {
        return 0;
    }

    size_t sin = upo_bst_rank_impl(n->left, key, key_cmp);

    if (key_cmp(n->key, key) >= 0)
    {
        return sin;
    }

    size_t des = upo_bst_rank_impl(n->right, key, key_cmp);

    if (key_cmp(n->key, key) < 0)
    {
        return 1 + sin + des;
    }
    
}

void* upo_bst_get_value_depth(const upo_bst_t bst, const void *key, long *depth) {
    if (bst == NULL)
    {
        return NULL;
    }

    return upo_bst_get_value_depth_impl(bst->root, key, depth, bst->key_cmp);
    
}

void* upo_bst_get_value_depth_impl(upo_bst_node_t *n, const void *key, long *depth, upo_bst_comparator_t key_cmp) {

    if (n == NULL)
    {
        *depth = -1;
        return NULL;
    }

    if (key_cmp(n->key, key) == 0)
    {
        *depth = 0;
        return n->value;
    }

    if (key_cmp(n->key, key) > 0)
    {
        void *value = upo_bst_get_value_depth_impl(n->left, key, depth, key_cmp);
        if (value == NULL)
        {
            return NULL;
        }
        
        *depth = *depth+1;
        return value;
        
    }

    if (key_cmp(n->key, key) < 0)
    {
        void *value = upo_bst_get_value_depth_impl(n->right, key, depth, key_cmp);
        if (value == NULL)
        {
            return NULL;
        }
        
        *depth = *depth+1;
        return value;
    }
    
}

upo_bst_key_list_t upo_bst_keys_le(const upo_bst_t bst, const void *key) {

    if (bst == NULL)
    {
        return NULL;
    }

    upo_bst_key_list_t key_list = NULL;
    upo_bst_keys_le_impl(bst->root, key, &key_list, bst->key_cmp);

    return key_list;
    
}

upo_bst_key_list_t upo_bst_keys_le_impl(upo_bst_node_t *n, const void *key, upo_bst_key_list_t *key_list, upo_bst_comparator_t key_cmp) {

    if(n == NULL) return NULL;

    upo_bst_keys_le_impl(n->left, key, key_list, key_cmp);

    if (key_cmp(n->key, key) <= 0)
    {
        /*
        devo: 
        1. creare un nuovo nodo per aggiungerlo alla lista
        2. visitare il sottoalbero sinistro, che se non nullo conterrà elementi candidati
        */

       upo_bst_key_list_node_t *node_list = upo_bst_key_list_node_create();
       node_list->key = n->key;
       node_list->next = *key_list;
       *key_list = node_list;

       upo_bst_keys_le_impl(n->right, key, key_list, key_cmp);

    }
    
}

void* upo_bst_predecessor(const upo_bst_t bst, const void *key) {
    if (bst == NULL)
    {
        return NULL;
    }

    return upo_bst_predecessor_impl(bst->root, key, bst->key_cmp);
    
}

void* upo_bst_predecessor_impl(upo_bst_node_t *n, const void *key, upo_bst_comparator_t key_cmp) {

    if (n == NULL)
    {
        return NULL;
    }

    int cmp = key_cmp(key, n->key);
    /*CASO 1*/
    if (cmp == 0)
    {
        if (n->left != 0)
        {
            upo_bst_node_t *node_max = upo_bst_max_impl(n->left);
            if (node_max != NULL)
            {
                return node_max->key;
            }
            
            /*NULL*/
        }

        return NULL;
        
    }

    /*CASO 2*/
    if (cmp > 0)
    {
        /*possibile predecessore*/
        void *value = upo_bst_predecessor_impl(n->right, key, key_cmp);
        return (value != NULL) ? value : n->key;
    }
    
    /*CASO 3*/
    if (cmp < 0)
    {
        return upo_bst_predecessor_impl(n->left, key, key_cmp);
    }
    
}

void* upo_bst_subtree_max(const upo_bst_t tree, const void *key) {

    return upo_bst_subtree_max_impl(tree->root, 0, tree->key_cmp, key);
}

void* upo_bst_subtree_max_impl(upo_bst_node_t *n, int found, upo_bst_comparator_t key_cmp, const *key) {

    if (n == NULL)
    {
        return NULL;
    }

    if (found)
    {
        return upo_bst_max_impl(n);
    }
    else
    {
        if (key_cmp(n->key, key) > 0)
        {
            return upo_bst_subtree_max_impl(n->left, found, key_cmp, key);
        }
        else if(key_cmp(n->key, key) < 0)
        {
            return upo_bst_subtree_max_impl(n->right, found, key_cmp, key);
        }
        else
        {
            return upo_bst_subtree_max_impl(n, 1, key_cmp, key);
        }
    }
}

/**** EXERCISE #2 - END of EXTRA OPERATIONS ****/

upo_bst_comparator_t upo_bst_get_comparator(const upo_bst_t tree)
{
    if (tree == NULL)
    {
        return NULL;
    }

    return tree->key_cmp;
}
