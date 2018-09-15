#ifndef READCSV_H
#define READCSV_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "util.h"

Matrix readCSV(const std::string &input_file, char delim);

#endif