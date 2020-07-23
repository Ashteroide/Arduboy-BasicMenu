// Ashlee J
// 23rd of July, 2020
// Testing a Menu system after testing on the Arduino Uno

#include <Arduboy2.h>

Arduboy2 arduboy;

int cursorPos;

enum class CursorRow
{
    cursorZero,
    cursorOne,
    cursorTwo
};

CursorRow cursorRow = CursorRow::cursorZero;

enum class PageState
{
    Main,
    Hello,
    Options,
};

PageState pageState = PageState::Main;

void setup()
{
    cursorPos = 0;
    arduboy.begin();
    arduboy.clear();
}

void loop()
{
    arduboy.pollButtons();
    arduboy.clear();

    switch(cursorRow)
    {
        case CursorRow::cursorZero:
            cursorPos = 0;
            drawCursor();      
            break;

        case CursorRow::cursorOne:
            cursorPos = 10;
            drawCursor();
            break;
        
        case CursorRow::cursorTwo:
            cursorPos = 20;
            drawCursor();
            break;
    }

    switch(pageState)
    {
        case PageState::Main:
            updateMain();
            drawMain();
            break;

        case PageState::Hello:
            updateHello();
            drawHello();
            break;

        case PageState::Options:
            updateOptions();
            drawOptions();
            break;
    }
    arduboy.display();

    if(arduboy.justPressed(DOWN_BUTTON) && cursorPos == 10) cursorRow = CursorRow::cursorTwo;
    else if((arduboy.justPressed(DOWN_BUTTON) && cursorPos == 0) || (arduboy.justPressed(UP_BUTTON) && cursorPos == 20)) cursorRow = CursorRow::cursorOne;
    else if(arduboy.justPressed(UP_BUTTON) && cursorPos == 10) cursorRow = CursorRow::cursorZero;

    if(arduboy.justPressed(A_BUTTON)) cursorRow = CursorRow::cursorZero;
}

void updateMain()
{
    if(arduboy.justPressed(A_BUTTON) && cursorPos == 10) pageState = PageState::Hello;
    else if(arduboy.justPressed(A_BUTTON) && cursorPos == 20) pageState = PageState::Options;
}

void drawMain()
{
    arduboy.setCursor(8, 0);
    arduboy.print(F("Main:"));

    arduboy.setCursor(8, 10);
    arduboy.print(F("Hello"));

    arduboy.setCursor(8, 20);
    arduboy.print(F("Options"));
}

void updateHello()
{
    if(arduboy.justPressed(A_BUTTON) && cursorPos == 10) pageState = PageState::Main;
}

void drawHello()
{
    arduboy.setCursor(8, 0);
    arduboy.print(F("Hello World!"));

    arduboy.setCursor(8, 10);
    arduboy.print(F("Back"));
}

void updateOptions()
{
    if(arduboy.justPressed(A_BUTTON) && cursorPos == 10) pageState = PageState::Main;
}

void drawOptions()
{
    arduboy.setCursor(8, 0);
    arduboy.print(F("Options Page:"));

    arduboy.setCursor(8, 10);
    arduboy.print(F("Back"));
}

void drawCursor()
{
    arduboy.setCursor(0, cursorPos);
    arduboy.print(F(">"));
}
