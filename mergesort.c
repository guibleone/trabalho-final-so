/*
  Final project for the discipline of Operational Systems
  at Unicamp.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mainUtils.h"

int main(int argc, char *argv[])
{
  struct timespec start, end;

  // Ensure we have enough arguments
  if (argc < 4)
  {
    fprintf(stderr, "Usage: %s <nThreads> <inputFiles> -o <outputFile>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // int nThreads = atoi(argv[1]);  // Uncomment to handle thread count if needed
  // printf("%d\n", nThreads);      // Debug print for number of threads

  clock_gettime(CLOCK_MONOTONIC, &start);
  FILE *outputFile = openOutputFile(argv[argc - 1]);

  processFiles(argc, argv, outputFile);

  clock_gettime(CLOCK_MONOTONIC, &end);
  handleTime(&start, &end);

  fclose(outputFile);

  return 0;
}
