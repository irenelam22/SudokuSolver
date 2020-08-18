/* 
 * file: hashtable.c - CS50 'hashtable' module
 * author: David Kantor
 *
 * see hashtable.h for more information.
 * NOTE: a lot of this code was adjusted from the bag.c example provided
 * SECOND NOTE: a lot of this code relies on set.c 
 *
 * CS50 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"
#include "./set.h"
#include "./jhash.h"

/**************** global types ****************/
typedef struct hashtable {
    set_t **table_slots; // pointer to an array of set pointers
    int num_slots;       // will need to keep track of size of our hashtable
} hashtable_t;           // opaque to users of the module


/**************** functions ****************/

/**************** hashtable_new ****************/
/* see hashtable.h for description */
hashtable_t *hashtable_new(const int num_slots){
    if (num_slots > 0){
        hashtable_t *hashtable = calloc(1, sizeof(hashtable_t));        // allocate memory for the hashtable
        if (hashtable != NULL){
            hashtable->num_slots = num_slots;                           // initialize number of slots
            hashtable->table_slots = calloc(num_slots, sizeof(set_t*)); // allocate memory for the slots (use set size)
            if ( hashtable->table_slots != NULL ){                      // make sure the memory allocation work
                for ( int i = 0; i < num_slots; i++ ){                  // if it did work...
                    hashtable->table_slots[i] = set_new();              // put a set in each slot
                }
                return hashtable;
            } 
            else{
                return NULL;
            }
        }
        else{
            return NULL;
        }
    }
    else{
        return NULL;
    }
}

/**************** hashtable_insert ****************/
/* see hashtable.h for description 
* note: each set_insert should handle making a copy of the key 
*/
bool hashtable_insert(hashtable_t *ht, const char *key, void *item){
    // note: need to make sure hashtable, key, and item all exist, and key doesn't already exist in hashtable
    if ( (ht != NULL) && (key != NULL) && (item != NULL) && (hashtable_find(ht, key) == NULL)){
        int number_slots = ht->num_slots;
        if ( number_slots < 1 ){              // need to ensure that JenkinsHash will work (check parameters)
            return false;
        } 
        else{
            int n = JenkinsHash(key, number_slots);            // determine hashed slot
            set_t *appropriate_slot = ht->table_slots[n];        // establish pointer to the slot we're adding into
            bool test = set_insert(appropriate_slot, key, item); // can use set_insert to insert into the correct slot
            return test;                                         // return true if success or false if failure
        }
    }
    else{
        return NULL;
    }
}

/**************** hashtable_find ****************/
/* see hashtable.h for description */
void *hashtable_find(hashtable_t *ht, const char *key){
    if ( (ht != NULL) && ( key != NULL)){ 
        int number_slots = ht->num_slots;
        if ( number_slots < 1){
            return NULL;
        }
        else{
            int n = JenkinsHash(key, ht->num_slots); // determine hashed slot
            set_t *slot = ht->table_slots[n];     // use the hashed slot to find the approporiate slot
            void* item = set_find(slot, key);     // find the item given the slot and key
            if (item == NULL){                    // account for the case where the item is not found
                return NULL;
            }
            return item;                          // otherwise return the item
        }
    }
    else{
        return NULL;
    }
}

/**************** hashtable_print ****************/
/* see hashtable.h for description */
void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)){
    if ( fp!= NULL){                                    // ignore scenario where file provided doesn't exist/is invalid
        if ( ht!= NULL){
            int number_slots = ht->num_slots;
            for ( int i = 0; i < number_slots; i++){    // loop over all over the slots 
                fprintf(fp, "Slot number %d: ", i);
                if ( (*itemprint) != NULL){
                    // note: set_print handles NULL itemprint and adds a newline
                    set_print(ht->table_slots[i], fp, (*itemprint)); 
                }
                else {
                    fputc('\n',fp);
                }
            }
        }
        else{
            fprintf(fp, "(null)\n");    // handle scenario where hashtable does not exist
        }
        
    }
}

/**************** hashtable_iterate ****************/
/* see hashtable.h for description */
void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item) ){
    if ( (ht != NULL) && (itemfunc != NULL) ){
        int number_slots = ht->num_slots;
        for ( int i = 0; i < number_slots; i++){
            set_iterate(ht->table_slots[i], arg, (*itemfunc)); // note: set_iterate handles NULL itemfunc
        }
    }
}

/**************** hashtable_delete ****************/
/* see hashtable.h for description */
void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item) ){
    if ( ht != NULL){
        int number_slots = ht->num_slots;
        for (int i = 0; i < number_slots; i++){
            set_delete(ht->table_slots[i], (*itemdelete)); // this will free all nodes related to the set
        }
        free(ht->table_slots);                             // free the memory allocated for the slots
        free(ht);                                          // free the hashtable
    }
}
