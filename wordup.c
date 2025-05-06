//Author: Faith Nelson
//Date: 5/6/25
//Purpose: Final Project

#include <stdio.h>

void loadword(char word[]);
void userguess(char guess[]);
int validguess(char guess[]);
void displayguesses(char guesses[][6], int numguess, char word[]);
void checkguess(char guess[], char word[], char result[], char pointer[]);
int correctguess(char guess[], char word[]);

int main(){
	int numguess = 5;
	char word[6];
	char guesses[6][6];
	int count = 0;
	loadword(word);
	while(count < 6){
		printf("Enter a 5 letter word: ");
		char guess[6];
		userguess(guess);
		while(validguess(guess) == 0){
			printf("Invalid guess. Try again.\n");
			userguess(guess);
		}
		for(int i = 0; i < 6; i++){
			guesses[count][i] = guess[i];
		}
		displayguesses(guesses, numguess + 1, word);
		if(correctguess(guess, word)){
		printf("Congratulation! You guessed the word!\n");
		return 0;
		}
		count++;
	}
	printf("Sorry, you ran out of guesses. The word was: %s\n", word);
	return 0;
}
void loadword(char word[]){
	FILE* file = fopen("word.txt", "r");
	if(file == NULL){
		printf("Couldn't open file.\n");
	}else{
		fscanf(file, "%5s", word);
		fclose(file);
	}
}
void userguess(char guess[]){
	printf("Enter your guess: ");
	scanf("%5s", guess);
}
int validguess(char guess[]){
	int valid = 1;
	for(int i = 0; i < 5; i++){
		if(guess[i] == '\0' || (guess[i] < 'A' || (guess[i] > 'Z' && guess[i] < 'a') || guess[i] > 'z')){
			valid = 0;
		}
	}
	if(guess[5] != '\0'){
		valid = 0;
	}
	return valid;
}
void displayguesses(char guesses[][6], int numguess, char word[]){
	for(int i = 0; i < numguess; i++){
		char result[6];
		char pointer[6];
		checkguess(guesses[i], word, result, pointer);
		printf("%s\n", result);
		printf("%s\n", pointer);
	}
}
void checkguess(char guess[], char word[], char result[], char pointer[]){
	for(int i = 0; i < 5; i++){
		result[i] = guess[i];
		pointer[i] = ' ';
	}
	result[5] = '\0';
	pointer[5] = '\0';
	int used[5] = {0};
	for(int i = 0; i < 5; i++){
		if(guess[i] != word[i]){
			if(result[i] >= 'a' && result[i] <= 'z'){
				result[i] -= 32;
			}
		used[i] = 1;
		}
	}
	for(int i = 0; i < 5; i++){
		if(guess[i] != word[i]){
			int found = 0;
			for(int j = 0; j < 5 && found == 0; j++){
				if(used[j] == 0 && guess[i] == word[j]){
					pointer[i] = '^';
					used[j] = 1;
					found = 1;
				}
			}
		}
	}
}
int correctguess(char guess[], char word[]){
	int correct = 1;
	for(int i = 0; i < 5; i++){
		if(guess[i] != word[i]){
			correct = 0;
		}
	}
	return correct;
}
