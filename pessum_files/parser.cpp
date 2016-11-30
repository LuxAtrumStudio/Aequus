#include "logging.h"
#include "parser.h"
#include "pessum_core.h"
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

namespace pessum {
namespace parser {
int logloc = 0;
std::vector<Equation> equations;
}
}

void pessum::parser::InitalizeParser() {
  logloc = logging::AddLogLocation("pessum_files/parser/");
}

int pessum::parser::ParseEquation(std::string equation) {
  std::string partstring = "";
  Equation newequation;
  newequation.rawequation = equation;
  equation += " ";
  equations.push_back(newequation);
  int equationpointer = equations.size() - 1;
  for (int i = 0; i < equation.size(); i++) {
    if (equation[i] == ' ') {
      Part newpart;
      if (int(partstring[0]) >= 48 && int(partstring[0]) <= 57) {
        newpart.value = stod(partstring);
        newpart.type = VALUE;
      } else if (partstring == "+") {
        newpart.operation = ADD;
        newpart.type = OPERATOR;
      } else if (partstring == "-") {
        newpart.operation = SUB;
        newpart.type = OPERATOR;
      } else if (partstring == "*") {
        newpart.operation = MUL;
        newpart.type = OPERATOR;
      } else if (partstring == "/") {
        newpart.operation = DIV;
        newpart.type = OPERATOR;
      } else if (partstring == "^") {
        newpart.operation = POW;
        newpart.type = OPERATOR;
      } else if (partstring == "SIN") {
        newpart.operation = SIN;
        newpart.type = OPERATOR;
      } else if (partstring == "COS") {
        newpart.operation = COS;
        newpart.type = OPERATOR;
      } else if (partstring == "TAN") {
        newpart.operation = TAN;
        newpart.type = OPERATOR;
      } else if (partstring == "(") {
        newpart.operation = OPENPAREN;
        newpart.type = OPERATOR;
      } else if (partstring == ")") {
        newpart.operation = CLOSEPAREN;
        newpart.type = OPERATOR;
      } else if (partstring == "E") {
        newpart.value = 2.7182818284590452;
        newpart.type = VALUE;
      } else if (partstring == "PI") {
        newpart.value = 3.1415926535897932;
        newpart.type = VALUE;
      } else {
        newpart.variable = partstring;
        newpart.type = VARIABLE;
        Variable newvariable;
        newvariable.name = partstring;
        equations[equationpointer].variables.push_back(newvariable);
      }
      partstring = "";
      equations[equationpointer].parts.push_back(newpart);
    } else {
      partstring += equation[i];
    }
  }
  return (equationpointer);
}

double pessum::parser::ComputeEquation(int equation,
                                       std::vector<double> variables) {
  if (equation > equations.size()) {
    logging::LogLoc(logging::LOG_ERROR, "Equation number is invalid", logloc,
                    "RunEquation");
  }
  Equation eq = equations[equation];
  for (int i = 0; i < variables.size(); i++) {
    if (i < eq.variables.size()) {
      eq.variables[i].value = variables[i];
    }
  }
  for (int i = 0; i < eq.parts.size(); i++) {
    if (eq.parts[i].type == VARIABLE) {
      for (int j = 0; j < eq.variables.size(); j++) {
        if (eq.variables[j].name == eq.parts[i].variable) {
          eq.parts[i].value = eq.variables[j].value;
          eq.parts[i].type = VALUE;
        }
      }
      if (eq.parts[i].type == VARIABLE) {
        logging::LogLoc(logging::LOG_ERROR, "Undefined variable", logloc,
                        "RunEquation");
        return (0);
      }
    }
  }
  double returnvalue = 0;
  returnvalue = SolveParts(eq.parts);
  return (returnvalue);
}

double pessum::parser::ComputeEquation(int equation, double variable) {
  std::vector<double> vars = {variable};
  ComputeEquation(equation, vars);
}

