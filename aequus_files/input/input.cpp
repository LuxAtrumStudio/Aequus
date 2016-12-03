#include "../../pessum_files/logging.h"
#include "../aequus_headers.h"
#include "input.h"

namespace aequus {
namespace input {
EventType eventtype;
SDL_Event sdlevent;
Event newevent;
bool press = false;
bool quitevent = false;
std::vector<Event> events;
}
}

void aequus::input::PollEvents() {
  events.clear();
  while (SDL_PollEvent(&sdlevent) == 1) {
    InterpretEvent();
    events.push_back(newevent);
  }
}

void aequus::input::InterpretEvent() {
  if (sdlevent.type == SDL_AUDIODEVICEADDED ||
      sdlevent.type == SDL_AUDIODEVICEREMOVED) {
    newevent.type = AUDIO;
    newevent.timestamp = sdlevent.adevice.timestamp;
    if (sdlevent.adevice.iscapture == 0) {
      newevent.capture = false;
    } else {
      newevent.capture = true;
    }
  }
  if (sdlevent.type == SDL_DROPFILE) {
    newevent.type = DROP;
    newevent.timestamp = sdlevent.drop.timestamp;
    newevent.file = sdlevent.drop.file;
  }
  if (sdlevent.type == SDL_KEYUP || sdlevent.type == SDL_KEYDOWN) {
    newevent.type = KEYBOARD;
    newevent.timestamp = sdlevent.key.timestamp;
    newevent.windowid = sdlevent.key.windowID;
    if (sdlevent.key.state == SDL_PRESSED) {
      newevent.buttonstate = PRESSED;
    } else {
      newevent.buttonstate = RELEASED;
    }
    if (sdlevent.key.repeat == 0) {
      newevent.repeate = false;
    } else {
      newevent.repeate = true;
    }
    newevent.keydata = sdlevent.key.keysym;
    if (sdlevent.key.keysym.mod == KMOD_NONE) {
      newevent.key = sdlevent.key.keysym.sym;
    } else if (sdlevent.key.keysym.mod == KMOD_LSHIFT ||
               sdlevent.key.keysym.mod == KMOD_RSHIFT) {
      int keyint = sdlevent.key.keysym.sym;
      if (keyint >= 97 && keyint <= 122) {
        keyint -= 32;
      } else if (keyint == 96) {
        keyint = 126;
      } else if (keyint == 48) {
        keyint = 41;
      } else if (keyint == 49) {
        keyint = 33;
      } else if (keyint == 50) {
        keyint = 64;
      } else if (keyint == 51) {
        keyint = 35;
      } else if (keyint == 52) {
        keyint = 36;
      } else if (keyint == 53) {
        keyint = 37;
      } else if (keyint == 54) {
        keyint = 94;
      } else if (keyint == 55) {
        keyint = 38;
      } else if (keyint == 56) {
        keyint = 42;
      } else if (keyint == 57) {
        keyint = 40;
      } else if (keyint == 45) {
        keyint = 95;
      } else if (keyint == 61) {
        keyint = 43;
      } else if (keyint == 91) {
        keyint = 123;
      } else if (keyint == 93) {
        keyint = 125;
      } else if (keyint == 92) {
        keyint = 124;
      } else if (keyint == 59) {
        keyint = 58;
      } else if (keyint == 39) {
        keyint = 34;
      } else if (keyint == 44) {
        keyint = 60;
      } else if (keyint == 46) {
        keyint = 62;
      } else if (keyint == 47) {
        keyint = 63;
      }
      pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION,
                              std::to_string(keyint));
      newevent.key = keyint;
    }
  }
  if (sdlevent.type == SDL_MOUSEMOTION) {
    newevent.type = MOUSEMOTION;
    newevent.timestamp = sdlevent.motion.timestamp;
    newevent.windowid = sdlevent.motion.windowID;
    newevent.posx = sdlevent.motion.x;
    newevent.posy = sdlevent.motion.y;
    newevent.mousepress = press;
    newevent.buttonstate = NONE;
  }
  if (sdlevent.type == SDL_MOUSEBUTTONDOWN ||
      sdlevent.type == SDL_MOUSEBUTTONUP) {
    newevent.type = MOUSEBUTTON;
    newevent.timestamp = sdlevent.button.timestamp;
    newevent.windowid = sdlevent.button.windowID;
    newevent.posx = sdlevent.button.x;
    newevent.posy = sdlevent.button.y;
    if (sdlevent.button.button == SDL_BUTTON_LEFT) {
      newevent.mousebutton = LEFT;
    } else if (sdlevent.button.button == SDL_BUTTON_MIDDLE) {
      newevent.mousebutton = MIDDLE;
    } else if (sdlevent.button.button == SDL_BUTTON_RIGHT) {
      newevent.mousebutton = RIGHT;
    }
    if (sdlevent.button.state == SDL_PRESSED) {
      newevent.buttonstate = PRESSED;
      press = true;
    } else if (sdlevent.button.state == SDL_RELEASED) {
      newevent.buttonstate = RELEASED;
      press = false;
    } else {
      newevent.buttonstate = NONE;
    }
    newevent.clicks = sdlevent.button.clicks;
    newevent.mousepress = press;
  }
  if (sdlevent.type == SDL_MOUSEWHEEL) {
    newevent.type = MOUSEWHEEL;
    newevent.timestamp = sdlevent.wheel.timestamp;
    newevent.windowid = sdlevent.wheel.windowID;
    newevent.scrollx = sdlevent.wheel.x;
    newevent.scrolly = sdlevent.wheel.y;
    newevent.mousepress = press;
    newevent.buttonstate = NONE;
  }
  if (sdlevent.type == SDL_QUIT) {
    newevent.type = QUIT;
    newevent.timestamp = sdlevent.quit.timestamp;
  }
  if (sdlevent.type == SDL_TEXTEDITING) {
    newevent.type = TEXTEDIT;
    newevent.timestamp = sdlevent.edit.timestamp;
    newevent.windowid = sdlevent.edit.windowID;
    newevent.text = sdlevent.edit.text;
    newevent.start = sdlevent.edit.start;
    newevent.length = sdlevent.edit.length;
  }
  if (sdlevent.type == SDL_TEXTINPUT) {
    newevent.type = TEXTINPUT;
    newevent.timestamp = sdlevent.text.timestamp;
    newevent.windowid = sdlevent.text.windowID;
    newevent.text = sdlevent.edit.text;
  }
  if (sdlevent.type == SDL_WINDOWEVENT) {
    newevent.type = WINDOW;
    newevent.timestamp = sdlevent.window.timestamp;
    newevent.windowid = sdlevent.window.windowID;
    newevent.data1 = sdlevent.window.data1;
    newevent.data2 = sdlevent.window.data2;
    if (sdlevent.type = SDL_WINDOWEVENT_SHOWN) {
      newevent.winevent = SHOWN;
    } else if (sdlevent.type = SDL_WINDOWEVENT_HIDDEN) {
      newevent.winevent = HIDDEN;
    } else if (sdlevent.type = SDL_WINDOWEVENT_EXPOSED) {
      newevent.winevent = EXPOSED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_MOVED) {
      newevent.winevent = MOVED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_RESIZED) {
      newevent.winevent = RESIZED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_SIZE_CHANGED) {
      newevent.winevent = SIZECHANGED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_MINIMIZED) {
      newevent.winevent = MINIMIZED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_MAXIMIZED) {
      newevent.winevent = MAXIMIZED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_RESTORED) {
      newevent.winevent = RESTORED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_ENTER) {
      newevent.winevent = ENTER;
    } else if (sdlevent.type = SDL_WINDOWEVENT_LEAVE) {
      newevent.winevent = LEAVE;
    } else if (sdlevent.type = SDL_WINDOWEVENT_FOCUS_GAINED) {
      newevent.winevent = FOCUSGAINED;
    } else if (sdlevent.type = SDL_WINDOWEVENT_FOCUS_LOST) {
      newevent.winevent = FOCUSLOST;
    } else if (sdlevent.type = SDL_WINDOWEVENT_CLOSE) {
      newevent.winevent = CLOSE;
    }
  }
}
