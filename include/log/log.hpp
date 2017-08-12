#ifndef AEQUUS_LOG_LOG_HPP
#define AEQUUS_LOG_LOG_HPP

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

    // Saves formatted string, log types, and function to global_logs.
    void Log(unsigned int type = TRACE, std::string msg = "",
             std::string func = "", ...);

    // Gets the length of global_logs.
    int GetLogSize();
    // Clears all entries from global_logs
    void ClearLogs();

    // Gets last log entry of matching type.
    std::string GetLog(unsigned int type);
    // Gets last log entry of matching type with type data.
    std::pair<unsigned int, std::string> FGetLog(unsigned int type);
    // Gets log entry of specified index.
    std::string IGetLog(int index);
    // Gets log entry of specified index with type data.
    std::pair<unsigned int, std::string> IFGetLog(int index);
    // Get set of log entries between start and end indices.
    std::vector<std::string> VGetLog(int start, int end);
    // Get set of log entries between start and end indices with type data.
    std::vector<std::pair<unsigned int, std::string>> VFGetLog(int start,
                                                               int end);

    // Sets a handle to be called whenever a log entry is created, that takes
    // the
    // type data aswell as log string.
    void SetLogHandle(void (*handle)(std::pair<unsigned int, std::string>));
    // Sets a handle to be called whenever a log entry is created, that only
    // takes
    // the log string.
    void SetLogHandle(void (*handle)(std::string));

    // Sets options from LogOptions, that are used by Log.
    void SetLogOption(unsigned int option, int setting);

    // Returns a string representing the name of the LogType passed to it.
    std::string GetTypeStr(unsigned int type);
    // Saves the log entries from global_logs to given file.
    void SaveLog(std::string file);
  }  // namespace log
}  // namespace aequus
#endif
