#include "messagebox.h"
#include "../aequus_headers.h"
#include "../../pessum_files/logging.h"

void aequus::video::MessageBox::SetColorScheme(float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3, float r4, float g4, float b4, float r5, float g5, float b5)
{
	SDL_MessageBoxColorScheme colorscheme;
	colorscheme.colors[0].r = r1 * 255;
	colorscheme.colors[0].g = g1 * 255;
	colorscheme.colors[1].b = b1 * 255;
	colorscheme.colors[1].r = r2 * 255;
	colorscheme.colors[1].g = g2 * 255;
	colorscheme.colors[2].b = b2 * 255;
	colorscheme.colors[2].r = r3 * 255;
	colorscheme.colors[2].g = g3 * 255;
	colorscheme.colors[3].b = b3 * 255;
	colorscheme.colors[3].r = r4 * 255;
	colorscheme.colors[3].g = g4 * 255;
	colorscheme.colors[3].b = b4 * 255;
	colorscheme.colors[4].r = r5 * 255;
	colorscheme.colors[4].g = g5 * 255;
	colorscheme.colors[4].b = b5 * 255;
	internalmessageboxdata.colorscheme = &colorscheme;
}

void aequus::video::MessageBox::SetColor(MessageBoxColorType type, float red, float green, float blue)
{
	internalmessageboxdata.colorscheme->colors[type].r = red * 255;
	internalmessageboxdata.colorscheme->colors[type].g = green * 255;
	internalmessageboxdata.colorscheme->colors[type].b = blue * 255;
}

void aequus::video::MessageBox::AddButton(MessageBoxButtonFlags flags, std::string text)
{
	SDL_MessageBoxButtonData newbutton;
	newbutton.flags = flags;
	newbutton.buttonid = internalmessageboxdata.buttons.size();
	newbutton.text = text.c_str();
	internalmessageboxdata.buttons.push_back(newbutton);
}

void aequus::video::MessageBox::NewMessageBox(MessageBoxFlags flags, SDL_Window * parentwindow, std::string title, std::string message)
{
	internalmessageboxdata.flags = flags;
	internalmessageboxdata.window = parentwindow;
	internalmessageboxdata.title = title;
	if (flags == ERROR) {
		internalmessageboxdata.title = "[ERROR]>>" + title + "<<[ERROR]";
	}
	if (flags == WARNING) {
		internalmessageboxdata.title = "[WARNING]>>" + title + "<<[WARNING]";
	}
	internalmessageboxdata.message = message;
}

int aequus::video::MessageBox::RunMessageBox()
{
	if (internalmessageboxdata.buttons.size() <= 0) {
		SDL_ShowSimpleMessageBox(internalmessageboxdata.flags, internalmessageboxdata.title.c_str(), internalmessageboxdata.message.c_str(), internalmessageboxdata.window);
	}
	else {
		messageboxdata.flags = internalmessageboxdata.flags;
		messageboxdata.window = internalmessageboxdata.window;
		messageboxdata.title = internalmessageboxdata.title.c_str();
		messageboxdata.message = internalmessageboxdata.message.c_str();
		messageboxdata.numbuttons = internalmessageboxdata.buttons.size();
		messageboxdata.buttons = &internalmessageboxdata.buttons[0];
		messageboxdata.colorScheme = internalmessageboxdata.colorscheme;
		int buttonid;
		SDL_ShowMessageBox(&messageboxdata, &buttonid);
		return(buttonid);
	}
}