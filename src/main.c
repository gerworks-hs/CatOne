//Made by Gerworks-HS (@itsgerliz)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int imethod; //Pointer to the input method flag, 1 for roll, 2 for index
char *archive_name; //Pointer to the string with the final archive name

void parse_arguments(const int count, char **vector) {
	//Check enough arguments
	if (count < 4) {
		fprintf(stderr, "Incorrect app usage\nUsage: %s <input method> <archive name> <catone index file or files>\n", vector[0]);
		exit(EXIT_FAILURE);
	}
	//Input method
	if (strcmp("roll", vector[1]) == 0) { //Check input method
		imethod = 1;
	} else if (strcmp("index", vector[1]) == 0) { //Check input method
		imethod = 2;
	} else {
		fprintf(stderr, "Not a valid input method\n");
		exit(EXIT_FAILURE);
	}
	//Final archive name
	archive_name = vector[2];
	//Rest
	if (imethod == 1) { //Roll
		
	} else if (imethod == 2) { //Index

	}
}

int main(int argc, char **argv) {
	parse_arguments(argc, argv); //Check for correct app usage and initialize base variables
	exit(EXIT_SUCCESS);
}
//Made by Gerworks-HS (@itsgerliz)
