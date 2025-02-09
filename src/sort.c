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

#include <assert.h>
#include "sort_private.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void upo_insertion_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    unsigned char *pBase = (unsigned char *) base;
    unsigned char *tmp = malloc(size);

    size_t i, j;

    for(i=1; i <= n-1; i++) {

        j = i;
        while(j>0 && (cmp(pBase + j*size, pBase + (j-1) * size) < 0)) {

            if(tmp == NULL) {
                perror("malloc failed");
                abort();
            }

            memmove(tmp, pBase + (j-1) * size, size);
            memmove(pBase + (j-1) * size, pBase + j * size, size);
            memmove(pBase + j * size, tmp, size);

            j--;
        }
    }

    free(tmp);
}

void upo_merge_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp)
{
    /* TO STUDENTS:
     *  Remove the following two lines and put here your implementation. */
    upo_merge_sort_rec(base, 0, n-1, size, cmp);
}

void upo_merge_sort_rec(void *base, size_t lo, size_t hi, size_t size, upo_sort_comparator_t cmp) {
    
    if(lo >= hi) 
        return;

    size_t mid = (lo + hi)/2;

    upo_merge_sort_rec(base, lo, mid, size, cmp);
    upo_merge_sort_rec(base, mid+1, hi, size, cmp);
    upo_merge(base, lo, mid, hi, size, cmp);
}

void upo_merge(void *base, size_t lo, size_t mid, size_t hi, size_t size, upo_sort_comparator_t cmp) {

    size_t i = 0;
    size_t j = (mid+1)-lo;

    unsigned char *pBase = (unsigned char *) base;
    unsigned char *aux = (unsigned char *)malloc(size*(hi-lo+1));
    memmove(aux, pBase + lo*size, size*(hi-lo+1));

    for(size_t k = lo; k <= hi; k++) {
        if(i > (mid-lo)) {
            memmove(pBase + k*size, aux + j*size, size);
            j++;
        }
        else if(j > (hi-lo)) {
            memmove(pBase + k*size, aux + i*size, size); 
            i++;
        }
        else if(cmp(aux + j*size, aux + i*size) < 0) {
            memmove(pBase + k*size, aux + j*size, size);
            j++;
        }
        else {
            memmove(pBase + k*size, aux + i*size, size);
            i++;
        }
    }

    free(aux);
}

void swap(void *a, void *b, size_t size) {
    unsigned char tmp[size];
    memmove(tmp, a, size);
    memmove(a, b, size);
    memmove(b, tmp, size);
}

void upo_quick_sort(void *base, size_t n, size_t size, int (*cmp)(const void *, const void *)) {
    if (base == NULL || n <= 1 || size == 0 || cmp == NULL) {
        return;
    }
    upo_quick_sort_rec(base, 0, n - 1, size, cmp);
}

void upo_quick_sort_rec(void *base, size_t lo, size_t hi, size_t size, int (*cmp)(const void *, const void *)) {
    if (lo >= hi) {
        return;
    }

    size_t pivot = upo_partition(base, lo, hi, size, cmp);
    
    if (pivot > 0) {
        upo_quick_sort_rec(base, lo, pivot - 1, size, cmp);
    }
    upo_quick_sort_rec(base, pivot + 1, hi, size, cmp);
}

size_t upo_partition(void *base, size_t lo, size_t hi, size_t size, int (*cmp)(const void *, const void *)) {
    size_t pivot = lo;
    size_t i = lo;
    size_t j = hi + 1;

    unsigned char *pBase = (unsigned char *)base;

    while (1) {
        do { i++; } while (i < hi && cmp(pBase + size * i, pBase + size * pivot) < 0);
        do { j--; } while (j > lo && cmp(pBase + size * j, pBase + size * pivot) > 0);

        if (i >= j) {
            break;
        }

        swap(pBase + size * i, pBase + size * j, size);
    }

    swap(pBase + size * pivot, pBase + size * j, size);
    return j;
}

void upo_bubble_sort(void *base, size_t n, size_t size, upo_sort_comparator_t cmp) {

    unsigned char *pBase = (unsigned char *)base;

    size_t changed, stop = 0;

    while (stop != 1)
    {
        changed = 0;
        for (size_t i = 1; i < n; i++)
        {
            if(cmp(pBase + size * (i-1), pBase + size * i) > 0) {
                swap(pBase + size * (i-1), pBase + size * i, size);
                changed++;
            }
        }

        if (changed == 0)
        {
            stop = 1;
            break;
        }
        
        
        
    }
    
    

}