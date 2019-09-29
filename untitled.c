bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]){
    FILE *fp;
	char str[LENGTH];
	fp = fopen(dictionary_file, "r");
    if (fp == NULL){
        printf("Could not open file %s",dictionary_file);
        return false;
    }
    // fgets (buffer, size, fp);
    // buffer – buffer to  put the data in.
	// size – size of the buffer
	// fp – file pointer
    while (fgets(str, LENGTH, fp) != NULL) {
        hash_function(str);
    }
    int index = hash_function(str)
    node hashtable_node;
    hashtable_node.word = str;
    hashtable_node.next = NULL;

    if (hashtable[index] == NULL)
        {
            hashtable[index] = hashtable_node;
        }
    else{
        node temp = hashtable[index];
        while (temp != NULL)
            {
                if (temp.next == NULL)
                {
                    break;
                }
                temp = tmp.next;
            }
        }

    fclose(fp);
    return true;  /// false?
}

int check_words(const char* fp, hashmap_t hashtable[], char * misspelled[]){
    FILE *fp;
    char str[LENGTH];
    fp = fopen(dictionary_file, "r");
    if (fp == NULL){
        printf("Could not open file %s",dictionary_file);
        return false;
    }
    while (fgets(str, LENGTH, fp) != NULL) {
        check_word(str);
    }
};

bool check_word(const char* word, hashmap_t hashtable[]){
    int index = hash_function(word);
    if (hashtable[index] != NULL) {
        return true;
    }
    return false;
};

int main(int argc, char * argv[])
{
    hashmap_t hashtable[HASH_SIZE];
    FILE *fp = fopen(argv[1], "r");
    load_dictionary(argv[2], hashtable);
    char *misspelled[MAX_MISSPELLED];
    int num_misspelled = check_words(fp, hashtable, misspelled);
    fclose(fp);
    printf("MISPELLED: %i\n",num_misspelled);
}