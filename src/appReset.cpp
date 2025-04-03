/*
    TODO: Add a way to reset the database (maybe using filesystem to delete it)
*/


#include "appReset.h"

#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <fstream>
#include "utils.h"

AppReset::AppReset()
{
    Utils::log("INFO: App Reset Started");
}

AppReset::~AppReset()
{
    Utils::log("INFO: App Reset Destroyed\n ---");
}

int AppReset::startApplication()
{
    sqlite3 *db;
    int returnCode = sqlite3_open(DATABASE_FILE_DIR, &db);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to open database");
        return 1;
    }

    std::ifstream sqlFile("database/starter_template.sql");
    std::stringstream currentQuery;
    std::string currentLine = "";

    if (!sqlFile.is_open())
    {
        Utils::log("ERROR: Can't open SQL starter template");
    }

    while (true)
    {
        std::getline(sqlFile, currentLine, '\n');
        
        if (currentLine == "-- END")
        {
            Utils::log("INFO: Reading starter template completed");
            break;
        } else if (currentLine[0] == '-') { // Ignore comment
            continue;
        }

        currentQuery << currentLine << " ";

        // Execute current query
        char lastChar = currentLine[currentLine.length() - 1];
        if (lastChar == ';') {

            char *errMsg;
            returnCode = sqlite3_exec(db, currentQuery.str().c_str(), nullptr, nullptr, &errMsg);

            if (returnCode != SQLITE_OK)
            {
                Utils::log("ERROR: Query execution failed: " + (std::string)errMsg);
                sqlite3_close(db);
                return 1;
            } else {
                currentQuery.str(""); // Clear stringstream
            }
        }
    }
    
    sqlite3_close(db);
    Utils::log("INFO: App Reset Completed");
    return 0;
}
