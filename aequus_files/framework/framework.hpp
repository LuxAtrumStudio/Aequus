#ifndef FRAMEWORK_FRAMEWORK_HPP
#define FRAMEWORK_FRAMEWORK_HPP
#include <string>
namespace aequus {
namespace framework {
enum Module { SDL = 1, IMG = 2, TTF = 3, MIX = 4 };
bool InitializeSdl();
void TerminateSdl();
std::string GetSdlError(Module mod);
}
}
#endif
