/**
* Luis Lopez
* March, 2025
*   This file contains all the implentetaion of the functions needed to display the GUI.
*
**/

#include "raylib.h"
#include "inventory.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "item.h"
#include <sstream>
#include <iomanip>
#include <string>


// Constructor
Inventory::Inventory()
{
    // Initialize a window
    InitWindow(screenWidth, screenHeight, "The Inventory Application");
    SetTargetFPS(60);
}

// Main entry of the application
void Inventory::MainLoop(){

    // Main loop
    while(!WindowShouldClose()){

        BeginDrawing();
            ClearBackground(DARKGRAY);

            // Switch between the different states
            switch (state){
                case MAINMENU:      MainMenu();
                                    break;
                case ADDITEM:       AddItem();
                                    break;
                case EDITITEM:      EditItem();
                                    break;
                case DELETEITEM:    DeleteItem();
                                    break;
                case DISPLAYITEMS:  DisplayItems();
                                    break;
                case FAIL:          FailWindow();
                                    break;
                case SUCCESS:       SuccessWindow();
                                    break;
                case SEARCH:        SearchItem();
                                    break;
                default: MainMenu();
            }
        EndDrawing();
    }

    // Close the window
    CloseWindow();
}


/// Display the main menu
void Inventory::MainMenu(){

    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);

    // Display the main menu buttons
    bool displayButton = GuiButton((Rectangle) {screenWidth/ 2.0f - 200, 200, 400, 80}, "Display Items");
    if(displayButton){
        state = DISPLAYITEMS;
    }

    bool addButton = GuiButton((Rectangle) {screenWidth/ 2.0f - 200, 350, 400, 80}, "Add Item");
    if(addButton){
        state = ADDITEM;
    }

    bool editButton = GuiButton((Rectangle) {screenWidth/ 2.0f - 200, 500, 400, 80}, "Edit Item");
    if(editButton){
        state = SEARCH;
    }

    bool deleteButton = GuiButton((Rectangle) {screenWidth/ 2.0f - 200, 650, 400, 80}, "Delete Item");
    if(deleteButton){
        state = DELETEITEM;
    }


}


/// Adds item to database
void Inventory::AddItem(){

    // Create an input box for name, price, and quantity
    ClearBackground(LIGHTGRAY);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    // Initialize rectangles for input boxes
    Rectangle nameBox = {screenWidth/ 2.0f - 200, 200, 400, 80};
    Rectangle priceBox = {screenWidth/ 2.0f - 200, 350, 400, 80};
    Rectangle qtyBox = {screenWidth/2.0f - 200, 500, 400, 80};

    // Draw name input box
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 150, 400, 80}, "Name: ");
    DrawRectangleRec(nameBox, WHITE);
    CheckMouseCollision(nameBox, 0);

    // Draw price input box
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 300, 400, 80}, "Price: ");
    DrawRectangleRec(priceBox, WHITE);
    CheckMouseCollision(priceBox, 1);

    // Draw quantity input box
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 440, 400, 80}, "Qty: ");
    DrawRectangleRec(qtyBox, WHITE);
    CheckMouseCollision(qtyBox, 2);

    //Submit button
    submitButton = GuiButton((Rectangle){400, 700, 200, 80}, "Submit");
    if(submitButton){
        if(setItem(name, std::stod(price), std::stoi(qty))){
            state = SUCCESS;
        }
        else{
            previousState = ADDITEM;
            state = FAIL;
        }
    }

    // Check if user wants to return to main menu
    ReturnToMainMenu();
}


/// Display success window
void Inventory::SuccessWindow(){
    GuiDrawText("Success!!!", (Rectangle){250, 400, 300, 100}, 1, BLACK);
    // Get time since last frame
    timer += GetFrameTime();

    // Pause the screen for 3 seconds
    if(timer >= 1.0){
        timer = 0.0; // Reset timer
        ResetValues();
    }


}

/// Display fail window
void Inventory::FailWindow(){
    ClearBackground(WHITE);
    GuiDrawText("Fail! Check name!", (Rectangle){250, 400, 300, 100}, 1, RED);
    // Get time since last frame
    timer += GetFrameTime();

    // Pause the screen for 3 seconds
    if(timer >= 1.0){
        state = previousState;
        timer = 0.0; // Reset timer
    }

}


