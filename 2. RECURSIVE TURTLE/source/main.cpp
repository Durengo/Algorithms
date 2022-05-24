#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <limits>

//#define CTURTLE_HEADLESS //Define to configure CTurtle for Headless mode.
//#define CTURTLE_HEADLESS_SAVEDIR "./test.gif" //Optional define, default is "./cturtle.gif".
//#define CTURTLE_HEADLESS_WIDTH 800 //Optional define, default is 400
//#define CTURTLE_HEADLESS_HEIGHT 600 //Optional define, default is 300
#include "CTurtle.hpp"

int factor = 1;

bool cycle = true;

void execute();
int fib(int number);
bool isFibonacci(int num);
void drawFibonacci(cturtle::Turtle &turtle, int n, int factor);
void drawFibonacciStep(cturtle::Turtle &turtle, int n, int factor);
void moveT(cturtle::Turtle &turtle, bool cycle, int fib);

//CONSOLE
int GIBI();
int GIBI(int min, int max);
double GIBD();
std::string GIBS();
std::string GIBSWW();
int Get_Input_Yes_Or_No();

int main() {

  while (true) {
	int input = 0;
	bool innerloop = true;
	std::cout << "This program will introduce what is the Fibonacci sequence and how it can be represented in a recursive programming.\n";
	std::cout << "0. Exit\n"
				 "--------------------------THEORY--------------------------\n"
				 "1. What is a Fibonacci sequence?\n"
				 "2. Fibonacci in recursive programming?\n"
				 "3. PSEUDO CODE FOR FIBONACCI SEQUENCE\n"
				 "4. EXECUTE FIBONACCI SEQUENCE N AMOUNT OF TIMES\n"
				 "5. CHECK IF A NUMBER IS IN A FIBONACCI SEQUENCE\n"
				 //"----------------------------------------------------------\n"
				 "--------------------------VISUAL--------------------------\n"
				 "6. Draw a Fibonacci sequence\n"
				 //"7. Draw a Fibonacci sequence step by step\n"
				 "----------------------------------------------------------\n";
	switch (GIBI(0, 6)) {
	  case 0:
		std::cout << "EXITING\n";
		return 0;
	  case 1:
		std::cout << "\n\n\n";
		std::cout << "A Fibonacci sequence is the sum of the two preceding numbers.\n";
		std::cout << "A Fibonacci sequence starts from the numbers 0 and 1.\n";
		std::cout << "\n\n\n";
		break;
	  case 2:
		std::cout << "\n\n\n";
		std::cout << "In programming the Fibonacci sequence can be represented in a recursive manner.\n";
		std::cout << "Recursion is the process in which a function calls itself directly or indirectly.\n";
		std::cout << "\n\n\n";
		break;
	  case 3:
		std::cout << "\n\n\n";
		std::cout << "Here is a pseudocode example of a recurring Fibonacci sequence:\n\n";
		std::cout << "FUNCTION FIBONACCI (A)\n";
		std::cout << "IF A <=2 THEN\n";
		std::cout << "RETURN 1\n";
		std::cout << "ELSE RETURN FIBONACCI (A-1) + FIBONACCI (A-2)\n";
		std::cout << "\n\n\n";
		break;
	  case 4:
		while (innerloop) {
		  std::cout << "\n\n\n";
		  std::cout << "ENTER THE AMOUNT OF TIMES TO CYCLE THROUGH THE FIBONACCI SEQUENCE (0 TO EXIT): ";
		  input = GIBI();
		  switch (input) {
			case 0:
			  innerloop = false;
			  break;
			default:
			  std::cout << "|";
			  for(int i = 0; i < input; i++){
				std::cout << fib(i) << " | ";
			  }
			 // std::cout << "THE NUMBER AT INDEX: " << input << " is " << fib(input - 1);
			  std::cout << "\n\n\n";
			  break;
		  }
		}
		break;
	  case 5:
		while (innerloop) {
		  std::cout << "\n\n\n";
		  std::cout << "ENTER A NUMBER TO CHECK IF IT IS A FIBONACCI NUMBER (0 TO EXIT): ";
		  input = GIBI();
		  switch (input) {
			case 0:
			  innerloop = false;
			  break;
			default:
			  isFibonacci(input);
			  std::cout << "\n\n\n";
			  break;
		  }
		}
		break;
	  case 6:
		while (innerloop) {
		  std::cout << "\n\n\n";
		  std::cout << "ENTER THE AMOUNT OF TIMES TO CYCLE THROUGH THE FIBONACCI SEQUENCE (0 TO EXIT): ";
		  input = GIBI();
		  switch (input) {
			case 0:
			  innerloop = false;
			  break;
			default:
			  std::cout << "SCALE FACTOR (RECOMMENDED 5 FOR 10 CYCLES, MINIMUM FACTOR 1 - MAX FACTOR 100): ";
			  factor = GIBI(1,100);
			  cturtle::TurtleScreen scr;
			  cturtle::Turtle turtle(scr);
			  turtle.speed(cturtle::TS_FASTEST);
			  drawFibonacci(turtle, input, factor);
			  scr.exitonclick();
			  std::cout << "\n\n\n";
			  break;
		  }
		}
		break;
	}
  }



/*  turtle.fillcolor({"purple"});
  turtle.begin_fill();
  for (int i = 0; i < 4; i++) {
	turtle.forward(50);
	turtle.right(90);
  }
  turtle.end_fill();
  scr.bye();*/

  /*turtle.forward(fdwd);
	  turtle.left(1);*/

  /*for (int i = 0; i <= valch; i++) {
	moveT(turtle, cycle, fibonacci(i));
  }*/
  //system("mpv --keep-open --loop-playlist test.gif");
  return 0;
}

