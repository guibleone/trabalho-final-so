/*
  Final project for the discipline of Operational Systems
  at Unicamp.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "mainUtils.h"
#include "manipulateFiles.h"

void *sortNumbers(void *arg){
  int *numbers[] = (*(int * args));
  
}

int main(int argc, char *argv[])
{
  struct timespec start, end;

  if (argc < 4)
  {
    fprintf(stderr, "Usage: %s <nThreads> <inputFiles> -o <outputFile>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  unsigned int nThreads = atoi(argv[1]);
  if (nThreads != 2 && nThreads != 4 && nThreads != 8)
  {
    fprintf(stderr, "Incorrect number of threads: %d\n", nThreads);
    exit(EXIT_FAILURE);
  }


  pthread_t threadsID[nThreads];
  for (register unsigned int i = 0; i < nThreads; i++)
  {
    pthread_create(&threadsID[i], NULL, sortNumbers, numbers);
  }
  


  clock_gettime(CLOCK_MONOTONIC, &start);
  FILE *outputFile = openOutputFile(argv[argc - 1]);

  processFiles(argc, argv, outputFile);
  // sortFile();

  clock_gettime(CLOCK_MONOTONIC, &end);
  handleTime(&start, &end);

  fclose(outputFile);

  return 0;
}
