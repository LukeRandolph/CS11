/*
 * adivsing.cpp
 * purpose: to answer querries to information about a binary search tree of
 *          advisors read in from a file.
 * author: Luke Randolph
 * last modified: April 11, 2023
 */
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

//define the struct for a Node
struct Node {
    string name;
    Node *supervisee_1;
    Node *supervisee_2;
    int advisee_count;
};
// const strings for querries
const string PRINT = "p";
const string ADD_A = "a";
const string ADD_F = "f";
const string TOTAL = "t";
const string SLACKER = "s";
const string QUIT = "q";

//function declarations
Node *new_node(string name);
Node *read_file(string filename);
void print_advisees(Node *curr_node, string bureaucracy);
Node *find_node(Node *curr_node, string name);
int Total_advisees(Node *curr_node);
void Slackers(Node *curr_node);
void Delete_Nodes(Node *curr_node);


//STYLE NOTE: You do not have to worry about making main() fit in 30 lines for
//this assignment!
int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: No filename provided as an argument" << endl;
        exit(EXIT_FAILURE);
    }
    Node *boss = read_file(argv[1]);
    //Loop to continually prompt for queries
    string c;
    cout << "Enter a query: ";
    while (cin >> c) {
        if (c == PRINT) {
            print_advisees(boss, "");
        } else if (c == TOTAL) {
            string name;
            cin >> name;
            //find the node where the inputted name is
            Node *curr_node = find_node(boss, name);
            //run the advisees function on that node
            int num_advisees = Total_advisees(curr_node);
            //put in a return -1 to ensure that the inputted name is in the file
            if (num_advisees != -1){
                cout << name << " is responsible for " << num_advisees <<
                " advisee(s)." << endl;
            }else{
                cout << name << " doesn't work here!" << endl;
            }
        } else if (c == SLACKER) {
            Slackers(boss);
        } else if (c == QUIT) {
            Delete_Nodes(boss);
            break;
        } else if (c == ADD_A) {
            ///// (OPTIONAL) YOUR CODE GOES HERE /////

        } else if (c == ADD_F) {
            ///// (OPTIONAL) YOUR CODE GOES HERE /////

        } else {
            cout << c << " not recognized." << endl;
        }
        cout << endl << "Enter a query: ";
    }
    return 0;
}

//Print the tree path of every person who has advisees
void print_advisees(Node *curr_node, string bureaucracy)
{
    //Base Case: If we are at a person who has advisees, print the count
    if (curr_node->advisee_count > 0) {
        cout << bureaucracy;
        cout << curr_node->name + "->";
        cout << curr_node->advisee_count << endl;
    } else {
        //Recursive Cases: If we are at a person who doesn't have advisees,
        //recurse to their subtrees
        if (curr_node->supervisee_1 != nullptr) {
            string bureaucracy_left = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_1, bureaucracy_left);
        }

        if (curr_node->supervisee_2 != nullptr) {
            string bureaucracy_right = bureaucracy + curr_node->name + "->";
            print_advisees(curr_node->supervisee_2, bureaucracy_right);
        }
    }
}

//Read file and build tree structure, returning root "boss" node.
//STYLE NOTE: You do not have to worry about paring down read_file() to a
//30-line limit for this assignment.
Node *read_file(string filename)
{
    //Open the given file
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: "
             << filename << endl;
        exit(EXIT_FAILURE);
    }

    //Read the first line of the file
    string supervisor;
    string supervisee;

    infile >> supervisor;
    infile >> supervisee;
    Node *boss = new_node(supervisor);
    bool first_line = true;

    //Process each line of the file
    while (!infile.eof()) {
        Node *supervisor_node;

        //Initialize the root node if we're on the first line of the file
        if (first_line) {
            supervisor_node = boss;
            first_line = false;
        } else {
            supervisor_node = find_node(boss, supervisor);
        }

        //Check if we're dealing with an advisor or a supervisor
        if (supervisee == "Advisee") {
            supervisor_node->advisee_count++;
        } else {
            //Determine if supervisee should be the first or second supervisee
            if (supervisor > supervisee) {
                supervisor_node->supervisee_1 = new_node(supervisee);
            } else {
                supervisor_node->supervisee_2 = new_node(supervisee);
            }
        }

        //Read the next line
        infile >> supervisor;
        infile >> supervisee;
    }

    infile.close();

    return boss;
}

