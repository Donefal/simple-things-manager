#pragma once

#include <string>

static constexpr int ASCII_INT_MIN = '0';
static constexpr int ASCII_INT_MAX = '9';
static constexpr int MAX_STR_LENGTH = 255;
static const char* DATABASE_FILE_DIR = "database/things_list.db";
enum ThingsType {NOTE, TODOs, EVENT, SHOPPING};

namespace Utils
{
    unsigned int userInput_choice(unsigned int maxValue);
    std::string userInput_str();
    bool userInput_binary();
    std::string userInput_date();

    void log(const std::string& message);
}

namespace Account
{
    bool isLoginSuccessful(std::string username, std::string password);
    bool usernameIsUsed(std::string username);
    int inputNewAccount(std::string name, std::string username, std::string password);
}

namespace Testing
{
    bool insertTestData();
}



 






