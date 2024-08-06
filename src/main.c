//Made by Gerworks-HS (@itsgerliz)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rollCount; //Roll arguments count (number of arguments - first three mandatory arguments)
int imethod; //Input method flag, 1 for roll, 2 for index
char *archive_name; //Pointer to the string with the final archive name
FILE **file_array; //Array of pointer to FILEs for the last arguments

void exit_and_cleanup(const char *message, const int executionResult) {
	if (executionResult == 0) { //When execution results in success
		if (imethod == 1) { //Roll
			for (int i = 0; i <= rollCount; i++) {
				fclose(file_array[i]);
			}	
		} else if (imethod == 2) { //Index
			fclose(file_array[0]);
		}
		fprintf(stdout, "%s\n", message);
		free(file_array);
		exit(EXIT_SUCCESS);
	} else if (executionResult == 1) { //When execution results in failure
		free(file_array);
		fprintf(stderr, "%s\n", message);
		exit(EXIT_FAILURE);
	}
}

void parse_arguments(int count, char **vector) {
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
	//Rest SINCE THIS POINT exit_and_cleanup() CAN BE CALLED
	if (imethod == 1) { //Roll case
		file_array = malloc(sizeof(FILE *) * (count - 3)); //Roll: define file_array as an arrray of pointers to FILEs long as argc - 3 initial args
		for (int i = 3, o = 0; i < count; i++, o++) { //i is set to 3 to start reading args avoiding the first three (0,1,2), o is set for the array
			fprintf(stdout, "Trying to open file <%s>\n", vector[i]);
			file_array[o] = fopen(vector[i], "rb"); //Define each member of the file array to a pointer to a FILE using the next arg and read binary mode
			if (file_array[o] == NULL) { //Check for errors on fopen()
				exit_and_cleanup("Cannot open current file", 1);
			}
		}		
	} else if (imethod == 2) { //Index case
		file_array = malloc(sizeof(FILE *)); //Index: define file_array as an array with a unique member pointing to the index file
		file_array[0] = fopen(vector[3], "rb"); //Define the array unique member to a pointer to a FILE pointing to the index file
		if (file_array[0] == NULL) { //Check for errors on fopen()
			exit_and_cleanup("Your index file cannot be opened", 1);
		}
	}
}

int main(int argc, char **argv) {
	parse_arguments(argc, argv); //Check for correct app usage and initialize base variables
	exit_and_cleanup("Reached end of normal execution", 0); //Normal end of execution
}
//Made by Gerworks-HS (@itsgerliz)
