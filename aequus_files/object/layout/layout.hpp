#ifndef AEQUUS_OBJECT_LAYOUT_HPP
#define AEQUUS_OBJECT_LAYOUT_HPP
#include <vector>
#include "../object.hpp"
#include "../object_base.hpp"
namespace aequus {
  enum LayoutFormat {
    AEQ_OBJ_LAY_FREE,
    AEQ_OBJ_LAY_HORIZONTAL,
    AEQ_OBJ_LAY_HORIZONTAL_FORCE,
    AEQ_OBJ_LAY_VERTICAL,
    AEQ_OBJ_LAY_VERTICAL_FORCE
  };
  class Layout : public ObjectBase {
   public:
    Layout();
    Layout(int w, int h);
    Layout(int type);
    Layout(int type, int w, int h);
    ~Layout();
    void SetFormat(int type);
    void Display();
    void AddObject(Object obj);
    int Type();
    int GetFormat();
    int Size();

   private:
    void ReformatObjects();
    int format = AEQ_OBJ_LAY_FREE;
    std::vector<Object> sub_objects;
    SDL_Rect layout_size;
  };
}
#endif
