#include "WordleWindow.h"
#include "WordleManager.h"
using namespace model;

#include <iostream>
using namespace std;

namespace view
{

WordleWindow::WordleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    WordleManager* manager = new WordleManager(5);
    manager->randomizeWord();
    cout << manager->getCurrentWord() << endl;
    manager->randomizeWord();
    cout << manager->getCurrentWord() << endl;
}

WordleWindow::~WordleWindow()
{
    //dtor
}
}
