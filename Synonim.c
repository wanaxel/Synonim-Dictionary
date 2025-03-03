#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  

#define MAX_WORDS 1000
#define WORD_LENGTH 50
#define CLEAR_COMMAND "clear" 

typedef struct {
    char word[WORD_LENGTH];
    char synonym[WORD_LENGTH];
} DictionaryEntry;

DictionaryEntry dictionary[MAX_WORDS];
int wordCount = 0;

int strcasecmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
        }
        s1++;
        s2++;
    }
    return tolower((unsigned char)*s1) - tolower((unsigned char)*s2);
}

void clearScreen() {
    system(CLEAR_COMMAND);
}

void displayMainMenu() {
    clearScreen();
    printf("==============================================================\n");
    printf("=                                                            =\n");
    printf("=                     Synonym Dictionary                     =\n");
    printf("=                      [1] Start                             =\n");
    printf("=                      [2] Add Word                          =\n");
    printf("=                      [3] Edit Word                         =\n");
    printf("=                      [4] Delete Word                       =\n");
    printf("=                      [5] List Words                        =\n");
    printf("=                      [6] Credits                           =\n");
    printf("=                      [7] Exit                              =\n");
    printf("=                                                            =\n");
    printf("==============================================================\n");
    printf("Enter your choice: ");
}

void saveDictionary() {
    FILE *file = fopen("dictionary.txt", "w");
    if (file) {
        for (int i = 0; i < wordCount; i++) {
            fprintf(file, "%s %s\n", dictionary[i].word, dictionary[i].synonym);
        }
        fclose(file);
    } else {
        printf("Error: Could not save dictionary to file.\n");
    }
}

void pauseScreen() {
    printf("\nPress Enter to continue...");
    getchar();
    getchar(); 
}

int main() {
    FILE *file = fopen("dictionary.txt", "r");
    if (file) {
        while (fscanf(file, "%s %s", dictionary[wordCount].word, dictionary[wordCount].synonym) == 2) {
            wordCount++;
        }
        fclose(file);
    }

    int choice;
    do {
        displayMainMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: { 
                char input[WORD_LENGTH];
                while (1) {
                    clearScreen();
                    printf("==============================================================\n");
                    printf("=                     Synonym Search                         =\n");
                    printf("==============================================================\n");
                    printf("Enter a word (or type 'exit' to return): ");
                    scanf("%s", input);
                    
                    if (strcasecmp(input, "exit") == 0) break;
                    
                    int found = 0;
                    for (int i = 0; i < wordCount; i++) {
                        if (strcasecmp(dictionary[i].word, input) == 0) {
                            printf("Synonym: %s\n", dictionary[i].synonym);
                            found = 1;
                            break;
                        } else if (strcasecmp(dictionary[i].synonym, input) == 0) {
                            printf("Synonym: %s\n", dictionary[i].word);
                            found = 1;
                            break;
                        }
                    }
                    
                    if (!found) {
                        printf("Word not found. Do you want to add it? (y/n): ");
                        char response;
                        scanf(" %c", &response);
                        if (response == 'y' || response == 'Y') {
                            printf("Enter synonym: ");
                            scanf("%s", dictionary[wordCount].synonym);
                            strcpy(dictionary[wordCount].word, input);
                            wordCount++;
                            saveDictionary();
                            printf("Word added successfully!\n");
                        }
                    }
                    
                    pauseScreen();
                }
                break;
            }
            
            case 2: { 
                clearScreen();
                printf("==============================================================\n");
                printf("=                     Add New Word                           =\n");
                printf("==============================================================\n");
                
                if (wordCount >= MAX_WORDS) {
                    printf("Dictionary is full!\n");
                } else {
                    printf("Enter word: ");
                    scanf("%s", dictionary[wordCount].word);
                    printf("Enter synonym: ");
                    scanf("%s", dictionary[wordCount].synonym);
                    wordCount++;
                    saveDictionary();
                    printf("Word added successfully!\n");
                }
                
                pauseScreen();
                break;
            }
            
            case 3: { 
                clearScreen();
                printf("==============================================================\n");
                printf("=                     Edit Word                              =\n");
                printf("==============================================================\n");
                
                char input[WORD_LENGTH];
                printf("Enter word to edit: ");
                scanf("%s", input);
                
                int found = 0;
                for (int i = 0; i < wordCount; i++) {
                    if (strcasecmp(dictionary[i].word, input) == 0) {
                        printf("Current synonym: %s\n", dictionary[i].synonym);
                        printf("Enter new synonym: ");
                        scanf("%s", dictionary[i].synonym);
                        saveDictionary();
                        printf("Word updated successfully!\n");
                        found = 1;
                        break;
                    }
                }
                
                if (!found) printf("Word not found!\n");
                pauseScreen();
                break;
            }
            
            case 4: { 
                clearScreen();
                printf("==============================================================\n");
                printf("=                     Delete Word                            =\n");
                printf("==============================================================\n");
                
                char input[WORD_LENGTH];
                printf("Enter word to delete: ");
                scanf("%s", input);
                
                int found = 0;
                for (int i = 0; i < wordCount; i++) {
                    if (strcasecmp(dictionary[i].word, input) == 0) {
                        for (int j = i; j < wordCount - 1; j++) {
                            strcpy(dictionary[j].word, dictionary[j + 1].word);
                            strcpy(dictionary[j].synonym, dictionary[j + 1].synonym);
                        }
                        wordCount--;
                        saveDictionary();
                        printf("Word deleted successfully!\n");
                        found = 1;
                        break;
                    }
                }
                
                if (!found) printf("Word not found!\n");
                pauseScreen();
                break;
            }
            
            case 5: { 
                clearScreen();
                printf("==============================================================\n");
                printf("=                     Dictionary Contents                    =\n");
                printf("==============================================================\n");
                
                if (wordCount == 0) {
                    printf("Dictionary is empty!\n");
                } else {
                    for (int i = 0; i < wordCount; i++) {
                        printf("%3d. %-20s - %s\n", i+1, dictionary[i].word, dictionary[i].synonym);
                    }
                    printf("\nTotal words: %d\n", wordCount);
                }
                
                printf("\nPress 'y' to return to main menu: ");
                char input;
                scanf(" %c", &input);
                break;
            }
            
            case 6: { 
                clearScreen();
                printf("==============================================================\n");
                printf("=                        Credits                             =\n");
                printf("==============================================================\n");
                printf("Synonym Dictionary\n");
                printf("Created by: \n");
                printf("2602208750 - Wan Mohamad Axel Rinaldi\n");
                printf("2440030834 - Dominique Christopher Nathaniel\n");
                printf("2802534235 - Muhammad Ridho Fathi Fauzan\n");
                printf("2802471524 - Valentino Pratama\n");
                printf("\nPress 'y' to return to main menu: ");
                char input;
                scanf(" %c", &input);
                break;
            }
            
            case 7: 
                clearScreen();
                printf("Thank you for using this progam\n");
                break;
                
            default:
                clearScreen();
                printf("Invalid choice. Please try again.\n");
                pauseScreen();
        }
    } while (choice != 7);

    return 0;
}
