#ifndef AEQUUS_CORE_HPP
#define AEQUUS_CORE_HPP
#define DEV_MODE true
namespace aequus {
extern bool QuitState;
void InitializeAequus();
void TerminateAequus();
void Frame();
}
#endif