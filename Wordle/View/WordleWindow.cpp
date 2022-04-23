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
    vector<WordleManager::LetterState> states = manager->getDetails("crane");
    for (auto aState = states.begin(); aState != states.end(); ++aState) {
        cout << *aState << "";
    }
    cout << "" << endl;
    cout << "crane" << endl;

}

WordleWindow::~WordleWindow()
{
    //dtor
}
}
