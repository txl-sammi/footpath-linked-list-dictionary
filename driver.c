#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "data.h"
#include "list.h"
#include "array.h"

// used or potential data structures for dictionary
#define STAGE_1 1 
#define STAGE_2 2

void listQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile);
void sortedQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile);
int processArgs(int argc, char *argv[]);

/* driver.c
*
* Created by Sammi Li (tingxin@student.unimelb.edu.au)
19/08/2022
*
* Print the footpath data from the address that is input by the user in stage 1
* and print the footpath data with the closest "grade1in" to the user input in stage 2
*
* To run stgae 1: 
* ./dict1 --dictionary_type 1 --input_filename dataset.csv --info_file_name output.txt
* To run stage 2:
* ./dict2 --dictionary_type 2 --input_filename dataset.csv --info_file_name output.txt

* To see all the input parameters, type:
* ./dict1 --help or ./dict2 --help
* Options::
*   --help                   Show help message
*   --dictionary_type arg    Input dictionary type
*   --input_file_name arg    Input dataset filename
*   --info_file_name arg     Input output filename  
* 
*/

int main(int argc, char *argv[]) {
	int stageType = processArgs(argc, argv);

    FILE *infoFile = fopen(argv[3], "w");
    assert(infoFile);
    
	switch (stageType) {
		case STAGE_1:
        	listQuerying(argv[2], stdin, stdout, infoFile);
			break;
		case STAGE_2:
			sortedQuerying(argv[2], stdin, stdout, infoFile);
			break;
		default: 
			fprintf(stderr, "Dictionary type %d not yet implemented\n", stageType);
			exit(EXIT_FAILURE);
	}

	fclose(infoFile);
    return 0;
}

// makes sure to have enough arguments in the command line
// returns the specified dictionnary type
int processArgs(int argc, char *argv[]) {
	if (argc < 3 || atoi(argv[1]) < STAGE_1 || atoi(argv[1]) > STAGE_2 ) {
		fprintf(stderr, "Usage: %s dictionary_type input_file_name info_file_name, where:\n", argv[0]);
		fprintf(stderr, "       \t - dictionary_type can be:\n");
		fprintf(stderr, "       \t - input_file_name: data file for buiding dictionary\n");
		fprintf(stderr, "       \t - info_file_name: a file for outputing technical details of searches\n");
		exit(EXIT_FAILURE);
	}
	return atoi(argv[1]);
}

// reads footpath from "filename", 
// returns lined list of footpaths
list_t *getFootpathList(char *filename) {
	FILE *f = fopen(filename, "r");
	assert(f);
	list_t *footpath = listCreate();
	footpathSkipHeaderLine(f);
	footpath_t *p;
	while ((p = footpathRead(f))) {
		listAppend(footpath, p);
	}
	fclose(f);
	return footpath;
}

// querying with footpath address on linked list_t
void listQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile) {
	// builds list of footpaths
	list_t *footpath = getFootpathList(dataFileName);

	char query[MAX_LINE_LEN + 1];
    int found=0;

	while (fgets(query, MAX_LINE_LEN, inFile)!=NULL) {
		int newline = strlen(query)-1;
		if(query[newline] == '\n') {
			query[newline] = '\0';
		}
        fprintf(infoFile, "%s\n", query);
		listSearch(footpath, query, infoFile);
    }

	listFree(footpath, footpathFree);
}

// reads footpath data from "filename", 
// returns sorted array of footpaths
array_t *getSortedArray(char *filename){
	FILE *f = fopen(filename, "r");
	assert(f);

	// builds starting array
	array_t *footpaths = arrayCreate();
	footpathSkipHeaderLine(f);
	footpath_t *p;

	while ((p = footpathRead(f))) {
		sortedArrayInsert(footpaths, p);
	}
	
	fclose(f);
	arrayShrink(footpaths);
	return footpaths;
}

// querying with footpath address on sorted array_t
void sortedQuerying(char *dataFileName, FILE *inFile, FILE *outFile, FILE *infoFile) {
	
	// builds sorted array with pointers to each footpath_t
	array_t *footpath_arr = getSortedArray(dataFileName);
	double query;
	int found=0;

	while (fscanf(inFile, "%lf", &query) == 1) {
		fprintf(infoFile, "%.2lf\n", query);
		getClosestGrade(infoFile, query, footpath_arr);
	}
	arrayFree(footpath_arr);
}
