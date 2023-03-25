#include "game.h"
#include "helper.h"
#include <string>
#include <iostream>

using std::string;
using std::vector;



#define NAME "Yiqi Du"
#define ID "s3665887"
#define EMAIL "s3665887@student.rmit.edu.au"
#define menuOption1 "1. Play game"
#define menuOption2 "2. Show student's information"
#define menuOption3 "3. Quit"


void showStudentInformation(string name, string id, string email);
void displayMainMenu();
string getMenuInput();
void executeMenu(string input);

/**    
     * Implemetation of random board generation:
     * Base on the input size and percentage, the program will frist generate a empty gaming borad with size*size and then
     * calculate the how many block cells is needed on the board. Then, the program will randomly generation 2 numbers
     * within the range from 0 to the input size which represent the coordinate of X and Y. Then the program will check
     * the cell located on (X,Y). If it is a block cell, the system will regenerate a coordinate, otherwise it will assign
     * that cell to a block cell.
     * 
     * Implemetation of menu functions:
     * the uses input is validated using do while loop. The program will take an input frist and validate it.
     * If the input is not an expected command, it will trigger the while condition and keep looping through untill
     * get the right input command.  
     * 
     * Implemetation of play game:
     * The program will take the use's input and validate it using combination of regex and string comparsion. 
     * When the player wants to move forward, base on the player's current position and direction, the 
     * program will check if the next position is a valid cell to place the player. If the cell is valid, 
     * the program will move player to that position and add 1 move to the player.
     * 
     * Issue encountered:
     * When receiving the user input, the 'std::cin' function will split the input string into multiple inputs based on the 
     * whitespace.The 'readinput' function in helper class does not work properly as well. Base on some research, I found 
     * another readline function which reads the user input from console with whitespaces.
     * 
     * Potential improvement:
     * The 'Player' class can be removed and replayed by a coordinate in the 'Board' class, by doing so the 'direction' 
     * and 'moves' attributes can be added to the 'board' class. This way, the methods in the 'board' class can use player 
     * directly instead of taking the player object as a parameter. This will help to reduce the code complexity of this 
     * program.
     */
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
    std::cout << "Welcome to Car Board" << std::endl;
    std::cout << "--------------------" << std::endl;
    std::cout << menuOption1 << std::endl;
    std::cout << menuOption2 << std::endl;
    std::cout << menuOption3 << std::endl;
}


string getMenuInput(){
    std::string input; 
    std::cout << std::endl;
    std::cout << "Please enter your choice: ";
    std::getline(std::cin >> std::ws, input);
    while(input != "1" && input != "2" && input != "3") {
        std::cout << std::endl;
        Helper::printInvalidInput();
        displayMainMenu();
        std::cin >> input;
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

