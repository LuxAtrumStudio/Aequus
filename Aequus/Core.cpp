#include <iostream>
#include "pessum\pessum_core.h"
using namespace std;

int main(int argc, char* argv[]) {
	pessum::InitializePessumComponents();
	pessum::TerminatePessumComponents();
	return(1);
}