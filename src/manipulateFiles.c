#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "manipulateFiles.h"

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
