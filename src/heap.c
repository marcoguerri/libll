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
#include "heap.h"

#define HEAP_DEFAULT_SIZE 10

/**
 * @brief Initializes a heap with a single element of size
 */
heap_t* 
heap_init(void *payload, size_t size )
{
    if(payload == NULL || size <= 0)
        return NULL;

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

    heap_t *ptr_heap = (heap_t*)malloc(sizeof(heap_t));
    if(ptr_heap == NULL) 
    {
        perror("malloc");
        goto err_heap;
    }

    /* Allocating space for HEAP_DEFAULT_SIZE pointers heap_element_t* and 
     * setting fillup coefficient */
    ptr_heap->heap_data = (heap_element_t**)malloc(sizeof(heap_element_t*)*HEAP_DEFAULT_SIZE);
    if(ptr_heap->heap_data == NULL) 
    {
        perror("malloc");
        goto err_heap_data;
    }

    ptr_heap->heap_data[0] = ptr_element;
    ptr_heap->size = HEAP_DEFAULT_SIZE;
    ptr_heap->fill = 1;

    assert(ptr_heap->heap_data != NULL);
    assert(ptr_heap->size == HEAP_DEFAULT_SIZE);
    assert(ptr_heap->fill = 1);

    return ptr_heap;

err_heap_data:
    free(ptr_heap->heap_data);
err_heap:
    free(ptr_heap);
err_payload:
    free(ptr_element->payload); 
err_element:
    free(ptr_element);
    return NULL;
}


/**
 * @brief Returns a pointer to element in position pos inside the heap
 * @param heap Pointer to the heap
 * @param pos 0-indexed position of the element to return
 * @return Pointer to the payload of the n-th element of the list or NULL upon
 * failure
 */
void*
heap_get(heap_t* heap, size_t pos)
{

    if(pos >= heap->fill)
        return NULL;
    
    return heap->heap_data[pos]->payload;
}

