#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "WordleWindow.h"
using namespace view;

int main (int argc, char ** argv)
{
    WordleWindow window(500, 500, "Wordle by Schmidt & Carriger");
    window.show ();
    return(Fl::run());
}
