#include "logging.h"
#include "lux_reader.h"
#include "matrixmath.h"
#include "parser.h"
#include "pessum_core.h"
#include "rest.h"

void pessum::InitializePessumComponents() {
  logging::InitializeLogging();
  luxreader::InitializeLuxReader();
  rest::Initialzierest();
  parser::InitalizeParser();
  math::InitializeMath();
}

void pessum::TerminatePessumComponents() {
  rest::Terminaterest();
  logging::TerminateLogging();
}
