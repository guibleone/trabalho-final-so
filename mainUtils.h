#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#include <stdio.h>

// Function prototypes
void processFiles(int argc, char *argv[], FILE *outputFile );
FILE *openOutputFile(const char *outputFileName);
void handleTime(const struct timespec *start, const struct timespec *end);

#endif
