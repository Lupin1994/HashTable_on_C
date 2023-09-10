#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>
#include "HashTable.h"

#define HASHTABLE_SIZE 1000 // size our hash table 

void hashTable_print(THashTable *hashTable){
    printf("\n ------Hash Table------\n");

    for (int i = 0; i < hashTable->count; i++)
    {
        printf("{Key:%s , Value:%d}\n", hashTable->items[i]->key, hashTable->items[i]->value);
    }
    
    printf("\n -------THE END--------\n");
}

void hashTable_printSearchValue(THashTable *hashTable, char *key){
    int value;
    if ((value = hashTable_searchValue(hashTable,key)) == NULL)
    {
        printf("Key:%s not found\n", key);
        return;
    }
    else
    {
        printf("{Key:%s, Value:%d\n}", key, value);
    }
}


THashTableItem* hashTable_createItem(char *key, int value){

    THashTableItem *item = (THashTableItem*)malloc(sizeof(THashTableItem));

    item->key = key;
    item->value = value;
    
    return item; 
}

THashTable* hashTable_create(){

    THashTable *hashTable = (THashTable*)malloc(sizeof(THashTable));
    //hashTable->size = 1000;
    hashTable->count = 0;
    hashTable->items = (THashTableItem**)calloc(HASHTABLE_SIZE, sizeof(THashTableItem*));

    for (int i=0; i < HASHTABLE_SIZE; i++)
        hashTable->items[i] = NULL;

    return hashTable;
}

unsigned long hashFunction(char *key){
    unsigned long key_int = 0;
    for (int i = 0; key[i] ; i++)
    {
        key_int += key[i];
    }
    return key_int % HASHTABLE_SIZE; 
}

void item_free(THashTableItem *item){
    free (item->key);
    free (item->value);
    free (item);
}

void item_hashTable(THashTable *hashTable){
    for (int i=0; i < HASHTABLE_SIZE; i++) {
        THashTableItem *item = hashTable->items[i];
        if (item != NULL)
            free_item(item);
    }
    free (hashTable->count);
    free (hashTable->items);
    free (hashTable);
}

void hashTable_collisionsProcessing(THashTable *hashtable, unsigned long key_index, THashTableItem *item){
    //  линейные перебор элементов не очень эффективен
    for (int i = key_index + 1; i < HASHTABLE_SIZE; i++)
    {
        if (hashtable->items[i] == NULL)
        {
            hashtable->items[i] = item; 
            hashtable->count++;
            return;
        }        
    }
}


void hashTable_addItem(THashTable *hashTable, char *key, int value){
    THashTableItem *item = hashTable_createItem(key , value);

    unsigned long key_index = hashFunction(key);

    THashTableItem *current_item = hashTable->items[key_index];

    if (current_item == NULL)
    {
        if (hashTable->count == HASHTABLE_SIZE)
        {
            printf("Hash table is full\n");
            free_item(item);
            return; 
        }
        hashTable->items[key_index] = item;
        hashTable->count++;
    }
    else
    {
        hashTable_collisionsProcessing(hashTable, key_index, item);
        return;
    }
}

char* hashTable_searchValue(THashTable *hashTable, char *key){
    int index = hashFunction(key);
    THashTableItem *item = hashTable->items[index];

    if (item != NULL)
    {
        return item->value;
    }
    return NULL;
}

// Delete for key


    
    
     
