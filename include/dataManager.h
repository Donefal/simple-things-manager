#pragma once

#include <string>
#include <array>
#include "utils.h"

class DataManager
{
    private:
        const char* DATABASE_FILE_DIR = "database/things_list.db";
        int user_id;
        std::string date;
    public:
        DataManager(std::string username, std::string date);
        ~DataManager();

        // Pull data
        int pullThings_created();
        int pullThings_assigned();

        // Input Function
        int inputToDatabase_event(int id, std::string eventDate = "");
        int inputToDatabase_todo(int id, std::string deadline = "");
        int inputToDatabase_shopping(int id, int quantity, int price);
        int inputToDatabase_base(std::string text = "Edit this", std::string type = "Note");

        // Change data value
        void changeDate(std::string date);
};

