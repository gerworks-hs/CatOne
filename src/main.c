//Made by Gerworks-HS (@itsgerliz)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rollCount; //Roll arguments count (number of arguments - first three mandatory arguments), if index method is used then we will use the 4th
int imethod; //Input method flag, 1 for roll, 2 for index
char *archive_name; //Pointer to the string with the final archive name
FILE **file_array; //Array of pointer to FILEs for the last arguments

void parse_arguments(int count, char **vector) {
	//CHECK FOR CORRECT USAGE
	if (count < 4) { //Check if the user used at leas t 4 arguments
		fprintf(stderr, "Incorrect app usage\nUsage: %s <input method> <archive name> <catone index file or files>\n", vector[0]);
		exit(EXIT_FAILURE);
	} else if (count > 258) {
		fprintf(stderr, "Too many arguments, max is 258\n");
		exit(EXIT_FAILURE);
	}
	//PARSE INPUT METHOD
	if (strcmp("roll", vector[1]) == 0) {
		imethod = 1;
	} else if (strcmp("index", vector[1]) == 0) {
		imethod = 2;
	} else {
		fprintf(stderr, "Not a valid input method\n");
		exit(EXIT_FAILURE);
	}
	//PARSE FINAL ARCHIVE NAME
	if (strlen(vector[2]) > 255) { //Check for too long final archive name
		fprintf(stderr, "Final archive name is too long: <%s>\n", vector[2]);
		exit(EXIT_FAILURE);
	} else {
		archive_name = vector[2]; //Equal global variable to argument
	}
	//REST OF THE ARGUMENTS 3 < count
	if (imethod == 1) { //Roll case
		file_array = malloc(sizeof(FILE *) * (count - 3));
		if (file_array == NULL) {
			fprintf(stderr, "Fatal error trying to dinamically allocate memory, aborting...\n");
			exit(EXIT_FAILURE);
		}
		for (int i = 3, o = 0; i < count; i++, o++) { //i = 3 to start reading args avoiding the first three (0,1,2)
			file_array[o] = fopen(vector[i], "rb"); //Define each member of the file array to a pointer to a FILE using the next arg and read binary mode
			if (file_array[o] == NULL) { //Check for errors on fopen()
				fprintf(stderr, "Cannot open the file <%s>\n", vector[i]);
				for (int j = 0; j < (count - 3); j++) {
					fclose(file_array[j]); //Free each FILE pointer in file_array
				}
				free(file_array);
				exit(EXIT_FAILURE);
			}
			fprintf(stdout, "File <%s> added for processing\n");
		}		
	} else if (imethod == 2) { //Index case
		file_array = malloc(sizeof(FILE *)); //Index: define file_array as a pointer to a pointer to a FILE (pointer to FILE *)
		if (file_array == NULL) {
			fprintf(stderr, "Fatal error trying to dinamically allocate memory, aborting...\n");
			exit(EXIT_FAILURE);
		}
		*file_array = fopen(vector[3], "rb"); //Define the data pointed by file_array pointer as a pointer to a FILE (FILE *)
		if (*file_array == NULL) { //Check for errors on fopen()
			fprintf(stderr, "Cannot open the file <%s>\n", vector[3]);
			free(file_array);
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char **argv) {
	parse_arguments(argc, argv);
	exit(EXIT_SUCCESS);
}
//Made by Gerworks-HS (@itsgerliz)
