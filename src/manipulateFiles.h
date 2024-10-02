#ifndef _MANIPULATEFILES_H
#define _MANIPULATEFILES_H

#include <stdio.h>

void processFiles(int argc, char *argv[], FILE *outputFile);
FILE *openOutputFile(const char *outputFileName);
void combineFiles(FILE *file, int fileIndex, FILE *outputFile);

#endif
