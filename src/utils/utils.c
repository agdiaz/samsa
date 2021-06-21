#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>

#include "utils.h"
#include "../third-party/fasta.h"

/* return a uniform random value in the range 0..n-1 inclusive */
int randRange(int n) {
  int limit;
  int r;

  limit = RAND_MAX - (RAND_MAX % n);
  while((r = rand()) >= limit);

  return r % n;
}

double rand01() {
  return (double)rand() / (double)RAND_MAX;
}

int countFastaFilesInFolder(char* folderPath) {
  DIR* FD;
  struct dirent* in_file;
  int fastaFilesCount = 0;

  /* Scanning the in directory */
  if (NULL == (FD = opendir(folderPath))){
    fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
    return 1;
  }

  while ((in_file = readdir(FD))) {
    if (!strcmp(in_file->d_name, ".") || !strcmp (in_file->d_name, "..")) {
      continue;
    }

    fastaFilesCount++;
  }

  return fastaFilesCount;
}

int readFastaFiles(char* folderPath, char** sequences) {
  DIR* FD;
  struct dirent* in_file;
  FASTAFILE *ffp;
  char *seq;
  char *name;
  int L;
  int folderPathLength = strlen(folderPath);
  int fastaFilenameLength;
  int fastaFilesCount;
  int sequenceIndex;

  /* Scanning the in directory */
  if (NULL == (FD = opendir(folderPath))) {
    fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
    return 1;
  }

  sequenceIndex = 0;
  while ((in_file = readdir(FD))) {
    if (!strcmp(in_file->d_name, ".") || !strcmp (in_file->d_name, "..")) {
      continue;
    }

    fastaFilenameLength = strlen(in_file->d_name);
    char filePath[folderPathLength + 1 + fastaFilenameLength];
    strcpy(filePath, folderPath);
    strcat(filePath, "/");
    strcat(filePath, in_file->d_name);

    ffp = OpenFASTA(filePath);
    while (ReadFASTA(ffp, &seq, &name, &L)) {
      sequences[sequenceIndex] = (char*)malloc(L*sizeof(char));
      strcpy(sequences[sequenceIndex], seq);

      free(seq);
      free(name);
    }
    CloseFASTA(ffp);
    sequenceIndex++;
  }

  return 0;
}

void debug_print_sequences(int sequenceCount, char** sequences) {
  for (int index = 0; index < sequenceCount; index++) {
    printf("%d %s\n", index, sequences[index]);
  }
}

int maxLength(int sequenceCount, char** sequences) {
  int maxSequenceLength = 0;

  for (int index = 0; index < sequenceCount; index++) {
    int sequenceLength = strlen(sequences[index]);

    if (sequenceLength > maxSequenceLength) {
      maxSequenceLength = sequenceLength;
    }
  }

  return maxSequenceLength;
}