//Finds and returns the node with the given name
Node *find_node(Node *curr_node, string name)
{
    //Base Case: If curr_node is the person we're looking for, return it
    if (curr_node->name == name) {
        return curr_node;
        //Recursive Cases: Search either the left or right subtree for the name
    } else if (curr_node->name > name) {
        if (curr_node->supervisee_1 == nullptr) {
            return nullptr;
        }
        return find_node(curr_node->supervisee_1, name);
    } else {
        if (curr_node->supervisee_2 == nullptr) {
            return nullptr;
        }
        return find_node(curr_node->supervisee_2, name);
    }

    return nullptr;
}

//Returns a new node that is blank except for the provided name
Node *new_node(string name)
{
    Node *new_node = new Node;

    new_node->name = name;
    new_node->supervisee_1 = nullptr;
    new_node->supervisee_2 = nullptr;
    new_node->advisee_count = 0;

    return new_node;
}

/* Total_evolution
* Input: A pointer to a specific node in a dynamically allocated BST of 
* Faculty Nodes
* Description: Runs through the BST from the node found from the inputted
* name recursively adding up the number of advisees they have.
* Output: The integer value of the total number of advisees a faculty has
*/
int Total_advisees(Node *curr_node){
    //base case 1, inputted name is not in the file.
    if (curr_node==nullptr){
        return -1;
    }
    //base case 2, if no supervisees, return their advisor count
    if(curr_node->supervisee_1==nullptr && curr_node->supervisee_2==nullptr){
        return curr_node->advisee_count;
    }
    //case 1- no supervisee 1 but there is a supervisee 2
    if(curr_node->supervisee_1==nullptr && curr_node->supervisee_2!=nullptr){
        return Total_advisees(curr_node->supervisee_2);
    }
    //case 2- no supervisee 2 but there is a supervisee 1
    if(curr_node->supervisee_2==nullptr && curr_node->supervisee_1!=nullptr){
        return Total_advisees(curr_node->supervisee_1);
    }
    //if not BC2, or case 1 and 2, then must have supervisee 1 and 2, so return
    //the sum of both recursively
    return Total_advisees(curr_node->supervisee_1) + 
    Total_advisees(curr_node->supervisee_2);
}

/* Slackers
* Input: A pointer to the parent node in a dynamically allocated BST of 
* Faculty Nodes
* Description: Runs through the BST from the boss node checking to see if any
* faculty member does not have any advisees and supervisees, printing them
* alphabetically
* Output: Void function that prints a list of Slackers, described above
*/
void Slackers(Node *curr_node){
    //base case for what a slacker is
    if (curr_node->supervisee_1==nullptr && curr_node->supervisee_2==nullptr
        && curr_node->advisee_count==0){
        cout << "Slacker: " << curr_node->name << endl;
    }
    //case 1- no supervisee 1 but there is a supervisee 2
    if(curr_node->supervisee_1==nullptr && curr_node->supervisee_2!=nullptr){
        return Slackers(curr_node->supervisee_2);
    }
    //case 2- no supervisee 2 but there is a supervisee 1
    if(curr_node->supervisee_2==nullptr && curr_node->supervisee_1!=nullptr){
        return Slackers(curr_node->supervisee_1);
    }
    //case 3- both supervisee 1 and 2, run the left node in the BST through
    //slackers first so it prints alphabetically
    if(curr_node->supervisee_2!=nullptr && curr_node->supervisee_1!=nullptr){
            return (Slackers(curr_node->supervisee_1),
            Slackers(curr_node->supervisee_2));
        }
}

/* Delete_Nodes
* Input: A pointer to the parent node in a dynamically allocated BST of 
* Faculty Nodes
* Description: Runs through the BST from the parent node recursively deleting
* each node in the BST from the roots up to the parent node.
* Output: None
*/
void Delete_Nodes(Node *curr_node){
    //case 1- no supervisee 1 but there is a supervisee 2
    if(curr_node->supervisee_1==nullptr && curr_node->supervisee_2!=nullptr){
        Delete_Nodes(curr_node->supervisee_2);
    }
    //case 2- no supervisee 2 but there is a supervisee 1
    if(curr_node->supervisee_2==nullptr && curr_node->supervisee_1!=nullptr){
        Delete_Nodes(curr_node->supervisee_1);
    }
    // case 3- has both a supervisee 1 and 2, recursively run delete_nodes
    // on the supervisee left in the tree first, then the one to the right.
    if(curr_node->supervisee_2!=nullptr && curr_node->supervisee_1!=nullptr){
        Delete_Nodes(curr_node->supervisee_1),
        Delete_Nodes(curr_node->supervisee_2);
    }
    delete curr_node;
}