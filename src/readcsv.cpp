#include "readcsv.h"


Matrix readCSV(const std::string &input_file, char delim){
    std::string line;

    Matrix v;

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
