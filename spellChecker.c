#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DICTIONARY_FILE "words_alpha.txt"
#define MAX_WORD_LENGTH 100

// Function to load words from a dictionary file
char** loadDictionary(int* dictionarySize) {
    FILE* file = fopen(DICTIONARY_FILE, "r");
    if (!file) {
        perror("Error opening dictionary file");
        exit(EXIT_FAILURE);
    }

    // Count the number of lines in the file to determine the dictionary size
    *dictionarySize = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*dictionarySize)++;
        }
    }
    rewind(file);

    // Allocate memory for the dictionary
    char** dictionary = (char**)malloc(*dictionarySize * sizeof(char*));

    // Read words from the file into the dictionary
    for (int i = 0; i < *dictionarySize; i++) {
        dictionary[i] = (char*)malloc(MAX_WORD_LENGTH * sizeof(char));
        fscanf(file, "%s", dictionary[i]);
    }

    fclose(file);
    return dictionary;
}

// Function to check if a word is in the dictionary
int isInDictionary(char* word, char** dictionary, int dictionarySize) {
    for (int i = 0; i < dictionarySize; i++) {
        if (strcmp(word, dictionary[i]) == 0) {
            return 1; // Word is in the dictionary
        }
    }
    return 0; // Word is not in the dictionary
}

// Function to check the spelling of a given text
void checkSpelling(char* text, char** dictionary, int dictionarySize) {
    char* token = strtok(text, " ,.-\n"); // Tokenize the text
    while (token != NULL) {
        // Convert token to lowercase for case-insensitive comparison
        for (int i = 0; token[i]; i++) {
            token[i] = tolower(token[i]);
        }

        // Check if the token is in the dictionary
        if (!isInDictionary(token, dictionary, dictionarySize)) {
            printf("Misspelled word: %s\n", token);
        }
        else{
            printf("correctly Spelled.");
        }
        token = strtok(NULL, " ,.-\n");
    }
}

int main() {
    
    int dictionarySize;
    char** dictionary = loadDictionary(&dictionarySize);

    char inputText[500];
    printf("Enter Word to check spelling: ");
    fgets(inputText, sizeof(inputText), stdin);

    checkSpelling(inputText, dictionary, dictionarySize);

    // Free allocated memory
    for (int i = 0; i < dictionarySize; i++) {
        free(dictionary[i]);
    }
    free(dictionary);

    return 0;
}
