#ifndef READCSV_H
#define READCSV_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "util.h"

std::vector<std::vector<double> > readCSV(const std::string &input_file, char delim);

#endif
