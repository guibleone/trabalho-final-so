
#include <stdlib.h>
#include <stdio.h>
#include "manipulateFiles.h"

void combineFiles(FILE *file, int fileIndex, FILE *outputFile)
{
  char number[50];
  printf("Lendo dados do arquivo #%d\n", fileIndex);

  int i = 0;
  while (fscanf(file, "%50s", number) == 1)
  {
    fprintf(outputFile, "%s\n", number);
    i++;
  }

  if (feof(file))
    printf("Fim do arquivo #%d.\n", fileIndex);
  else
    fprintf(stderr, "Error reading file #%d.\n", fileIndex);
}
