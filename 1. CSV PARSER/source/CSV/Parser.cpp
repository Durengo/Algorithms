#include "Parser.h"

namespace CSV {

/*int readCSV(const std::string &FILEPATH, CSV &newCSV) {
  std::fstream CSVFILE;
  CSVFILE.open(FILEPATH, std::ios::in);
  if (CSVFILE.is_open()) { std::cout << "FILE OPENED SUCCESSFULLY\n"; }
  else { std::cout << "FILE FAILED TO OPEN\n"; return -1; }
  parseCSV(CSVFILE, newCSV);
  return 0;
}

void parseCSV(std::fstream &CSVFILE, std::vector<CSV> &newCSV) {
  std::string line, word, temp;

  std::cout << "Loading File..." << std::endl;

  getline(CSVFILE, line);
  parseColumns(line, newCSV);

  while (getline(CSVFILE, line)) {
	parseElements(line, newCSV);
  }
}

void parseColumns(const std::string &line, std::vector<CSV> &newCSV) {
  std::string main = line;
  std::string temp;
  bool firstColumnChecked = false;

  while (!main.empty()) {
	if (main.length() <= 4) {
	  main = "";
	  break;
	}
	//First column
	if (main.find(',') != std::string::npos && !firstColumnChecked) {
	  firstColumnChecked = true;

	  temp = main.substr(1, main.find(',', +1) - 2);
	  main = main.substr(main.find(',', +1), main.length());

	  CSV col;
	  col.setCategory(temp);
	  newCSV.push_back(col);
	}
	//Second column
	if (main.find(',') != std::string::npos) {

	  temp = main.substr(2, main.find(',', +1) - 3);
	  main = main.substr(main.find(',', +1), main.length());

	  CSV col;
	  col.setCategory(temp);
	  newCSV.push_back(col);
	}
  }
}

void parseElements(const std::string &line, std::vector<CSV> &newCSV) {
  std::string main = line;
  std::string temp;
  int colcount = 0;
  bool firstColumnChecked = false;
  //std::cout << main << "\n";
  bool mode = false;

  while (!main.empty()) {
	if (main.length() == 1) {
	  main = "";
	  break;
	}
	if (main.find(',') != std::string::npos) {
	  temp = main.substr(main.find('"') + 1, main.find('"', +1) - 1);
	  main = main.substr(main.find('"', +2) + 2, main.length());

	  newCSV[colcount].setElements(temp);
	  colcount++;
	  //std::cout << "temp : " << temp << "\n";
	  //std::cout << "main : " << main << "\n";
	}
  }
}*/



}