/// Check if mouse is in textbox
void Inventory::CheckMouseCollision(Rectangle box, int choice){

    // Outline box in color red
    if(CheckCollisionPointRec(GetMousePosition(), box)){
        DrawRectangleLinesEx(box, 3, RED);
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        GetInput(choice);
    }

    // Outline box in color black
    else{
        DrawRectangleLinesEx(box, 3, BLACK);

    }
    // Draw name Text onto screen
    DrawText(name.c_str(), screenWidth/2.0f - 170, 220, 30, BLACK);
    DrawText(price.c_str(), screenWidth/2.0f - 170, 360, 30, BLACK);
    DrawText(qty.c_str(), screenWidth/2.0f - 170, 520, 30, BLACK);

}

/// Get user Input
void Inventory::GetInput(int choice){

    switch(choice){
        case 0: CheckName();
                break;
        case 1: CheckDecimal();
                break;
        case 2: CheckNumber();
                break;

    }
}

/// Check name input
void Inventory::CheckName(){

/**************************************************************
* For this section of the code, the official input box example*
* from the official Raylib website was used as reference,     *
* it was modified to fit in this project                      *
**************************************************************/
    int keyPressed = GetCharPressed();

    // Loop while key is bieng pressed
    while(keyPressed > 0){

        // Check that only letter are being entered
        if ((isalpha(keyPressed)) && (wordLength < 20)){
            name += char(keyPressed);
            wordLength++;
        }
        // Get next character
        keyPressed = GetCharPressed();


    }

    // Remove last character when backspace is pressed
    if(IsKeyPressed(KEY_BACKSPACE)){
        wordLength--;
        if(wordLength < 0){
            wordLength = 0;
        }
        else{
            name.pop_back();
        }
    }
}

/// Check if decimal input
void Inventory::CheckDecimal(){
    int keyPressed = GetCharPressed();

    // Loop while key is bieng pressed
    while(keyPressed > 0){

        // Check that only letter are being entered
        if ((isdigit(char(keyPressed)) || (char(keyPressed) == '.')) && (priceLength < 20)){

            // Check if more than one period has been entered
            if(char(keyPressed) == '.'){
                if(!periodPresent){
                    periodPresent = true;
                    price += char(keyPressed);
                    periodIndex = priceLength;
                    priceLength++;
                }
                break;
            }

            else{
                price += char(keyPressed);
                priceLength++;
            }
        }
        // Get next character
        keyPressed = GetCharPressed();

    }

    // Remove last character when backspace is pressed
    if(IsKeyPressed(KEY_BACKSPACE)){
        priceLength--;
        if(priceLength < 0){
            priceLength = 0;
        }
        else{
            price.pop_back();
        }
        // Check if the period has been removed
        if(priceLength == (periodIndex)){
            periodPresent = false;
        }
    }
}

/// Check if input is number
void Inventory::CheckNumber(){
    int keyPressed = GetCharPressed();

    // Loop while key is bieng pressed
    while(keyPressed > 0){

        // Check that only letter are being entered
        if ((isdigit(keyPressed)) && (qtyLength < 20)){
            qty += char(keyPressed);
            qtyLength++;
        }
        // Get next character
        keyPressed = GetCharPressed();


    }

    // Remove last character when backspace is pressed
    if(IsKeyPressed(KEY_BACKSPACE)){
        qtyLength--;
        if(qtyLength < 0){
            qtyLength = 0;
        }
        else{
            qty.pop_back();
        }
    }

}

// Edit item
void Inventory::EditItem(){
    // Create an input box for name, price, and quantity
    ClearBackground(LIGHTGRAY);
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    // Initialize rectangles for input boxes
    Rectangle nameBox = {screenWidth/ 2.0f - 200, 200, 400, 80};
    Rectangle priceBox = {screenWidth/ 2.0f - 200, 350, 400, 80};
    Rectangle qtyBox = {screenWidth/2.0f - 200, 500, 400, 80};

    // Draw name input box
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 150, 400, 80}, "Name: ");
    DrawRectangleRec(nameBox, WHITE);

    // Draw price input box
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 300, 400, 80}, "Price: ");
    DrawRectangleRec(priceBox, WHITE);
    CheckMouseCollision(priceBox, 1);

    // Draw quantity input box
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 440, 400, 80}, "Qty: ");
    DrawRectangleRec(qtyBox, WHITE);
    CheckMouseCollision(qtyBox, 2);

    //Submit button
    submitButton = GuiButton((Rectangle){400, 700, 200, 80}, "Submit");
    if(submitButton){
        if(editItem(name, std::stod(price), std::stoi(qty))){
            state = SUCCESS;
        }
        else{
            previousState = EDITITEM;
            state = FAIL;
        }
    }
    // Check if user wants to return to main menu
    ReturnToMainMenu();
}

