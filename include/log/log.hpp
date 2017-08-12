#ifndef PESSUM_LOG_HPP
#define PESSUM_LOG_HPP

#include <stdarg.h>
#include <time.h>
#include <array>
#include <fstream>
#include <string>
#include <vector>

namespace aequus {
  namespace log {
    // Used to define the type/importance of the log entry.
    enum LogOptions { TIME_STAMP, DATE_STAMP };
    // Used to specify a logging option to set using SetLogOption.
    enum LogType { ERROR, WARNING, TRACE, DEBUG, SUCCESS, INFO, DATA, NONE };

    std::array<int, 2> options_ = {{0, 0}};
    std::vector<std::pair<unsigned int, std::string>> global_logs_;
    void (*log_handle_full_)(std::pair<unsigned int, std::string>);
    void (*log_handle_)(std::string);

    // Returns a string representing the name of the LogType passed to it.
    std::string GetTypeStr(int type) {
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
    // Saves formatted string, log types, and function to global_logs.
    void Log(int type = TRACE, std::string msg = "", std::string func = "",
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
      if (options_[0] == true || options_[1] == true) {
        time_t current = time(NULL);
        std::string time_stamp = ctime(&current);
        if (options_[0] == false) {
          time_stamp.erase(time_stamp.begin() + 10, time_stamp.begin() + 18);
        } else if (options_[1] == false) {
          time_stamp.erase(time_stamp.begin(), time_stamp.begin() + 11);
          time_stamp.erase(time_stamp.end() - 6, time_stamp.end());
        }
        str = "[" + time_stamp + "]" + str;
      }
      str = "[" + GetTypeStr(type) + "]" + str;
      str = str + "[" + func + "]";
      global_logs_.push_back(std::make_pair(type, str));
      if (log_handle_full_ != NULL) {
        log_handle_full_(std::make_pair(type, str));
      } else if (log_handle_ != NULL) {
        log_handle_(str);
      }
    }

    // Gets the length of global_logs.
    int GetLogSize() { return global_logs_.size(); }
    // Clears all entries from global_logs
    void ClearLogs() { global_logs_.clear(); }

    // Gets last log entry of matching type.
    std::string GetLog(int type = NONE) {
      std::string entry;
      if (type == NONE && global_logs_.size() > 0) {
        entry = global_logs_[global_logs_.size() - 1].second;
      }
      for (int i = global_logs_.size() - 1; i >= 0 && entry == ""; i--) {
        if (global_logs_[i].first == type) {
          entry = global_logs_[i].second;
        }
      }
      return entry;
    }
    // Gets last log entry of matching type with type data.
    std::pair<int, std::string> FGetLog(int type) {
      std::pair<int, std::string> entry;
      bool search = true;
      if (type == NONE && global_logs_.size() > 0) {
        entry = global_logs_[global_logs_.size() - 1];
        search = false;
      }
      for (int i = global_logs_.size() - 1; i >= 0 && search == true; i--) {
        if (global_logs_[i].first == type) {
          entry = global_logs_[i];
          search = false;
        }
      }
      return entry;
    }
    // Gets log entry of specified index.
    std::string IGetLog(int index) {
      std::string entry;
      if (index >= 0 && (size_t)index < global_logs_.size()) {
        entry = global_logs_[index].second;
      }
      return entry;
    }
    // Gets log entry of specified index with type data.
    std::pair<int, std::string> IFGetLog(int index) {
      std::pair<int, std::string> entry;
      if (index >= 0 && (size_t)index < global_logs_.size()) {
        entry = global_logs_[index];
      }
      return entry;
    }
    // Get set of log entries between start and end indices.
    std::vector<std::string> VGetLog(int start, int end) {
      std::vector<std::string> entries;
      for (int i = start; i <= end && i >= 0 && (size_t)i < global_logs_.size();
           i++) {
        entries.push_back(global_logs_[i].second);
      }
      return entries;
    }
    // Get set of log entries between start and end indices with type data.
    std::vector<std::pair<int, std::string>> VFGetLog(int start, int end) {
      std::vector<std::pair<int, std::string>> entries;
      for (int i = start; i <= end && i >= 0 && (size_t)i < global_logs_.size();
           i++) {
        entries.push_back(global_logs_[i]);
      }
      return entries;
    }

    // Sets a handle to be called whenever a log entry is created, that takes
    // the
    // type data aswell as log string.
    void SetLogHandle(void (*handle)(std::pair<unsigned int, std::string>)) {
      log_handle_full_ = handle;
    }
    // Sets a handle to be called whenever a log entry is created, that only
    // takes
    // the log string.
    void SetLogHandle(void (*handle)(std::string)) { log_handle_ = handle; }

    // Sets options from LogOptions, that are used by Log.
    void SetLogOption(int option, int setting) { options_[option] = setting; }

    // Saves the log entries from global_logs to given file.
    void SaveLog(std::string file) {
      std::ofstream output(file.c_str(), std::ios::out);
      if (output.is_open()) {
        for (int i = 0; (size_t)i < global_logs_.size(); i++) {
          output << global_logs_[i].second << "\n";
        }
        output.close();
      }
    }
  }  // namespace log
}  // namespace aequus
#endif
