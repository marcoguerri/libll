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

#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

typedef struct {
    void *payload;
} ll_data_t;

typedef struct ll_node_t_internal {
    ll_data_t *data;
    struct ll_node_t_internal *next;
    struct ll_node_t_internal *prev;
} ll_node_t;

typedef struct {
    ll_node_t* root;
    size_t element_size;
} ll_t;

ll_t* ll_init(void *payload, size_t size);
void ll_destroy(ll_t* ptr_list);
char* ll_print(ll_t* ptr_list, int(print)(void*, char *));
size_t ll_len(ll_t* ptr_list);
ll_t* ll_insert(ll_t* ptr_list, void *payload, size_t pos);
ll_node_t* ll_node_get(ll_t* ptr_list, size_t pos);
void* ll_node_payload(ll_node_t* ptr_node);
ll_t* ll_del(ll_t* ptr_list, void* payload);
ll_node_t* ll_search(ll_t* ptr_list, void* payload);
#endif