double pessum::parser::SolveParts(std::vector<Part> eq) {
  for (int i = 0; i < eq.size(); i++) {
    if (eq[i].operation == OPENPAREN) {
      std::vector<Part> neweq;
      int endparen = i;
      for (int j = i + 1; j < eq.size() && eq[j].operation != CLOSEPAREN; j++) {
        neweq.push_back(eq[j]);
        if (j == eq.size() - 1 && eq[j].operation != CLOSEPAREN) {
          logging::LogLoc(logging::LOG_ERROR,
                          "No closing parenthesis in equation", logloc,
                          "SolveParts");
          return (0);
        }
        endparen = j + 1;
      }
      eq.erase(eq.begin() + i, eq.begin() + endparen);
      eq[i].value = SolveParts(neweq);
      eq[i].operation = NONE;
      eq[i].type = VALUE;
      neweq.clear();
    }
  }
  for (int i = 0; i < eq.size(); i++) {
    if (eq[i].operation == SIN || eq[i].operation == COS ||
        eq[i].operation == TAN) {
      if (i == eq.size() - 1) {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (trig) placement", logloc,
                        "SolveParts");
        return (0);
      } else if (eq[i + 1].type == VALUE) {
        if (eq[i].operation == SIN) {
          eq[i].value = sin(eq[i + 1].value);
        }
        if (eq[i].operation == COS) {
          eq[i].value = cos(eq[i + 1].value);
        }
        if (eq[i].operation == TAN) {
          eq[i].value = tan(eq[i + 1].value);
        }
        eq.erase(eq.begin() + i + 1);
      } else {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (trig) placement", logloc,
                        "SolveParts");
        return (0);
      }
    }
  }
  for (int i = 0; i < eq.size(); i++) {
    if (eq[i].operation == POW) {
      if (i == 0 || i == eq.size() - 1) {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (^) placement", logloc,
                        "SolveParts");
        return (0);
      } else if (eq[i - 1].type == VALUE && eq[i + 1].type == VALUE) {
        eq[i - 1].value = pow(eq[i - 1].value, eq[i + 1].value);
        eq.erase(eq.begin() + i, eq.begin() + i + 2);
        i--;
      } else {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (^) placement", logloc,
                        "SolveParts");
        return (0);
      }
    }
  }
  for (int i = 0; i < eq.size(); i++) {
    if (eq[i].operation == MUL) {
      if (i == 0 || i == eq.size() - 1) {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (*) placement", logloc,
                        "SolveParts");
        return (0);
      } else if (eq[i - 1].type == VALUE && eq[i + 1].type == VALUE) {
        eq[i - 1].value = eq[i - 1].value * eq[i + 1].value;
        eq.erase(eq.begin() + i, eq.begin() + i + 2);
        i--;
      } else {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (*) placement", logloc,
                        "SolveParts");
        return (0);
      }
    }
  }
  for (int i = 0; i < eq.size(); i++) {
    if (eq[i].operation == DIV) {
      if (i == 0 || i == eq.size() - 1) {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (/) placement", logloc,
                        "SolveParts");
        return (0);
      } else if (eq[i - 1].type == VALUE && eq[i + 1].type == VALUE) {
        eq[i - 1].value = eq[i - 1].value / eq[i + 1].value;
        eq.erase(eq.begin() + i, eq.begin() + i + 2);
        i--;
      } else {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (/) placement", logloc,
                        "SolveParts");
        return (0);
      }
    }
  }
  for (int i = 0; i < eq.size(); i++) {
    if (eq[i].operation == ADD) {
      if (i == 0 || i == eq.size() - 1) {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (+) placement", logloc,
                        "SolveParts");
        return (0);
      } else if (eq[i - 1].type == VALUE && eq[i + 1].type == VALUE) {
        eq[i - 1].value = eq[i - 1].value + eq[i + 1].value;
        eq.erase(eq.begin() + i, eq.begin() + i + 2);
        i--;
      } else {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (+) placement", logloc,
                        "SolveParts");
        return (0);
      }
    }
  }
  for (int i = 0; i < eq.size(); i++) {
    if (eq[i].operation == SUB) {
      if (i == 0 || i == eq.size() - 1) {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (-) placement", logloc,
                        "SolveParts");
        return (0);
      } else if (eq[i - 1].type == VALUE && eq[i + 1].type == VALUE) {
        eq[i - 1].value = eq[i - 1].value - eq[i + 1].value;
        eq.erase(eq.begin() + i, eq.begin() + i + 2);
        i--;
      } else {
        logging::LogLoc(logging::LOG_ERROR,
                        "Invalid equation operation (-) placement", logloc,
                        "SolveParts");
        return (0);
      }
    }
  }
  return (eq[0].value);
}

void pessum::parser::DisplayParts(std::vector<Part> eq) {
  for (int i = 0; i < eq.size(); i++) {
    std::cout << " ";
    if (eq[i].type == VALUE) {
      std::cout << "V" << eq[i].value;
    }
    if (eq[i].type == OPERATOR) {
      std::cout << "O" << eq[i].operation;
    }
    if (eq[i].type == VARIABLE) {
      std::cout << "X" << eq[i].variable;
    }
  }
  std::cout << "\n";
}
