/**
* Luis Lopez
* Decleration of funcions and variables used to store the items in a map
**/
#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED
#include <string>
#include <cctype>
#include <map>


/// Struct to contain the item qty and price
struct Items{
    double price;
    int qty;
};

/// Map to save all the items
std::map<std::string, Items> myItems = {};

/// prototype fuctions
bool checkItem(std::string);
std::string toLower(std::string);

/// Add item into the map, return true if sucessfull
bool setItem(std::string name, double price = 0.0, int qty = 0){
    std::string lowerName = toLower(name);
    // Check is name already exist
    bool itemExists = checkItem(name);

    if(itemExists){
        return false;
    }
    else{
        Items item = {price, qty};

        myItems.insert({lowerName, item});
    }
    return true;
}

/// Display all the items
void displayItems(){
    for(auto item: myItems){

    }
}

/// Delete an item from the map
bool deleteItem(std::string name){
    std::string lowerName = toLower(name);

    bool itemValid = checkItem(name);

    if(itemValid){
        myItems.erase(lowerName);
        return true;
    }
    return false;
}

/// Edit an item in the map
bool editItem(std::string name, double price, int qty){
    std::string lowerName = toLower(name);

    // Check that the item exists
    auto itemLocation = myItems.find(lowerName);

    // If exist make changes to item
    if(itemLocation != myItems.end()){
        Items item = {price, qty};
        myItems.at(lowerName) = item;
        return true;
    }
    else{
        // Item not found
    }
    return false;
}

/// Check if item exists in map
bool checkItem(std::string name){
    std::string lowerName = toLower(name);

    return myItems.count(lowerName);
}

/// Convert to string to lower case
std::string toLower(std::string name){
    std::string lowerName = "";
    for(char letter : name){
        lowerName += tolower(letter);
    }
    return lowerName;
}

#endif // ITEM_H_INCLUDEDf
