#include "input.h"
#include "../../pessum_files/logging.h"
#include "../aequus_headers.h"

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
    newevent.key = sdlevent.key.keysym.sym;
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