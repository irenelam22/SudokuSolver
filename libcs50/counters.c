/* 
 * file: counters.c - CS50 'counter' module
 * author: David Kantor
 *
 * see counters.h for more information.
 * NOTE: a lot of this code was adjusted from the bag.c example provided
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "counters.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct node {
  int key;                 
  int count; 
  struct node *next;     
} node_t;

/*************** local functions ************/
static node_t *node_new(int key); // helper to allocate memory and initialize a new counter node

/**************** global types ****************/
typedef struct counters{
    struct node *head;
} counters_t;  // module for my counter data type


/**************** functions ****************/

/**************** counters_new ****************/
/* see counters.h for description */
counters_t *counters_new(void){
    counters_t *counters = calloc(1, sizeof(counters_t));
    if (counters == NULL){
        return NULL;              // handle a memory allocation error
    }
    else {
        counters->head = NULL;    // initialize the head to null
        return counters;
    }
}

/**************** counters_add ****************/
/* see counters.h for description */
int counters_add(counters_t *ctrs, const int key){
    if ( (ctrs != NULL) && ( key >= 0) ){
      if ( counters_get(ctrs, key) == 0){ // if the item does not exist in counters, add it
        node_t *new_node = node_new(key);
        if (new_node != NULL){           // as long as the memory allocation worked, add the node at the beginning of the list
          new_node->next = ctrs->head;
          ctrs->head = new_node;
        }
        else {
          return 0;
        }
      }
      else{
        for ( node_t *node = ctrs->head; node != NULL; node = node->next) { // if the item is in the list already...
            if ( node->key == key){                               // note: key will be an int so can compare with ==
                node->count ++;                                   // increment its count
                return node->count;
            }
        }
      }
    }
    return 0;
}

/**************** counters_get ****************/
/* see counters.h for description */
int counters_get(counters_t *ctrs, const int key){
    if ( (ctrs != NULL) && (key >= 0) ){
          for ( node_t *node = ctrs->head; node != NULL; node = node->next) { // loop through list
              if ( node->key == key){                    // try to find a match with the given key
                  return node->count;
              }
          }
            return 0;
    }
    else{
        return 0;
    }
}

/**************** counters_set ****************/
/* see counters.h for description */
bool counters_set(counters_t *ctrs, const int key, const int count){
    if ( (ctrs != NULL) && (key >= 0 ) && (count >= 0)){
      if (counters_get(ctrs, key) == 0){      // if the key doesn't exist within ctrs, make a new node
        node_t *new_node = node_new(key);
        if ( new_node != NULL){               // only proceed if the memory was allocated properly
          new_node->next = ctrs->head;        // insert the node at the beginning of the linked list
          ctrs->head = new_node;
          new_node->count = count;            // set the count
          return true;
        }
        else{
          return false;
        }
      }
      else {                    // if the key already exists within ctrs, find the node and update its count
          for ( node_t *node = ctrs->head; node != NULL; node = node->next) { 
            if ( node->key == key){
                node->count = count;
                return true;
            }
          }
          return false;
      }
    }
    else{
        return false;
    }
}

/**************** counters_print ****************/
/* see counters.h for description */
void counters_print(counters_t *ctrs, FILE *fp){
    if (fp != NULL) {                                                       // ignore if fp doesn't exist/is invalid
      if (ctrs != NULL) {
        fputc('{', fp);
        for ( node_t *node = ctrs->head; node != NULL; node = node->next) { // loop over all nodes
          // print this node
          fprintf(fp, "{%d,%d}, ", node->key, node->count);                 // print the key and the count
        }
        fputc('}', fp);
        fputc('\n', fp);                                                    // add newline for visual purposes
      } else {                                                              // handle a NULL ctrs
          fputs("(null)", fp);
      }
    }
  }

/**************** counters_iterate ****************/
/* see counters.h for description */
void counters_iterate(counters_t *ctrs, void *arg, void (*itemfunc)(void *arg, const int key, const int count)){
  if (ctrs != NULL && itemfunc != NULL) {
    // call itemfunc with arg, on each item
    for (node_t *node = ctrs->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->count);                           // dereference and execute the function
    }
  }
}

/**************** counters_delete ****************/
/* see counters.h for description */
void counters_delete(counters_t *ctrs){
    if (ctrs != NULL) {
      for ( node_t *node = ctrs->head; node != NULL; ) {
        node_t *next = node->next;     // remember what comes next
        free(node);                    // free the node
        node = next;                   // and move on to next
      }
    free(ctrs);                        // free the entire ctrs object
  }
}

/**************** helper to add a new node ****************/

static node_t *node_new(int key){
  node_t *node = calloc(1, sizeof(node_t));
  if ( node == NULL ){
    return NULL;
  }
  else{
    // initialize the variables for the node
    node->key = key;
    node->count = 1;
    return node;
  }
}
