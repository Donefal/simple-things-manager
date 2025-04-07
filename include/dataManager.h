#pragma once

#include <string>
#include <array>
#include <sqlite3.h>

#include "utils.h"


class DataManager
{
    private:
        const char* DATABASE_FILE_DIR = "database/things_list.db";
        int user_id = -1;
        std::string date;
    public:
        DataManager(std::string username, std::string date);
        ~DataManager();

        // Pull data
        int pullThings_created();
        int pullThings_assigned();

        // Input Function
        int inputToDatabase_eventData(int id, std::string eventDate);
        int inputToDatabase_todoData(int id, std::string deadline);
        int inputToDatabase_shoppingData(int id, int quantity, int price);

        // Return newly created things_id
        sqlite3_int64 inputToDatabase_base(std::string text, std::string type);

        // Change data value
        void changeDate(std::string date);
};

