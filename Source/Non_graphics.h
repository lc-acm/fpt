

#ifndef NG_aabbxyz_9875678__2
#define NG_aabbxyz_9875678__2


#include <stdio.h>
#include <math.h>
#include <stdlib.h> // drand48, atoi
#include <unistd.h> // usleep
#include <time.h> // for the get_time stuff
#include <sys/time.h> 



int check_input_error_flag () ;

int inI () ;
// input an integer
// its value is returned


void outI (int x) ;
// output an integer


double inD () ;
// input a double
// its value is returned


void outD (double x) ;
// output a double...switches to scientific notation
// for the extremely small and the extremely large



void inS (void *p) ;
// the wisdom of the void * 
// allows for the input to go into
// a packed arrary of doubles (for instance)

void outS (const void *p) ;
// the wisdom of the void * 
// allows for the output to come from
// a packed arrary of doubles (for instance)



void pack (void *destination, void *source) ;
// pack a null-terminated array of double-characters
// into an array of single-byte-characters
// The null terminator is also packed
// destination and source can point to the same
// actual space.


void unpack (void *destination, void *source) ;
// unpack a null-terminated array of single-byte
// characters into an array of  double-characters.
// the null terminator is also unpacked.
// destination and source can point to the same
// actual space provided it is of sufficient size
// to hold the unpacked data.



int get_timeI (int *hms) ;
// hms had better be at least 3 ints long
// returns 1 for success, 0 for failure
// which is the opposite of what the standard
// gettimeofday returns


int get_timeD (double *hms) ;
// hms had better be at least 3 doubles long
// returns 1 for success, 0 for failure
// which is the opposite of what the standard
// gettimeofday returns



///////////////////////////////////////////////////////



double ind () ;
// synonym for inD

void outd (double x) ;
// synonym for outD

void outsci (double x) ;
// output in scientific notation

void outs (const void *p) ;
// synonym for outS

int get_time (double *hms) ;
// synonym for get_timeD

double loge (double x) ;
// synonym for log

double rem (double a, double b) ;
// synonym for fmod

double quo (double a, double b) ;
// whole number of (a divided by b) rounded toward zero


int mki (double x) ;
// convert doubles to ints in [-billion,billion] 
// symmetric about zero
// not really a tool most people want to use, but you
// might use it in a preprocessor


int chka (double x, int n) ;
// Knowing the size, n, of an array, check if x (after rounding)
// is an in-range array subscript. If not, print an error message 
// and exit the program, otherwise return the rounded value.
// Usable in a preprocessor.


#endif
