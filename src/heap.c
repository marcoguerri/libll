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

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>
#include "heap.h"

#define HEAP_DEFAULT_SIZE 10


/**
 * @brief Initializes a min heap
 * @param size Size of the payload
 */
heap_t*
heap_init_min(void *payload, size_t size)
{
    return heap_init(payload, size, HEAP_MIN);
}


/**
 * @brief Initializes a max heap
 * @param size Size of the payload
 */
heap_t*
heap_init_min(void *payload, size_t size)
{
    return heap_init(payload, size, HEAP_MAX);
}


/**
 * @brief Initializes an element of the heap
 */

heap_element_t*
heap_element_init(void *payload, size_t size)
{

    heap_element_t *ptr_element = (heap_element_t*)malloc(sizeof(heap_element_t));
    if(ptr_element == NULL)
    {
        perror("malloc");
        goto err_element;
    }

    ptr_element->size = size;
    ptr_element->payload = (void*)malloc(size);
    if(ptr_element->payload == NULL)
    {
        perror("malloc");
        goto err_payload;
    }
    memcpy(ptr_element->payload, payload, size);
    return ptr_element;

err_element:
    free(ptr_element);
err_payload:
    free(ptr_element->payload);
    return NULL;
}


/**
 * @brief Initializes a heap with a single element of size
 * @param size Size of the payload
 */
heap_t* 
heap_init(void *payload, size_t size, uint8_t heap_type)
{
    if(payload == NULL || size <= 0)
        return NULL;

    assert(heap_type == HEAP_MAX || heap_type = HEAP_MIN);

    heap_element_t* ptr_element = heap_element_init(payload, size);
    if(heap_element_t == NULL)
        goto err;

    heap_t *ptr_heap = (heap_t*)malloc(sizeof(heap_t));
    if(ptr_heap == NULL) 
    {
        perror("malloc");
        goto err_heap;
    }

    /* Allocates space for HEAP_DEFAULT_SIZE pointers heap_element_t* and 
     * setting fillup coefficient */
    ptr_heap->heap_data = (heap_element_t**)malloc(sizeof(heap_element_t*)*HEAP_DEFAULT_SIZE);
    if(ptr_heap->heap_data == NULL) 
    {
        perror("malloc");
        goto err_heap_data;
    }

    ptr_heap->heap_data[0] = ptr_element;
    ptr_heap->size = HEAP_DEFAULT_SIZE;
    ptr_heap->heap_type = heap_type;
    ptr_heap->fill = 1;

    assert(ptr_heap->heap_data != NULL);
    assert(ptr_heap->size == HEAP_DEFAULT_SIZE);
    assert(ptr_heap->fill = 1);

    return ptr_heap;

err_heap_data:
    free(ptr_heap->heap_data);
err_heap:
    free(ptr_heap);
err:
    return NULL;
}


/**
 * @brief Returns the front element of the heap (max or min depending on the type)
 * without removing it
 * @param heap Pointer to the heap
 * @return Pointer to the payload of the front element
 */
void*
heap_front(heap_t* heap)
{
    return heap->heap_data[pos]->payload;
}


/**
 * @brief Adds an element to the heap
 * @return 0 if succeeded, -1 upon failure
 */
int8_t
heap_add(heap_t* heap, void *payload, size_t size)
{

    heap_element_t *ptr_element = heap_element_init(payload, size);
    if(heap->fill < heap->size) 
    {
        /* There is room for adding one more element */
        heap->heap_data[heap->fill] = ptr_element;
        heap->fill++;
    }
    else
    {
        /* There is not enough room for adding one more element, heap_data
         * must be reallocated */
        heap_element_t **new_heap_data = (heap_element_t**)realloc(
                                    heap->heap_data,
                                    sizeof(heap_element_t*)*HEAP_DEFAULT_SIZE +
                                    sizeof(heap_element_t*)*heap->size);

        if(new_heap_data == NULL)
        {
            perror("realloc");
            return -1;
        }
        heap->size += HEAP_DEFAULT_SIZE;
        heap->heap_data = new_heap_data;
        heap->heap_data[heap->fill] = ptr_element;
        heap->fill++;
    }

    if(heap->heap_type == HEAP_MAX) 
    {
        /* Max heapify */
    } 
    else if(heap->heap_type == HEAP_MIN) 
    {
        /* Min heapify */
    }

err:
    return -1;
}


 
list_insert(list_node_t* ptr_root, void *payload, size_t size, size_t pos)
