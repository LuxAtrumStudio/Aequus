#ifndef AEQUUS_ERROR_ERROR_HPP
#define AEQUUS_ERROR_ERROR_HPP

#include <string>

namespace aequus {
  namespace error {
    void LogSdlError();
    void LogImgError();
    void LogTtfError();
    void LogMixError();

    std::string GetSdlError();
    std::string GetImgError();
    std::string GetTtfError();
    std::string GetMixError();
  }  // namespace error
}  // namespace aequus

#endif /* ifndef AEQUUS_ERROR_ERROR_HPP */
