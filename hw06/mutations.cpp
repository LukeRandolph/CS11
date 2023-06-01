/*
 * mutations.cpp
 * purpose: to answer querries to information about gene mutation
 *          put into a compact file
 * author: Luke Randolph
 * last modified: March 10, 2023
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Hard coded queries that the user can execute
const string Print = "p";
const string Mutations = "m";
const string Mutations_with_Energy= "me";
const string QUIT = "q";

const int num_pos_mutations = 5;
/* Putting this declaration here let's me define the Target struct with a Gene
 * pointer struct inside it*/
struct Gene;

struct Target {
    string target_name;
    Gene *mutates;
    int energy;
};

struct Gene {
    string gene_name;
    int possible_mutations;
    Target mutations[num_pos_mutations];
};

Gene *read_genes(string filename, int *num_mutations);
void init_data(Gene *all_mutations, int num_mutations);
Gene *find_mutation(Gene *all_mutations, int num_mutations, string gene_name);
void populate_names(Gene *all_mutations, int num_mutations, ifstream *file_p);
void populate_mutations(Gene *all_mutations, int num_mutations, 
                        ifstream *file_p);
void prompt_and_execute(Gene *all_mutations, int num_mutations);
void print(Gene *all_mutations, int num_mutations);
bool mutations(Gene *all_mutations, int num_mutations, string gene, 
               string target);
void mutation_cost(Gene *all_mutations, int num_mutations, string gene, 
                   string target);
void mutation_cost(Gene *all_mutations, int num_mutations);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    string filename = argv[1];
    int num_mutations;
    Gene *all_mutations = read_genes(filename, &num_mutations);

    /* CALL YOUR prompt_and_execute FUNCTION HERE */
    // cout << "Enter a command: ";
    //prompt_and_execute(movies, num_movies);

    prompt_and_execute(all_mutations, num_mutations);

    delete[] all_mutations;
    return 0;
}

/* Gene *read_genes
 * Input: a file, and a pointer to an initialized value
 * Description: Read in Gene data from a file named by the first parameter, 
 * use the second parameter to "return" the number of Genes read 
 * in from the file
 * Output: return a pointer to a dynamically 
 * allocated array of Genes populated with the data read from the file.
 */
Gene *read_genes(string filename, int *num_mutations)
{
    //Open the given file
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "ERROR OPENING FILE: Exiting Program " << endl;
        exit(EXIT_FAILURE);
    }
    //read the number of genes in the file
    infile >> *num_mutations;
    //make a dynamically allocated array on the heap
    Gene *all_mutations = new Gene[*num_mutations];
    //initialize those values
    init_data(all_mutations, *num_mutations);
    //first run through populate gene name and possible mutations for that gene
    populate_names(all_mutations, *num_mutations, &infile);
    infile.close();
    //second run through
    infile.open(filename);
    infile >> *num_mutations; //Need to "read past" the number

    //Populate each Gene's array of mutation and energy combos
    populate_mutations(all_mutations, *num_mutations, &infile);
    infile.close();

    return all_mutations;
}

/* init_data
 * Input: A dynamically allocated array, number of Genes in the file
 * Description: Initializes the values of the dynamically allocated array
 * Output: None
 */
void init_data(Gene *all_mutations, int num_mutations)
{
    // Initialize dynamically allocated array
    for (int i = 0; i < num_mutations; i++) {
        all_mutations[i].gene_name = "";
        all_mutations[i].possible_mutations = 0;

        for(int j = 0; j < num_pos_mutations; j++){
            all_mutations[i].mutations[j].target_name = "";
            all_mutations[i].mutations[j].mutates = nullptr;
        }
    }
}

/* populate_names
 * Input: A dynamically allocated array, number of Genes in the file,
 * and a trick that lets us pass stuff in the file, used in monster demo
 * Description: Populates the gene names and possible number of 
 * mutations a gene can have
 * Output: A semi-populated array
 */
void populate_names(Gene *all_mutations, int num_mutations, ifstream *file_p){
    string g_name, next_mutations;
    int NUM_MUTATIONS;

    //Get each Gene's name and possible mutations
    for (int i = 0; i < num_mutations; i++) {
        *file_p >> g_name >> NUM_MUTATIONS;
        all_mutations[i].gene_name = g_name;
        all_mutations[i].possible_mutations = NUM_MUTATIONS;
        // Skip over all the target info for now
        for (int j = 0; j < NUM_MUTATIONS; j++) {
            *file_p >> next_mutations >> g_name;
        }
    }
}

/* populate_mutation
 * Input: A dynamically allocated array, number of Genes in the file,
 * and a trick that lets us pass stuff in the file, used in monster demo
 * Description: Populates the array of possible mutations and energy counts
 * Output: Finishes populating the array, no real output though- void function
 */
