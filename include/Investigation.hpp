// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_INVESTIGATION_HPP_
#define INCLUDE_INVESTIGATION_HPP_

#include "Experiment.hpp"

#include <fstream>
#include <vector>


const size_t kBytesInKilobytes = 1024;
// Intel Core i7-9750H
// in bytes
struct SizeOfCaches{
 public:
  const size_t l1 = 384 * kBytesInKilobytes;
  const size_t l2 = 1536 * kBytesInKilobytes;
  const size_t l3 = 9216 * kBytesInKilobytes;
};

struct BufferSize {
  double minSize;
  double currentSize;
  double maxSize;
};

class Investigation {
 public:
  Investigation();
  void Start();
  void MakeReport(std::ofstream &file);
  virtual ~Investigation();

 private:
  BufferSize bufferInfo{};
  std::vector<Experiment *> results;
};
#endif  // INCLUDE_INVESTIGATION_HPP_
