/* perching-panda.c
 *
 * Copyright 2021 Goutham Krishna K V
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name(s) of the above copyright
 * holders shall not be used in advertising or otherwise to promote the sale,
 * use or other dealings in this Software without prior written
 * authorization.
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct hashcell_node {
    int content;
    struct hashcell_node *next;
};

struct hashcell_node *hashcell_node_create(int                   content,
                                           struct hashcell_node *next)
{
    struct hashcell_node *newnode =
        (struct hashcell_node*)malloc(sizeof(struct hashcell_node));
    newnode->content = content;
    newnode->next = next;
    return newnode;
}

struct hashcell_node *hashcell_node_destroy(struct hashcell_node *node)
{
    if (node != NULL) {
        struct hashcell_node *next_node = node->next;
        free(node);
        return next_node;
    }
    return NULL;
}

struct hashcell {
    struct hashcell_node *top;
    size_t length;
};

struct hashcell *hashcell_create() {
    struct hashcell *newcell =
        (struct hashcell*)malloc(sizeof(struct hashcell));
    newcell->top = NULL;
    newcell->length = 0;
    return newcell;
}

void hashcell_destroy(struct hashcell *cell)
{
    if (cell != NULL)
    {
        struct hashcell_node *topval = cell->top;
        while (topval != NULL && cell->length > 0)
        {
            topval = hashcell_node_destroy (topval);
        }
        free(cell);
    }
}

bool hashcell_insert(struct hashcell *cell, int ele)
{
    if (cell != NULL)
    {
        cell->top = hashcell_node_create (ele, cell->top);
        cell->length++;
        return true;
    }
    return false;
}

void hashcell_print(struct hashcell *cell)
{
    if (cell != NULL)
    {
        struct hashcell_node *current = cell->top;
        while (current != NULL)
        {
            printf("%d ", current->content);
            current = current->next;
        }
        printf("\n");
    }
}

struct hashset {
    struct hashcell *elements;
    size_t length;
};

struct hashset *hashset_create(size_t length) {
    struct hashset *newset =
        (struct hashset*)malloc (sizeof(struct hashset));
    newset->elements = (struct hashcell*)malloc(sizeof(struct hashcell) * length);
    newset->length = length;
    return newset;
}

void hashset_destroy(struct hashset* set)
{
    if (set != NULL)
    {
        if (set->elements != NULL)
        {
            for(size_t i = 0; i < set->length; i++)
            {
                hashcell_destroy (&set->elements[i]);
            }
            free(set->elements);
        }
        free(set);
    }
}

void hashset_insert(struct hashset *set, int ele)
{
    size_t hashset_ins = (size_t)ele % set->length;
    hashcell_insert(&set->elements[hashset_ins], ele);
}

void hashset_print(struct hashset *set)
{
    if (set != NULL)
    {
        for(size_t i = 0; i < set->length; i++)
        {
            printf("%zu: ", i);
            hashcell_print (&set->elements[i]);
        }
    }
}

int
main (
    // int argc,
    // char *argv[]
)
{
    int arr[] = {1,2,67,3,5,734,6,4,23,324,245,2357};

    struct hashset *set = hashset_create (21);
     for(size_t i = 0; i < 12; i++)
    {
        hashset_insert (set, arr[i]);
    }
    hashset_print(set);
    return (0);
}
