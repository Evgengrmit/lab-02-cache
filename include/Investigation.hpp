// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_INVESTIGATION_HPP_
#define INCLUDE_INVESTIGATION_HPP_

#include "Experiment.hpp"

#include <fstream>
#include <vector>


const size_t bytesInKilobytes = 1024;
// Intel Core i7-9750H
// in bytes
struct SizeOfCaches{
 public:
  const size_t l1 = 384 * bytesInKilobytes;
  const size_t l2 = 1536 * bytesInKilobytes;
  const size_t l3 = 9216 * bytesInKilobytes;
};

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
