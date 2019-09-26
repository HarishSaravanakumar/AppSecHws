int check_words(FILE* fp, hashmap_t hashtable[], char* misspelled[]);
bool load_dictionary(const char* dictionary_file, hashmap_t
hashtable[]);
bool check_word(const char* word, hashmap_t hashtable[]);