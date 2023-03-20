#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "data.h"
#include "list.h"
#include "array.h"

struct array {
	footpath_t **A;      // use as array of student_t *, ie. student_t *A[]
	int size;           // current array size
	int n;              // current number of elements
};

// creates & returns an empty array
array_t *arrayCreate() {
	array_t *arr = malloc(sizeof(*arr));
	assert(arr);
	int size = INIT_SIZE;
	arr->size = size;
	arr->A = malloc(size * sizeof(*(arr->A)));
	assert(arr->A);
	arr->n = 0;
	return arr;
}

// free memory used by array "arr"
void arrayFree(array_t *arr) {
	for (int i = 0; i < arr->n; i++) {
		footpathFree(arr->A[i]);
	}
	free(arr->A);
	free(arr);
}

// shrinks the array, to reduce array size to the same 
//    as the number of element used
void arrayShrink(array_t *arr) {
	if (arr->size != arr->n) {
		// the new size should be at least INIT_SIZE
		arr->size = (arr->n > INIT_SIZE) ? arr->n : INIT_SIZE;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}


// makes sure that array's size exceeds its number of elements
//    ie. there is space for adding new element
void arrayEnableInsert(array_t *arr) {
	if (arr->n == arr->size) {
		arr->size <<= 1;       // same as arr->size *= 2;
		arr->A = realloc(arr->A, arr->size * sizeof(*(arr->A)));
		assert(arr->A);
	}
}

// inserts data "p" into sorted array "arr", ensuring "arr" remain sorted 
void sortedArrayInsert(array_t *arr, footpath_t *p) {
	int i;
	arrayEnableInsert(arr);
	// starting from the end, shift all elements > p one position to the right
	for (i = arr->n - 1; i >= 0 && grade1incmp(p, arr->A[i]) == -1 ; i-- ) {
		arr->A[i + 1] = arr->A[i];
	}
	// now "p" should be in A[i + 1]
	arr->A[i + 1] = p;
	arr->n++;
}

// searches for closest grade1in in sorted array "arr" to "query"
void getClosestGrade(FILE *infoFile, double query, array_t *arr) {
	double difference = getDifference(arr->A[0], query);
	int i=0, found=0;
	// case where there is one footpath in "arr"
	if (arr->n == 1) {
		footpathPrint(infoFile, arr->A[0]);
		fprintf(stdout, "%g --> %g\n", query, getGrade1in(arr->A[0]));
		found = 1;
	}
	else {
		for (i=1; i< arr->n; i++) {
			if (getDifference(arr->A[i], query) < difference) {
				difference = getDifference(arr->A[i], query);
			} 
			// once the absolute difference is greater than the 
			//    difference in the previous node, prints the footpath in previous node
			else if (getDifference(arr->A[i], query) > difference) {
				fprintf(stdout, "%g --> %g\n", query, getGrade1in(arr->A[i-1]));
				footpathPrint(infoFile, arr->A[i-1]);
				found = 1;
				break;
			}
		}
	}
	// case where the closest grade1in is the last index
	if (found == 0) {
		fprintf(stdout, "%g --> %g\n", query, getGrade1in(arr->A[arr->n - 1]));
		footpathPrint(infoFile, arr->A[arr->n - 1]);
	}
}

