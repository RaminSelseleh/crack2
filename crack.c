#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

const int PASS_LEN = 20;        // Maximum any password will be
const int HASH_LEN = 33;        // Length of MD5 hash strings

// Given a target hash, crack it. Return the matching
// password.
char * crackHash(char * targetHash, char * dictionaryFilename)
{
    // Open the dictionary file
    FILE *in = fopen(dictionaryFilename, "r");
    if (in == NULL) {
        printf("Cant open file for reading!\n");
        exit(1);
    }
    // Loop through the dictionary file, one line
    // at a time.
    char line[PASS_LEN];
    while (fgets(line, PASS_LEN, in) != NULL) {
        char *nl = strchr(line, '\n');
        if (nl != NULL) *nl = '\0';

        char* hash = md5(line,strlen(line));

        if (strcmp(hash, targetHash) == 0) {
            printf("Found: %s: %s\n\n", hash, line);
            free(hash);
            break;
        }
        free(hash);

    }

    // Hash each password. Compare to the target hash.
    // If they match, return the corresponding password.
    
    // Close the dictionary file. Free up memory?
    fclose(in);
    return 0;
}


int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        fprintf(stderr, "Usage: %s hash_file dict_file\n", argv[0]);
        exit(1);
    }

    // Open the hash file for reading.
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        printf("Cant open file for reading!\n");
        exit(1);
    }

    char hashline[50];

    while (fgets(hashline, 50, f) != NULL) {
        //printf("Before: %s\n", hashline);
        char *nl = strchr(hashline, '\n');
        if (nl != NULL) *nl = '\0';
        crackHash(hashline, argv[2]);
    }
    fclose(f);

    // For each hash, crack it by passing it to crackHash
    
    // Display the hash along with the cracked password:
    //   5d41402abc4b2a76b9719d911017c592 hello
    
    // Close the hash file
    
    // Free up any malloc'd memory?
    //free(f);
}
