// Copyright 2020 Your Name <your_email>

#include "Investigation.hpp"

Investigation::Investigation() {
  const SizeOfCaches myCache;
  bufferInfo.minSize = 0.5 * myCache.l1;
  bufferInfo.currentSize = bufferInfo.minSize;
  bufferInfo.maxSize = 1.5 * myCache.l3;
}

void Investigation::Start() {
  size_t numberOfElements = bufferInfo.minSize / sizeof(int);
  size_t degree = std::log2(bufferInfo.minSize);
  while (bufferInfo.currentSize <= bufferInfo.maxSize) {
    auto *experiment = new Experiment(numberOfElements);
    experiment->start();
    results.push_back(experiment);
    degree++;
    bufferInfo.currentSize = pow(2, degree);
    numberOfElements = bufferInfo.currentSize / sizeof(int);
  }
  if (bufferInfo.currentSize != bufferInfo.maxSize) {
    auto *experiment = new Experiment(bufferInfo.maxSize / sizeof(int));
    experiment->start();
    results.push_back(experiment);
  }
}
void Investigation::MakeReport(std::ofstream &file) {
  file << "investigation:\n";
  file << "\ttravel_variant: Direct\n";
  file << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    file << "\t- experiment:\n";
    file << "\t\tnumber: " << i + 1 << "\n";
    file << "\t\tinput data:\n";
    file << "\t\t\tbuffer size: \""
         << results[i]->getCardinality() * sizeof(int) / 1024 << " kB\"\n";
    file << "\t\tresults:\n";
    file << "\t\t\tduration: \"" << results[i]->getTime().straightDuration
         << " ms\"\n";
  }
  file << "\n";
  file << "investigation:\n";
  file << "\ttravel_variant: Reverse\n";
  file << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    file << "\t- experiment:\n";
    file << "\t\tnumber: " << i + 1 << "\n";
    file << "\t\tinput data:\n";
    file << "\t\t\tbuffer size: \""
         << results[i]->getCardinality() * sizeof(int) / 1024 << " kB\"\n";
    file << "\t\tresults:\n";
    file << "\t\t\tduration: \"" << results[i]->getTime().reverseDuration
         << " ms\"\n";
  }
  file << "\n";
  file << "investigation:\n";
  file << "\ttravel_variant: Random\n";
  file << "\texperiments:\n";
  for (size_t i = 0; i < results.size(); i++) {
    file << "\t- experiment:\n";
    file << "\t\tnumber: " << i + 1 << "\n";
    file << "\t\tinput data:\n";
    file << "\t\t\tbuffer size: \""
         << results[i]->getCardinality() * sizeof(int) / 1024 << " kB\"\n";
    file << "\t\tresults:\n";
    file << "\t\t\tduration: \"" << results[i]->getTime().randomDuration
         << " ms\"\n";
  }
  file << "\n";
}

Investigation::~Investigation() {
  for (auto element : results) {
    delete element;
  }
  results.clear();
}
