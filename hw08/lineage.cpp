/*
 * lineage.cpp
 * purpose: to answer querries to information about gene mutation
 *          put into a compact file
 * author: Luke Randolph
 * last modified: March 30, 2023
 */

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

//since pointer in mutation, need to initialize Gene first
struct Gene;

//initialize structs
struct Mutation {
    int cost;
    Gene *target;
};

struct Gene {
    string sq; // Name of gene sequence
    bool seen; // Used in recursive functions to avoid loops
    Mutation mut;
};

//const strings for prompt and execute querries
const string EVOLVE = "e";
const string E_STEPS = "es";
const string ENE_EVOLVE = "ene";
const string PATH = "path";
const string QUIT = "q";

Gene *read_genes(string filename, int *num_genes);
void populate_nodes(Gene *genes, ifstream *inf, int num_nodes);
void populate_links(Gene *genes, ifstream *inf, int num_nodes);
int index_of(Gene *genes, string seq, int num_nodes);
void init(Gene *genes, int num_nodes);
void prompt_and_execute(Gene *all_mutations, int num_genes);
void prompt_and_execute2(Gene *all_genes, int num_genes, string command);
void prompt_and_execute3(Gene *all_genes, int num_genes, string command);
bool evolution(Gene *all_genes, int num_genes, string gene, string target, int i);
void resetseen(Gene *all_genes, int num_genes);
bool evolution_steps(Gene *all_genes, int num_genes, string gene, string target,
                     int i, int *n);
bool evolution_energy(Gene *all_genes, int num_genes, string gene,
                      string target, int i, int *e);
bool Pathprint(Gene *all_genes, int num_genes, string gene, string target,
               int i, string *arr, int *n);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: No filename provided as an argument" << endl;
        exit(EXIT_FAILURE);
    }

    //After these two lines execute, all_genes is a pointer to the array of gene
    //information read in from a given data file, and num_genes contains the
    //number of genes stored in that array.
    int num_genes;
    Gene *all_genes = read_genes(argv[1], &num_genes);

    //USE all_genes AND num_genes AFTER THIS LINE TO CONTINUE THE COMPUTATION
    //run prompt and execute
    prompt_and_execute(all_genes, num_genes);
    //need to delete the dynamically allocated array
    delete[] all_genes;
    return 0;
}

// read_genes
// Input: A file name and a pointer to store the number of genes in the file.
// Description: Read in a file provided the user and use the data to populate an
//              array of Genes.
// Output: Returns a pointer to an array of Genes (populated with the contents
//         of a data file), and indirectly returns the number of array elements
//         through the num_genes pointer.
Gene *read_genes(string filename, int *num_genes)
{
    ifstream inf;
    inf.open(filename);
    if (inf.fail()) {
        cout << "ERROR OPENING FILE: Exiting Program" << endl;
        exit(EXIT_FAILURE);
    }

    inf >> *num_genes;

    // Create and populate the the names in the array of genes
    Gene *dna_p = new Gene[*num_genes];
    init(dna_p, *num_genes);
    populate_nodes(dna_p, &inf, *num_genes);

    // Reset the file to read in the mutation information
    inf.close();
    inf.open(filename);
    inf >> *num_genes; // NEED TO READ "past" NUMBER ON FIRST LINE

    populate_links(dna_p, &inf, *num_genes);

    inf.close();

    return dna_p;
}

// init
// Input: A pointer to an uninitialized array of genes and the size of
//        that array.
// Description: Initializes the array of genes with non-garbage information.
// Output: Initializes the array pointed to by 'dna'.
void init(Gene *dna, int num_nodes)
{
    for (int i = 0; i < num_nodes; i++) {
        dna[i].sq = "";
        dna[i].seen = false;
        dna[i].mut.cost = -1;
        dna[i].mut.target = nullptr;
    }
}

