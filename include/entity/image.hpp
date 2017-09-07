#ifndef AEQUUS_IMAGE_HPP
#define AEQUUS_IMAGE_HPP

#include "surface.hpp"

namespace aequus {
  class Image : public aequus::entity::Surface {
   public:
    Image();
    Image(const char* file);
    Image(const Image& copy);
    ~Image();

   private:
  };
}  // namespace aequus

#endif /* ifndef AEQUUS_IMAGE_HPP */
