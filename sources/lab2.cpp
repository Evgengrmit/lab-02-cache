// Copyright 2020 Your Name <your_email>

#include "Investigation.hpp"

int main() {
  Investigation investigation;

  std::ofstream report;
  report.open("../reports/report.txt");
  investigation.Start();
  investigation.MakeReport(report);
  report.close();

  return 0;
}
