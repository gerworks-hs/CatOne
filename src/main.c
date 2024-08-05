//Made by Gerworks-HS (@itsgerliz)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *imethod; //Pointer to the input method flag, 1 for roll, 2 for index

void parse_arguments(const int count, char **vector) {
	imethod = malloc(sizeof(int)); //Allocate pointer
	if (count < 3) { //Check enough arguments
		fprintf(stderr, "Incorrect app usage\nUsage: %s <input method> <archive name> <catone index file or files>\n", vector[0]);
		free(imethod);
		exit(EXIT_FAILURE);
	}
	if (strcmp("roll", vector[1]) == 0) { //Check input method
		*imethod = 1;
	} else if (strcmp("index", vector[1]) == 0) { //Check input method
		*imethod = 2;
	} else {
		fprintf(stderr, "Not a valid input method\n");
		free(imethod);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv) {
	parse_arguments(argc, argv); //Check for correct app usage and initialize base variables
	free(imethod);
	exit(EXIT_SUCCESS);
}
//Made by Gerworks-HS (@itsgerliz)
