/*
    Author:     Ammar Mohammed
    Compiler:
    Date:       2/28/2023-3//2023

 Purpose of program: Manage homework assignments in an organized list

 The program allows user to enter the
 new homework assignments they have: name, course, and date.
 It will store this data in a file.
 It will also pull previous homework entry data from this file.
 You will be able to remove old homework assignments.
 The program will prompt a menu to print a table of the homeworks
 based on course, date, or priority.

 In C++, I intend to print the tables to the console. I will be using structures which I recently learned to sort the data efficiently.
 In Python, I intend to implement this program with GUI. I will probably use... to store the data.
 
*/
#include <iostream>
#include <fstream>
using namespace std;

struct Date
{
    int month;
    int day;
    int year;
};

struct Homework
{
    string name; // name of the assignment
    Date dueDate; // date the assignment should be completed by
    int priority;
    string course; // the subject/course of the assignment
};

//Function prototypes
char menu();
int getNumAssignments();
void addAssignments(Homework * newHWPtr, Homework * oldHWPtr, int numOfAssignments, int numCurr);
void storeAssignments(Homework *, int);
void getNumLines(int &numLines);
void currentInfo(Homework *, int numLines);
void deleteAssignment(Homework * newHWPtr, int numOfAssignments, int foundIndex);
int searchElementByName(Homework * newHWPtr, int numOfAssignments, string hwName);

int main()
{
    char userOption = menu(); // stores user option to perform menu action
    int numOfCurrTasks; //number of current homework assignments in the file will be stored here
    
    Homework * ogHwPtr = nullptr;
    Homework * newHwPtr = nullptr;
    getNumLines(numOfCurrTasks);
    
    ogHwPtr = new Homework[numOfCurrTasks];
    currentInfo(ogHwPtr, numOfCurrTasks); //loads in the data from the file to the first hwPtr
    
    if(userOption == '1')
    {
        int numAssignments = getNumAssignments() + numOfCurrTasks; //num of HWs user wants to add plus what is already there
        newHwPtr = new Homework[numAssignments]; //allocate space to add new assignments in hwPtr
        
        addAssignments(newHwPtr, ogHwPtr, numAssignments, numOfCurrTasks);
        //cout << hwPtr << endl; //FIXME: test to see if hwPtr is nullptr of assigned value
        //add Assignments used to have a the hwPtr initialized inside of itself (the function), this would not work as HWPtr would not change and still be nullptr
        //I had to create a seperate function to get the number of assignments the user wants to enter, then use new to declare the pointer. then i am able to initialize the pointer inside the function
        
        delete [] ogHwPtr; //delete the original homework pointer
        
        if(newHwPtr)
        { //FIXME: if hwPtr is not nullptr, SUCCESS
            cout << endl << "Content for array of structures:\n";
            for (int i = 0; i < numAssignments; i++)
            {
                cout << "-----HOMEWORK " << i + 1 << "-----" << endl;
                cout << "Assignment Name: " << newHwPtr[i].name << endl;
                cout << "Assignment Date: " << newHwPtr[i].dueDate.month << "/" << newHwPtr[i].dueDate.day << "/" << newHwPtr[i].dueDate.year << endl;
                cout << "Priority: " << newHwPtr[i].priority << endl;
                cout << "Subject: " << newHwPtr[i].course << endl;
                cout << endl;
            } // end of for loop
            storeAssignments(newHwPtr, numAssignments);
            
        } // end of if block
        else
        {
            cout << "Not okay" << endl; //FIXME: if hwPtr is still nullptr, FAIL
        } // end of else block
        //delete [] newHwPtr;
    } // end of add new assignment if block: OPTION 1
    else if (userOption == '4')
    {
        //List 1 priority at top of printed list, list 0 priority at bottom of list
        //Furthermore, sort the priorities by dates.
        
        
    } // end of else if block for list by priority
    else if (userOption == 'Q')
    {
        cout << "Program exiting..." << endl;
        delete [] newHwPtr; //delete the new homework pointer
    } // end of else if block for quit program
    else
    {
        cout << "Invalid menu option, restart program and try again." << endl;
    } // end of else block
    
    return 0;
} // end of main()

char menu()
{
    char option; // stores user option to perform menu action
    
    cout << "HOMEWORK LIST MENU" << endl;
    cout << "------------------" << endl;
    cout << "1 - Add new assignments" << endl;
    cout << "2 - List by Due Date" << endl;
    cout << "3 - List by Course" << endl;
    cout << "4 - List by Priority" << endl; // FOCUS vs All Upcoming
    cout << "Q - Quit" << endl;
    cin >> option;
    
    return option;
} // end of menu

int getNumAssignments()
{
    int numOfAssignments; // the number of assignments
    
    cout << endl <<  "How many assignments would you like to add? ";
    cin >> numOfAssignments;
    
    return numOfAssignments;
} // end of getNumAssignments()

