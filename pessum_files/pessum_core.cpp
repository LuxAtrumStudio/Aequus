#include "logging.h"
#include "lux_reader.h"
#include "parser.h"
#include "pessum_core.h"
#include "rest.h"

void pessum::InitializePessumComponents() {
  logging::InitializeLogging();
  luxreader::InitializeLuxReader();
  rest::Initialzierest();
  parser::InitalizeParser();
}

void pessum::TerminatePessumComponents() {
  rest::Terminaterest();
  logging::TerminateLogging();
}