// populate_nodes
// Input: A pointer to an array of genes, a pointer to a file stream,
//        and the size of the array.
// Description: Read the file pointed to and set the sequence name of
//              each gene in the array.
// Output: Populates the sequence information for the gene array pointed to by
//         'dna'. Moves the file pointer further into the file.
void populate_nodes(Gene *dna, ifstream *inf, int num_nodes)
{
    string seq, mut_seq;
    int num_muts, num;
    for (int i = 0; i < num_nodes; i++) {
        *inf >> seq >> num_muts;
        dna[i].sq = seq;
        for (int j = 0; j < num_muts; j++) {
            *inf >> mut_seq >> num;
        }
    }
}

// populate_links
// Input: A pointer to an array of genes, a pointer to a file stream,
//        and the size of the array.
// Description: Read the file pointed to and populate the mutation
//              information between genes in the array. We assume the data file
//              only contains well-formed input.
// Output: Populates the mutation information for the gene array pointed to by
//         'dna'. Moves the file stream pointed to further into the file.
void populate_links(Gene *dna, ifstream *inf, int num_nodes)
{
    string seq, mut_seq;
    int num_muts;
    for (int i = 0; i < num_nodes; i++) {
        *inf >> seq >> num_muts;

        // Add the one mutation if it exists
        if (num_muts == 1) {
            int cost;
            *inf >> mut_seq >> cost;

            int index = index_of(dna, mut_seq, num_nodes);

            dna[i].mut.cost = cost;
            dna[i].mut.target = &dna[index];
        }
    }
}

// index_of
// Input: An array of genes, a gene sequence, and the size of the array.
// Description: Find the index of the given sequence in the array.
// Output: The index of the sequence in the array, or -1 if the sequence is not
//         in the array.
int index_of(Gene *dna, string seq, int num_nodes)
{
    for (int i = 0; i < num_nodes; i++) {
        if (dna[i].sq == seq) {
            return i;
        }
    }
    return -1;
}

/* prompt_and_execute
* Input: A pointer to a dynamically allocated array of Genes
* and the number of Genes in a file
* Description: Repeatedly prompt the user to provide a query, then respond to
* the query. Continue until the user provides the "quit" query.
* Output: This function may print out messages if a provided query isn’t
* valid, but otherwise it will simply call other functions to handle each
* query individually. Nothing is returned by this function.
*/
void prompt_and_execute(Gene *all_genes, int num_genes) {
    //need to initialize command and some strings
    string command = " ";
    //query loop to run functions given certain commands
    while(command != QUIT){
        cout << "Enter a query: ";
        cin >> command;
        //to shorten function length, split into two seperate p_and_e commands
        if (command == EVOLVE || command == E_STEPS) {
            prompt_and_execute2(all_genes, num_genes, command);
        }else if(command == ENE_EVOLVE || command == PATH){
            prompt_and_execute3(all_genes, num_genes, command);
        }else if (command == QUIT) {
        } else {
            cout << command << " not recognized.\n\n";
        }
    }
}

/* prompt_and_execute2
* Input: A pointer to a dynamically allocated array of Genes
* and the number of Genes in a file
* Description: Takes in a command from prompt_and_execute and responds to
* the query from the command
* Output: This function may print out messages if a provided query isn’t
* valid, but otherwise it will simply call other functions to handle each
* query individually. Nothing is returned by this function.
*/
void prompt_and_execute2(Gene *all_genes, int num_genes, string command) {
   string gene, target;
   if (command == EVOLVE){
       cin >> gene >> target;
        int i = 0;
        if (evolution(all_genes, num_genes, gene, target, i)){
            cout << gene << " can evolve into " << target << endl << endl;
        }else{
            cout << gene << " cannot evolve into " << target << endl << endl;
        }
        resetseen(all_genes, num_genes);
    } else if(command == E_STEPS){
        cin >> gene >> target;
        int i = 0;
        int n = 0;
        if(evolution_steps(all_genes, num_genes, gene, target, i, &n)){
            cout << "It will take "<< n <<" evolutionary steps to get from " 
            << gene << " to " << target << endl << endl;
        }else{
            cout << "It will take -1 evolutionary steps to get from " <<
            gene << " to " << target << endl << endl;
        }
        resetseen(all_genes, num_genes);
    }
}

