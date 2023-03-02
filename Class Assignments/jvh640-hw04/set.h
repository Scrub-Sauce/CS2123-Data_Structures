#ifndef _set_h
#define _set_h

typedef int setElementT;
typedef struct setCDT *setADT;

setADT setNew(); /* Create a new empty set */
void setFree(setADT S); /* Free the space allocated for the set S */
int setInsertElementSorted(setADT S, setElementT E); /* If not successful return 0; otherwise return the number of elements in the set */
setADT setUnion (setADT A, setADT B); /* Returns a new set containing A Union B*/
setADT setIntersection (setADT A, setADT B); /* Returns a new set containing A Intersection B */
setADT setDifference(setADT A, setADT B); /* Returns a new set containing A Difference B */
int setCardinality(setADT S); /* Return the number of elements in S */
void setPrint(setADT S, char *name); /* print elements of S, in format <Set> = {<Elements>} */

#endif