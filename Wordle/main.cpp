#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "WordleWindow.h"
using namespace view;

int main (int argc, char ** argv)
{
  WordleWindow window(1000, 1000, "Wordle by Carriger");
  window.show ();
  return(Fl::run());
}
