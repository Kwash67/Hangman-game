#include <stdio.h>
#include <stdlib.h> //This takes away a warning that comes from the rand() function
#include <stdbool.h> //For true or false variables
#include <string.h> // This contains an inbuilt function for string length
#include <time.h> //Used to seed the random function with time, to make rand() less repetitive.

//GLOBAL VARIABLES
int length;
char* beginnerWords[] = {"cat", "dog", "hat", "car", "cup", "pen", "sun", "tree", "book", "cake"};
char* amateurWords[] = {"pencil", "guitar", "camera", "jacket", "soccer", "basket", "banana", "orange", "coffee", "jungle", "turtle", "elephant"};
char* proWords[] = {"university", "chandelier", "turquoise", "labyrinth", "oblivion", "enthusiasm", "pneumonia", "magnificent", "saxophone", "xylophone", "quintessence", "xenophobia", "bureaucracy"};
int score = 0;
int tries = 0;
bool correct = false;
char* word;

// DECLARATION OF FUNCTIONS
void randomWord(char* wordbank[], int length);
void errorCatcher();

int main(){
    start:
        printf("WORD GUESS GAME!\n");

    menu:
        printf("Main Menu:\n");
        int menu_item;
        printf("Select an option\n 1. Start Game\n 2. Help\n 3. Exit\n");
        scanf("%d", &menu_item);
        switch(menu_item){
            case 1: goto game;
            break;
            case 2: goto help;
            break;
            case 3: goto bye;
            break;
            default:errorCatcher();
                    goto menu;
        }

    game:
        printf("Select Difficulty:\n 1. Beginner\n 2. Amateur\n 3. Pro\n");
        int level;
        scanf("%d", &level);
        switch(level){
            case 1: printf("This is Beginner's Level\n");
                    randomWord(beginnerWords, sizeof(beginnerWords)/sizeof(beginnerWords[0]));
                    break;
            case 2: printf("This is Amateur's Level\n");
                    randomWord(amateurWords, sizeof(amateurWords)/sizeof(amateurWords[0]));
                    break;
            case 3: printf("This is Professional Level\n");
                    randomWord(proWords, sizeof(proWords)/sizeof(proWords[0]));
                    break;
            default:errorCatcher();
                    goto game;
        }

        int word_length = strlen(word);
        char* state = malloc(word_length * sizeof(char));
        for (int i = 0; i < word_length; i++) {
                state[i] = '_';
            }
        for (int i = 0; i < word_length; i++) {
                printf("[_]");
            }

        while (score < word_length * 5 && tries < 5) {
            printf("\nGuess the letters of this word:\n");

            printf("\n");
            bool already_guessed=false;
            char guess[1];
            scanf("%s", guess);
            for (int i = 0; i < word_length; i++) {
                if(guess[0] == state[i]){
                    already_guessed = true;
                }
            }
            if(already_guessed){
                printf("You already guessed this!\n");
                printf("You gotta do better than that!\n");
            }
            else{

                for (int i = 0; i < word_length; i++) {
                    if (guess[0] == word[i]) {
                        state[i] = guess[0];
                        correct = true;
                        int count=0;
                        for(int j = 0; j<word_length; j++){
                            if (state[j] == state[i] && state[j]!= "_"){
                                score+=5;
                                count++;
                            }
                        }
                        if(count>=2){
                            score-=5;
                        }
                    }
                }


                for (int i = 0; i < word_length; i++) {
                    printf("[%c]", state[i]);
                }
                printf("\n");
                if (correct) {
                    printf("Correct!\n");
                } else {
                    printf("Incorrect.\n");
                    tries++;
                }
            }
            printf("Score : %d\n", score);
            printf("Tries: %d\n", tries);
            if (score == word_length*5) {
                    printf("\nYou won!\n");
                    printf("*****************\n");
                    printf("*Final Score: %d*\n", score);
                    printf("*****************\n");
                    break;
            }
            correct = false; //Send Correct back to false
        }
        printf("\nPlay again\?\n1. Yes\n2. Main Menu\n3. Exit\n");
        int response;
        scanf("%d", &response);
        switch(response){
            case 1: tries = 0;
                    score = 0;
                    correct = false;
                    goto game;
            case 2:goto menu;
            case 3: goto bye;
            default:errorCatcher();
                    goto help;
        }
        free(state);


    help:
        printf("\n\n");
        printf("*************************************\n");
        printf("This is a word guess game, built by Group 8.");
        printf("\nGuess the letters of the words given and earn 5 points for each guess!");
        printf("\nYou have 5 tries for each guess, after which the game ends\n");
        printf("*************************************");
        printf("\n\n");
        printf("Go back to main\?\n1. Yes\n2. No, I want to Exit.\n");
        int back_response;
        scanf("%d", &back_response);
        switch(back_response){
            case 1: goto menu;
            case 2: goto bye;
            default:errorCatcher();
                    goto help;
        }

    bye:
        printf("\nHope you enjoyed the game!\n");
        printf("See you next time!");

    return 0;
}

void randomWord(char* wordbank[], int length){
    srand(time(NULL));
    int index = rand() % length;
    printf("%s\n", wordbank[index]);
    word = wordbank[index];
}

void errorCatcher(){
    printf("\nInvalid Input!\n\n");
    fflush(stdin);//Flushes the input
}

