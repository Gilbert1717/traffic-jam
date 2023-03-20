#include "game.h"
#include "helper.h"
// #include "board.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;



#define NAME "Yiqi Du"
#define ID "s3665887"
#define EMAIL "s3665887@student.rmit.edu.au"


void showStudentInformation(string name, string id, string email);
void displayMainMenu();
string getMenuInput();
void executeMenu(string input);


int main()
{
    std::string input;
    displayMainMenu();
    do{
        input = getMenuInput(); 
        executeMenu(input);
    }
    while(input != "3");
    
    
    return EXIT_SUCCESS;
}

void showStudentInformation(string name, string id, string email){
    std::cout << std::endl;
    std::cout << "Name: " <<name << std::endl;
    std::cout << "No: " << id << std::endl;
    std::cout << "Email: " << email << std::endl;
}

void displayMainMenu() {
    std::string option1 = "1. Play game";
    std::string option2 = "2. Show student's information";
    std::string option3 = "3. Quit";
    std::cout << "Welcome to Car Board" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << option1 << std::endl;
    std::cout << option2 << std::endl;
    std::cout << option3 << std::endl;
    std::cout << std::endl;
    std::cout << "Please enter your choice: ";
}


string getMenuInput(){
    std::string input; 
    std::getline(std::cin >> std::ws, input);
    while(input != "1" && input != "2" && input != "3") {
        std::cout << std::endl;
        Helper::printInvalidInput();
        displayMainMenu();
        std::getline(std::cin >> std::ws, input);
    };
    return input;
}



void executeMenu(string input){
    if (input == "1") {
        Game* gameptr = new Game();
        gameptr->start();
        delete gameptr;
        gameptr = nullptr;
    }

    else if (input == "2") {
        showStudentInformation(NAME,ID,EMAIL);
    }

    else if (input == "3") {
        std::cout << std::endl;
        std::cout << "Good bye!\n\n";
    }
}

