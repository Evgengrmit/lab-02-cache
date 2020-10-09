// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_EXPERIMENT_HPP_
#define INCLUDE_EXPERIMENT_HPP_
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iostream>
#include <random>
#include <string>
#include <utility>
#include <vector>

const size_t kcycles = 1000;

struct ExperimentsTimes {
  double straightDuration;
  double reverseDuration;
  double randomDuration;
};
class Experiment {
 public:
  static int experimentsCounter;
  explicit Experiment(const size_t &numbersOfElements);
  void start();
  [[nodiscard]] size_t getCardinality() const;
  [[nodiscard]] const ExperimentsTimes &getTime() const;
  ~Experiment();

 private:
  ExperimentsTimes time;
  int *buffer;
  size_t cardinality;
  std::vector<size_t> indexesForWarming;
  std::vector<size_t> indexesForBuffer;
  int doSomething(int value);
  void warmingUpCache();
  auto loopingByArray();
  void directBypass();
  void reverseBypass();
  void randomBypass();
};
#endif  // INCLUDE_EXPERIMENT_HPP_
