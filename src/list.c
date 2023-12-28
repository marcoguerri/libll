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
#include <libll/ll.h>

#define LLIST_PRINT_BUFF_SIZE             16
#define LLIST_REALLOC_THRESHOLD           8


/**
 * @brief Frees a node and associated dynamically allocated memory
 */
void 
_ll_free_node(ll_node_t* ptr_node)
{
    if(ptr_node == NULL) {
        return;
    }
    free(ptr_node->data->payload);
    free(ptr_node->data);
    free(ptr_node);
}


/**
 * @brief Initializes a new list with a single root node
 * @param payload Payload of the root node
 * @param Size of each data element within the list
 */
ll_t*
ll_init(void *payload, size_t size)
{
    if(payload == NULL || size <= 0)
        return NULL;

    ll_t* ptr_list = (ll_t*)malloc(sizeof(ll_t));
    if(ptr_list == NULL)
    {
        perror("malloc:");
        goto err_list;
    }
    ptr_list->element_size = size;
    ll_node_t* ptr_node = (ll_node_t*)malloc(sizeof(ll_node_t));
    if(ptr_node == NULL)
    {
        perror("malloc:");
        goto err_node;
    }
    ll_data_t *ptr_data = (ll_data_t*)malloc(sizeof(ll_data_t));
    if(ptr_data == NULL)
    {
        perror("malloc");
        goto err_data;
    }
    void *ptr_payload = (void*)malloc(size);
    if(ptr_payload == NULL)
    {
        perror("malloc");
        goto err_payload;
    }

    memcpy(ptr_payload, (char *)payload, size);

    ptr_data->payload = ptr_payload;
    ptr_node->data = ptr_data;
    ptr_node->next = NULL;
    ptr_node->prev = NULL;
    ptr_list->root = ptr_node;

    assert(ptr_node != NULL);
    assert(ptr_node->data != NULL);
    assert(ptr_node->data->payload != NULL);
    assert(ptr_node->next == NULL);
    assert(ptr_node->prev == NULL);

    return ptr_list;

err_payload:
    free(ptr_payload); 
err_data:
    free(ptr_data);
err_node:
    free(ptr_node);
err_list:
    free(ptr_list);
    return NULL;
}


char*
ll_print(ll_t *ptr_list, int (*print)(void*, char*))
{
    size_t curr_buff_size = LLIST_PRINT_BUFF_SIZE;

    if(ptr_list == NULL || print == NULL) {
        return NULL;
    }

    char *buff = (char*)malloc(sizeof(char)*LLIST_PRINT_BUFF_SIZE);
    if(buff == NULL) {
	perror("malloc:");
	goto free_buff;
    }
    memset(buff, 0, LLIST_PRINT_BUFF_SIZE);

    int written = 0;
    size_t buff_ptr = 0;
    ll_node_t* root = ptr_list->root;
    while(root != NULL)
    {
        written =  (*print)(root->data->payload, buff + buff_ptr);
        if(written == -1)
        {
            free(buff);
            return NULL;
        }

        buff_ptr += written;
        if(buff_ptr  > curr_buff_size - LLIST_REALLOC_THRESHOLD)
        {
            char *new_buff = (char*)realloc(buff, sizeof(char)*(curr_buff_size*2));
            if(new_buff == NULL) 
            {
                /* Old buffer has not been freed */
                free(buff); 
                perror("realloc");
                return NULL;
            }
            buff = new_buff;
            memset(buff + buff_ptr, 0, curr_buff_size);
            curr_buff_size = curr_buff_size*2;
        }
        root = root->next;
    }
    return buff;

free_buff:
    free(buff);
    return NULL;
}


/**
 * @brief Frees all nodes in the list
 * @param ptr_list Pointer to the list
 */
void
ll_destroy(ll_t *ptr_list)
{

    if(ptr_list == NULL) {
        return;
    }
    ll_node_t* root = ptr_list->root;

    /* Free the list staring from root onwards */
    if(root != NULL && root->prev != NULL)
        root->prev->next = NULL;

    while(root != NULL)
    {
        ll_node_t* next = root->next;
        free(root->data->payload);
        free(root->data);
        free(root);
        root = next;
    }
    free(ptr_list);
}

/**
 * @brief Returns the size of the list
 */
size_t 
ll_len(ll_t* ptr_list)
{
    size_t len = 0;
    if(ptr_list == NULL)
        return 0;

    ll_node_t* root = ptr_list->root;
    while(root != NULL)
    {
        ++len;
        root = root->next;
    }
    return len;
}

/*
 * @brief Inserts a new node in position pos
 * @param ptr_list Pointer to the list. If null, a new list is initialized
 * @param pos Position, indexed from 0, where to add the new node
 * @return Pointer to the new list or NULL upon failure. When returning
 * NULL the old list is NOT destroyed.
 */
