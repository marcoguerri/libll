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
#include <libll/ll.h>
#include "test.h"

int
print_integer_payload(void *ptr, char *str)
{
    return sprintf(str,"%d ", *((uint8_t*)ptr));
}

void 
test_list_init_creates_list_with_one_node()
{
    uint8_t data = 100;
    ll_t *ptr_list =  ll_init(&data, sizeof(uint8_t));
    _assert(ptr_list != NULL);
    _assert(ptr_list->root != NULL);
    _assert(ptr_list->root->next == NULL && ptr_list->root->prev == NULL);
    _assert(*((uint8_t*)ptr_list->root->data->payload) == 100);
    ll_destroy(ptr_list);
}

void 
test_list_insert_at_end_appends()
{
    uint8_t data = 0, str_len = 0;
    uint8_t i, max_element = 20;
    char list_repr_test[512];

    ll_t* ptr_list =  ll_init(&data, sizeof(int));
   
    for(i = 0; i < max_element; ++i)
        str_len += snprintf(list_repr_test + str_len, 512 - str_len, "%d ", i);
    for(i = 1; i < max_element; ++i)
        ptr_list = ll_insert(ptr_list, &i, i);
    
    char *list_repr = ll_print(ptr_list, print_integer_payload);
    _assert(strcmp(list_repr, list_repr_test) == 0);
    free(list_repr);
    ll_destroy(ptr_list);
}


void
test_list_len_returns_correct_length()
{
    uint8_t data = 102;
    uint8_t i = 0, max_element = 100;

    _assert(ll_len(NULL) == 0);
    
    ll_t *ptr_list =  ll_init(&data, sizeof(uint8_t));
    _assert(ll_len(ptr_list) == 1);

    for(i = 1; i < max_element; ++i)
    {
        /* Repeatedly inserting at the beginning */
        ptr_list = ll_insert(ptr_list, &data, 0);
        if(ll_len(ptr_list) != i + 1)
        {
            _assert(0);
            ll_destroy(ptr_list);
            return;
        }
    }
    _assert(1);
    ll_destroy(ptr_list);
    return;
}


void test_list_get_returns_correct_value()
{
    uint8_t data = 0, i, max_element = 100;
    
    ll_t* ptr_list =  ll_init(&data, sizeof(uint8_t));

    for(i = 1; i < max_element; ++i)
        ptr_list = ll_insert(ptr_list, &i, i);
    for(i = 0; i < max_element; ++i)
    {
        ll_node_t* ptr_node = ll_node_get(ptr_list, i);
        if(*((uint8_t*)ll_node_payload(ptr_node)) != i)
        {
            _assert(0);
            ll_destroy(ptr_list);
            return;
        }
    }
    _assert(1);
    ll_destroy(ptr_list);
    return;
}

void 
test_list_del_deletes_root()
{
    uint8_t data = 100;
    ll_t* ptr_list =  ll_init(&data, sizeof(uint8_t));
    ptr_list = ll_del(ptr_list, &data);
    _assert(ptr_list == NULL);
    _assert(ll_len(ptr_list) == 0);
}


void 
test_list_del_deletes_at_the_end()
{
    uint8_t data_a = 100, data_b = 101, data_c = 102;
    ll_t *ptr_list = ll_init(&data_a, sizeof(uint8_t));
    ptr_list = ll_insert(ptr_list, &data_b, ll_len(ptr_list));
    ptr_list = ll_insert(ptr_list, &data_c, ll_len(ptr_list));
    
    ptr_list = ll_del(ptr_list, &data_c);
    _assert(ll_len(ptr_list) == 2);
    _assert(ll_search(ptr_list, &data_b) != NULL);
    _assert(ll_search(ptr_list, &data_a) != NULL);

    ll_destroy(ptr_list);
}


void 
test_list_del_deletes_in_the_middle()
{

    uint8_t data_a = 100, data_b = 101, data_c = 102;
    ll_t *ptr_list = ll_init(&data_a, sizeof(uint8_t));
    ptr_list = ll_insert(ptr_list, &data_b, ll_len(ptr_list));
    ptr_list = ll_insert(ptr_list, &data_c, ll_len(ptr_list));
    
    ptr_list = ll_del(ptr_list, &data_c);
    _assert(ll_len(ptr_list) == 2);
    _assert(ll_search(ptr_list, &data_b) != NULL);
    _assert(ll_search(ptr_list, &data_a) != NULL);

    ll_destroy(ptr_list);
}
