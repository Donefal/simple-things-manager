#include "DataManager.h"

#include <iostream>
#include <sqlite3.h>
#include <string>
#include "utils.h"
#include <vector>

/*
    TODO: Better Callback
    I think for the callback, I need to create a vector or linked list
    to store additional attribute that the different type of things have
    And it need to be done at the start of the base callback, so the box can be checked 
    or whatsoever. 

    I can also make a row struct for this

*/ 

DataManager::DataManager(std::string username, std::string date)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char *errMsg;
    int returnCode;  

    const char* query = "SELECT user_id FROM user_tb WHERE username = ?";

    returnCode = sqlite3_open(DATABASE_FILE_DIR, &db);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to open database");
    }
    
    returnCode = sqlite3_prepare_v3(db, query, -1, 0, &stmt, nullptr);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to prepare statement: " + (std::string)sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    returnCode = sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to bind data to statement" + (std::string)sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    returnCode = sqlite3_step(stmt);
    if (returnCode == SQLITE_ROW)
    {
        const char* user_id = (const char*)sqlite3_column_text(stmt, 0);
        this->user_id = std::stoi(user_id);
        this->date = date;
        returnCode = 0;
    }  else {
        returnCode = 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    
    if (returnCode)
    {
        Utils::log("INFO: Data Manager constructed with failure");
    } else {
        Utils::log("INFO: Data Manager constructed successfully");
    }
    
    
}

DataManager::~DataManager()
{
    Utils::log("INFO: Data Manager destructed");
}

int additionalCallback(void* head, int columnCount, char** data, char** columnName)
{
    std::string* results = static_cast<std::string*>(head);
    
    for (int i = 0; i < columnCount; i++)
    {
        results[i] = data[i] ? data[i] : "NULL";
    }

    return 0;
}

int callbackDisplay(void* unused, int columnCount, char** data, char** columnName)
{
    enum ThingsType type;
    std::string type_str = (std::string)data[0];
    sqlite3* db;
    char* errMsg;
    int returnCode;
    

    // Database for additional information
    returnCode = sqlite3_open(DATABASE_FILE_DIR, &db);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Can't open database");
        return 1;
    }

    // Setting up type enum & the bullet
    Utils::log("LOG: " + (std::string)data[0] + " banding NOTE");
    if (type_str == "NOTE") {
        type = NOTE;
    } else if (type_str == "TODO") {
        type = TODOs;
    } else if (type_str == "EVENT") {
        type = EVENT;
    } else if (type_str == "SHOPPING") {
        type = SHOPPING;
    } else {
        Utils::log("ERROR: " + (std::string)data[0] + " is not a valid type");
        return 1;
    }

    // Pulling additional data & displaying
    switch (type)
    {
        case NOTE:
            std::cout << "-o- " << data[1] << std::endl;
            break;
        case TODOs:
        {
            std::string additional[2];
            std::string query = 
                "SELECT status, deadline FROM todo_data_tb " 
                "WHERE things_id = '" + (std::string)data[2] + "';";

            returnCode = sqlite3_exec(db, query.c_str(), additionalCallback, additional, &errMsg);
            if (returnCode != SQLITE_OK)
            {
                Utils::log("ERROR: Query execution failed: " + (std::string)errMsg);
                sqlite3_close(db);
                return 1;
            }

            if (additional[0] == "Listed") {
                std::cout << "[ ] ";
            } else if (additional[0] == "Done") {
                std::cout << "[v] ";
            } else if (additional[0] == "Canceled") {
                std::cout << "[x] ";
            }

            std::cout << data[1] << " <Dl: " << additional[1] << ">" << std::endl;
            break;
        }
        case EVENT:
        {
            std::string additional[1];
            std::string query =
                "SELECT date_of_event FROM event_data_tb "
                "WHERE things_id = '" + (std::string)data[2] + "';";

            returnCode = sqlite3_exec(db, query.c_str(), additionalCallback, additional, &errMsg);
            if (returnCode != SQLITE_OK)
            {
                Utils::log("ERROR: Query execution failed: " + (std::string)errMsg);
                sqlite3_close(db);
                return 1;
            }

            std::cout << "--> " << data[1] << " <on " << additional[0] << ">" << std::endl;
            break;
        }
        case SHOPPING:
        {
            std::string additional[3];
            std::string query =
                "SELECT status, quantity, price_per_pcs FROM shopping_data_tb "
                "WHERE things_id = '" + (std::string)data[2] + "';";

            returnCode = sqlite3_exec(db, query.c_str(), additionalCallback, additional, &errMsg);
            if (returnCode != SQLITE_OK)
            {
                Utils::log("ERROR: Query execution failed: " + (std::string)errMsg);
                sqlite3_close(db);
                return 1;
            }

            if (additional[0] == "Listed") {
                std::cout << "( ) ";
            } else if (additional[0] == "Done") {
                std::cout << "(v) ";
            } else if (additional[0] == "Canceled") {
                std::cout << "(x) ";
            }

            float price = std::stoi(additional[2])/100;
            std::cout << data[1] << " <Qty: " << additional[1] << "| Rp. " << price << "/pcs>" << std::endl;
            break;
        }
        default:
            break;

    }

    return 0;
}

int DataManager::pullThings_created()
{
    sqlite3 *db;
    char *errMsg;
    int returnCode;


    // TODO: Maybe implement joint in this query
    std::string query = 
        "SELECT type, things_text, things_id " 
        "FROM things_tb WHERE user_id = '" + std::to_string(user_id) + "' AND date_created = '" + date +  "';";
    
    returnCode = sqlite3_open(DATABASE_FILE_DIR, &db);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Can't open database");
        return 1;
    }

    returnCode = sqlite3_exec(db, query.c_str(), callbackDisplay, nullptr, &errMsg);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Query execution failed: " + (std::string)errMsg);
        sqlite3_close(db);
        return 1;
    }
    
    return 0;
}   

