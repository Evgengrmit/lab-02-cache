// Copyright 2020 Your Name <your_email>

#include "Experiment.hpp"

int Experiment::experimentsCounter = 0;

Experiment::Experiment(const size_t &numbersOfElements)
    : time{}, cardinality{numbersOfElements} {
  experimentsCounter++;
  std::cout << "_____________________________________" << std::endl;
  std::cout << "Experiment № " << experimentsCounter << std::endl;
  std::cout << "Numbers of elements: " << cardinality << std::endl;
  buffer = new int[cardinality];
  std::mt19937 generator(clock());
  for (size_t i = 0; i < cardinality; ++i) {
    buffer[i] = generator();
  }
  for (size_t i = 0; i < cardinality; i += 16) {
    indexesForWarming.push_back(i);
  }
  for (size_t i = 0; i < cardinality; i++) {
    indexesForBuffer.push_back(i);
  }
}

void Experiment::start() {
  directBypass();
  reverseBypass();
  randomBypass();
}

Experiment::~Experiment() { delete[] buffer; }
int Experiment::doSomething(int value) { return value; }

void Experiment::warmingUpCache() {
  for (const size_t &i : indexesForWarming) {
    doSomething(buffer[i]);
  }
}
void Experiment::directBypass() {
  warmingUpCache();
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < cycles; ++i) {
    for (const size_t &j : indexesForBuffer) {
      doSomething(buffer[j]);
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  time.straightDuration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();
  std::cout << "Straight bypass duration: " << time.straightDuration << " ms"
            << std::endl;
}
void Experiment::reverseBypass() {
  std::reverse(indexesForWarming.begin(), indexesForWarming.end());
  warmingUpCache();
  std::reverse(indexesForBuffer.begin(), indexesForBuffer.end());
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < cycles; ++i) {
    for (const size_t &j : indexesForBuffer) {
      doSomething(buffer[j]);
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  time.reverseDuration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();
  std::cout << "Reverse bypass duration: " << time.reverseDuration << " ms"
            << std::endl;
}
void Experiment::randomBypass() {
  std::mt19937 g(clock());
  std::shuffle(indexesForWarming.begin(), indexesForWarming.end(), g);
  warmingUpCache();
  std::shuffle(indexesForBuffer.begin(), indexesForBuffer.end(), g);
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < cycles; ++i) {
    for (const size_t &j : indexesForBuffer) {
      doSomething(buffer[j]);
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  time.randomDuration =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
          .count();
  std::cout << "Random bypass duration: " << time.randomDuration << " ms"
            << std::endl;
}
size_t Experiment::getCardinality() const { return cardinality; }
const ExperimentsTimes &Experiment::getTime() const { return time; }
