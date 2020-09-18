// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_INVESTIGATION_HPP_
#define INCLUDE_INVESTIGATION_HPP_

#include "Experiment.hpp"

#include <fstream>
#include <vector>


const size_t BYTES_IN_KILOBYTES = 1024;
// Intel Core i7-9750H
// in bytes
const size_t L1 = 384 * BYTES_IN_KILOBYTES;
const size_t L2 = 1536 * BYTES_IN_KILOBYTES;
const size_t L3 = 9216 * BYTES_IN_KILOBYTES;
struct BufferSize {
  double minSize;
  double currentSize;
  double maxSize;
};

class Investigation {
 public:
  Investigation();
  Investigation(const size_t &min, const size_t &max);
  void Start();
  void MakeReport(std::ofstream &file);
  virtual ~Investigation();

 private:
  BufferSize bufferInfo{};
  std::vector<Experiment *> results;
};
#endif  // INCLUDE_INVESTIGATION_HPP_
