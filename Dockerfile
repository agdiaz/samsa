FROM gcc:4.9

COPY . /samsa-c
WORKDIR /samsa-c

RUN gcc -std=c99 -o /samsa-c/bin/samsa-c \
  /samsa-c/src/main.c \
  /samsa-c/src/simulated-annealing/simulated-annealing.c \
  /samsa-c/src/utils/utils.c \
  -lm

CMD ["./bin/samsa-c"]
