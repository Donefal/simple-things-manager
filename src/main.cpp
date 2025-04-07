#include <iostream>     // Basic input/output 
#include <string>       // For string functions 
#include <conio.h>      // For console control
#include <stdlib.h>     // For clear screen
#include <sqlite3.h>    // Access to self contained databases 
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>

#include "utils.h"
#include "appReset.h"
#include "DataManager.h"

int beginAppReset()
{
    AppReset ar;
    if (ar.startApplication() != SQLITE_OK)
    {
        return 1;
    }

    return 0;
}

// -----------------------------------------------------------------------------------------------------------------------

std::string jumpToOtherDay()
{
    system("cls");
    std::cout << "Jump to other day" << std::endl;
    std::cout << "(Quick action: 'T' for tomorrow || 'Y' yesterday)" << std::endl;
    std::cout << "Input date (YYYY-MM-DD):";
    
    return Utils::userInput_date();
}

void createNewThing(DataManager dm)
{
    ThingsType selectedType;
    std::string text;
    sqlite3_int64 newId;

    system("cls");
    std::cout << "Select type:" << std::endl;
    std::cout << "(1) Note" << std::endl;
    std::cout << "(2) Todo" << std::endl;
    std::cout << "(3) Event" << std::endl;
    std::cout << "(4) Shopping" << std::endl;

    switch (Utils::userInput_choice(4))
    {
        case 1:
            selectedType = NOTE;
            break;
        case 2:
            selectedType = TODOs;
            break;
        case 3:
            selectedType = EVENT;
            break;
        case 4:
            selectedType = SHOPPING;
            break;
        default:
            break;
    }

    system("cls");
    std::cout << "Input text:" << std::endl;
    text = Utils::userInput_str();

    system("cls");
    switch (selectedType)
    {
        case NOTE:
            dm.inputToDatabase_base(text, "NOTE");
            break;
        case TODOs:
        {
            std::string deadline;

            std::cout << "(input '-' if none) (format: YYYY-MM-DD)" << std::endl;
            std::cout << "Input deadline : " << std::endl;
            deadline = Utils::userInput_date();

            newId = dm.inputToDatabase_base(text, "TODO");

            if (dm.inputToDatabase_todoData(newId, deadline) == 0)
            {
                Utils::log("INFO: New todo input succeed");
            } else {
                Utils::log("ERROR: New todo input failed");
            }
            
            break;
        }
        case EVENT:
        {
            std::string dateOfEvent;

            std::cout << "(input '-' if none) (format: YYYY-MM-DD)" << std::endl;
            std::cout << "Input date of event : " << std::endl;
            dateOfEvent = Utils::userInput_date();

            newId = dm.inputToDatabase_base(text, "EVENT");

            if (dm.inputToDatabase_eventData(newId, dateOfEvent) == 0)
            {
                Utils::log("INFO: New event input succeed");
            } else {
                Utils::log("ERROR: New event input failed");
            }
            
            break;
        }
        case SHOPPING:
        {
            int qty, price;

            std::cout << "How many? : " << std::endl;
            qty = Utils::userInput_choice(MAX_INT_VALUE);
            std::cout << "How much per pcs? : " << std::endl;
            price = Utils::userInput_choice(MAX_INT_VALUE);

            newId = dm.inputToDatabase_base(text, "SHOPPING");

            if (dm.inputToDatabase_shoppingData(newId, qty, price) == 0)
            {
                Utils::log("INFO: New shopping input succeed");
            } else {
                Utils::log("ERROR: New shopping input failed");
            }

            break;
        }
        default:
            break;
    }
    
}

void displayThings(DataManager dm)
{
    std::cout << "CREATED ON THIS DAY:" << std::endl;
    dm.pullThings_created();
    
    std::cout << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "ASSIGNED FOR THIS DAY:" << std::endl;
    dm.pullThings_assigned();
}

void mainMenu(std::string username, std::string currentDate)
{
    std::string date = currentDate;
    DataManager dm(username, date);
    bool menuShouldClose = false;

    while (!menuShouldClose)
    {
        system("cls");
        std::cout << "Things List | Today, " << date << std::endl;
        std::cout << std::endl;
    
        displayThings(dm);
    
        std::cout << std::endl;
        std::cout << "---" << std::endl;
        std::cout   << "Select Action" << std::endl
                    << "(1) Do someThings" << std::endl
                    << "(2) New Things" << std::endl
                    << "(3) Jump to other day" << std::endl
                    << "(4) See All Things" << std::endl
                    << "(5) Log Out" << std::endl;
        std::cout << "---" << std::endl;

        switch (Utils::userInput_choice(5))
        {
            case 1:
                std::cout << "Do someThings" << std::endl;
                break;
            case 2:
                createNewThing(dm);
                break;
            case 3:
            {
                std::string newdate = jumpToOtherDay();
                dm.changeDate(newdate);
                date = newdate;
                break;
            }
            case 4:
                std::cout << "See All Things" << std::endl;
                break;
            case 5:
                menuShouldClose = true;
                break;
            default:
                break;
        }
    
        std::cout << "Press anything to continue" << std::endl;
        getch();
        
    }
}

