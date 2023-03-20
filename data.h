#ifndef _DATA_H_
#define _DATA_H_
#include <stdio.h>

//constant definitions
#define MAX_STRING_LEN 128     /* max length of a string */
#define MAX_LINE_LEN 512       /* max length of a line */
#define MAX_INPUTS 19          /* max number of data inputs */

// data definitions
typedef struct footpath footpath_t;

/*------------ function definitions -----------------------------*/

// skip the header line of .csv file "f"
void footpathSkipHeaderLine(FILE *f);

// reads a footpath from file "f" to build a footpath_t data
// returns the pointer, or NULL if reading is unsuccessful
footpath_t *footpathRead(FILE *f);

// prints a footpath record *p to file "f"
void footpathPrint(FILE *f, footpath_t *p);

// free the memory allocated to a footpath "p"
void footpathFree(void *p);

// return address of footpath "p"
char *getFootpathAddress(void *p);

// compares the address of footpath "p" and returns 0 if they are equal
int addresscmp(char *query, footpath_t *p);

// compares the grade1in of footpath "f" and footpath "p"
//    returns 0 if equal, -1 if f is less than p, 1 if f is greater than p
int grade1incmp(footpath_t *f, footpath_t *p);

// returns the absolute difference between grade1in of footpath "f" and "query"
double getDifference(footpath_t *f, double query);

// returns grade1in of footpath "f"
double getGrade1in(footpath_t *f);

#endif

