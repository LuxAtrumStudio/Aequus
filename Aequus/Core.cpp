#include <iostream>
#include "aequus_files\aequus_core.h"
#include "aequus_files\framework.h"
#include "aequus_files\video.h"
#include "aequus_files\video\window.h"
#include "aequus_files\video\messagebox.h"
#include "pessum_files\pessum_core.h"
using namespace std;

int main(int argc, char* argv[]) {
	pessum::InitializePessumComponents();
	aequus::framework::SdlStartUp();
	aequus::framework::TerminateSdl();
	pessum::TerminatePessumComponents();
	return(1);
}