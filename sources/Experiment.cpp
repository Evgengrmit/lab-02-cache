// Copyright 2020 Your Name <your_email>

#include "Experiment.hpp"

int Experiment::experimentsCounter = 0;

Experiment::Experiment(const size_t &numbersOfElements)
    : cardinality(numbersOfElements) {
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
    indexes.push_back(i);
  }
}

void Experiment::start() {
  directBypass();
  reverseBypass();
  randomBypass();
}

Experiment::~Experiment() { delete[] buffer; }
int Experiment::doSomething(int value) { return value; }
double Experiment::loopingThroughBuffer() {
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < CYCLES; ++i) {
    for (size_t j = 0; j < cardinality; ++j) {
      doSomething(buffer[j]);
    }
  }
  auto end = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
      .count();
}
void Experiment::warmingUpCache() {
  for (const size_t &i : indexes) {
    doSomething(buffer[i]);
  }
}
void Experiment::directBypass() {
  warmingUpCache();

  time.straightDuration = loopingThroughBuffer();
  std::cout << "Straight bypass duration: " << time.straightDuration << " ms"
            << std::endl;
}
void Experiment::reverseBypass() {
  std::reverse(indexes.begin(), indexes.end());
  warmingUpCache();

  time.reverseDuration = loopingThroughBuffer();
  std::cout << "Reverse bypass duration: " << time.reverseDuration << " ms"
            << std::endl;
}
void Experiment::randomBypass() {
  std::mt19937 g(clock());
  std::shuffle(indexes.begin(), indexes.end(), g);
  warmingUpCache();
  time.randomDuration = loopingThroughBuffer();
  std::cout << "Random bypass duration: " << time.randomDuration << " ms"
            << std::endl;
}
size_t Experiment::getCardinality() const { return cardinality; }
const ExperimentsTimes &Experiment::getTime() const { return time; }
