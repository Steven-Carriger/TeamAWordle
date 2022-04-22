#include "WordleWindow.h"

#define NUMBER_OF_KEYS 28
#define KEYBOARD_X 90
#define KEYBOARD_Y 450
#define BUTTON_WIDTH 50
#define BUTTON_HEIGHT 50
#define X_OFFSET 25
#define MAX_FIRST_ROW 10
#define MAX_OTHER_ROWS 9
#define BUTTON_PADDING 55
#define EMPTY_VALUE 0
namespace view
{

WordleWindow::WordleWindow(int width, int height, const char* title) : Fl_Window(width, height, title)
{
    begin();
    this->keyLabels = {"Q","W","E","R","T","Y","U","I","O","P","A","S","D","F","G","H","J","K","L","Enter","Z","X","C","V","B","N","M","Undo"};
    this->createTheKeyboard();
    end();
}

void WordleWindow::createTheKeyboard()
{
    this->keyButtons = vector<Fl_Button*>();
    this->addKeysToTheKeyboard();
}

void WordleWindow::addKeysToTheKeyboard()
{
    int x = KEYBOARD_X;
    int y = KEYBOARD_Y;
    int rowCount = EMPTY_VALUE;
    bool isFirstRow = true;
    for (int i = EMPTY_VALUE; i < NUMBER_OF_KEYS; i++)
    {
        Fl_Button* newButton = new Fl_Button(x + BUTTON_PADDING * rowCount, y, BUTTON_WIDTH, BUTTON_HEIGHT, this->keyLabels[i]);
        newButton->callback(cbKeyPressed);
        this->keyButtons.push_back(newButton);
        rowCount++;

        if (rowCount == MAX_FIRST_ROW && isFirstRow) {
            x = KEYBOARD_X + X_OFFSET;
            rowCount = EMPTY_VALUE;
            y += BUTTON_PADDING;
            isFirstRow = false;
        }
        if (rowCount == MAX_OTHER_ROWS && !isFirstRow) {
            x = KEYBOARD_X + X_OFFSET;
            rowCount = EMPTY_VALUE;
            y += BUTTON_PADDING;
        }
    }
}

void WordleWindow::cbKeyPressed(Fl_Widget* widget)
{
    cout << "button: " << widget->label() << " pressed." << endl;
}

WordleWindow::~WordleWindow()
{
    //dtor
}
}
