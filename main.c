#include "dictionary.h"
#include <stdlib.h>
int main(int argc, char * argv[]){
	FILE *test_file = fopen(argv[1], "r"); //test_wordlist
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(argv[2], hashtable);
    char *misspelled[MAX_MISSPELLED]; //array that holds misspelled words
    int misspell_count = check_words(test_file, hashtable, misspelled);
    fclose(test_file);
<<<<<<< HEAD
    bool yes = check_words('Justice', hashtable);
    printf("Justice: %d\n",yes);
=======
    printf("MISPELLED: %i\n",misspell_count);
>>>>>>> 1567d6ad590fe8fa657853b355cf090d52b39e12
}