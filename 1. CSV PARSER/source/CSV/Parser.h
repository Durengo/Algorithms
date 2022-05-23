#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "CSV.h"

namespace CSV {

int readCSV(const std::string &FILEPATH, CSV newCSV);
void parseCSV(std::fstream &CSVFILE, std::vector<CSV> &newCSV);
void parseColumns(const std::string &line, std::vector<CSV> &newCSV);
void parseElements(const std::string &line, std::vector<CSV> &newCSV);

//void strinToInt(std::vector<CSV> &newCSV);

}