/* prompt_and_execute3
* Input: A pointer to a dynamically allocated array of Genes
* and the number of Genes in a file
* Description: Takes in a command from prompt_and_execute and responds to
* the query from the command(prompt_and_execute was too long originally)
* Output: This function may print out messages if a provided query isn’t
* valid, but otherwise it will simply call other functions to handle each
* query individually. Nothing is returned by this function.
*/
void prompt_and_execute3(Gene *all_genes, int num_genes, string command){
    string gene, target;
    if(command == ENE_EVOLVE){
        //need energy value, then cin from inputs
        int energy;
        cin >> gene >> target >> energy;
        int i = 0;
        int e = 0;
        //run evolution + energy cost, cout info based on hw spec then resetseen 
        if(evolution_energy(all_genes, num_genes, gene, target, i, &e) && 
        (energy >= e)){
            cout << gene << " can evolve into " << target <<
            " with at most " << energy << " evolutionary cost" << endl << endl;
        } else{
            cout << gene << " cannot evolve into " << target <<
            " with at most " << energy << " evolutionary cost" << endl << endl;
        }resetseen(all_genes, num_genes);
    }else if(command == PATH){
        cin >> gene >> target;
        int n = 0;
        string arr[num_genes];
        for (int k = 0; k < num_genes; k++){
            arr[k] = " ";
        }//run Pathprint, cout info based on hw spec, then resetseen
        if(Pathprint(all_genes, num_genes, gene, target, 0, arr, &n)){
            cout << gene << " -> "; 
            for(int j = 0; j < n; j++){
                cout << arr[j] << " -> ";
            }
            cout << target << endl << endl;
        }else{
            cout << "There is no path from " << gene << " to " << target << endl
            << endl;
        }resetseen(all_genes, num_genes);
    }
}

/* evolution
* Input: A pointer to a dynamically allocated array of Genes,
* the number of Genes in a file, two inputs, and an integer counter.
* Description: Checks if a gene can mutate into another target gene directly,
* and uses recursion to check if there is a path for a gene to mutate
* into the target
* Output: True if a gene can evolve into target, otherwise false
*/
bool evolution(Gene *all_genes, int num_genes, string gene, string target, int i){
    //to prevent infinite loop
    if (i >= num_genes) {
        return false;
    } 
    //recursion to find index where gene is in dynamic array
    if(all_genes[i].sq != gene){
        i = i + 1;
        return (evolution(all_genes, num_genes, gene, target, i));
    }else {
        //need seen to prevent infinite loop
        if(all_genes[i].seen){
            return false;
        }
        //if a gene doesn't mutate, false. If gene/new_gene ever = target, true
        if(all_genes[i].mut.target == nullptr){
            return false;
        }else if(all_genes[i].mut.target->sq == target){
            return true;
        }else{
            string new_gene;
            new_gene = all_genes[i].mut.target->sq;
            all_genes[i].seen = true;
            return(evolution(all_genes, num_genes, new_gene, target, 0));
        }
    }
}

/* resetseen
* Input: A pointer to a dynamically allocated array of Genes,
* and the number of Genes in a file
* Description: Resets the seen part of a struct to false for the four
* other evolution functions
* Output: None
*/
void resetseen(Gene *all_genes, int num_genes) {
    for (int i=0; i<num_genes; i++) {
        all_genes[i].seen = false;
    }
}

