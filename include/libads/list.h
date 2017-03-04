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
} ads_list_data_t;

typedef struct ads_list_node_t_internal {
    ads_list_data_t *data;
    struct ads_list_node_t_internal *next;
    struct ads_list_node_t_internal *prev;
} ads_list_node_t;

typedef struct {
    ads_list_node_t* root;
    size_t element_size;
} ads_list_t;

ads_list_t* ads_list_init(void *payload, size_t size);
void ads_list_destroy(ads_list_t* ptr_list);
char* ads_list_print(ads_list_t* ptr_list, int(print)(void*, char *));
size_t ads_list_len(ads_list_t* ptr_list);
ads_list_t* ads_list_insert(ads_list_t* ptr_list, void *payload, size_t pos);
ads_list_node_t* ads_list_node_get(ads_list_t* ptr_list, size_t pos);
void* ads_list_node_payload(ads_list_node_t* ptr_node);
ads_list_t* ads_list_del(ads_list_t* ptr_list, void* payload);
ads_list_node_t* ads_list_search(ads_list_t* ptr_list, void* payload);
#endif
