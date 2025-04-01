#pragma once

#include <string>
#include <array>

class dataManager
{
    private:
        const char* DATABASE_FILE_DIR = "database/things_list.db";
        std::string username;
        std::string date;
    public:
        dataManager(std::string username);
        ~dataManager();

        // Pull data
        int callbackDisplay_event(void* unused, int columnCount, char** data, char** columnName);
        int callbackDisplay_todo(void* unused, int columnCount, char** data, char** columnName);
        int callbackDisplay_shopping(void* unused, int columnCount, char** data, char** columnName);
        int callbackDisplay_base(void* unused, int columnCount, char** data, char** columnName);
        int pullThings_created();
        int pullThings_assigned();

        // Input Function
        int inputToDatabase_event(int id, std::string eventDate = "");
        int inputToDatabase_todo(int id, std::string deadline = "");
        int inputToDatabase_shopping(int id, int quantity, int price);
        int inputToDatabase_base(std::string text = "Edit this", std::string type = "Note");
};

