#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

/* ------------------ graph file reader ------------------ */

char *load_file(char *file, int *file_size) {

	long pos = 0;
	char current_character;
	char *file_buffer;

	FILE *pfile = fopen(file, "r");

	if(pfile == NULL) {
		printf("\nFehlerhafte Eingabe\n\n");
		exit(1);
	}

	fseek(pfile, 0, SEEK_END);
	*file_size = ftell(pfile);
	rewind(pfile);

	file_buffer = (char *)malloc(*file_size * sizeof(char));

	if(file_buffer == NULL) {
		perror("\nSYSTEM: Sorry, can't get memory..\n\n");
		exit(1);
	}

	fread(file_buffer, sizeof(char), *file_size, pfile);

	file_buffer[pos] = 0;

	fclose(pfile);
	return(file_buffer);
}
