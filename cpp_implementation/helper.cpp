#include <vector> 
#include <stdio.h>
#include <unistd.h> 
#include <fstream> 
#include "helper.h"

/* A file for helper function implmentation.*/

std::vector<double> 
populate_vector(double start, double inc, int n){ 

    /* Returns a vector v populated by {start - inc, start - 2* inc, ... , start - n*inc}*/

	std::vector<double> v; 
	v.reserve(n-1);	
	for (int i = 1; i < n; i++){ 
        v.push_back(start - inc*i); 
    }

    return v; 
}

void 
read_from_file(int file){ 
    /* reads the contents of a file stream and prints to stdout*/


    FILE *stream; //the FILE struct identifies a stream and info needed to control it
    stream = fdopen(file, "r"); 
    int c; //fgetc returns an unsigned char cast to an int
    while ((c= fgetc(stream) )!= EOF) { 
        putchar (c); 
    }
    
}

void slice_c_str(char* str, char * buffer, size_t start, size_t end){ 
    size_t pos = 0; 

    for (size_t i = start; i <= end; i++){ 
        buffer[pos] = str[i]; pos++;
    }

    buffer[pos] = 0; 
}

