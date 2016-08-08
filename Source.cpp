#include "Pessum/pessum_core.h"
#include "Pessum/lux_reader.h"
#include "Pessum/rest.h"
#include "Pessum/logging.h"
int main(int argc, char* argv[]) {
	pessum::InitializePessumComponents();
	pessum::TerminatePessumComponents();
	return(0);
}
