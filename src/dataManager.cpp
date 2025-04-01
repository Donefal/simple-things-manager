#include "dataManager.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include "utils.h"


/*
    TODO: Better Callback
    I think for the callback, I need to create a vector or linked list
    to store additional attribute that the different type of things have
    And it need to be done at the start of the base callback, so the box can be checked 
    or whatsoever. 

    I can also make a row struct for this

*/ 
int callbackDisplay_base(void* unused, int columnCount, char** data, char** columnName)
{
    enum TYPE {NOTE, TODOs, EVENT, SHOPPING};
    enum TYPE type;

    // Setting up type enum & the bullet
    if (data[0] == "NOTE")
    {
        std::cout << "-o- ";
        type = NOTE;
    } else if (data[0] == "TODO") {
        std::cout << "[ ] ";
        type = TODOs;
    } else if (data[0] == "EVENT") {
        std::cout << ">>> ";
        type = EVENT;
    } else if (data[0] == "SHOPPING") {
        std::cout << "( ) ";
        type = SHOPPING;
    } else {
        Utils::log("ERROR: " + (std::string)data[0] + " is not a valid type");
        return 1;
    }
    
    // Print out things_text
    std::cout << data[1];

    // Print out additional attribute
    sqlite3 *db;
    char *errMsg;
    int returnCode;

    switch (type)
    {
        case NOTE: 
            break;
        case TODOs:
            
            break;
        case EVENT:
            break;
        case SHOPPING:
            break;
        default:
            break;
    }
    
}

int dataManager::pullThings_created()
{
    sqlite3 *db;
    char *errMsg;
    int returnCode;


    // TODO: Maybe implement joint in this query
    std::string query = 
        "SELECT type, things_text, user_id" 
        "FROM things_tb WHERE username = '" + username + "' && date_created = '" + date +  "';";
    
    returnCode = sqlite3_open(DATABASE_FILE_DIR, &db);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Can't open database");
        return 1;
    }

    returnCode = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
    
}   

