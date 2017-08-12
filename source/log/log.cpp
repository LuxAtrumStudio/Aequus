#include "log/log.hpp"

#include <stdarg.h>
#include <time.h>
#include <array>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace aequus {
  namespace log {
    std::array<unsigned int, 2> options = {{0, 0}};
    std::vector<std::pair<unsigned int, std::string>> global_logs;
    void (*log_handle_full)(std::pair<unsigned int, std::string>) = NULL;
    void (*log_handle)(std::string) = NULL;
  }
}

void aequus::log::Log(unsigned int type, std::string msg, std::string func,
                      ...) {
  std::string str;
  va_list args, buff_args;
  va_start(args, func);
  va_start(buff_args, func);
  ssize_t buff_size = vsnprintf(NULL, 0, msg.c_str(), buff_args);
  char* formated_string = new char[buff_size];
  vsprintf(formated_string, msg.c_str(), args);
  va_end(buff_args);
  va_end(args);
  str = std::string(formated_string);
  if (options[0] == true || options[1] == true) {
    time_t current = time(NULL);
    std::string time_stamp = ctime(&current);
    if (options[0] == false) {
      time_stamp.erase(time_stamp.begin() + 10, time_stamp.begin() + 18);
    } else if (options[1] == false) {
      time_stamp.erase(time_stamp.begin(), time_stamp.begin() + 11);
      time_stamp.erase(time_stamp.end() - 6, time_stamp.end());
    }
    str = "[" + time_stamp + "]" + str;
  }
  str = "[" + GetTypeStr(type) + "]" + str;
  str = str + "[" + func + "]";
  global_logs.push_back(std::make_pair(type, str));
  if (log_handle_full != NULL) {
    log_handle_full(std::make_pair(type, str));
  } else if (log_handle != NULL) {
    log_handle(str);
  }
}

int aequus::log::GetLogSize() { return global_logs.size(); }

void aequus::log::ClearLogs() { global_logs.clear(); }

std::string aequus::log::GetLog(unsigned int type) {
  std::string entry;
  if (type == NONE && global_logs.size() > 0) {
    entry = global_logs[global_logs.size() - 1].second;
  }
  for (int i = global_logs.size() - 1; i >= 0 && entry == ""; i--) {
    if (global_logs[i].first == type) {
      entry = global_logs[i].second;
    }
  }
  return entry;
}

std::pair<unsigned int, std::string> aequus::log::FGetLog(unsigned int type) {
  std::pair<unsigned int, std::string> entry;
  bool search = true;
  if (type == NONE && global_logs.size() > 0) {
    entry = global_logs[global_logs.size() - 1];
    search = false;
  }
  for (int i = global_logs.size() - 1; i >= 0 && search == true; i--) {
    if (global_logs[i].first == type) {
      entry = global_logs[i];
      search = false;
    }
  }
  return entry;
}

std::string aequus::log::IGetLog(int index) {
  std::string entry;
  if (index >= 0 && (size_t)index < global_logs.size()) {
    entry = global_logs[index].second;
  }
  return entry;
}

std::pair<unsigned int, std::string> aequus::log::IFGetLog(int index) {
  std::pair<unsigned int, std::string> entry;
  if (index >= 0 && (size_t)index < global_logs.size()) {
    entry = global_logs[index];
  }
  return entry;
}

std::vector<std::string> aequus::log::VGetLog(int start, int end) {
  std::vector<std::string> entries;
  for (int i = start; i <= end && i >= 0 && (size_t)i < global_logs.size();
       i++) {
    entries.push_back(global_logs[i].second);
  }
  return entries;
}

std::vector<std::pair<unsigned int, std::string>> aequus::log::VFGetLog(
    int start, int end) {
  std::vector<std::pair<unsigned int, std::string>> entries;
  for (int i = start; i <= end && i >= 0 && (size_t)i < global_logs.size();
       i++) {
    entries.push_back(global_logs[i]);
  }
  return entries;
}

void aequus::log::SetLogHandle(
    void (*handle)(std::pair<unsigned int, std::string>)) {
  log_handle_full = handle;
}

void aequus::log::SetLogHandle(void (*handle)(std::string)) {
  log_handle = handle;
}

void aequus::log::SetLogOption(unsigned int option, int setting) {
  if (option == TIME_STAMP) {
    options[0] = setting;
  } else if (option == DATE_STAMP) {
    options[1] = setting;
  }
}

std::string aequus::log::GetTypeStr(unsigned int type) {
  std::string str;
  if (type == ERROR) {
    str = "ERROR";
  } else if (type == WARNING) {
    str = "WARNING";
  } else if (type == TRACE) {
    str = "TRACE";
  } else if (type == DEBUG) {
    str = "DEBUG";
  } else if (type == SUCCESS) {
    str = "SUCCESS";
  } else if (type == INFO) {
    str = "INFO";
  } else if (type == DATA) {
    str = "DATA";
  }
  return str;
}

void aequus::log::SaveLog(std::string file) {
  std::ofstream output(file.c_str(), std::ios::out);
  if (output.is_open()) {
    for (int i = 0; (size_t)i < global_logs.size(); i++) {
      output << global_logs[i].second << "\n";
    }
    output.close();
  }
}