void addAssignments(Homework * newHWPtr, Homework * oldHWPtr, int numOfAssignments, int numCurr)
{
    string aName, aCourse;
    Date aDueDate; // store assignment name and due date
    int aPriority; // store assignment priority as 1 - FOCUS or 0 - GENERAL
    
    int i;
    
    if(numOfAssignments > 0)
    {
        i = 0;
        for(; i < numCurr; i++) //FIXED BUG ISSUE 2
        {
            newHWPtr[i].name = oldHWPtr[i].name;
            newHWPtr[i].dueDate = oldHWPtr[i].dueDate;
            newHWPtr[i].priority = oldHWPtr[i].priority;
            newHWPtr[i].course = oldHWPtr[i].course;
        } // end of for loop
        i = numCurr;
    } // end of if block
    else
        i = 0;
    
    for (; i < numOfAssignments; i++)
    {
        cout << "Enter assignment name, due date, and priority: ";
        cin >> aName >> aDueDate.month >> aDueDate.day >> aDueDate.year >> aPriority >> aCourse;
        
        newHWPtr[i].name = aName;
        newHWPtr[i].dueDate = aDueDate;
        newHWPtr[i].priority = aPriority;
        newHWPtr[i].course = aCourse;
    } // end of for loop
    
    //cout << "Content for array of structures:\n";
    /*for (int i = 0; i < numOfAssignments; i++)
    {
        cout << "Assignment Name: " << newHWPtr[i].name << endl;
        cout << "Assignment Date: " << newHWPtr[i].dueDate.month << "/" << newHWPtr[i].dueDate.day << "/" << newHWPtr[i].dueDate.year << endl;
        cout << "Priority: " << newHWPtr[i].priority << endl;
        cout << "Subject: " << newHWPtr[i].course << endl;
    }*/
} // end of addAssignments()

void storeAssignments(Homework * hwPtr, int numOfAssignments)
{
    ofstream outputFile;
    outputFile.open("hw_records.txt");
    
    if(outputFile)
    {
        for(int i = 0; i < numOfAssignments; i++)
        {
            outputFile << hwPtr[i].name << " " << hwPtr[i].dueDate.month << " " << hwPtr[i].dueDate.day << " " << hwPtr[i].dueDate.year << " " << hwPtr[i].priority << " " << hwPtr[i].course << endl;
        } // end of for loop
        outputFile.close();
    } // end of if block
    else
    {
        cout << "File failed to open..." << endl;
    } // end of else block
} // end of storeAssignments()

//Transfers info currently in file to the first hwPtr
void currentInfo(Homework * hwPtr, int numLines)
{
    ifstream inputFile("hw_records.txt");
    
    int lineNumber = 0;
    
    if(inputFile)
    {
        string name, course;
        int month, day, year, priority;
        while(lineNumber < numLines)
        {
            while(inputFile >> name >> month >> day >> year >> priority >> course)
            {
                hwPtr[lineNumber].name = name; //bug where non-numbers are read improperly
                hwPtr[lineNumber].dueDate.month = month;
                hwPtr[lineNumber].dueDate.day = day;
                hwPtr[lineNumber].dueDate.year = year;
                hwPtr[lineNumber].priority = priority;
                hwPtr[lineNumber].course = course;
                lineNumber++;
            } // end of while input loop
        } // end of while loop
    } // end of inputFile if block
    else
    {
        cout << "File failed to open...";
    } // end of inputFile else block
} // end of currentInfo()

//This function was made because I was getting the error. Thread 1: EXC_BAD_ACCESS (code=1, address=0x17). It happened because I was trying to call hwPtr and assign the string to the memory locations in the array, but hwPtr was still nullptr, and had not been assigned a array size yet.
void getNumLines(int &numLines)
{
    ifstream inputFile("hw_records.txt");
    
    string iterator;
    numLines = 0;
    
    if(inputFile)
    {
        while (getline(inputFile,iterator))
        {
            numLines++;
            //cin.ignore();
        } // end of while loop()
    } // end of if block
    else
    {
        cout << "ERROR: Unable to read number of lines in current file..." << endl;
    } // end of else block
    
} // end of getNumLines()

//Delete the assignment the user wishes to remove from the list
void deleteAssignment(Homework * newHWPtr, int numOfAssignments, int foundIndex)
{
    Homework * deletedHwPtr = new Homework[numOfAssignments - 1];
    if (foundIndex == -1)
    {
        cout << "HW assignment not found, unable to perform operation." << endl;
    } // end of if block
    else
    {
        for (int i = 0; i < numOfAssignments; i++)
        {
            if (i != foundIndex)
            {
                deletedHwPtr[i].name = newHWPtr[i].name;
            } // end of if block
            else if (i >= foundIndex)
            {
                
            } // end of else if block
        } // end of for loop
    } // end of else block
} // end of deleteAssignment()

//Searches through the hwPtr to find a specific assignment
int searchElementByName(Homework * newHWPtr, int numOfAssignments, string hwName)
{
    int foundIndex = -1;
    for(int i = 0; i < numOfAssignments; i++)
    {
        if (newHWPtr[i].name == hwName)
            foundIndex = i;
    } // end of for loop
    
    return foundIndex;
} // end of searchElement()
