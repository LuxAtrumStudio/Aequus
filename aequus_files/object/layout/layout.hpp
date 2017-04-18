#ifndef AEQUUS_OBJECT_LAYOUT_HPP
#define AEQUUS_OBJECT_LAYOUT_HPP
#include <vector>
#include "../object.hpp"
#include "../object_base.hpp"
namespace aequus {
  enum LayoutFormat {
    AEQ_OBJ_LAY_FREE,
    AEQ_OBJ_LAY_HORIZONTAL,
    AEQ_OBJ_LAY_VERTICAL
  };
  class Layout : public ObjectBase {
   public:
    Layout();
    Layout(int type);
    ~Layout();
    void SetFormat(int type);
    void Display();
    void AddSubObject(Object obj);
    int Type();
    int GetFormat();

   private:
    int format = AEQ_OBJ_LAY_FREE;
    std::vector<Object> sub_objects;
  };
}
#endif
