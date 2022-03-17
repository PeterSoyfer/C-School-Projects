#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NSYM 256 //number of symbols in ASCII

const char *delim = " .,;:!?()[]"; //word delimiters
const int n_delim = 11;

int is_delim(int);
void wordmaxmin(char*,int*);
void wordlengths(char*,int*,int*);
double wordarithm(int*,int);
double symbolfreq(int*,int);
void symbolprint(FILE*,int*);
void general(void);