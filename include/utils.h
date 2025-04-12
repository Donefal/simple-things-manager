#pragma once

#include <string>
#include <vector>

static constexpr int ASCII_INT_MIN = '0';
static constexpr int ASCII_INT_MAX = '9';
static constexpr int MAX_STR_LENGTH = 255;
static constexpr int MAX_INT_VALUE = 1000000000;
static const char* DATABASE_FILE_DIR = "database/things_list.db";
enum ThingsType {NOTE, TODOs, EVENT, SHOPPING};

struct ThingsID
{
    std::vector<int> created;
    std::vector<int> assigned;
};

namespace Utils
{
    unsigned int userInput_choice(unsigned int maxValue);
    std::string userInput_str();
    bool userInput_binary();
    std::string userInput_date();
    unsigned int userInput_list(ThingsID ids);

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



 






