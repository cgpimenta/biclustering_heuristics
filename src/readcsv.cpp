#include "readcsv.h"

std::vector<std::vector<double> > readCSV(const std::string &input_file, char delim){
    std::string line;

    std::vector<std::vector<double> > v;

    std::ifstream myfile(input_file.c_str());

    if (myfile.is_open()){
        while (getline(myfile, line)){
            v.push_back(split<std::vector<double> >(line, delim));
        }

        myfile.close();
    }
    else{
        std::cerr << "Unable to open file"; 
    }
    return v;
}
