#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void clean_stdin(void)
{
    int c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


int main()
{
	int N;

	printf("Input the length of the string A: ");
	scanf("%d", &N);

	char A[N+1], B[N+1];

	// fflush(stdin);
	// I uuse clean_std for fflush(stdin) because fflush does not work in Linux
	printf("Input string: ");
	clean_stdin();

	fgets(A, N+1, stdin);

	strcpy(B, A);


	// Print splitted words
	printf("\nSplitted words from string: ");

	char *token = strtok(B,  " ");

	while (token != NULL){
		printf("\"%s\" ", token);
		token = strtok(NULL, " ");
	}

	// Print corrected string 
	printf("\n\nCorrected string: ");
	strcpy(B, A);

	token = strtok(B,  " ");

	while (token != NULL){
		printf("%s ", token);
		token = strtok(NULL, " ");
	}


	// Print capitalized string 
	printf("\n\nCorrected capitalized string: ");
	strcpy(B, A);

	token = strtok(B,  " ");


	while (token != NULL){
		*token = toupper(*token);
		printf("%s ", token);
		token = strtok(NULL, " ");
	}



	printf("\n");


}