/* evolution_steps
* Input: A pointer to a dynamically allocated array of Genes,
* the number of Genes in a file, two inputs, an integer counter, a pointer to
* an integer count for number of steps updated by the function.
* Description: Checks if a gene can mutate into another target gene directly,
* and uses recursion to check if there is a path for a gene to mutate
* into the target. Updates the integer pointer of number of steps for 
* outside the bool function
* Output: True if a gene can evolve into target, otherwise false
*/
bool evolution_steps(Gene *all_genes, int num_genes, string gene, string target,
                     int i, int *n){
//same as evolution, just added a pointer to an integer for steps
if (i >= num_genes) {
        return false;
    }
    if(all_genes[i].sq != gene){
        i = i + 1;
        return (evolution_steps(all_genes, num_genes, gene, target, i, n));
    }else {
        if(all_genes[i].seen){
            return false;
        }
        if(all_genes[i].mut.target == nullptr){
            return false;
        }else if(all_genes[i].mut.target->sq == target){
            //update n here by 1
            *n +=1;
            return true;
        }else{
            string new_gene;
            new_gene = all_genes[i].mut.target->sq;
            //this is another step, update n by 1
            *n +=1;
            all_genes[i].seen = true;
            return(evolution_steps(all_genes, num_genes, new_gene, target, 0, n));
        }
    }
}

/* evolution_energy
* Input: A pointer to a dynamically allocated array of Genes,
* the number of Genes in a file, two inputs, an integer counter, and a pointer
* to an integer that stores the needed energy for an evolution.
* Description: Checks if a gene can mutate into another target gene directly,
* and uses recursion to check if there is a path for a gene to mutate
* into the target. Updates the energy cost pointer for outside the bool function
* Output: True if a gene can evolve into target, otherwise false
*/
bool evolution_energy(Gene *all_genes, int num_genes, string gene, 
                      string target, int i, int *e){
    //same as evolution_steps, just instead f=of updating by 1, update with
    //the cost part of the mutation struct from the index we find
    if (i >= num_genes) {
        return false;
    }
    if(all_genes[i].sq != gene){
        i = i + 1;
        return (evolution_energy(all_genes, num_genes, gene, target, i, e));
    }else {
        if(all_genes[i].seen){
            return false;
        }
        if(all_genes[i].mut.target == nullptr){
            return false;
        }else if(all_genes[i].mut.target->sq == target){
            *e += all_genes[i].mut.cost;
            return true;
        }else{
            string new_gene;
            new_gene = all_genes[i].mut.target->sq;
            *e += all_genes[i].mut.cost;
            all_genes[i].seen = true;
            return(evolution_energy(all_genes, num_genes, new_gene, target, 0, 
            e));
        }
    }
}

/* Pathprint
* Input: A pointer to a dynamically allocated array of Genes,
* the number of Genes in a file, two inputs, an integer counter, a pointer to
* an array, and a pointer to a counter integer.
* Description: Checks if a gene can mutate into another target gene directly,
* and uses recursion to check if there is a path for a gene to mutate
* into the target. Updates a pointer array with the name of the targets along
* the way, and an integer for recursion purposes each run through.
* Output: True if a gene can evolve into target, otherwise false
*/
bool Pathprint(Gene *all_genes, int num_genes, string gene, string target, int i,
               string *arr, int *n){
    //same as evolution
    if (i >= num_genes) {
        return false;
    }
    if(all_genes[i].sq != gene){
        i = i + 1;
        return (Pathprint(all_genes, num_genes, gene, target, i, arr, n));
    }else {
        if(all_genes[i].seen){
            return false;
        }
        if(all_genes[i].mut.target == nullptr){
            return false;
        }else if(all_genes[i].mut.target->sq == target){
            return true;
        }else{
            string new_gene;
            new_gene = all_genes[i].mut.target->sq;
            // here we update the array with the path, but also the pointer
            //to n and update that by one to store the next target in the
            //next position of the array
            arr[*n] = new_gene;
            *n += 1;
            all_genes[i].seen = true;
            return(Pathprint(all_genes, num_genes, new_gene, target, 0, arr, n));
        }
    }
}
