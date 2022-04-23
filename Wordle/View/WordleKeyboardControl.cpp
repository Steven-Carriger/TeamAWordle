#include "WordleKeyboardControl.h"

#define KEYBOARD_GAP 5
#define NUM_FIRST_ROW 10
#define NUM_OTHER_ROW 9
#define NUM_ROW 3

#include <algorithm>
#include <iostream>
using namespace std;

namespace view {

WordleKeyboardControl::WordleKeyboardControl(int x, int y, int width, int height) : Fl_Group(x, y, width, height, nullptr)
{
    begin();
    this->createButtons();
    end();
}

WordleKeyboardControl::~WordleKeyboardControl()
{
    //dtor
}

void WordleKeyboardControl::createButtons() {

    int keySize = min((this->w() - NUM_FIRST_ROW * KEYBOARD_GAP) / NUM_FIRST_ROW, (this->h() - NUM_ROW * KEYBOARD_GAP) / NUM_ROW);
    int initXFirstRow = this->x() + (this->w() - (NUM_FIRST_ROW - 1) * KEYBOARD_GAP - NUM_FIRST_ROW * keySize) / 2;
    int initXOtherRow = this->x() + (this->w() - (NUM_OTHER_ROW - 1) * KEYBOARD_GAP - NUM_OTHER_ROW * keySize) / 2;
    int initY = this->y() + (this->h() - (NUM_ROW - 1) * KEYBOARD_GAP - NUM_ROW * keySize) / 2;
    vector<const char*> keyLabels = {"Q","W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","Enter","Z","X","C","V","B","N","M","Back"};
    int row = 0;

    for (int i = 0; i < keyLabels.size(); i++)
    {
        int x = initXFirstRow;
        int colMod = i % NUM_FIRST_ROW;
        if (i >= NUM_FIRST_ROW) {
            x = initXOtherRow;
            colMod = (i - NUM_FIRST_ROW) % NUM_OTHER_ROW;
            row = (i - NUM_FIRST_ROW) / NUM_OTHER_ROW + 1;

        }
        cout << x + (i % NUM_FIRST_ROW) * (keySize + KEYBOARD_GAP) << endl;
        Fl_Button* newKeyButton = new Fl_Button(x + colMod * (keySize + KEYBOARD_GAP), initY + row * (keySize + KEYBOARD_GAP), keySize, keySize, keyLabels[i]);
        this->buttons.push_back(newKeyButton);
    }
}

}