void populate_mutations(Gene *all_mutations, int num_mutations, 
                        ifstream *file_p){
    string gene_name, mutation_name;
    int NUM_MUTATIONS, energy_count;

    /* Second pass over the file: set each Gene's mutations as pointers to other
     * genes in the same dynamically allocated array */
    for (int i = 0; i < num_mutations; i++) {
        *file_p >> gene_name >> NUM_MUTATIONS;

        for (int mutation_index = 0; mutation_index < NUM_MUTATIONS; 
             mutation_index++) {
            *file_p >> mutation_name >> energy_count;

            //Get a pointer to the Gene's mutations
            Gene *mutation_p = find_mutation(all_mutations, num_mutations, 
                                             mutation_name);
        
            //Add the mutation connection to our current gene's array
            all_mutations[i].mutations[mutation_index].target_name = mutation_name;
            all_mutations[i].mutations[mutation_index].mutates = mutation_p;
            all_mutations[i].mutations[mutation_index].energy = energy_count;
        }
    }
}

/* Gene *find_mutation
 * Input: a dynamically allocated array, the number of Genes in a file,
 * and a previously read in part of a file that stores a mutation of a gene
 * Description: Look for a Gene with the given name in our array. 
 * Return a pointer to that Gene if found and a nullptr otherwise.
 * Output: return a pointer to a dynamically 
 * allocated array of Genes populated with the data read from the file.
 */
Gene *find_mutation(Gene *all_mutations, int num_mutations, 
                    string mutation_name){
    for (int i = 0; i < num_mutations; i++) {
        if (all_mutations[i].gene_name == mutation_name) {
            return &all_mutations[i];
        }
    }
    return nullptr;
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
void prompt_and_execute(Gene *all_mutations, int num_mutations) {
    //need to initialize command and some strings
    string command = " ";
    string gene, target;
    //query loop to run functions given certain commands
    while(command != QUIT){
        cout << "Enter a query: ";
        cin >> command;
        if (command == Print) {
            print(all_mutations, num_mutations);
        } else if (command == Mutations) {
            cin >> gene >> target;
            bool result = mutations(all_mutations, num_mutations, gene, target);
            if (result) {
                cout << "\n";
            }
            cout << endl;
        } else if (command == Mutations_with_Energy) {
            mutation_cost(all_mutations, num_mutations);
            cout << endl;
        } else if (command == QUIT) {
        } else {
            cout << command << " not recognized.\n\n";
        }
    }
}

/* print
* Input: A pointer to a dynamically allocated array of Genes
* and the number of Genes in a file
* Description: Systematically prints the read in contents of the dynamically
* allocated array according to the homework file's specs
* Output: A printed message of the read in file's contents
*/
void print(Gene *all_mutations, int num_mutations) {
    //prints according to homework specs from array of structs
    for (int i = 0; i < num_mutations; i++) {
        cout << "== " << all_mutations[i].gene_name << " ==" << endl;
        cout << "Mutations:\n";
        if(all_mutations[i].possible_mutations == 0){
            cout << "None\n";
        }
        for (int j = 0; j < all_mutations[i].possible_mutations; j++) {
            cout << all_mutations[i].mutations[j].target_name;
            cout << " - Cost: " << all_mutations[i].mutations[j].energy;
            cout << "\n";
        }
    }
    cout << "\n";
}

/* mutations
* Input: A pointer to a dynamically allocated array of Genes, the number of
* Genes in a file, and two strings gathered from an inputted command
* Description: Checks if a gene can mutate into a target
* Output: A printed message of whether the gene can mutate into a target
*/
bool mutations(Gene *all_mutations, int num_mutations, string gene, 
               string target) {
    //for loop to check if a gene can mutate into a target or not
    for (int i = 0; i < num_mutations; i++) {
        if (gene == all_mutations[i].gene_name) {
            for (int j = 0; j < all_mutations[i].possible_mutations; j++) {
                if (target == all_mutations[i].mutations[j].target_name) {
                    cout << gene << " can mutate into " << target;
                    return true;
                }
            }
        }
    }
    cout << gene << " cannot mutate into " << target << endl;
    return false;
}

/* mutation_cost
* Input: A pointer to a dynamically allocated array of Genes
* and the number of Genes in a file
* Description: Reads in commands to initialized values, runs the mutation
* function on them, and if it returns true checks if the inputted energy amount
* is greater or equal to the amount needed to mutate into that gene
* Output: A printed message that tells whether a gene can or can't mutate,
* and if it can whether the inputted energy is enough to do so
*/
void mutation_cost(Gene *all_mutations, int num_mutations) {
    //need to initialize some values and strings
    int energy;
    string gene, target;
    //take in commands here
    cin >> gene >> target >> energy;
    //run mutations on first two parts of command after 'me'
    bool result = mutations(all_mutations, num_mutations, gene, target);
    if (!result) {
        return;
    }
    //if target is a mutation of gene, figure out if the input energy cost is
    //greater than or equal to the energy needed to activate mutation
    for (int i = 0; i < num_mutations; i++) {
        if (gene == all_mutations[i].gene_name) {
            for (int j = 0; j < all_mutations[i].possible_mutations; j++) {
                if (target == all_mutations[i].mutations[j].target_name) {
                    if (energy >= all_mutations[i].mutations[j].energy) {
                        cout << " with evolutionary cost " << energy << "\n";
                        return;
                    }
                }
            }
        }
    }
    cout << " but not with evolutionary cost " << energy << "\n";
}