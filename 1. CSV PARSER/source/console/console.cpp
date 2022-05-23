#include "console.h"

#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <fmt/format.h>

#define print fmt::print

console::console() {
  execute();
}

void console::execute() {
  print("This program will parse and read a CSV file\n");
  loop();
}

void console::loop() {
  selectFile();
  while (true) {
	print("0. Exit\n"
		  "1. Change CSV file\n"
		  "2. Display whole CSV file\n"
		  "3. Display row or column\n"
		  "4. Search table by argument\n"
		  "5. Sort table\n"
		  "6. Queue up and execute sorting algorithms\n");
	switch (GIBI(0, 6)) {
	  case 0:
		print("EXITING\n");
		return;
	  case 1:
		selectFile();
		break;
	  case 2:
		parser->displayTable(neatly);
		break;
	  case 3:
		displayPart();
		break;
	  case 4:
		search();
		break;
	  case 5:
		sort();
		break;
	  case 6:
		queueUp();
		break;
	}
  }
}

void console::selectFile() {
  int input = 0;
  filepath = "";
  system("dir res");
  while (input == 0) {
	print("\nSelect a file to parse:\n");
//	print("0. RETURN\n1. TEST.csv\n2. TESTII.csv\n3.TESTIII.csv\n4. I.scv\n5.IV.csv\n");
	print("0. RETURN\n1. TEST.csv\n2. TESTII.csv\n3.TESTIII.csv\n4. I.scv\n");
	input = GIBI(0, 4);
	switch (input) {
	  case 0:
		if(!firstset){
		  print("\nMUST SELECT FILE ON START!\n");
		  break;
		}
		return;
	  case 1:
		filepath = "../source/res/TEST.csv";
		neatly = true;
		firstset = true;
		break;
	  case 2:
		filepath = "../source/res/TESTII.csv";
		neatly = true;
		firstset = true;
		break;
	  case 3:
		filepath = "../source/res/TESTIII.csv";
		neatly = true;
		firstset = true;
		break;
	  case 4:
		filepath = "../source/res/I.csv";
		neatly = false;
		firstset = true;
		break;/*
	  case 5:
		filepath = "res/IV.csv";
		neatly = false;
		break;*/
	}
  }
  if (parser != nullptr) {
	DTYPES::CSVLL* temp = parser;
	parser = nullptr;
	delete (temp);
  }
  parser = new DTYPES::CSVLL(filepath);
  std::cout << "\n" << filepath;
  print(" SELECTED.\n");
}

void console::displayPart() {
  while (true) {
	print("\n0. EXIT\n1. DISPLAY ROW\n2. DISPLAY COLUMN\n");
	int input = GIBI(0, 2);
	int arg = 0;
	switch (input) {
	  case 0:
		return;
	  case 1:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT ROW TO DISPLAY:");
		arg = GIBI(1, parser->getHead()->getTotalElements());
		arg--;
		parser->displayRow(arg);
		print("\n");
		break;
	  case 2:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT COLUMN TO DISPLAY:");
		arg = GIBI(1, parser->length());
		arg--;
		parser->displayColumn(arg);
		print("\n");
		break;
	}
  }
}

void console::search() {
  while (true) {
	print("\n0. EXIT\n1. GENERAL SEARCH\n2. SEARCH BY ROW\n3. SEARCH BY COLUMN\n4. BINARY SEARCH\n");
	int input = GIBI(0, 4);
	int index = 0;
	std::string arg = "";
	switch (input) {
	  case 0:
		return;
	  case 1:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nEnter KEYWORD: ");
		arg = GIBSWW();
		ALGO::LSearch(arg, parser);
		print("\n");
		break;
	  case 2:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT ROW:");
		index = GIBI(1, parser->getHead()->getTotalElements());
		index--;
		print("\nEnter KEYWORD: ");
		arg = GIBSWW();
		ALGO::LSearch(arg, ALGO::ROW, index, parser);
		print("\n");
		break;
	  case 3:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT COLUMN:");
		index = GIBI(1, parser->length());
		index--;
		print("\nEnter KEYWORD: ");
		arg = GIBSWW();
		ALGO::LSearch(arg, ALGO::COLUMN, index, parser);
		print("\n");
		break;
	  case 4:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nEnter KEYWORD: ");
		arg = GIBSWW();
		ALGO::BSearch(arg, parser);
		print("\n");
		break;
	}
  }
}

