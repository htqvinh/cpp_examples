#include <iostream>
#include "LogPrinter.h"

using namespace std;

int main(int argc, char** argv){

	LogPrinter printer;
	printer.active();

	unsigned times = 10;
	while(times > 0){
		printer.push("Hello %u\n", times--);
	}

	while(1){}

	return 1;
}
