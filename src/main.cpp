#include <iostream>     // Basic input/output 
#include <string>       // For string functions 
#include <conio.h>      // For console control
#include <stdlib.h>     // For clear screen
#include <sqlite3.h>    // Access to self contained databases 

#include "utils.h"
#include "appReset.h"

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

/* 
    TODO: Try to finish this function
    - Read data from database
    - Don't forget to enable foreign key
    - From the type, then read into their respective table 

    IDEA: Symbol for each type 
    -o- For notes
    --> For event <Date: >
    [ ] For todo <Dl: >
    ( ) For shopping <Q: nn | Rp. nnnn,nn/pcs >

    Split it to two part:
    
        Things List | date
        ---
        >> CREATED THIS DAY:
        -o- Lorem ipsum
        --> Example event

        ---
        >> ASSIGNED FOR THIS DAY:
        [ ] Example todo 
        ( ) Example shopping 

        ---
        Select Action
*/

void displayThings(std::string username, std::string date)
{
    
}

void mainMenu(std::string username)
{
    std::string date;

    std::cout << "Things List | Today, date" << std::endl;
    std::cout << "---" << std::endl;

    displayThings(username, date);

    std::cout << "---" << std::endl;
    std::cout   << "Select Action" << std::endl
                << "(1) New Things" << std::endl
                << "(2) Jump to other day" << std::endl
                << "(3) See All Things" << std::endl
                << "(4) Log Out" << std::endl;
    std::cout << "---" << std::endl;

}

// -----------------------------------------------------------------------------------------------------------------------
void login()
{
    std::string usernameInput;
    std::string passwordInput;

    while (true)
    {
        std::cout << "Login" << std::endl;
        std::cout << "---" << std::endl;
        std::cout << "Username : ";
        usernameInput = Utils::userInput_str();
        std::cout << "Password : ";
        passwordInput = Utils::userInput_str();
    
        if (Account::isLoginSuccessful(usernameInput, passwordInput))
        {
            std::cout << ">> Login Succesfully!" << std::endl;
            mainMenu(usernameInput);
        } else {
            std::cout << ">> Username or password is not valid!" << std::endl;
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




int main()
{
    std::cout << "| Wellcome to things list |" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "(1) Login" << std::endl;
    std::cout << "(2) Create new account" << std::endl;
    std::cout << "(3) Reset Application" << std::endl;
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
            if (beginAppReset())
            {
                std::cout << "FATAL ERROR: Exiting Program..." << std::endl;
            } else {
                std::cout << "App reset succeeded" << std::endl;
            }
            break;
        default:
            break;
    }
    
    std::cout << "Application ended.";
    getch();
    return 0;
}