// Delete item
void Inventory::DeleteItem(){
    ClearBackground(LIGHTGRAY);
    // Draw text lable
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 150, 420, 80}, "Enter name of item to delete: ");
    // Draw the text boxes for input
    GuiTextBox((Rectangle){screenWidth/ 2.0f - 200, 200, 400, 80}, searchText, 30, true);

    // Draw the search button
    searchButtonClicked = GuiButton((Rectangle){400, 350, 200, 40}, "Delete");
    if(searchButtonClicked){
        std::string newSearchText = searchText;
        if(deleteItem(newSearchText)){
            state = SUCCESS;
        }
        else{
            previousState = DELETEITEM;
            state = FAIL;
        }

    }
    ReturnToMainMenu();
}

// Panel to serach for item
void Inventory::SearchItem(){
ClearBackground(LIGHTGRAY);
    // Draw text lable
    GuiLabel((Rectangle){screenWidth/ 2.0f - 200, 150, 420, 80}, "Enter name of item to edit: ");
    // Draw the text boxes for input
    GuiTextBox((Rectangle){screenWidth/ 2.0f - 200, 200, 400, 80}, searchText, 30, true);

    // Draw the search button
    searchButtonClicked = GuiButton((Rectangle){400, 350, 200, 40}, "Edit");
    if(searchButtonClicked){

        // Convert to string
        std::string newSearchText = searchText;

        // Check if item exists
        if(checkItem(newSearchText)){

            name = newSearchText;
            wordLength = name.size();

            // Format price to display $ and two decimal places
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << myItems.at(name).price;
            price = ss.str();
            priceLength = price.size();

            qty = std::to_string(myItems.at(name).qty);
            qtyLength = qty.size();
            state = EDITITEM;
        }
        else{
            previousState = SEARCH;
            state = FAIL;
        }

    }
    ReturnToMainMenu();

}

// Display Items
void Inventory::DisplayItems(){
    ClearBackground(LIGHTGRAY);

    // Draw the lables onto the screen
    GuiLabel((Rectangle){10, 0, 400, 80}, "Name of Item");
    DrawLine(250, 0, 250, 1000, DARKGRAY);
    GuiLabel((Rectangle){300, 0, 200, 80}, "Price of Item");
    DrawLine(525, 0, 525, 1000, DARKGRAY);
    GuiLabel((Rectangle){600, 0, 200, 80}, "Qty of Item");
    DrawLine(0, 85, 800, 85, DARKGRAY);

    int itemNum = 1;  // Keep track of the number of items
    for(auto const& [key, value] : myItems){

        // Format price to display $ and two decimal places
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << value.price;
        std::string newPrice = "$ " + ss.str();

        // Dispaly the items
        GuiLabel((Rectangle){10,(itemNum * 80), 400, 80}, key.c_str());
        GuiLabel((Rectangle){300,(itemNum * 80), 200, 80}, newPrice.c_str());
        GuiLabel((Rectangle){600,(itemNum * 80), 200, 80}, std::to_string(value.qty).c_str());
        itemNum++;
    }
    // If return to main menu is clicked
    ReturnToMainMenu();
}

// Return to main menu
void Inventory::ReturnToMainMenu(){
    bool homeButton = GuiButton((Rectangle){700, 900, 50, 50}, "#185#");
    if(homeButton){
        ResetValues();
    }
}

// Reset values to default
void Inventory::ResetValues(){

    state = MAINMENU;
    name = "\0";
    price = "\0";
    qty = "\0";
    searchText[0] = '\0';
    wordLength = 0;
    priceLength = 0;
    qtyLength = 0;
    periodIndex = -1;
    periodPresent = false;

}
