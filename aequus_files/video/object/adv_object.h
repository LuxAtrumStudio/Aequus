#ifndef _AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "object.h"
#include "surface.h"
#include "text.h"
#include "texture.h"
namespace aequus {
namespace video {
// Advanced Object class is used to create complex objects that utilize many sub
// objects
class AdvObject {
 public:
  // Used to define what type of advanced object is being used
  enum AdvType { GRAPH, TEXTBOX };
  // Used to define what graph type
  enum GraphType { LINE, BAR, SCATTER, PIE, PLOT };
  // Used to store single line graph data
  struct GraphData {
    std::string title;
    std::vector<aequus::ValueGroup> points;
  };
  // Texture for advanced object
  Object globalobj;
  // Used to define advanced object type
  AdvType objtype;
  // Initalizes Advanced object functions
  void InitializeAdvObj(Renderer renderer, int counter = 0,
                        std::string resource = "resources/");
  // Creates a graph from a datefile, or equations with folowing args
  // graphheight(int) in pixels, graphwidth(int) in pixels
  // background(bool), axis(bool), grid(bool), values(bool), labels(bool),
  // title(bool), graphtitle(bool)
  // graphname(string), domain start(double), domain end(double), range
  // start(double), range end(double)
  void CreateGraph(std::string datafile, GraphType graphtype,
                   int graphwidth = 100, int graphheight = 100,
                   bool graphbackground = false, bool graphaxis = false,
                   bool graphgrid = false, bool graphvalues = false,
                   bool graphlabels = false, bool graphtitle = false,
                   bool graphimagetitle = false, std::string graphname = "",
                   double xstart = 0, double xend = 0, double ystart = 0,
                   double yend = 0);
  // Updates data in previously defined graph
  void UpdateGraph(std::string data);
  // Creates a text box for entering text
  void CreateTextBox(int width = 100, int height = 100,
                     std::string texture = "", bool whitetext = false,
                     bool clip = false, std::string defaulttext = "");
  // Updates the statues of selected for text box
  void UpdateTextBox(int x = 0, int y = 0, int state = 0);
  // Updates text box text
  void UpdateTextBoxText(int key = 0);
  // Returns text box string if it is unselected
  std::string GetString();
  // Displays the advanced object
  void Display();
  // Moves advanced object to specified position
  void SetPos(int x = 0, int y = 0);
  // Termiantes advanced object
  void TerminateAdvObject();

 private:
  // Pointer to logging locaiton
  int logloc = 0;
  // The advanced object count for the window
  int advobjcount = 0;
  // Pointer to currently set sdl renderer
  Renderer objrenderer;
  // Standard directory for all resources
  // Image files are stored in "images/"
  // Font files are stored in "fonts/"
  std::string resourcedir = "resources/";
  // Storage for position and size values of the advanced object
  int posx, posy, width, height;
  // The color modification data for the object
  //[0] red, [1] green, [2] blue, [3] alpha
  double colormod[4];
  // Used to store text entered to text box
  std::string storedtext;
  // Saved date for recreation of button
  std::string texturedir;
  bool whitetextcheck, clipcheck;
  // Used to determin if textbox is selected
  bool selected;
  // Titles for graphs
  std::string titlestr;
  std::vector<std::string> titles;
  // Storage for graph points in either 2D or 3D
  std::vector<GraphData> graphs;
  // Stores the colors for differnt graphs
  std::vector<ValueGroup> colors;
  // Stores the domain and range for graphs
  double minx, maxx, miny, maxy, stepx, stepy;
  // The object class for the actual advanced object
  bool axis, values, labels, title, grid, imagetitle, background;
  // Stores the background color for the graphs
  ValueGroup backgroundcolor;
  // Stores the graph type
  GraphType graphformat;
  // Loads the data for 2D graphs
  void LoadGraphData(std::string datafile = "NULL");
  // Computes the values for the plot graphs
  void ComputeDataPoints(std::string funciton = "x");
  // Draws the line graphs to the object
  void DrawLineGraph();
  // Draws the background for grapns
  void DrawBackground(int colorjump = 0);
  // Draws the axis for graphs
  void DrawAxis();
  // Draws the coordinate grid for graphs
  void DrawGrid();
  // Draws labels for the axis and grid Lines
  void DrawLabels();
  // Draws the title of the curves
  void DrawTitle();
  // Draws labels for values along curve
  void DrawValues();
  // Draws title for compleate graphs
  void DrawImageTitle();
  // Genorates colors for the color vector
  void GenColors(int number = 0);
  // Converted value to display position
  int ConvertValue(double value, bool yaxis);
};
}
}
#endif  // !_AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
