/**
 * Title:   Lab 3 - Menu class Implementation: extracredit.cpp
 *
 * Purpose: Extracredit.cpp implements the classes Menu and Menu_Element to construct a menu program for creating, manipulating, and analyzing
 * a dynamically allocated array of double elements.
 * Class:   CSC 2430 Winter 2022
 * Author:  Karena Qian
 */
#include <iostream>
#include <iomanip>
#include "menu.h"

using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::fixed;
using std::setprecision;

//Note: I don't know how to solve the 2 Clang-Tidy warnings I kept getting, so I just left them in.

int main(){
    cout << fixed << setprecision(6); //set decimal precision

    int userInput; //for the user
    double* array = nullptr; //the array
    int size; //size of array
    int numFilled = 0; //number of slots filled

    //create the array menu
    Menu arrayMenu(7);
    arrayMenu.SetTitle("Working with Arrays");
    arrayMenu.SetInputType(INT);
    arrayMenu.SetErrorMessage("- - > Unrecognized Input < - -");
    arrayMenu.SetInvalidOption("- - > Please Input One of the Given Choices < - -");
    arrayMenu.AddMenuOption(0, "1", "Set Size of the Array");
    arrayMenu.AddSeparator(1);
    arrayMenu.AddMenuOption(2, "2", "Add Number to the Array");
    arrayMenu.AddMenuOption(3, "3", "List the Numbers");
    arrayMenu.AddMenuOption(4, "4", "Remove a Number");
    arrayMenu.AddSeparator(5);
    arrayMenu.AddMenuOption(6, "5", "Calculate Average");


    //The Main Program
    while ((userInput = arrayMenu.Run()) != EXIT){
        switch (userInput) {
            //Error for incorrect integer from user input
            case INVALID_INPUT:
                break;
            //Error for incorrect type of input from user
            case INPUT_ERROR:
                break;
            //Option 1: Creates a dynamic array of the size that the user inputs (frees the array if it was already created!)
            case 0:
                //if array is already created, delete the old array and reset num of filled slots to 0
                if(array != nullptr){
                    cout << "The created array will be lost" << endl;
                    delete[] array;
                    numFilled = 0;
                }
                //create new dynamically allocated array with user input size
                cout << "Please input the maximum capacity of the array: ";
                cin >> size;
                array = new double[size];
                cout << "Array Created Successfully" << endl << endl;
                break;
            //the separator index
            case 1:
                cout << "Should not happen!" << endl;
                break;
            //Option 2: Reads a number from the user and adds it to the end of the array... if it fits, if it doesn't signals the error
            case 2:
                //sends message if array is not set
                if(array == nullptr){
                    cout << "Need to create array first!" << endl << endl;
                }
                else{
                    cout << "Adding Number to Array" << endl;
                    //sends message if array is full
                    if(numFilled == size){
                        cout << "The array is full" << endl;
                    }
                    //adds user input to the next available slot in the array
                    else {
                        double num;
                        cout << "Please input the number you want to add: ";
                        cin >> num;
                        array[numFilled] = num;
                        cout << "Number " << num << " Added to Position " << numFilled << " Successfully" << endl << endl;
                        numFilled++;
                    }
                }
                break;
            //Option 3: Shows all the numbers very nicely formatted in the screen
            case 3:
                //sends message if array is not set
                if(array == nullptr){
                    cout << "Need to create array first!" << endl << endl;
                }
                //prints a list of tne numbers in the array in a specific way
                else{
                    cout << "Listing Numbers" << endl;
                    for(int i = 0; i < numFilled; i++){
                        cout << setw(4)  << i << setw(10) << array[i] << endl;
                    }
                    cout << endl << endl;
                }
                break;
            //Option 4: Given the position of the number it removes it from the array, it pushes the numbers if it is not the last
            case 4:
                //sends message if array is not set
                if(array == nullptr){
                    cout << "Need to create array first!" << endl << endl;
                }
                else {
                    int index;
                    cout << "Remove a Number" << endl;
                    //prints message if array has no numbers
                    if(numFilled == 0){
                        cout << "No available elements for removal" << endl;
                    }
                    else {
                        //displays formatted list of numbers in the array
                        for (int i = 0; i < numFilled; i++) {
                            cout << setw(4) << i << setw(10) << array[i] << endl;
                        }
                        //get user input for number index
                        cout << "What is the position where you want to remove a number: ";
                        cin >> index;
                        //removes number at user index from array and pushes the numbers after it to the left
                        if (index < size && index > -1) {
                            numFilled--; //reduce number of filled slots by 1
                            for (int i = index; i < numFilled; i++) {
                                array[i] = array[i + 1];
                            }
                            array[numFilled] = 0.0;
                            cout << "Number in Position " << index << " Removed Successfully" << endl << endl;
                        }
                            //prints message if user index is invalid
                        else {
                            cout << "Invalid Position" << endl;
                        }
                    }
                }
                break;
            //the separator index
            case 5:
                cout << "Should not happen!" << endl;
                break;
            //Option 5: Calculates the average of the numbers in the array
            case 6:
                //sends message if array is not set
                if(array == nullptr){
                    cout << "Need to create array first!" << endl << endl;
                }
                //calculates and prints out the average of all the available numbers in the array
                else{
                    double average = 0;
                    for(int i = 0; i < numFilled; i++){
                        average += array[i];
                    }
                    average /= numFilled;
                    cout << "The average is: " << average << endl << endl;
                }
                break;
        }
    }
    cout << "Finished the Program... Goodbye" << endl << endl;
    return 0;
}



// EXTRA CREDIT IDEA
/**
 * Create a menu with the following options
 * 1. Set Size of the Array
 *  =========================
 * 2. Add Number to the Array
 * 3. List the Numbers
 * 4. Remove a Number
 *  ========================
 * 5. Calculate Average
 * 99. Exit
 *
 * AND the program that goes with it!  <------------ <------------- <--------------
 * What happens on each option:
 * 1. Creates a dynamic array of the size that the user inputs (frees the array if it was already created!)
 * >> None of the options below work if there is no array created!
 * 2. Reads a number from the user and adds it to the end of the array... if it fits, if it doesn't signals the error
 * 3. Shows all the numbers very nicely formatted in the screen
 * 4. Given the position of the number it removes it from the array, it pushes the numbers if it is not the last
 * 5. Calculates the average of the numbers in the array
 */