int fib(int number) {
  if (number == 0 || number == 1) {
	return number;
  } else {
	return (fib(number - 1) + fib(number - 2));
  }
}

bool isFibonacci(int num) {
  int count = 0;
  int fibo = fib(count);
  while (count <= num + 1) {
	if (fibo == num) {
	  std::cout << num << " is a fibonacci number!\n";
	  return true;
	}
	count++;
	fibo = fib(count);
  }
  std::cout << num << " is NOT a fibonacci number!\n";
  return false;
}

void drawFibonacci(cturtle::Turtle &turtle, int n, int factor) {
  int a = 0;
  int b = 1;
  int square_a = a;
  int square_b = b;

  turtle.pencolor(cturtle::detail::resolveColorInt(0, 0, 255));
  turtle.fillcolor(cturtle::detail::resolveColorInt(0, 0, 255));
  turtle.begin_fill();
  turtle.forward(b * factor);
  turtle.left(90);
  turtle.forward(b * factor);
  turtle.left(90);
  turtle.forward(b * factor);
  turtle.left(90);
  turtle.forward(b * factor);
  turtle.end_fill();

  int temp = square_b;
  square_b = square_b + square_a;
  square_a = temp;

  int count = 1;
  for (int i = 1; i < n; i++) {
	if (count == 5) {
	  count = 0;
	}
	switch (count) {
	  case 0:
		turtle.fillcolor(cturtle::detail::resolveColorInt(0, 0, 255));
		break;
	  case 1:
		turtle.fillcolor(cturtle::detail::resolveColorInt(0, 255, 0));
		break;
	  case 2:
		turtle.fillcolor(cturtle::detail::resolveColorInt(255, 0, 0));
		break;
	  case 3:
		turtle.fillcolor(cturtle::detail::resolveColorInt(255, 255, 0));
		break;
	  case 4:
		turtle.fillcolor(cturtle::detail::resolveColorInt(255, 0, 255));
		break;
	  default:
		break;
	}
	count++;

	turtle.backward(square_a * factor);
	turtle.begin_fill();
	turtle.right(90);
	turtle.forward(square_b * factor);
	turtle.left(90);
	turtle.forward(square_b * factor);
	turtle.left(90);
	turtle.forward(square_b * factor);

	turtle.end_fill();

	//std::cout << temp << ", ";

	temp = square_b;
	square_b = square_b + square_a;
	square_a = temp;
  }
  /*turtle.penup();
  turtle.setposition(factor, 0);
  turtle.seth(0);
  turtle.pendown();

  turtle.pencolor(cturtle::detail::col::red);
  turtle.left(90);
  for(int i = 0; i < n; i++){
	//std::cout << "i: " << i << "b: " << b << "\n";
	//float fdwd = ((float)std::numbers::pi * (float)b * (float)factor) / 2;
	//float step = (((float)std::numbers::pi / 90) * (((float)b * (float)b ) / 2)) * (float)factor;
	int step = std::numbers::pi * b * factor / 2;
	//std::cout << "fdwd before: " << fdwd << "\n";
	//fdwd = fdwd/90;
	step /= 90	;
	//std::cout << "fdwd after: " << fdwd << "\n";

	for(int j = 0; j < 90; j++){
	  //std::cout << "j: " << j << "\n";
	  //std::cout << "fdwd: " << fdwd << "\n";
	  turtle.forward(step);
	  turtle.left(1);

	  *//*turtle.forward(fdwd);
	  turtle.left(1);*//*
	}
	//std::cout << "temp before: " << temp << "\n";
	temp = a;
	//std::cout << "temp after: " << temp << "\n";
	//std::cout << "a before: " << a << "\n";
	a = b;
	//std::cout << "a after: " << a << "\n";
	//std::cout << "b before: " << b << "\n";
	b = temp + b;
	//std::cout << "b after: " << b << "\n";
  }
*/

}

