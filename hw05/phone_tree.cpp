/*
 * phone_tree.cpp
 * purpose: To make a call plan using structs to
 * reach every parent
 * author: Luke Randolph
 * Date Started: March 3, 2023
 */

 #include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

//make struct
struct Contact {
    string name;
    int time;
    string callee;
    Contact *calls_them = nullptr;
    Contact *nextcall;
};

//make function declarations
Contact *read_contacts(string filename, int *book_size);
void match_contacts(Contact *black_book, int book_size);
Contact *firstcaller(Contact *black_book, int book_size);
void print_contacts(Contact *first, Contact *black_book, int book_size);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }
    //initialize booksize
    int book_size = 0;
    //call the functions in order in main
    Contact *black_book = read_contacts(argv[1], &book_size);
    match_contacts(black_book, book_size);
    Contact *first = firstcaller(black_book, book_size);
    print_contacts(first, black_book, book_size);
    //delete the array black_book to clear the heap
    delete [] black_book;
    return 0;
}

/* Contact *read_contacts
* Input: The name of a file and a pointer to array size
* Description: Read the file into an array of structs
* Output: Populates the array of structs and returns the
*         array.
*/
Contact *read_contacts(string filename, int *book_size)
{
    ifstream infile(filename);
    if(infile.fail()){
        cerr << "ERROR: Error opening file, please check file name." << endl;
        exit(EXIT_FAILURE);
    }
    //Read in the number of contacts (i.e., how big of an array I need)
    infile >> *book_size;
    //Dynamically create an array for the contacts on the heap
    Contact *black_book = new Contact[*book_size];
    //Read in the Contact data
    for (int i = 0; i < *book_size; i++) {
        infile >> black_book[i].name >> black_book[i].time >> black_book[i].callee; 
    }
    //Close the file
    infile.close();
    //Return the array
    return black_book;
}

/* match_contacts
* Input: The array of contacts and the size of the array
* Description: Matches contact structs to one another based
*              on who calls them and who they call
* Output: The matches
*/
void match_contacts(Contact *black_book, int book_size)
{
    //nested for loop to check each struct in the array
    for(int i = 0; i < book_size; i++){
        for(int j = 0; j < book_size; j++){
            //if the callee of one struct is the name of another struct
            if(black_book[i].callee == black_book[j].name ){
                //nextcall part of one struct to the address of other struct
                black_book[i].nextcall = &black_book[j];
                //callsthem part of other struct to the address of one struct
                black_book[j].calls_them = &black_book[i];
            }
        }
    }
}

/* Contact *firstcaller
* Input: The array of contacts and the size of the array
* Description: Finds the firstcaller and if Harold sabotaged
*              the input file
* Output: Either a nullptr or the first caller, depending on
*         if Harold sabotaged or not
*/
Contact *firstcaller(Contact *black_book, int book_size)
{
    //Set first to nullptr to initialize
    Contact *first = nullptr;
    //initialize a count for testing if harold meddled
    int testharold = 0;
    //for loop size of book_size
    for(int i = 0; i < book_size; i++){
        //if the calls them part of a struct is nullptr
        //meaning nobody calls them, thus they are a firstcaller
        if (black_book[i].calls_them == nullptr){
            testharold++;
            first = &black_book[i];
        }
    } 
    //if harold meddled, return nullptr
    if (testharold != 1) {
        return nullptr;
    }
    //if harold didn't, return first
    return first;
}

   /* print_contacts
   * Input: The firstcaller struct, the array of structs,
            and the size of the array
   * Description: Checks if Harold meddled, if he did, print
                  out that he did. If he didn't, prints out
                  the name of the first caller and the
                  calltime added in the function
   * Output: A printed message found in the description above
   */
void print_contacts(Contact *first, Contact *black_book, int book_size) 
{
    if (first == nullptr){
        cout << "Curse you, Harold Hacker!" << endl;
    }
    else{
        cout << "Starting with " << first->name << " the phone tree will succeed in ";
        int calltime = 0;
        for (int i = 0; i < book_size; i++){
            if (black_book[i].nextcall->name != "2nd") {
                calltime += black_book[i].time;
                black_book[i].nextcall->name = "2nd";
            }
        }
        cout << calltime << " seconds!" << endl;
    }
}