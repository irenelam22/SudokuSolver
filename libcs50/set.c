/* 
 * file: counters.c - CS50 'set' module
 * author: David Kantor
 *
 * see set.h for more information.
 * NOTE: a lot of this code was adjusted from the bag.c example provided
 *
 * CS50 
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

typedef struct setnode {
  char *key;                 // key will be a string pointer
  void *item;                // item can be any data type
  struct setnode *next;       // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
  struct setnode *head;       // head of the list of items in bag
} set_t;

/**************** local function declarations ****************/
static setnode_t *node_new(char *key, void *item);

/**************** functions ****************/

/**************** set_new ****************/
/* see set.h for description */
set_t *set_new(void){
    set_t *set = calloc(1, sizeof(set_t)); // alocate memory for the set
    if (set == NULL){
        return NULL; // handle memory allocation error
    }
    else{
        set->head = NULL;
        return set;
    }
}

/**************** set_insert ****************/
/* see set.h for description */
bool set_insert(set_t *set, const char *key, void *item){
    // note: need to check that the key, item, and set exists, and that the key is not in set already
    if ( (key != NULL) && (item != NULL) && (set != NULL) && (set_find(set, key) == NULL)){ 
        char *key_copy = malloc(strlen(key) + 1); // need to allocate enough memory for the entire string (length + 1)
        strcpy(key_copy, key);                    // copy the key variable into the new pointer
        if ( (key_copy != NULL) ){                // only proceed if the key was copied properly
            setnode_t *new_node = node_new(key_copy, item);
            if ( (new_node != NULL)){             // make sure the key does not already exist
                new_node->next = set->head;       // insert the node at the beginning of the linked list
                set->head = new_node;
                return true;
            }
            else{
                return false;
            }
        }
        else{
            return false;
        }
    }
    else{
        return false;
    }
}

/**************** set_find ****************/
/* see set.h for description */
void *set_find(set_t *set, const char *key){
    if ( (set != NULL) && (key != NULL)){
        for ( setnode_t *node = set->head; node != NULL; node = node->next) { // search through all of the set nodes
            if ( strcmp(key, node->key) == 0){         // if the given key string matches any of the given node keys
                return node->item;                     // return that item
            }
        }
        return NULL;
    }
    else{
        return NULL;
    }
}

/**************** set_print ****************/
/* see set.h for description */
void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item) ){
    if (fp != NULL) {
      if (set != NULL) {
        fputc('{', fp);
        for (setnode_t *node = set->head; node != NULL; node = node->next) {
          // print this node
          if (itemprint != NULL) { // print the node's item (function provided in test)
            (*itemprint)(fp, node->key, node->item); // note: need to use void because generic item type
            fputc(',', fp);
          }
        }
        fputc('}', fp);
        fputc('\n', fp);
      } else {
        fputs("(null)", fp);
      }
    }
}

/**************** set_iterate ****************/
/* see set.h for description */
void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) ){
    if (set != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
      for (setnode_t *node = set->head; node != NULL; node = node->next) {
        (*itemfunc)(arg, node->key, node->item); // dereference and execute the function
      }
    }
}

/**************** set_delete ****************/
/* see set.h for description */
void set_delete(set_t *set, void (*itemdelete)(void *item) ){
    if (set!= NULL) {
      for (setnode_t *node = set->head; node != NULL; ) {
        if (itemdelete != NULL) {         // if possible...
          (*itemdelete)(node->item);      // delete node's item
        }
        setnode_t *next = node->next;     // remember what comes next
        free(node->key);                  // have to free the string for the key that we allocated
        free(node);                       // free the node
        node = next;                      
    }

    free(set);                            // need to free the entire set             
  }
}

/************  helper to create a new node ************/
static setnode_t *node_new(char *key, void *item){ // use static modifier because local function
  setnode_t *node = calloc(1, sizeof(setnode_t));
  if ( node == NULL ){                            // return NULL right away if the memory was not allocated properly
    return NULL;
  }
  else {                                          // initialize the node's variables
    node->key = key;
    node->item = item;
    return node;
  }
}
