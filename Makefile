build:
	gcc -std=c99 -o ./bin/samsa-c \
		./src/main.c \
		./src/simulated-annealing/simulated-annealing.c \
		./src/multiple-sequence-alignment/msa.c \
		./src/utils/utils.c \
		./src/third-party/fasta.c \
		-lm

clean:
	rm -fr ./bin/*
	touch ./bin/.git

run:
	./bin/samsa-c --input /home/adrian/workspace/samsa-c/datasets/ebola --output /home/adrian/workspace/samsa-c/result.msa

docker-build:
	docker build --tag samsa-c .

docker-run:
	docker run samsa-c

build-and-run: build run