// -----------------------------------------------------------------------------------------------------------------------

void login()
{
    bool loginShouldStop = false;
    std::string usernameInput;
    std::string passwordInput;

    while (!loginShouldStop)
    {
        std::cout << "Login" << std::endl;
        std::cout << "---" << std::endl;
        std::cout << "Username : ";
        usernameInput = Utils::userInput_str();
        std::cout << "Password : ";
        passwordInput = Utils::userInput_str();
    
        if (Account::isLoginSuccessful(usernameInput, passwordInput))
        {
            std::stringstream currentDate;
            std::time_t now = std::time(nullptr);
            std::tm tm = *std::localtime(&now);
    
            currentDate << std::put_time(&tm, "%Y-%m-%d") ;

            std::cout << ">> Login Succesfully!" << std::endl;
            std::cout << "Press anything to continue" << std::endl;
            getch();
            mainMenu(usernameInput, currentDate.str());

        } else {
            std::cout << ">> Username or password is not valid!" << std::endl;
            std::cout << "Do you want to try again (y/n): ";
            
            bool wantToContinue = Utils::userInput_binary();

            if (wantToContinue) {
                continue;
            } else {
                loginShouldStop = true;
            }
        }
    }
}

void createAccount()
{
    std::string nameInput ;
    std::string usernameInput;
    std::string passwordInput;
    std::string passwordReEnter;
    int returnCode;

    while (true)
    {
        std::cout << "Create new Account" << std::endl;
        std::cout << "---" << std::endl;
        std::cout << "Name : ";
        nameInput = Utils::userInput_str();
        std::cout << "Username : ";
        usernameInput = Utils::userInput_str();
        std::cout << "Password : ";
        passwordInput = Utils::userInput_str();
        std::cout << "Re-enter Password : ";
        passwordReEnter = Utils::userInput_str();

        if (passwordInput != passwordReEnter)
        {
            std::cout << ">> Password input is not matching!" << std::endl;
            std::cout << ">> Press anything to try again" << std::endl;
            getch();
            system("cls");
            continue;
        } else if (Account::usernameIsUsed(usernameInput)) {
            std::cout << ">> Username is already used!"  << std::endl;
            std::cout << ">> Press anything to try again" << std::endl;
            getch();
            system("cls");
            continue;
        }

        returnCode = Account::inputNewAccount(nameInput, usernameInput, passwordInput);
        std::cout << ">> Account created!" << std::endl;
        getch();
        break;
    }
}

// -----------------------------------------------------------------------------------------------------------------------

void masterAction()
{
    std::cout << "PLEASE SELECT WITH CAUTION!" << std::endl;
    std::cout << "PLEASE SELECT WITH CAUTION!" << std::endl;
    std::cout << "PLEASE SELECT WITH CAUTION!" << std::endl;
    std::cout << "---" << std::endl << std::endl;

    std::cout << "Select Action:" << std::endl;
    std::cout << "(1) App Reset" << std::endl;
    std::cout << "(2) Insert Test Data" << std::endl;
    std::cout << "(3) Cancel Action" << std::endl;
    

    switch (Utils::userInput_choice(2))
    {
        case 1:
            system("cls");
            if (beginAppReset())
            {
                std::cout << "Error" << std::endl;
            } else {
                std::cout << "App reset succeeded" << std::endl;
            }
            break;
        case 2:
            system("cls");
            if (Testing::insertTestData())
            {
                std::cout << "Test data insertion failed" << std::endl;
            } else {
                std::cout << "Test data insertaion succeed" << std::endl;
            }

            getch();
            system("cls");
            break;
        case 3:
            return;
        default:
            break;
    }
}


int main()
{
    bool appShouldStop = false;

    while (!appShouldStop)
    {
        std::cout << "Welcome to things list" << std::endl;
        std::cout << "What would you like to do?" << std::endl;
        std::cout << "(1) Login" << std::endl;
        std::cout << "(2) Create new account" << std::endl;
        std::cout << "(3) Master Action" << std::endl;
        std::cout << "(4) Exit Application" << std::endl;


        switch (Utils::userInput_choice(3))
        {
            case 1:
                system("cls");
                login();
                break;
            case 2:
                system("cls");  
                createAccount();
                break;
            case 3:
                system("cls");
                masterAction();
                break;
            case 4:
                system("cls");
                appShouldStop = true;
            default:
                break;
        }
    }
    
    std::cout << "Application ended.";
    getch();
    return 0;
}