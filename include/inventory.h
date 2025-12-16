/**
* Luis Lopez
* March, 2025
* This file contains all the decleration of the variables and funtions used to create the GUI of the application.
**/

#ifndef INVENTORY_H
#define INVENTORY_H
#include "raylib.h"
#include <string>

class Inventory
{
    private:
        // Variables for screen size
        const int screenHeight = 1000;
        const int screenWidth = 800;

        // Variable for user input of item
        std::string name = "";
        std::string qty = "";
        std::string price = "";
        char searchText[20] = {'\0'};
        bool searchButtonClicked = false;
        double timer = 0.0;

        // Variables to to validate user input of the item
        int wordLength = 0;
        int qtyLength  = 0;
        int priceLength = 0;
        int periodIndex = -1;
        bool periodPresent = false;
        bool submitButton = false;

        // States used to move from one screen to another
        enum States  {MAINMENU, ADDITEM, DELETEITEM, EDITITEM, DISPLAYITEMS, SUCCESS, FAIL, SEARCH};
        enum States previousState;
        enum States state = MAINMENU;

    public:
        Inventory();
        void MainLoop();
        void MainMenu();
        void AddItem();
        void EditItem();
        void DeleteItem();
        void DisplayItems();
        void ReturnToMainMenu();
        void CheckMouseCollision(Rectangle, int);
        void GetInput(int);
        void CheckName();
        void CheckNumber();
        void CheckDecimal();
        void ResetValues();
        void SuccessWindow();
        void FailWindow();
        void SearchItem();

};

#endif // INVENTORY_H