ll_t*
ll_insert(ll_t* ptr_list, void *payload, size_t pos)
{
    if(payload == NULL || ptr_list == NULL || pos > ll_len(ptr_list))
        return NULL;
    
    
    ll_node_t *ptr_prev = NULL, *ptr_pos = ptr_list->root;
    while(pos > 0)
    {
        ptr_prev = ptr_pos;
        /* Checked pos against the length of the list */
        assert(ptr_pos != NULL);
        ptr_pos = ptr_pos-> next;
        --pos;
    }
    ll_node_t *ptr_node = (ll_node_t*)malloc(sizeof(ll_node_t));
    if(ptr_node == NULL)
    {
        perror("malloc");
        goto err_node;
    }
    ll_data_t* ptr_data = (ll_data_t*)malloc(sizeof(ll_data_t));
    if(ptr_data == NULL)
    {
        perror("malloc");
        goto err_data;
    }
    ptr_data->payload = (void*)malloc(ptr_list->element_size);
    if(ptr_data->payload == NULL)
    
    {
        perror("malloc");
        goto err_payload;
    }

    if(ptr_pos == NULL) 
    {
        /* Appending at the end */
        assert(ptr_node != NULL && ptr_prev != NULL);
        ptr_node->next = NULL;
        ptr_node->prev = ptr_prev;
        ptr_prev->next = ptr_node;
    }
    else if(ptr_pos->prev == NULL)
    {
        /* Beginning of the list */
        assert(ptr_node != NULL && ptr_pos != NULL);
        ptr_node->next = ptr_list->root;
        ptr_node->prev = NULL;
        ptr_pos->prev = ptr_node;
        /* The node just allocated is the new root  */
        ptr_list->root = ptr_node;
    }
    else
    {  
        /* Adding in the middle */ 
        assert(ptr_node != NULL && ptr_pos != NULL && ptr_pos->prev != NULL);
        ptr_node->next = ptr_pos;
        ptr_node->prev = ptr_pos->prev;
        ptr_pos->prev = ptr_node;
        ptr_pos->prev->next = ptr_node;
    }
    memcpy(ptr_data->payload, (char *)payload, ptr_list->element_size);
    ptr_node->data = ptr_data;
    return ptr_list;

err_payload:
    free(ptr_data);
err_data:
    free(ptr_node);
err_node:
    return NULL;
}

/**
 * @brief Deletes the first node which matches the payload passed as argument
 * @param payload Paylod to delete
 * @return The pointer to the new list
 */
ll_t*
ll_del(ll_t* ptr_list, void* payload)
{
 
    if(ptr_list == NULL || payload == NULL) {
        return NULL;
    }

    ll_node_t *ptr_node = ptr_list->root;
    while(ptr_node != NULL) 
    {
        if(memcmp(ptr_node->data->payload, payload, ptr_list->element_size) == 0)
        {
            if(ptr_node->prev == NULL)
            {
                /* First node of the list */
                if(ptr_node->next != NULL)
                {
                   /* First node is followed by at least one more node */
                   ptr_node->next->prev = NULL;
                   ptr_list->root = ptr_node->next;
                   _ll_free_node(ptr_node);
                   return ptr_list;
                }
                else
                {
                    /* First node is the only one in the list */
                    _ll_free_node(ptr_node);
		    ptr_list->root = NULL;
                    return ptr_list;
                }
            }
            else
            {
                /* Node is not the first in the list */
                if(ptr_node->next != NULL)
                {
                    /* Node is followed by at least one more node */
                    ptr_node->next->prev = ptr_node->prev;
                    ptr_node->prev->next = ptr_node->next;
                    _ll_free_node(ptr_node);

                }
                else
                { 
                    /* Node is the last in the list */
                    ptr_node->prev->next = NULL;
                    _ll_free_node(ptr_node);
                }
                return ptr_list;
            }
        }
        ptr_node = ptr_node->next;
    }
    return ptr_list;
}


/**
 * @brief Returns a pointer to the first node with matching payload
 * @param ptr_list Pointer to the list
 * @param payload Payload to be searched in the list
 * @return Pointer to the first node with matching payload or NULL if payload
 * is not found
 */
ll_node_t*
ll_search(ll_t* ptr_list, void* payload)
{
    if(ptr_list == NULL || payload == NULL) {
        return NULL;
    }
    ll_node_t* ptr_root = ptr_list->root;
    while(ptr_root != NULL)
    {
        if(memcmp(ptr_root->data->payload, payload, ptr_list->element_size) == 0)
            return ptr_root;
        else
            ptr_root = ptr_root->next;
    }
    return NULL;   
}


/**
 * @brief Returns a pointer to the node in position pos
 * @param ptr_list Pointer to the list
 * @param pos position, indexed from 0, of the element to be returned
 * @return Pointer to node in position pos or NULL upon failure
 */
ll_node_t*
ll_node_get(ll_t *ptr_list, size_t pos)
{
    if(ptr_list == NULL) {
        return NULL;
    }
    ll_node_t* ptr_root = ptr_list->root;
    if(ptr_root == NULL || pos >= ll_len(ptr_list))
        return NULL;
    while(pos > 0)
    {
        /* pos was checked against the length of the list, can't be null at this point */
        assert(ptr_root != NULL);
        ptr_root = ptr_root->next;
        --pos;
    }
    return ptr_root;

}

/**
 * @brief Returns the payload pointed to by a node
 * @param ptr_node Pointer to the node
 * @return Pointer to the payload of the node
 */
void*
ll_node_payload(ll_node_t* ptr_node)
{
     
    if(ptr_node == NULL || ptr_node->data == NULL)
        return NULL;
    else
        return ptr_node->data->payload;
}

/**
 * @brief Returns a pointer to the node which follows the one passed as paramter
 * @param ptr_node Pointer to the current node
 * @return Pointer to the next node, NULL if the node is last
 */
ll_node_t*
ll_node_next(ll_node_t* ptr_node)
{
    if(ptr_node == NULL)
        return NULL;
    else
        return ptr_node->next;
}

/**
 * @brief Returns a pointer to the node which comes before the one passed as parameter
 * @param ptr_node Pointer to the current node
 * @return Pointer to the previous node, NULL if the node is the root
 */
ll_node_t*
ll_node_prev(ll_node_t* ptr_node)
{
    if(ptr_node == NULL)
        return NULL;
    else
        return ptr_node->prev;
}