void drawFibonacciStep(cturtle::Turtle &turtle, int n, int factor) {
  int a = 0;
  int b = 1;
  int square_a = a;
  int square_b = b;

  enum tcol {
	BLUE = cturtle::detail::col::blue, RED = cturtle::detail::col::red,
	GREEN = cturtle::detail::col::green, YELLOW = cturtle::detail::col::yellow,
	PINK = cturtle::detail::col::pink
  };

  turtle.pencolor(tcol::BLUE);
  turtle.fillcolor(tcol::BLUE);
  turtle.begin_fill();
  turtle.forward(b * factor);
  turtle.left(90);
  turtle.forward(b * factor);
  turtle.left(90);
  turtle.forward(b * factor);
  turtle.left(90);
  turtle.forward(b * factor);
  turtle.end_fill();

  int temp = square_b;
  square_b = square_b + square_a;
  square_a = temp;

  int count = 1;
  for (int i = 1; i < n; i++) {
	if (count == 5) {
	  count = 0;
	}
	switch (count) {
	  case 0:
		turtle.fillcolor(tcol::BLUE);
		break;
	  case 1:
		turtle.fillcolor(tcol::RED);
		break;
	  case 2:
		turtle.fillcolor(tcol::GREEN);
		break;
	  case 3:
		turtle.fillcolor(tcol::YELLOW);
		break;
	  case 4:
		turtle.fillcolor(tcol::PINK);
		break;
	  default:
		break;
	}
	count++;

	turtle.backward(square_a * factor);
	turtle.begin_fill();
	turtle.right(90);
	turtle.forward(square_b * factor);
	turtle.left(90);
	turtle.forward(square_b * factor);
	turtle.left(90);
	turtle.forward(square_b * factor);

	turtle.end_fill();

	std::cout << temp << ", ";

	temp = square_b;
	square_b = square_b + square_a;
	square_a = temp;
  }
}

void moveT(cturtle::Turtle &turtle, bool cycle, int fib) {
  if (cycle) {
	turtle.forward(fib * 10);
	cycle = false;
	return;
  } else
	turtle.right(fib * 10);
  cycle = true;
  return;
}

//CONSOLE
int GIBI() {
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
	  std::cout << "\n!EXCEPTION!\n"
				   "\n!EXCEPTION!\n !STOI INVALID ARGUMENT!: " << input << "\n";
	}
	catch (std::out_of_range &i) {
	  std::cout << i.what();
	  std::cout << "\n!EXCEPTION!\n"
				   "\n!EXCEPTION!\n !STOI OUT OF RANGE!: " << input << "\n";
	}
  }
  return converted;
}

int GIBI(int min, int max) {
  while (true) {
	int input = GIBI();
	if (input >= min && input <= max) {
	  return input;
	} else {
	  std::cout << "!EXCEPTION!\n"
				   "\n!EXCEPTION!\n !OUT OF RANGE INPUT: " << input << " in" << min << " " << max;
	}
  }
}

double GIBD() {
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
	  std::cout << "\n!EXCEPTION!\n"
				   "\n!EXCEPTION!\n !STOI INVALID ARGUMENT!: " << input << "\n";
	}
	catch (std::out_of_range &i) {
	  std::cout << i.what();
	  std::cout << "\n!EXCEPTION!\n"
				   "\n!EXCEPTION!\n !STOI OUT OF RANGE!: " << input << "\n";
	}
  }
  return converted;
}

std::string GIBS() {
  std::string input;
  std::cin >> input;
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return input;
}

std::string GIBSWW() {
  std::string input;
  std::getline(std::cin >> std::ws, input);
  return input;
}

int Get_Input_Yes_Or_No() {
  while (true) {
	std::cout << "Answer with: (1) Yes; (0) No.\n";
	int input = GIBI(0, 1);

	switch (input) {
	  case 0:
		std::cout << "\nNo selected!\n";
		return input;
	  case 1:
		std::cout << "\nYes selected!\n";
		return input;
	  default:
		std::cout << "\n!EXCEPTION!\n";
		break;
	}
  }
}