#include <string.h>
#include "../utils/utils.h"

int createInitialAlignment(int sequencesCount, char** sequences, char** alignment) {
  int maxSequenceLength = maxLength(sequencesCount, sequences);

  for (int sequenceIndex = 0; sequenceIndex < sequencesCount; sequenceIndex++ ){
    alignment[sequenceIndex] = (char*) malloc(maxSequenceLength * sizeof(char));

    strcpy(alignment[sequenceIndex], alignment[sequenceIndex]);
    int trailingGap = maxSequenceLength - strlen(alignment[sequenceIndex]);

  }


  return 0;
}

double measureAlignmentTemperature(int sequencesCount, char** sequences) {
  int maxSequenceLength = maxLength(sequencesCount, sequences);

  return 0.0;
}

int createNeighborAlignment(int sequencesCount, char** sequences, char** alignment) {
  return 0;
}

/*
012345
ABCD-
ABCD-
ABC--
ABCDE
*/