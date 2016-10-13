#ifndef _AEQUUS_FILES_INPUT_INPUT_H_
#define _AEQUUS_FILES_INPUT_INPUT_H_
#include "../sdl_headers.h"
#include <ctime>
#include <string>
#include <vector>
namespace aequus {
namespace input {
// Used to declare event type for general usage later
enum EventType {
  WINDOW,
  KEYBOARD,
  TEXTEDIT,
  TEXTINPUT,
  MOUSEMOTION,
  MOUSEBUTTON,
  MOUSEWHEEL,
  AUDIO,
  QUIT,
  DROP
};
// Used to declare different events for SDL windows
enum WindowEvent {
  SHOWN,
  HIDDEN,
  EXPOSED,
  MOVED,
  RESIZED,
  SIZECHANGED,
  MINIMIZED,
  MAXIMIZED,
  RESTORED,
  ENTER,
  LEAVE,
  FOCUSGAINED,
  FOCUSLOST,
  CLOSE
};
// Used to determin button or key state
enum State { PRESSED, RELEASED, NONE };
// Used to to declare mouse button that was pressed
enum Button { LEFT, MIDDLE, RIGHT };
// Used for internal event declaration
struct Event {
  // All event types
  EventType type;
  // All event types
  time_t timestamp;
  // Window/Keyboard/TextEdit/TextInput/MouseMotion/MouseButton/MouseWheel
  int windowid = 0;
  // Window
  WindowEvent winevent;
  // Window
  int data1 = 0, data2 = 0;
  // Keyboard/MouseButton
  State buttonstate = NONE;
  // Keyboard
  bool repeate = false;
  // Keyboard
  SDL_Keysym keydata;
  // Keyboard
  int key = 0;
  // TextEdit/TextInput
  std::string text = "NULL";
  // TextEdit
  int start = 0, length = 0;
  // MouseMotion/MouseButton
  int posx = 0, posy = 0;
  // MouseButton
  int clicks = 0;
  // MouseButton
  Button mousebutton = LEFT;
  bool mousepress = false;
  // MouseWheel
  int scrollx = 0, scrolly = 0;
  // Audio
  bool capture = false;
  // DragDrop
  std::string file = "NULL";
};
// Current event type
extern EventType eventtype;
// Current SDL event
extern SDL_Event sdlevent;
// New Internal event
extern Event newevent;
// Used to store if button is pressed
extern bool press;
// Used to determine if a quit event has been called
extern bool quitevent;
// Vector to store all events that are loaded when PollEvents is called
extern std::vector<Event> events;
// Gets all SDL events that can be read
void PollEvents();
// Interprets events into aequus event structure
void InterpretEvent();
}
}
#endif // !_AEQUUS_FILES_INPUT_INPUT_H_
