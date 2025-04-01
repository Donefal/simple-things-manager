#include "utils.h"

#include <iostream>
#include <iomanip>      // For put_time
#include <array>
#include <string>
#include <fstream>
#include <ctime>
#include <sqlite3.h>
#include "bcrypt.h"

std::ofstream logFile("docs/log.txt");

unsigned int Utils::userInput_choice(unsigned int maxValue)
{
    std::string input_str;
    unsigned int input_int;

    while (true)
    {
        std::cout << "--Input Choice: ";
        std::getline(std::cin, input_str, '\n');

        bool interrupt = false;
        for(const char c : input_str)
        {
            int c_int = static_cast<int>(c);
            if (c_int < ASCII_INT_MIN && c_int > ASCII_INT_MAX)
            {
                interrupt = true;
                break;
            }
        }
        
        if (interrupt)
        {
            std::cout << "Input is not entirely a number!" << std::endl;
            continue;
        } 
    
        input_int = std::stoi(input_str);
        if (input_int > maxValue || input_int < 1)
        {
            std::cout << "Input is exceeding the max value!" << std::endl;
            continue;
        }

        break;
    }
    
    return input_int;
}

std::string Utils::userInput_str()
{
    std::string input;

    while (true)
    {
        std::getline(std::cin, input, '\n');

        if (input.length() > MAX_STR_LENGTH)
        {
            std::cout << "Input is too long!" << std::endl;
            continue;
        }

        break;
    }

    return input;
}


void Utils::log(const std::string& message)
{
    if (logFile.is_open())
    {
        std::time_t now = std::time(nullptr);
        std::tm tm = *std::localtime(&now);

        logFile << std::put_time(&tm, "[%Y-%m-%d %H:%M:%S] ") << message << std::endl;
    }    
}

// Find account in user_tb. Return password if found, "NULL" if not
std::string Account::findAccount(std::string username)
{
    std::string returnString = "NULL";
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int returnCode;

    const char* query = "SELECT password FROM user_tb WHERE username = ?";

    // 1. Open Database
    returnCode = sqlite3_open(DATABASE_FILE_DIR, &db);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to open database");
        return "NULL";
    }

    // 2. Prepare Query
    returnCode = sqlite3_prepare_v3(db, query, -1, 0, &stmt, nullptr);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to prepare query: " + (std::string)sqlite3_errmsg(db));
        sqlite3_close(db);
        return "NULL";
    }
    
    // 3. Bind the statement with the username text
    returnCode = sqlite3_bind_text(stmt, 1, username.c_str(), username.length(), SQLITE_STATIC);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to bind query: " + (std::string)sqlite3_errmsg(db));
        sqlite3_close(db);
        return "NULL";
    }

    // 4. Execute the statement on database & validate password
    returnCode = sqlite3_step(stmt);
    if (returnCode == SQLITE_ROW)
    {
        const char* storedPassword = (const char*)sqlite3_column_text(stmt, 0);
        returnString = storedPassword;
    } 
    
    // 5. Free resources to avoid memory leak
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    Utils::log("INFO: username '" + username + "' is " + ((returnString != "NULL")? ("found") : ("not found")));
    return returnString;
}


bool Account::isLoginSuccessful(std::string username, std::string password)
{
    std::string passwordToCheck = Account::findAccount(username);
    if ((passwordToCheck != "NULL") && (Bcrypt::validatePassword(password, passwordToCheck)))
    {
        return true;
    }

    return false;
}

bool Account::usernameIsUsed(std::string username)
{   
    return Account::findAccount(username) != "NULL";
}

int Account::inputNewAccount(std::string name, std::string username, std::string password)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int returnCode;

    std::array<std::string, 3> bindValue = {name, username, Bcrypt::generateHash(password)};
    const char* query = "INSERT INTO user_tb (name, username, password) VALUES (?, ?, ?);";

    /*
        NOTE: SQLite3 Full Flow
        1. Open database
        2. Prepare statement
        3. Bind value
        4. Evaluate & execute
        5. Destruct
    */

    // 1. Open Database
    returnCode = sqlite3_open(DATABASE_FILE_DIR, &db);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Can't open database");
        return 1;
    }

    // 2. Prepare statement
    returnCode = sqlite3_prepare_v3(db, query, -1, 0, &stmt, nullptr);
    if (returnCode != SQLITE_OK)
    {
        Utils::log("ERROR: Failed to prepare query: " + (std::string)sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // 3. Bind value
    for (int i = 0; i < 3; i++)
    {
        returnCode = sqlite3_bind_text(stmt, (i + 1), bindValue[i].c_str(), bindValue[i].length(), SQLITE_STATIC);

        if (returnCode != SQLITE_OK)
        {
            Utils::log("ERROR: Failed to bind query: " + (std::string)sqlite3_errmsg(db));
            sqlite3_close(db);
            return 1;
        }
    }

    // 4. Evaluate & execute
    returnCode = sqlite3_step(stmt);

    // 5. Destruct
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    Utils::log("INFO: New account created successfully");
    return 0;
}