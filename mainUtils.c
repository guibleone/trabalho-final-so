#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "manipulateFiles.h"
#include "mainUtils.h"

void processFiles(int argc, char *argv[], FILE *outputFile)
{
    register unsigned int cont = 2;
    while (cont < argc && strcmp(argv[cont], "-o") != 0 && strcmp(argv[cont], "–o") != 0)
    {
        FILE *entryFile = fopen(argv[cont], "r+");
        if (entryFile == NULL)
        {
            fprintf(stderr, "Problem while opening an entry file: %s\n", argv[cont]);
            exit(EXIT_FAILURE);
        }

        combineFiles(entryFile, cont - 1, outputFile); 
        fclose(entryFile);
        cont++;
    }

    if (cont + 1 >= argc)
    {
        fprintf(stderr, "Output file not specified after '-o'.\n");
        exit(EXIT_FAILURE);
    }
}

FILE *openOutputFile(const char *outputFileName)
{
    FILE *outputFile = fopen(outputFileName, "w+");
    if (outputFile == NULL)
    {
        fprintf(stderr, "Problem while opening the output file: %s\n", outputFileName);
        exit(EXIT_FAILURE);
    }
    return outputFile;
}

void handleTime(const struct timespec *start, const struct timespec *end)
{
    double totalTime = (end->tv_sec - start->tv_sec) + (end->tv_nsec - start->tv_nsec) / 1e8;
    printf("Time stamp of reading all files: %f\n", totalTime);
}
