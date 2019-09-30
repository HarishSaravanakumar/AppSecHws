#include "dictionary.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
/** 
 * Harish Saravanakumar (hs3209)
 * Application Security
 * Assignment 1
 **/

/**
 * Returns true if word is in dictionary else false.
 **/
bool check_word(const char* word, hashmap_t hashtable[])
{
    int word_index = hash_function(word); // hash value of word being passed in
    node * index_node = hashtable[word_index]; // access hashtable at index (first item in linked list)
    while(index_node != NULL){ // compare word and item in linked list
        if (strcmp(word, index_node->word) == 0)
            return true;
        else // if false, traverse linked list
            index_node=index_node->next;
    }
    return false; // word not found in hashtable
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 **/
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[5000000]){   
    FILE *dict_file = fopen(dictionary_file, "r"); // open and store dictionary_file
    if(!dict_file){ //if dict_file doesn't exist, return false
    	return false;
    }

    if(dict_file){ //
        int line_hashvalue;
        char buffer[LENGTH]; // char array of allowed word length
        for(int w=0; w<=HASH_SIZE;w++){ // set all values in hashtable to NULL
        	hashtable[w]=NULL;
        }
        while(fgets(buffer,LENGTH,dict_file)){ // copy LENGTH amount of data from dict_file into line
            if(buffer[strlen(buffer)-1] =='\n'){ // if last char is newline, change it to a NULL char (C specific)
            	buffer[strlen(buffer)-1]='\0';
            }
            for(int i=0;i<=strlen(buffer);i++){ // convert all characters to lowercase
            	buffer[i]= tolower(buffer[i]);
            }
            line_hashvalue = hash_function(buffer); // hashtable at index retrieved by hash function for buffer
            if(hashtable[line_hashvalue] == NULL){ // if there's no node at this index, create one
                node * new_node = malloc(sizeof(node)); // allocate memory on the heap for node
                strncpy(new_node->word,buffer,LENGTH); // copy buffer data into new_node
                new_node->next = NULL; // initialize next link in linked list to NULL
                hashtable[line_hashvalue] = new_node; // attach the new node to the hashtable at index line_hashvalue
            }
            else{ // if there is a node at this index, append a new_node to the existing one
                node * new_node = malloc(sizeof(node));
                strncpy(new_node->word,buffer,LENGTH);
                new_node->next = hashtable[line_hashvalue]; // add to existing linked list
                hashtable[line_hashvalue] = new_node;
            }
        }
        fclose(dict_file);
        return true;
    }
    else{
      	return false;
    }
}

/**
 * Returns lowercase of input
 **/
char * str_lower(char *str_input){
    char *pointer1 = str_input;
    char *pointer2 = str_input;
    if(str_input != NULL){
        if(strlen(str_input) != 0){
            while(*pointer1){ //use two pointers to step over string changing each character to lowercase
                *pointer1 = tolower(*pointer2);
                ++pointer1;
                ++pointer2;
            }
            *pointer1 = '\0';
            return str_input;// return changed-in-place string
        }           
    }
    return "";
}


/**
 * Removes punctuation from input
 **/
char *remove_punc(char *str_input) {
    if (str_input == NULL){
        return NULL;
    }
    char *a = str_input;
    char *b = str_input + strlen(str_input) - 1;
    while (ispunct(*a)){
    	a++;
    } 
    while (ispunct(*b) && a < b){ 
    	*b = 0; b--; 
    }
    /* also if you want to preserve the original address */
    if (strlen(a) == 0){
        return NULL;
    }
    return a;
}

/**
 * Returns true if all words are spelled correcty, false otherwise. Array misspelled is populated with words that are misspelled.
 **/
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[])
{
    int misspell_count = 0;
    char file_buffer[95];
    char * word_ptr;
    char *newline_ptr = 0;
    if(fp==NULL){ // if test file is NULL, exit program
    	exit(1);
    }
    while (fgets(file_buffer, 95, fp) != NULL){
        if ((newline_ptr = strchr(file_buffer, '\n')) != NULL){ //checking whether string has '/n'
            *newline_ptr = '\0'; //change to NULL, C expects NULL to be string
        }
        word_ptr = strtok(file_buffer," "); // get first word in file_buffer
        if (word_ptr != NULL && strlen(word_ptr) > LENGTH){
            word_ptr = NULL;
        }
        word_ptr = remove_punc(word_ptr); // remove punctuation
        while (word_ptr != NULL) {
            if (check_word(word_ptr, hashtable)){ // check untouched word
                word_ptr = strtok(NULL, " ");
                word_ptr = remove_punc(word_ptr);
            }
            // if not on list, check lowercase version
            else if (check_word(str_lower(word_ptr), hashtable)){ // check lowercase version
                word_ptr = strtok(NULL, " ");
                word_ptr = remove_punc(word_ptr);
            }
            else{ // add word to misspelled, and increment misspell_count
                if (misspell_count < MAX_MISSPELLED){
                    misspelled[misspell_count] = (char *)malloc((LENGTH+1)*sizeof(char)); // allocate memory to store misspelled words
                    strncpy(misspelled[misspell_count],word_ptr,(LENGTH+1)); // move misspelled word into array
                    misspell_count++; // increment counter
                    word_ptr = strtok(NULL, " ");
                    word_ptr = remove_punc(word_ptr);
                }
                else{
                    return misspell_count;
                }
            }
        }
    }
    return misspell_count;
}
// int main(int argc, char * argv[]){
// 	FILE *test_file = fopen(argv[1], "r"); //test_wordlist
//     hashmap_t hashtable[HASH_SIZE];
//     load_dictionary(argv[2], hashtable);
//     char *misspelled[MAX_MISSPELLED]; //array that holds misspelled words
//     int misspell_count = check_words(test_file, hashtable, misspelled);
//     fclose(test_file);
//     printf("MISPELLED: %i\n",misspell_count);
// }