void console::sort() {
  while (true) {
	print("\n0. EXIT\n1. SORT COLUMN FROM HIGHEST TO LOWEST(10-0 OR Z-A)\n2. SORT COLUMN FROM LOWEST TO HIGHEST(0-10 OR A-Z)\n3. INVERT ROW\n4. INVERT COLUMN\n");
	int input = GIBI(0, 4);
	int index = 0;
	switch (input) {
	  case 0:
		return;
	  case 1:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT COLUMN:");
		index = GIBI(1, parser->length());
		index--;
		ALGO::ISort(false, parser, index);
		print("\n");
		break;
	  case 2:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT COLUMN:");
		index = GIBI(1, parser->length());
		index--;
		ALGO::ISort(true, parser, index);
		print("\n");
		break;
	  case 3:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT ROW:");
		index = GIBI(1, parser->getHead()->getTotalElements());
		index--;
		ALGO::REVERSE(false, parser, index);
		print("\n");
		break;
	  case 4:
		if(neatly){
		  parser->displayTable(neatly);
		}
		print("\nSELECT COLUMN:");
		index = GIBI(1, parser->length());
		index--;
		ALGO::REVERSE(true, parser, index);
		print("\n");
		break;
	}
  }
}

//  ALGO::CSVQUEUE L1Q(&L1);
//  L1Q.queue(ALGO::ALGOFUNC::LSEARCH, "123");
//  L1Q.queue(ALGO::ALGOFUNC::LSEARCH2, "01", ALGO::AXIS::COLUMN, 2);
//  L1Q.queue(ALGO::ALGOFUNC::BSEARCH, "UNIVERSITY OF UTAH");
//  L1Q.queue(ALGO::ALGOFUNC::ISORT, true, 0);
//  L1Q.execute();
void console::queueUp() {
  while (true) {
	bool cyclestate = true;
	print("\n0. EXIT\n1. EXECUTE QUEUE\n2. QUEUE UP SEARCH\n3. QUEUE UP SORTING ALGORITHM\n");
	int input = GIBI(0, 3);
	int index = 0;
	std::string arg = "";
	switch (input) {
	  case 0:
		return;
	  case 1:
		if (QUEUE == nullptr) {
		  print("\nQUEUE DOES NOT EXIST\n");
		  break;
		}
		QUEUE->execute();
		delete (QUEUE);
		QUEUE = nullptr;
		break;
	  case 2:
		if (QUEUE == nullptr) {
		  QUEUE = new ALGO::CSVQUEUE(parser);
		}
		while (cyclestate) {
		  print("\n0. RETURN\n1. GENERAL SEARCH\n2. SEARCH BY ROW\n3. SEARCH BY COLUMN\n4. BINARY SEARCH\n");
		  int input = GIBI(0, 4);
		  int index = 0;
		  std::string arg = "";
		  switch (input) {
			case 0:
			  cyclestate = false;
			  break;
			case 1:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nEnter KEYWORD: ");
			  arg = GIBSWW();
			  QUEUE->queue(ALGO::ALGOFUNC::LSEARCH, arg);
			  print("SEARCH ADDED\n");
			  break;
			case 2:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nSELECT ROW:");
			  index = GIBI(1, parser->getHead()->getTotalElements());
			  index--;
			  print("\nEnter KEYWORD: ");
			  arg = GIBSWW();
			  QUEUE->queue(ALGO::ALGOFUNC::LSEARCH2, arg, ALGO::ROW, index);
			  print("SEARCH BY ROW ADDED\n");
			  break;
			case 3:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nSELECT COLUMN:");
			  index = GIBI(1, parser->length());
			  index--;
			  print("\nEnter KEYWORD: ");
			  arg = GIBSWW();
			  QUEUE->queue(ALGO::ALGOFUNC::LSEARCH2, arg, ALGO::COLUMN, index);
			  print("SEARCH BY COLUMN ADDED\n");
			  break;
			case 4:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nEnter KEYWORD: ");
			  arg = GIBSWW();
			  QUEUE->queue(ALGO::ALGOFUNC::BSEARCH, arg);
			  print("BINARY SEARCH ADDED\n");
			  break;
		  }
		}
		break;
	  case 3:
		if (QUEUE == nullptr) {
		  QUEUE = new ALGO::CSVQUEUE(parser);
		}
		while (cyclestate) {
		  print("\n0. RETURN\n1. SORT COLUMN FROM HIGHEST TO LOWEST(10-0 OR Z-A)\n2. SORT COLUMN FROM LOWEST TO HIGHEST(0-10 OR A-Z)\n3. INVERT ROW\n4. INVERT COLUMN\n");
		  int input = GIBI(0, 4);
		  int index = 0;
		  switch (input) {
			case 0:
			  cyclestate = false;
			  break;
			case 1:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nSELECT COLUMN:");
			  index = GIBI(1, parser->length());
			  index--;
			  QUEUE->queue(ALGO::ALGOFUNC::ISORT, false, index);
			  print("ADD SORT COLUMN FROM HIGHEST TO LOWEST\n");
			  break;
			case 2:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nSELECT COLUMN:");
			  index = GIBI(1, parser->length());
			  index--;
			  QUEUE->queue(ALGO::ALGOFUNC::ISORT, true, index);
			  print("ADD SORT COLUMN FROM LOWEST TO HIGHEST\n");
			  break;
			case 3:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nSELECT ROW:");
			  index = GIBI(1, parser->getHead()->getTotalElements());
			  index--;
			  QUEUE->queue(ALGO::ALGOFUNC::INVERT, false, index);
			  print("ADDED INVERT ROW\n");
			  break;
			case 4:
			  if(neatly){
				parser->displayTable(neatly);
			  }
			  print("\nSELECT COLUMN:");
			  index = GIBI(1, parser->length());
			  index--;
			  QUEUE->queue(ALGO::ALGOFUNC::INVERT, true, index);
			  print("ADDED INVERT COLUMN\n");
			  break;
		  }
		}
		break;
	}
  }
}

