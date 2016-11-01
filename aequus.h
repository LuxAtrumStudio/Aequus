#ifndef _AEQUUS_FILES_
#define _AEQUUS_FILES_
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_version.h>
#include <ctime>
#include <fstream>
#include <string>
#include <vector>
// Pessum Headers
// pessum namespace is a compleate namespace for the pessum components
namespace pessum {
// logging namespace is used to provide debuging assistance to the
// user. It saves data to a seperate file incase of a crash.
namespace logging {
// Used to define different posible log types
enum LogType {
  LOG_ERROR,
  LOG_WARNING,
  LOG_SUCCESS,
  LOG_DATA,
  LOG_INFORMATION,
  LOG_DEVELOPMENT_CHECK
};
extern std::ofstream logfile;
extern std::vector<std::string> loglocationbindings;
// Used to initialize and open logging file for log output
bool InitializeLogging(std::string outputfile = "log_output.log");
// Enters the logstring into the output log
void Log(LogType type = LOG_DEVELOPMENT_CHECK, std::string logstring = "NULL",
         std::string logfilelocation = "NULL");
void LogLoc(LogType type = LOG_DEVELOPMENT_CHECK,
            std::string logstring = "NULL", int logfilelocation = 0,
            std::string functionname = "NULL");
// Used to determin log type and convert into a string
std::string InterpretType(LogType type);
// Used to add a log location to the vector, making logging shorter
int AddLogLocation(std::string loglocationstring);
// Used to log current time/date
void LogTimeStamp(bool date = false);
// Used to clear loglocationbindigns, and close out the outputfile
void TerminateLogging();
}
// luxreader namespace provides support for lux files, and reading the data
// files
// from lux code to be used in a program.
namespace luxreader {
// Struct for raw lux code loading
struct RawLuxCode {
  std::vector<std::string> luxcodelines;
};
// Structs for lux menu loading
struct List {
  std::string listname;
  std::vector<std::string> listitems;
};
struct Page {
  std::string pagename;
  std::vector<List> pagelists;
};
struct Hierarchy {
  std::string hierarchyname;
  std::vector<Page> mierarchypages;
};
// Structs for lux data loading
struct Variable {
  std::string variablename, variabletype, variabledefinitiontype;
  int intvalue;
  std::vector<int> intvectorvalues;
  double doublevalue;
  std::vector<double> doublevectorvalues;
  std::string stringvalue;
  std::vector<std::string> stringvectorvalues;
};
struct DataFile {
  std::string datafilename;
  std::vector<Variable> datafilevariables;
};
// Defines different types of Lux Code files for the file reader
enum LuxFileType { LUX_DATA, LUX_HIERARCHY, LUX_CODE, LUX_LIST };
// Sets log location for lux reader logging
extern int logloc;

// Sets the logging location code(must be called)
void InitializeLuxReader();

// Loads the data from a lux data file, and returns in a DataFile struct
DataFile LoadLuxDataFile(std::string filedirectory);
// Loads the data from a lux hierarchy file, and returns in a Hierarchy struct
Hierarchy LoadLuxHierarchyFile(std::string filedirectory);
// Loads the data from a lux list file, and returns in a vector of strings
std::vector<std::string> LoadLuxListFile(std::string filedirectory);

// Takes a DataFile structure, and converts it to RawLuxCode, to output
void SaveLuxDataFile(std::string filedirectory, DataFile ouputdata);

// Loads the raw lux code data from specified file
RawLuxCode GetRawFileData(LuxFileType filetype, std::string filedirectory);
// Saves a raw lux code data to specifed file
void OuputRawFileData(LuxFileType filetype, std::string filedirectory,
                      RawLuxCode rawoutputcode);
}
// rest namespace allows access to urls and internet
// api through the use of return json files
namespace rest {
// Struct for variables in json files
struct Variable {
  std::string variablename;
  std::vector<Variable> subvariables;
  std::string stringvalue;
  int intvalue;
  double doublevalue;
};
// Struct for json file variables
struct JsonFile {
  std::vector<Variable> filevariables;
};
// Log location integer index
extern int logloc;
// Int index to identify level of json file branches
extern unsigned int index;
// Vector of loaded json files
extern std::vector<JsonFile> loadedjsonfiles;
// Sets log location for rest logging
void Initialzierest();
// Clears loaded json files, freeing up memory
void Terminaterest();

// Runs specified python script with script arguments from vector
void RunScript(std::vector<std::string> scriptargs);
// Reads script output file, and creates a JsonFile from the raw file
void InterpretJson(std::string scriptoutputfiledirectory);
// Reads contents of a variable, and returns a Variable structure from raw
// variable string
Variable InterpretVariable(std::string variablename, std::string rawvariable);
// Access json file from loaded json file vector
JsonFile GetJsonFile(std::string filename);

// Returns sub variable searched from variable
Variable LocateVariable(std::string variablename, Variable searchvariable);
// Returns sub variable searched from json file
Variable GetVariable(std::string variablename, std::string jsonfilename);
// Returns int value searched from json file
int GetIntVariable(std::string variablename, std::string jsonfilename);
// Returns double value searched from json file
double GetDoubleVariable(std::string variablename, std::string jsonfilename);
// Returns string value searched from json file
std::string GetStringVariable(std::string variablename,
                              std::string jsonfilename);
}
// Runs initialization funcitons for logging, luxreader, and rest
void InitializePessumComponents();
// Runs terminatrion functions for rest, and logging
void TerminatePessumComponents();
}
// Aequus Headers
namespace aequus {
// namespace framework overall framework for SDL api that does not fit in any
// catagory
namespace framework {
// Used to declare the specific subsystems to be initialized
enum SubSystem {
  TIMER = SDL_INIT_TIMER,
  AUDIO = SDL_INIT_AUDIO,
  VIDEO = SDL_INIT_VIDEO,
  JOYSTICK = SDL_INIT_JOYSTICK,
  HAPTIC = SDL_INIT_HAPTIC,
  GAMECONTROLLER = SDL_INIT_GAMECONTROLLER,
  EVENTS = SDL_INIT_EVENTS,
  EVERYTHING = SDL_INIT_EVERYTHING,
  NOPARACHUTE = SDL_INIT_NOPARACHUTE
};
// Sets log location for aequus framework logging
extern int logloc;
// Initalizes all SDL subsystems, and checks versions
void SdlStartUp();
// Initalizes specific SDL subsystems
void InitializeSdl(Uint32 flags);
// Terminates all initialized SDL subsystems
void TerminateSdl();
// Sets program main function over SDL main function
void SetMain();
// Returns SDL error for further logging
std::string SdlError();
// Returns other lib error
// SDL errors type = 1
// SDL IMG errors type = 2
// SDL TTF errors type = 3
// SDL MIX errors type = 4
std::string GetError(int errortype = 1);
// Checks and compairs compiled version of SDL and run version of SDL
void CheckSdlVersions();
// Initializes SDL IMG
void InitalizeImg();
// Initializes SDL TTF
void InitializeTtf();
// Initializes SDL Mixer
void InitializeMixer();
}
// namespace video controlls all video componenents of SDL, with windows
// objects, and everything elses that the end user will see.
namespace video {
// draw namespace is used to directly draw to the pixels of the set renderer
namespace draw {
// Pointer to sdl renderer to draw to
extern SDL_Renderer *sdlrenderer;
// Stores the logging location index
extern int logloc;
// Stores the current color to draw with
// red, green, blue, alpha
extern double drawcolor[4];
// Initalizes neccesary data, and set the standard renderer to draw to
void InitializeDraw(SDL_Renderer *renderer);
// Sets the sdl renderer that will be drawn to
void SetRenderer(SDL_Renderer *renderer);
// Draws a line given two points
// a = x, y
// b = x, y
void Line(int a[2] = 0, int b[2] = 0);
// Draws a series of connected lines, given a vector of points
// point = x, y
void Lines(std::vector<int *> points);
// Draws a single point
// p = x, y
void Point(int p[2] = 0);
// Draws a series of points, given a vector of points
// point = x, y
void Points(std::vector<int *> points);
// Draws a rectangle
// rect = x, y, width, height
void Rect(int rect[4]);
// Draws a series of rectangels, given a vector of rectangle definitions
// rectanlge = x, y, width, height
void Rects(std::vector<int *> rects);
// Draws a solid rectangles
// rect = x, y, width, height
void FillRect(int rect[4]);
// Draws a series of solid rectangels, gicen a vector of rectangle definitions
// rectanlge = x, y, width, height
void FillRects(std::vector<int *> rects);
// Sets the draw color for all drawing functions
void SetColor(double red, double green, double blue, double alpha);
}
// Texture class is used for all uses of sdl textures, and manages all
// funcitons in relation to textures and manipulation of the texture
class Texture {
public:
  // Used to define the current mode of blending for the texture
  enum BlendMode {
    NONE = SDL_BLENDMODE_NONE,
    BLEND = SDL_BLENDMODE_BLEND,
    ADD = SDL_BLENDMODE_ADD,
    MOD = SDL_BLENDMODE_MOD
  };
  // Used to set any texture mirroring is applied
  enum RenderFlip { NOFLIP = 0, HORIZONTAL = 1, VERITCAL = 2 };
  // Pointer to sdl texture
  SDL_Texture *sdltexture;
  // Pointer to sdl renderer for texture rendering
  SDL_Renderer *sdlrenderer;
  // Pointer to sdl surface for texture creation
  SDL_Surface *sdlsurface;
  // Creates a new sdl texture from provided sdl surface
  void CreateTexture(SDL_Surface *surface);
  // Termiantes the texture, and clears all data
  void TerminateTexture();
  // Sets the sdl renderer for texture rendering to the provided sdl renderer
  void SetRenderer(SDL_Renderer *renderer = NULL);
  // Renders the texture to the currently set renderer
  void Render();
  // Sets the color modication to the texture
  // red, green, blue, alpha
  void SetColorMod(double colormod[4] = 0);
  // Sets the blending mode for the texture
  void SetBlendMode(BlendMode mode);
  // Rotates the texture to specified angle given in degrees or radians
  void Rotate(double angle, bool degree = false);
  // Mirrors the texture according to the provided value
  void Flip(RenderFlip flip);
  // Sets the point of rotaiton fr the texture
  void SetRotatePoint(int x, int y);
  // Sets the source clip rectangle
  // x, y are the top right of the clip
  // x, y, width, height
  void SetSourceRect(int rect[4] = 0);
  // Sets the destination clip rectangle that the texture is sent to
  // Defaults to the same size as the texture clip space
  // x, y are the top right of the clip
  // x, y, widht, height
  void SetDestinationRect(int rect[4] = 0);

private:
  // Stores the log location index
  int logloc = 0;
  // Stores the textures width and height, for future use
  int texturewidth, textureheight;
  // Declairs where the texture originated from:
  // either a text surface, or an image surface
  bool textorigin = false;
  // Stores the current angle of rotation for the texutre
  double rotateangle = 0;
  // Stores the current blending mode for the texture
  BlendMode blendmode = NONE;
  // Stores the currently set mirroring settings for the texture
  RenderFlip renderflip = RenderFlip::NOFLIP;
  // Stores the current roation axis for the texture
  int rotatex = -1, rotatey = -1;
  // Sdl rectangles for the source and destinaiton clips
  SDL_Rect sourcerect = {0, 0, 0, 0}, destinationrect = {0, 0, 0, 0};
  // Stores the color modification data for the texture
  // red, green, blue, alpha
  double color[4];
  // Loades the sdl texture structure from preassigned variables
  void LoadTexture();
  // Closes the sdl texture and reloads a new one based off of new variables
  void UpdateTexture();
  // Terminates the sdl texture, but maintains all class data
  void CloseTexture();
};
// Text class is used to modify any and all data points in relation to the use
// of text for objects
class Text {
public:
  // Used for setting the differnet font weights that are posible
  enum FontWeight {
    THIN = 0,
    EXTRALIGHT = 1,
    LIGHT = 2,
    REGULAR = 3,
    MEDIUM = 4,
    SEMIBOLD = 5,
    BOLD = 6,
    EXTRABOLD = 7,
    BLACK = 8
  };
  // Changes the quality ofthe font rendering mode
  enum FontRenderMode { SOLIDTEXT, SHADEDTEXT, BLENDTEXT };
  // Pointer to sdl surface for the text object
  SDL_Surface *textsurface = NULL;
  // Sdl rectange structures for the source and destinaation rectangles
  SDL_Rect sourcerect, destinationrect;
  // Loads a new font based off of directory, size, weight, and italics
  void CreateFont(std::string directory = "resources/fonts/Raleway/",
                  int point = 12, FontWeight weight = REGULAR,
                  bool italic = false);
  // Terminates the ttf font pointer
  void TerminateFont();
  // Sets the size of the font to be loaded
  void SetPoint(int point = 12);
  // Sets the weight of the font to be loaded
  void SetWeight(FontWeight weight = REGULAR);
  // Sets the italics of the font to be loaded
  void SetItalic(bool italic = false);
  // Sets the primary color of the font to be loaded
  // red, green, blue, alpha
  void SetColor(double colors[4] = 0);
  // Sets the secondary color of the font to be loaded
  // red, green, blue, alpha
  void SetBackgroundColor(double colors[4] = 0);
  // Renders out the text for given text with the currently loaded font file
  void RenderText(std::string str = "NULL", FontRenderMode mode = BLENDTEXT);
  // Loads a new font with given paramaters
  // Renders text from the given text, and the currently loaded font
  void CreateText(std::string str = "NULL", int point = 12,
                  FontWeight weight = REGULAR, bool italic = false,
                  std::string direcory = "resources/fonts/Raleway/",
                  double colors[4] = 0);
  // Find text size
  void FindSize(int *x, int *y, std::string str = "NULL");

private:
  // Stores the log location index
  int logloc;
  // Stores the font folder, name, and file path
  std::string folderpath, fontname, filepath;
  // Stores the currently set text that is to be rendered
  std::string text;
  // Stores the current weight of the font
  FontWeight fontweight;
  // Stores the current italcis of the font
  bool fontitalic;
  // Stores the current size of the font
  int fontpoint = 12;
  // Stores the text color
  double textcolor[4];
  // Stores the background color
  double backgroundcolor[4];
  // Pointer to ttf font structure
  TTF_Font *ttffont = NULL;
  // Loads the ttf font from all loaded data
  void LoadFont();
  // Termiantes the ttf font pointer, and creates a new one based uppon the
  // current data
  void UpdateFont();
  // Termiantes the ttf font pointer
  void CloseFont();
  // Creates the file path for the font file for font loading
  void GenFilePath();
};
// Surface class is used to define everything that is part o the
// sdl surface library, and used to create and terminate surfaces
class Surface {
public:
  // Used to set the different blend modes for the surface
  enum BlendMode {
    NONE = SDL_BLENDMODE_NONE,
    BLEND = SDL_BLENDMODE_BLEND,
    ADD = SDL_BLENDMODE_ADD,
    MOD = SDL_BLENDMODE_MOD
  };
  // SDL surface pointer
  SDL_Surface *sdlsurface;
  // SDL surface rectangle pointers
  SDL_Rect *sourcerect = new SDL_Rect();
  SDL_Rect *destinationrect = new SDL_Rect();
  // Loads the given filepath to the surface
  void LoadSurface(std::string filepath = "NULL");
  // Returns the surfaces image file path
  std::string GetSurfaceFilePath();
  // Sets the source rect.
  // x, y, width, height
  void SetSourceRectangle(int rectangle[4]);
  // Returns the source rect.
  int *GetSourceRectangle();
  // Sets the destination rect.
  // x, y, width, height
  void SetDestinationRectangle(int rectangle[4]);
  // Returns the destination rect.
  int *GetDestinationRectangle();
  // Sets the color mod of the surface
  // red, green, blue, alpha
  void SetColorMod(double color[4] = 0);
  // Returns the currently set color mod of the surface
  double *GetColorMode();
  // Sets the blend mode of the surface
  void SetBlendMode(BlendMode mode = NONE);
  // Returns the currently set blend mode of the surface
  BlendMode GetBlendMode();
  // Returns the width and height of the surface
  int *GetSize();
  // Terminates the surface, and frees the SDL pointer from memory
  void Terminate();
  // Scales the surface to given values for width, and height
  void ScaleSurface(int width, int height);

private:
  // Stores the log location index
  int logloc = 0;
  // The width and height of the surface
  int width, height;
  // The file path of the surfaces image
  std::string surfacefilepath;
  // The bounding source and destination rectangles
  int source[4];
  int destination[4];
  // The current color mod applied to the surface
  double colormod[4];
  // The current blend mode applied to the surface
  BlendMode blendmode;
  // Converts from internal Rectangle struct to SDL_Rect struct
  void ConvertRectangles();
  // Sets the surfaces color from the colormod
  void SetSurfaceColor();
  // Sets the surfaces blend mode from the blendmode
  void SetSurfaceBlend();
};
// Object class is used to manage everything to do with visual objects
// Used to create an manipulates image texture or text textures
class Object {
public:
  enum ObjectType { IMAGE, TEXT, BUTTON };
  // Storage to Surface class assosiated with the object
  Surface objsurface;
  // Storage to Text class assosiated with the object
  Text objtext;
  // Storage to Texture class assosiated with the object
  Texture objtexture;
  ObjectType objtype = IMAGE;
  // Sets the base initialization requiered for a new object
  void InitalizeObj(SDL_Renderer *renderer = NULL, int counter = 0,
                    std::string resource = "resources/");
  // Creates a new image object, based off of the given file path
  // Creates a new surface and links it to the texture
  void CreateImgObj(std::string filepath = "NULL.png",
                    SDL_Renderer *renderer = NULL);
  // Creates a new text object, based off of the given text and other parameters
  // Creates a new text and links it to the texture
  void CreateTextObj(std::string text = "NULL", int point = 12, double red = 1,
                     double green = 1, double blue = 1, double alpha = 1,
                     Text::FontWeight weight = Text::REGULAR,
                     bool italic = false,
                     std::string fontdirectory = "Raleway/",
                     SDL_Renderer *renderer = NULL);
  // Scales the object to be a raw x by y size
  void Scale(int x = -1, int y = -1);
  // Scales the object relative to the percent of the total window size
  void ScalePercent(double x = 1, double y = 1);
  // Moves the object by adding the x and y to the current position vector for
  // the object
  void Translate(int x = 0, int y = 0);
  // Sets the objects position vector to x and y
  void SetPos(int x = 0, int y = 0);
  // Alters the color modification for the texture
  void SetColor(double red, double green, double blue, double alpha);
  // Selects a specific portion of the object to copy to the renderer
  // The final appearence is always at the correct scale, causing the clip to be
  // streached as needed
  void SetClipSpace(int startx, int starty, int width, int height);
  // Rotates the object around a set point
  void Rotate(double angle = 0, bool degree = false, int axisx = -1,
              int axisy = -1);
  // Renders a copy of the object to the currently set renderer
  void DisplayObj();
  // Creates a button that returns the button id
  void CreateButton(std::string text = "NULL",
                    std::string imagepath = "NULL.png", bool whitetext = false,
                    bool clipbutton = false, int width = -1, int height = -1,
                    SDL_Renderer *renderer = NULL);
  bool UpdateButton(int mousex = 0, int mousey = 0, int mousestate = 0);

private:
  // Pointer to logging locaiton
  int logloc = 0;
  // Pointer to currently set sdl renderer
  SDL_Renderer *objrenderer;
  // Position, size, and point of rotation data for the object
  int posx, posy, sizex, sizey, rotateaxisx, rotateaxisy;
  double scalex, scaley;
  // Clipping locaiton and size data fo the object
  int clipx, clipy, clipsizex, clipsizey;
  int destsizex, destsizey;
  // The angle of rotation applied to the object
  double rotateangle;
  // The color modification data for the object
  //[0] red, [1] green, [2] blue, [3] alpha
  double colormod[4];
  // Baseline colormod data
  double savedcolormod[4] = {0, 0, 0, 0};
  // Mouseover colormod data
  double mouseovercolormod[4] = {-0.3, -0.3, -0.3, 0};
  // MousePress colormod data
  double mousepresscolormod[4] = {-1, -0.5, -0.15, 0};
  // Sets weather to update button based on color mod or clipspace
  bool buttonclip = false;
  // Standard directory for all resources
  // Image files are stored in "images/"
  // Font files are stored in "fonts/"
  std::string resourcedir = "resources/";
};
// Renderer class, used to store all data for an SDL renderer, aswell as
// running all basic renderer funcitons, such as changing settings
// and basic draw functions.
class Renderer {
public:
  // Used to set renderer mode between the different poslible SDL modes
  enum RendererFlags {
    SOFTWARE = SDL_RENDERER_SOFTWARE,
    ACCELERATED = SDL_RENDERER_ACCELERATED,
    VSYNC = SDL_RENDERER_PRESENTVSYNC,
    TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
  };
  // Sets the blending mode for the renderer
  enum BlendMode {
    NONE = SDL_BLENDMODE_NONE,
    BLEND = SDL_BLENDMODE_BLEND,
    ADD = SDL_BLENDMODE_ADD,
    MOD = SDL_BLENDMODE_MOD
  };
  // The pointer to the SDL renderer
  SDL_Renderer *sdlrenderer;
  // Internal storage of the renderer mode, for functions to check against
  RendererFlags rendererflag;
  // Genoreates a new renderer from a given window, and creates the log
  void CreateRenderer(SDL_Window *sdlwindow, std::string title,
                      RendererFlags flags);
  // Destroys the renderer, but not the window
  void DestroyRenderer();
  // Sets a texture to render to
  void SetTargetTexture(Object target);
  // Sets the viewport of the renderer
  // x, y, width, height
  void SetViewport(int rect[4] = 0);
  // Sets the scale in an x factor and y factor of the renderer
  void SetScale(float scalex, float scaley);
  // Sets the resolution of the renderer, without changing the window
  void SetResolution(int width, int height);
  // Sets the zone to renderer to on the target texture
  // x, y, width, height
  void SetTargetClip(int rect[4] = 0);
  // Updates the renderer and displays everything that has been drawn
  void Update();
  // Clears the renderer with the current draw color
  void Clear();

private:
  // Sets log location for aequus framework logging
  int logloc = 0;
};
// Message box class is used to contain data and functions that pertain
// to message boxes, that can be used for providing error, or information
// to the user.
class MessageBox {
public:
  // Used to set different message box types
  enum MessageBoxFlags {
    ERROR = SDL_MESSAGEBOX_ERROR,
    WARNING = SDL_MESSAGEBOX_WARNING,
    INFORMATION = SDL_MESSAGEBOX_INFORMATION
  };
  // Used to set the default key controls for a button
  enum MessageBoxButtonFlags {
    RETURNKEY = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
    ESCAPEKEY = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
    NOKEY = 0
  };
  // Used to set specific color in a color scheme
  enum MessageBoxColorType {
    BACKGROUND,
    TEXT,
    BUTTON_BORDER,
    BUTTON_BACKGROUND,
    BUTTON_SELECTED,
    COLOR_MAX
  };
  // Sets the color scheme for all rgb colors for five sections, with variables
  // of 0.0-1.0
  void SetColorScheme(float r1, float g1, float b1, float r2, float g2,
                      float b2, float r3, float g3, float b3, float r4,
                      float g4, float b4, float r5, float g5, float b5);
  // Sets single color of the color scheme, with variables of 0.0-1.0
  void SetColor(MessageBoxColorType type, float red, float green, float blue);
  // Adds an additional button to the message box
  void AddButton(MessageBoxButtonFlags flags, std::string text);
  // Creates a message box, must be called before any other message box function
  void NewMessageBox(MessageBoxFlags flags, SDL_Window *parentwindow,
                     std::string title, std::string message);
  // Displays the message box, and returns button press
  int RunMessageBox();

private:
  // Data struct to contain and manage all internal data about the message box
  struct MessageBoxData {
    Uint32 flags = NULL;
    SDL_Window *window = NULL;
    std::string title = "";
    std::string message = "";
    std::vector<SDL_MessageBoxButtonData> buttons;
    SDL_MessageBoxColorScheme *colorscheme = NULL;
  };
  // Variable to conatin and use the internal message box data
  MessageBoxData internalmessageboxdata;
  // SDL variable that is unedditable, but is used for all SDL funcitons
  SDL_MessageBoxData messageboxdata;
};
// Sets log location for aequus framework logging
extern int logloc;
// Used for setting different window initialization settings
enum WindowFlags {
  FULLSCREEN = SDL_WINDOW_FULLSCREEN,
  FULLSCREEN_DESKTOP = SDL_WINDOW_FULLSCREEN_DESKTOP,
  OPENGL = SDL_WINDOW_OPENGL,
  SHOWN = SDL_WINDOW_SHOWN,
  HIDDEN = SDL_WINDOW_HIDDEN,
  BORDERLESS = SDL_WINDOW_BORDERLESS,
  RESIZABLE = SDL_WINDOW_RESIZABLE,
  MINIMIZED = SDL_WINDOW_MINIMIZED,
  MAXIMIZED = SDL_WINDOW_MAXIMIZED,
  INPUT_GRABBED = SDL_WINDOW_INPUT_GRABBED,
  INPUT_FOCUS = SDL_WINDOW_INPUT_FOCUS,
  MOUSE_FOCUS = SDL_WINDOW_MOUSE_FOCUS,
  FOREIGN = SDL_WINDOW_FOREIGN,
  ALLOW_HIGHDPI = SDL_WINDOW_ALLOW_HIGHDPI,
  MOUSE_CAPTURE = SDL_WINDOW_MOUSE_CAPTURE,
  WINDOWED = 0
};
// Used for setting different window position settings
enum WindowPositionFlags {
  CENTERED = SDL_WINDOWPOS_CENTERED,
  CENTERED_MASK = SDL_WINDOWPOS_CENTERED_MASK,
  UNDEFINED = SDL_WINDOWPOS_UNDEFINED,
  UNDEFINED_MASK = SDL_WINDOWPOS_UNDEFINED_MASK
};
// Used for setting the return data type
enum ReturnType { BUTTON };
// Structure for storing window data
struct WindowData {
  SDL_Window *sdlwindow = NULL;
  Renderer windowrenderer;
  Object *obj = NULL;
  std::vector<Object> objects;
  int logloc = 0;
  bool hidden = false;
  bool minimized = false;
  bool maximized = false;
  bool bordered = true;
  bool grabbed = false;
  int sizex = 0, sizey = 0;
  std::string title;
};
// Structure for storing object return data, based off of user input
struct ReturnData {
  ReturnType type;
  int windowID = 0;
  int objectID = 0;
  int value = 0;
};
// Storage for all windows that are created
extern std::vector<WindowData> windows;
// Int pointer to the currently active window from windows
extern int boundwindow;
// Int pointer to the currently active object from a windows object vector
extern int boundobj;
// String directory for the file location of all resources:
// Files, fonts, textures, ect.
extern std::string globalresourcedir;
// Storage for any messagecoxes that are daughter windows to current
// window
extern std::vector<MessageBox> messageboxes;
// Pointer directly to bound window data
extern WindowData *win;
// External access to return data from objects
extern std::vector<ReturnData> output;
// Creates new SDL window based off of given arguments
void CreateWindow(std::string title = "NULL", int width = 600, int height = 600,
                  int x = SDL_WINDOWPOS_UNDEFINED,
                  int y = SDL_WINDOWPOS_UNDEFINED,
                  Uint32 flags = WINDOWED | RESIZABLE);
// Terminates an SDL window, and erases all data
void TerminateWindow(int pointer = boundwindow);
// Toggles weather the window is hidden
void SetHidden(bool hide, int pointer = boundwindow);
// Maximizes window
void Maximize(int pointer = boundwindow);
// Minimizes window
void Minimize(int pointer = boundwindow);
// Brings window to top above other windows
void Raise(int pointer = boundwindow);
// Restores window to original size and position
void Restore(int pointer = boundwindow);
// Toggels window border mode
void SetBordered(bool border, int pointer = boundwindow);
// Sets window brightness
void SetBrightness(float brightness, int pointer = boundwindow);
// Toggles fullscreen mode
void SetFullscreen(Uint32 flags, int pointer = boundwindow);
// Sets gamma color ramp of window
void SetGammaRamp(float red, float green, float blue,
                  int pointer = boundwindow);
// Toggles grabing of input to window
void SetGrab(bool grab, int pointer = boundwindow);
// Sets window icon, given imagedirectory
void SetIcon(std::string iconfiledirectory, int pointer = boundwindow);
// Sets the maximum size for the window to be resized to
void SetMaximumSize(int width, int height, int pointer = boundwindow);
// Sets the minimum size for the window to be resized to
void SetMinimumSize(int width, int height, int pointer = boundwindow);
// Sets the windows position in pixels
void SetPosition(int x, int y, int pointer = boundwindow);
// Sets the window size in pixels
void SetSize(int width, int height, int pointer = boundwindow);
// Changes the windows title
void SetTitle(std::string title, int pointer = boundwindow);
// Displays the updated window surface
void Update(bool persistent = false, int pointer = boundwindow);
// Displays all updated windows
void UpdateAll(bool persistent = false);
// Sets the currently active window
void BindWindow(int pointer = 0);
// Checks is there are any currently open windows
//(true) if all windows are closed
//(false) if there are any open windows
bool AllClose();
// Initalizes a new object and sets it as the currently bound object
void NewObject(int pointer = boundwindow);
// Binds the current object
void BindObject(int pointer);
// Binds the current window, and the current object
void Bind(int windowpointer = 0, int objectpointer = 0);
// Either enables or disables the screensaver
void SetScreenSaver(bool screensaver);
// Checks the event handling for the current window
void HandleEvents(int pointer = boundwindow);
// Checks the event handling for all windows
void HandleEventsAll();
}
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
namespace audio {
namespace music {
// Stucture to store song data
struct Song {
  // SDL music pointer
  Mix_Music *mixsong;
  // Song name
  std::string songname;
};
// Stores loaded songs and data
extern std::vector<Song> songs;
// int pointer to current song in song playlist
extern int currentsong;
// Pointer to log location index
extern int logloc;
// Playback settings for autoplay, shuffle, and check if song is playing
extern bool autoplay, shuffle, playing;
// Saves the number of loops to play for a song, and the ms for fade in
extern int loops, fadeint;
// Saves the position in s to begin song at
extern double position;
// Initalizes music playback
void InitalizeMusic();
// Loads a song into the song vector from given file(mp3)
void LoadSong(std::string file);
// Plays the current song from the song vector with given fade in time ms, for
// number of loops, and given start positon s
void PlaySong(int startfadein = -1, int startloops = -1,
              double startposition = -1.0);
// Sets the song playing volume for song playback
void SetVolume(double percent);
// Stops song playback immediately
void StopSong();
// Toggles auto playing funciton for song vector. Requiers update to be called
// regularly
void SetAutoPlay(bool setting);
// Toggles shuffle playng for song vector, selecting a random song as the
// current song
void SetShuffle(bool setting);
// Fades out current song given ms for fade time
void FadeOut(int endfadeout = -1);
// Loades songs from a given playlist folder
void LoadPlaylist(std::string folder);
// Clears song vector of all current songs
void ClearQueue();
// Updates any per frame checks eg. autoplay
void Update();
// Terminates all music functions
void TerminateMusic();
}
class Chunk {
public:
  // Load chunk from file
  void Load(std::string file);
  // Sets chunk playback volume
  void Volume(double percent);
  // Terminates chunk and clears memory
  void Terminate();
  // Returns the SDL chunk
  Mix_Chunk *GetChunk();

private:
  // Pointer to SDL chunk data
  Mix_Chunk *chunk = NULL;
};
// Stores the number of channels, the currently bound channel, and the currently
// bound chunk
extern int channels, boundchannel, boundchunk;
// Stoes all the loaded audio chunks
extern std::vector<Chunk> chunks;
// Stores the log location pointer
extern int logloc;
// Initalizes the audio system
void InitializeAudio();
// Initalizes the SDL audio device for playback
void InitalizeDevice();
// Terminates the SDL audio device removing it
void TerminateDevice();
// Sets the number of avaliable playback channels for audo playback
void AllocateChannels(int channelcount);
// Binds the current channel for audio playback
void BindChannel(int channel);
// Sets the volume of a channel
void ChannelVolume(double percent = 1, int channel = boundchannel);
// Plays a previously loaded chunck.
// loop number of loops that will be played
// fadein ms of fade in from begining
// time seconds into the audio to begin at
void PlayChunk(int loops = 0, int fadein = 0, int time = -1,
               int chunk = boundchunk, int channel = boundchannel);
// Stops playing any audio on given channel
void StopChannel(int channel = boundchannel);
// Loads and plays sound file on selected channel
void PlaySound(std::string file, int channel = boundchannel);
// Loads sound file to a chunk
void LoadSound(std::string file);
}
namespace fileio {}
extern int FPS;
extern time_t FPStimecheck;
void Frame();
}

#endif //! _AEQUUS_FILES_
