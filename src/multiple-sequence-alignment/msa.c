#include <math.h>

#include "msa.h"
#include "../utils/utils.h"

int createInitialAlignment(int arg0) {
  int r = 1 + randRange(arg0);

  return r;
}

double measureTemperature(int alignment) {
  double cnt = 1;

  for(int i = 1; i < alignment; i++) {
		if ((alignment % i) == 0){
      cnt++;
		}
	}

  return 1 - (1 / cnt);
}

int createNeighborAlignment(int previousAlignment) {
  int gap = randRange(previousAlignment);

  if (rand01() > 0.5) {
    return previousAlignment + gap;
  } else {
    return previousAlignment - gap;
  }
}