bool console::Exists(const std::string &filepath) {
  std::ifstream file(filepath);
  file.open(filepath, std::ifstream::in);
  if (file.is_open()) {
	return true;
  } else {
	return false;
  }
}

int console::GIBI() {
  std::string input;
  int converted;
  while (true) {
	std::cin >> input;
	try {
	  converted = std::stoi(input);
	  break;
	}
	catch (std::invalid_argument &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI INVALID ARGUMENT!: ", input, "\n");
	}
	catch (std::out_of_range &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI OUT OF RANGE!: ", input, "\n");
	}
  }
  return converted;
}

int console::GIBI(int min, int max) {
  while (true) {
	int input = GIBI();
	if (input >= min && input <= max) {
	  return input;
	} else {
	  print("!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !OUT OF RANGE INPUT: ", input, " in", min, " ", max);
	}
  }
}

double console::GIBD() {
  std::string input;
  double converted;
  while (true) {
	std::cin >> input;
	try {
	  converted = std::stod(input);
	  break;
	}
	catch (std::invalid_argument &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI INVALID ARGUMENT!: ", input, "\n");
	}
	catch (std::out_of_range &i) {
	  std::cout << i.what();
	  print("\n!EXCEPTION!\n");
	  print("\n!EXCEPTION!\n !STOI OUT OF RANGE!: ", input, "\n");
	}
  }
  return converted;
}

std::string console::GIBS() {
  std::string input;
  std::cin >> input;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return input;
}

std::string console::GIBSWW() {
  std::string input;
  std::getline(std::cin >> std::ws, input);
  return input;
}

int console::Get_Input_Yes_Or_No() {
  while (true) {
	print("Answer with: (1) Yes; (0) No.\n");
	int input = GIBI(0, 1);

	switch (input) {
	  case 0:
		print("\nNo selected!\n");
		return input;
	  case 1:
		print("\nYes selected!\n");
		return input;
	  default:
		print("\n!EXCEPTION!\n");
		break;
	}
  }
}