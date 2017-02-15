/*
 * The MIT License (MIT)
 * Copyright (C) 2016 Marco Guerri
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in 
 * the Software without restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
 * Software, and to permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "list.h"
#include "test.h"

int 
print_integer_payload(void *ptr, char *str)
{
    return sprintf(str,"%d ", *((int*)ptr));
}

void 
test_list_init_creates_list_with_one_node()
{
    int el = 100;
    list_node_t *ptr_root =  list_init(&el, sizeof(int));
    _assert(ptr_root != NULL && 
            *((int*)ptr_root->data->payload) == 100 &&
            ptr_root->next == NULL &&
            ptr_root->prev == NULL);
    list_destroy(ptr_root);
}

void 
test_list_insert_at_end_appends()
{
    int el = 0, num_elements = 20, str_len = 0;
    uint8_t i;
    char test_result[512];

    for(i = 0; i < num_elements; ++i)
        str_len += snprintf(test_result + str_len, sizeof(test_result) - str_len, "%d ", i);

    list_node_t *ptr_root =  list_init(&el, sizeof(int));
    for(i = 1; i < num_elements; ++i)
        ptr_root = list_insert(ptr_root, &i, sizeof(int), i);
    
    char *list_printed = list_print(ptr_root, print_integer_payload);
    _assert(strcmp(list_printed, test_result) == 0);

    free(list_printed);
    list_destroy(ptr_root);
}


void
test_list_len_returns_correct_length()
{
    int el = 100;
    uint8_t num_err = 0, i = 0;
    
    if(list_len(NULL) != 0)
        ++num_err;
    
    list_node_t *ptr_root =  list_init(&el, sizeof(int));
    if(list_len(ptr_root) != 1)
        goto fail;

    for(i = 1; i < 100; ++i)
    {
        /* Inserting at the beginning */
        ptr_root = list_insert(ptr_root, &el, sizeof(int), 0);
        if(list_len(ptr_root) != i + 1)
            goto fail;
    }
    
    list_destroy(ptr_root);
    _assert(1);
    return;

fail:
   list_destroy(ptr_root);
    _assert(0);
}


void test_list_get_returns_correct_value()
{
    int el = 0;
    uint64_t i = 0;
    
    list_node_t *ptr_root =  list_init(&el, sizeof(int));

    for(i = 1; i < 100; ++i)
        ptr_root = list_insert(ptr_root, &i, sizeof(int), i);

    for(i = 0; i < 100; ++i)
    {
        int *test = list_get(ptr_root, i);
        if(*test != i)
            goto fail;
    }
    list_destroy(ptr_root);
    _assert(1);
    return;

fail:
    list_destroy(ptr_root);
    _assert(0);
    return;
}

void 
test_list_del_deletes_root()
{
    int el = 100;
    list_node_t *ptr_root =  list_init(&el, sizeof(int));
    ptr_root = list_del(ptr_root, &el, sizeof(int));
    _assert(ptr_root == NULL && list_len(ptr_root) == 0);
}


void 
test_list_del_deletes_at_the_end()
{

    int el1 = 100, el2 = 102, el3 = 102;
    list_node_t *ptr_root =  list_init(&el1, sizeof(int));
    ptr_root = list_insert(ptr_root, &el2, sizeof(int), list_len(ptr_root));
    ptr_root = list_insert(ptr_root, &el3, sizeof(int), list_len(ptr_root));
    
    ptr_root = list_del(ptr_root, &el3, sizeof(int));
    _assert(list_len(ptr_root) == 2 && 
            list_search(ptr_root, &el2, sizeof(int)) &&
            list_search(ptr_root, &el1, sizeof(int)));

    list_destroy(ptr_root);
}


void 
test_list_del_deletes_in_the_middle()
{

    int el1 = 100, el2 = 102, el3 = 102;
    list_node_t *ptr_root =  list_init(&el1, sizeof(int));
    ptr_root = list_insert(ptr_root, &el2, sizeof(int), list_len(ptr_root));
    ptr_root = list_insert(ptr_root, &el3, sizeof(int), list_len(ptr_root));
    
    ptr_root = list_del(ptr_root, &el2, sizeof(int));
    _assert(list_len(ptr_root) == 2 && 
            list_search(ptr_root, &el1, sizeof(int)) &&
            list_search(ptr_root, &el3, sizeof(int)));

    list_destroy(ptr_root);
}
