#pragma once

#include <string>
#include <array>
#include <sqlite3.h>
#include <vector>

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
        std::vector<int> pullThings_created();
        std::vector<int> pullThings_assigned();

        // Input Function
        int inputToDatabase_eventData(int id, std::string eventDate);
        int inputToDatabase_todoData(int id, std::string deadline);
        int inputToDatabase_shoppingData(int id, int quantity, int price);

        // Return newly created things_id
        sqlite3_int64 inputToDatabase_base(std::string text, std::string type);

        // Change data value
        void changeDate(std::string date);

        // Do somethings feature
        int changeThings_type(int id, ThingsType newType);
        int changeThings_shopping(int id, int newData[2]);
        int changeThings_TodoEventdate(int id, std::string newDate);
        int changeThings_status(int id, std::string newStatus);
        int changeThings_text(int id, std::string newText);

};

