#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

#include "simulated-annealing.h"

#include "../multiple-sequence-alignment/msa.h"
#include "../utils/utils.h"

int execute(char* inputFolder) {
  srand(time(NULL));

  int bestAlignment = createInitialAlignment(100);
  double bestAlignmentEnergy = measureTemperature(bestAlignment);

  printf("iter,temperature,best-alignment,best-alignment-energy,neighbor-alignment,neighbor-alignment-energy\n");
  int iteration_count = 0;

  for (double currentTemperature = MAX_TEMPERATURE; currentTemperature >= MIN_TEMPERATURE; currentTemperature *= (1-COOLING_RATE), iteration_count++) {
    int neighborAlignment = createNeighborAlignment(bestAlignment);
    double neighborAlignmentEnergy = measureTemperature(neighborAlignment);

    printf("%04d,%04.3f,%04d,%0.3f,%04d,%0.3f\n", iteration_count, currentTemperature, bestAlignment, bestAlignmentEnergy, neighborAlignment, neighborAlignmentEnergy);

    if (neighborAlignmentEnergy < bestAlignmentEnergy) {
      bestAlignment = neighborAlignment;
      bestAlignmentEnergy = neighborAlignmentEnergy;
    } else {
      double deltaEnergy = neighborAlignmentEnergy - bestAlignmentEnergy;
      double r = rand01();

      if (r < exp((deltaEnergy * -1) / (BOLTZMANN_CONSTANT * currentTemperature))) {
        bestAlignment = neighborAlignment;
        bestAlignmentEnergy = neighborAlignmentEnergy;
      }
    }
  }

  return bestAlignment;
}
