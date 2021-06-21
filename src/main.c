#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./simulated-annealing/simulated-annealing.h"
#include "./utils/utils.h"

char* inputFolder = "";
char* outputFolder = "";

int printHelp() {
  printf("Welcome to SAMSA-c\n\t-i (--input) /path/to/fasta/folder\n\t-o (--output) /path/to/output/\n\t-h (--help) Display this message.\n");

  return EXIT_SUCCESS;
}

int printBadRequestError() {
  printf("Welcome to SAMSA-c\nWrong arguments: both input and output folder are required. Please read instructions using -h or --help parameter.\n");
  return EXIT_FAILURE;
}

int main(int argCount, char *argVector[]) {
  if (argCount <= 1) {
    return printHelp();
  }

  for (int argIndex = 1; argIndex < argCount; argIndex++)
  {
    char* argValue = argVector[argIndex];

    if (strcmp(argValue, "-i") == 0 || strcmp(argValue, "--input") == 0) {
      inputFolder = argVector[argIndex + 1];
    } else if (strcmp(argValue, "-o") == 0 || strcmp(argValue, "--output") == 0) {
      outputFolder = argVector[argIndex + 1];
    } else if (strcmp(argValue, "-h") == 0 || strcmp(argValue, "--help") == 0) {
      return printHelp();
    }
  }

  if (strlen(inputFolder) == 0 || strlen(outputFolder) == 0) {
    return printBadRequestError();
  }

  printf("Ready to read files from %s and write result in %s\n", inputFolder, outputFolder);


  int fastaFilesCount = countFastaFilesInFolder(inputFolder);
  char* sequences[fastaFilesCount];

  readFastaFiles(inputFolder, sequences);
  debug_print_sequences(fastaFilesCount, sequences);

  int bestAlignment = execute(inputFolder);
  return EXIT_SUCCESS;
}
