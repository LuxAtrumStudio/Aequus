#ifndef _PESSUM_FILES_PARSER_H_
#define _PESSUM_FILES_PARSER_H_
#include <string>
#include <vector>
namespace pessum {
namespace parser {
enum Operator {
  SUB,
  ADD,
  DIV,
  MUL,
  POW,
  OPENPAREN,
  CLOSEPAREN,
  SIN,
  COS,
  TAN,
  NONE
};
enum PartType { VALUE, OPERATOR, VARIABLE };
struct Part {
  PartType type;
  double value = 0;
  Operator operation = NONE;
  std::string variable = "";
};
struct Variable {
  std::string name;
  double value = 0;
};
struct Equation {
  std::string rawequation;
  std::vector<Part> parts;
  std::vector<Variable> variables;
};
extern int logloc;
extern std::vector<Equation> equations;
void InitalizeParser();
int ParseEquation(std::string equation);
double ComputeEquation(int equation, std::vector<double> variables);
double ComputeEquation(int equation, double variable);
double SolveParts(std::vector<Part> eq);
void DisplayParts(std::vector<Part> eq);
}
}
#endif
