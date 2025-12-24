/*
------------------
THE TEAM  Members:
------------------
    *   MALEG MANEL          SEC G2
    *   Wissal Hadjira       SEC G2
    *   Nadjah Belgouchi     SEC G1
*/

// --- Standard libraries ---
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// --- Define constants for maximum values to simplify array allocation ---
#define MAX_STATES 20
#define MAX_SYMBOLS 10

// --- Global Variables defining ---
int num_symbols;
int num_states;
int num_final_states;
char alphabet[MAX_SYMBOLS];
int final_states[MAX_STATES];
int initial_state;

// --- Store using a *bitmask*. ---
int transitions[MAX_STATES][MAX_SYMBOLS]; // **transitions[from][symbol_index]**
int epsilon_transitions[MAX_STATES];      //**epsilon_transitions[state]**

// --- Structures for the new NFA ---
int new_final_states[MAX_STATES];
int num_new_final_states = 0;
int new_transitions[MAX_STATES][MAX_SYMBOLS];

// --- Epsilon Closures ---
int epsilon_closures[MAX_STATES]; // Stores the e-closure for each state as a bitmask


// --- Function Prototypes --
void read_NFA();
void calculate_Epsilon_Closures();
void compute_New_Transitions();
void determine_New_Final_States();
void display_New_Automaton();
void find_closure_recursive(int state, int* closure); 

//THE MAIN FUNCTION OF OUR PROGRAM********************************************************************************
//
int main() {
    printf("\n-- Welcome to the TP of **Eliminating epsilon-Transitions from an NFA** : --\n");
    printf("\n**HINT: you can use the information of **EXO3 TD02** for testing:\nNum of states: 6 | Alphabet: ab\nInitial state: 0 | Number of final states: 1\nFinal states: 5  |  Number of transitions : 10\ntransitions (from_state symbol to_state):\n0 e 1\n0 e 2\n1 a 3\n1 b 1\n2 a 2\n2 b 4\n3 b 3\n3 e 5\n4 a 4\n4 e 5\n");
    printf("\n\n");
    while(1){
        char command[10];
        printf("Type 'run' to enter a new NFA or 'exit' to quit: ");
        scanf("%9s", command);

        for (int i = 0; command[i]; i++) {// Convert each character in the 'command' string to lowercase
        command[i] = tolower(command[i]);
        }

        if (strcmp(command, "exit") == 0) {
            printf("\nExiting program... Goodbye!\n\n");
            break;
        }
        else if (strcmp(command, "run") == 0) {
            printf("\n---Entering NFA with Epsilon-Transitions ---\n");
            // Task 1: Read the NFA details from the user.
            read_NFA();
            printf("\nProcessing...\n");
            // Task 2: Calculate the ε-closure of each state 
            calculate_Epsilon_Closures();
            // Task 3: Compute the new transitions of the NFA without ε 
            compute_New_Transitions();
            // Task 4: Determine the new final states 
            determine_New_Final_States();
            printf("\n--- Equivalent NFA without Epsilon-Transitions ---\n");
            // Task 5: Display the new automaton 
            display_New_Automaton();
            printf("\n========================================\n\n");
        }
        else {
            printf("\nInvalid command. Please type 'run' or 'exit'.\n\n");
        }
    }
    return 0;
}
//
//**************************************************************************************************************

//HELPER FUN: function to get the index of a symbol in the alphabet.
int get_symbol_index(char symbol) {
    for (int i = 0; i < num_symbols; i++) {
        if (alphabet[i] == symbol) return i;
    }
    return -1;
}

//-- Task 1: Read the NFA ---------------------------------------------------------------------------------------
void read_NFA() {

    //FIRST we need to Initialize all transition sets to be empty (0).
    memset(transitions, 0, sizeof(transitions));
    memset(epsilon_transitions, 0, sizeof(epsilon_transitions));

    // THEN prompt the user to input the number of states
    while (1) {
        printf("Enter number of states (max %d): ", MAX_STATES);
        scanf("%d", &num_states);
        // Check if number of states is within allowed range**
        if (num_states < 1 || num_states > MAX_STATES) {
            printf("ERROR: Number of states must be between 1 and %d. Please RETRY.\n\n", MAX_STATES);
            continue; // Retry input
        }

        // If input is valid, exit the loop
        break;
    }

//

   while (1) {
        printf("Enter the alphabet ( e.g: ab, max %d symbols, without 'e'): ", MAX_SYMBOLS);
        scanf("%s", alphabet);
        num_symbols = strlen(alphabet);

        // Check if the number of symbols is within allowed range
        if (num_symbols < 1 || num_symbols > MAX_SYMBOLS) {
            printf("ERROR: Number of symbols must be between 1 and %d. Please RETRY.\n\n", MAX_SYMBOLS);
            continue; // Retry input
        }

        // Check that 'e' (epsilon) is not part of the alphabet
        int invalid = 0;
        for (int i = 0; i < num_symbols; i++) {
            if (alphabet[i] == 'e') {
                invalid = 1;
                break;
            }
        }
        if (invalid) {
            printf("ERROR: 'e' is reserved for epsilon. Please RETRY.\n\n");
            continue; // Retry input
        }

        // Remove duplicate symbols from the alphabet
        int write_index = 0;
        for (int i = 0; i < num_symbols; i++) {
            int duplicate = 0;
            for (int j = 0; j < write_index; j++) {
                if (alphabet[i] == alphabet[j]) {
                    duplicate = 1; // Found duplicate
                    break;
                }
            }
            if (!duplicate) {
                alphabet[write_index++] = alphabet[i]; // Keep unique symbol
            }
        }
        num_symbols = write_index;       // Update the actual number of symbols after removing duplicates
        alphabet[num_symbols] = '\0';    // Null-terminate the string

        // All checks passed, exit the loop
        break;
    }

//

    while (1) {
    printf("Enter initial state (0 to %d): ", num_states-1);
    scanf("%d", &initial_state);
    if (initial_state >= 0 && initial_state < num_states) break;
    printf("ERROR: Invalid initial state. Please RETRY.\n");
    }
    
//

    while (1) {
    printf("Enter number of final states (1 to %d): ", num_states);
    scanf("%d", &num_final_states);
    if (num_final_states >= 1 && num_final_states <= num_states) break;
    printf("ERROR: Invalid number of final states. Please RETRY.\n");
    }
    
//

    printf("Enter final states (space to separate): ");
    for (int i = 0; i < num_final_states; i++) {
        while (1) {
            scanf("%d", &final_states[i]);
            if (final_states[i] >= 0 && final_states[i] < num_states) break;
            printf("ERROR: Invalid final state. Please RETRY. ");
        }
    }
    
//

    int num_trans;
    while(1) {
    printf("Enter number of transitions: ");
    scanf("%d", &num_trans);
    if(num_trans < 0) {
        printf("ERROR: Number of transitions cannot be negative. Please RETRY.\n");
        continue;
    }
    if(num_trans == 0) {
        printf("WARNING: You entered 0 transitions. The NFA will have no transitions.\n");
    }
    break;
}
    
//

printf("Enter transitions (e.g: 0 e 1, from_state symbol to_state), \nuse 'e' for epsilon:\n");
// For each transition entered by the user
    for (int i = 0; i < num_trans; i++) {
        int from, to;
        char symbol_buffer[2]; // Temporary buffer to safely read a single character

        while (1) { // Loop until valid input
            scanf("%d %1s %d", &from, symbol_buffer, &to);
            char symbol = symbol_buffer[0];

            // Check if 'from' and 'to' states are valid
            if (from < 0 || from >= num_states || to < 0 || to >= num_states) {
                printf("ERROR: Invalid state(s). 'from' and 'to' must be between 0 and %d. Please RETRY ", num_states-1);
                continue; // Retry
            }

            // Check if symbol is valid
            if (symbol != 'e' && get_symbol_index(symbol) == -1) {
                printf("ERROR: Invalid symbol '%c'. Must be in alphabet or 'e'. Please RETRY. ", symbol);
                continue; // Retry
            }

            // If everything is valid, add the transition
            if (symbol == 'e') {
                epsilon_transitions[from] |= (1 << to);
            } else {
                int sym_idx = get_symbol_index(symbol);
                transitions[from][sym_idx] |= (1 << to);
            }

            break; // Exit loop after successful input
        }
    }


    printf("\n");
}

//HELPER FUN: A recursive function to find the epsilon closure of a state using DFS.
//*It explores all reachable states via epsilon transitions.*
void find_closure_recursive(int state, int* closure) {
    // Iterate through all possible destination states 'i'
    for (int i = 0; i < num_states; i++) {
        // Check if there is an epsilon transition from 'state' to 'i'
        // AND if 'i' is not already in the current closure set
        if ((epsilon_transitions[state] & (1 << i)) && !(*closure & (1 << i))) {
            *closure |= (1 << i); // Add 'i' to the closure set
            find_closure_recursive(i, closure); // Continue searching from 'i'
        }
    }
}

// -- Task 2: Calculate the ε-closure of each state --------------------------------------------------------------
// NOTE: *The e-closure includes the state itself plus all states reachable via epsilon.*
void calculate_Epsilon_Closures() {
    for (int i = 0; i < num_states; i++) {
        epsilon_closures[i] = (1 << i); // A state's closure always includes itself.
        find_closure_recursive(i, &epsilon_closures[i]);
    }
    printf("Epsilon closures calculated.\n");
}

// --- Task 3: Compute the new transitions of the NFA without ε --------------------------------------------------
// NOTE: *This uses the formula: δ'(q, a) = ε-closure( U_{p ∈ ε-closure(q)} δ(p, a) )*
void compute_New_Transitions() {
    memset(new_transitions, 0, sizeof(new_transitions));

    // For each state q
    for (int q = 0; q < num_states; q++) {
        // For each symbol 'a' in the alphabet
        for (int a_idx = 0; a_idx < num_symbols; a_idx++) {
            int intermediate_states = 0;
            // Find all states p in e-closure(q)
            for (int p = 0; p < num_states; p++) {
                if (epsilon_closures[q] & (1 << p)) {
                    // Union the transitions from p on symbol a
                    intermediate_states |= transitions[p][a_idx];
                }
            }

            int final_transition_states = 0;
            // For each state r in the intermediate set
            for (int r = 0; r < num_states; r++) {
                if (intermediate_states & (1 << r)) {
                    // Union the e-closure of r to get the final result
                    final_transition_states |= epsilon_closures[r];
                }
            }
            new_transitions[q][a_idx] = final_transition_states;
        }
    }
    printf("New transitions computed.\n");
}

// -- Task 4: Determine the new final states ---------------------------------------------------------------------
// NOTE: *A state is a new final state if its e-closure contains any of the original final states.*
void determine_New_Final_States() {
    num_new_final_states = 0;
    // For each state q
    for (int q = 0; q < num_states; q++) {
        int is_new_final = 0;
        // For each original final state
        for (int i = 0; i < num_final_states; i++) {
            // Check if the e-closure of q intersects with the final state set
            if (epsilon_closures[q] & (1 << final_states[i])) {
                is_new_final = 1;
                break;
            }
        }
        if (is_new_final) {
            new_final_states[num_new_final_states++] = q;
        }
    }
    printf("New final states determined.\n");
}

//HELPER FUN: function to print a set of states from its bitmask representation.
void print_state_set(int mask) {
    printf("{ "); 
    int first = 1; // Flag to handle commas between state numbers

    // Iterate through all possible states
    for (int i = 0; i < num_states; i++) {
        // Check if state 'i' is included in the mask
        if (mask & (1 << i)) {
            // Print comma before state number if it's not the first element
            if (!first) {
                printf(", ");
            }
            printf("%d", i); // Print the state number
            first = 0;       // Clear the first-element flag
        }
    }

    // If no states were printed, the set is empty
    if (first) { 
        printf("Ø");
    }

    printf(" }"); // Close the set representation
}


// --Task 5: Display the new automaton --------------------------------------------------------------------------
void display_New_Automaton() {
    // Print all states
    printf("States: { ");
    for (int i = 0; i < num_states; i++) 
        printf("%d%s", i, (i == num_states - 1) ? "" : ", ");
    printf(" }\n");

    // Print the alphabet
    printf("Alphabet: { ");
    for (int i = 0; i < num_symbols; i++) 
        printf("'%c'%s", alphabet[i], (i == num_symbols - 1) ? "" : ", ");
    printf(" }\n");

    // Print the initial state
    printf("Initial State: %d\n", initial_state);

    // Print the final states
    printf("Final States: ");
    int final_mask = 0;
    // Create a bitmask representing all new final states
    for(int i = 0; i < num_new_final_states; i++) 
        final_mask |= (1 << new_final_states[i]);
    // Print the final states using print_state_set
    print_state_set(final_mask);
    printf("\n");
    // Optionally, print epsilon-closures for reference
    printf("\n------------------------------------");
    printf("\nEpsilon Closures for reference:\n");
    printf("------------------------------------\n");
    for(int i = 0; i < num_states; i++) {
        printf("e-closure(%d) = ", i);
        print_state_set(epsilon_closures[i]);
        printf("\n");
    }
    printf("------------------------------------\n");
    // Print all transitions of the new automaton
    printf("------------------------------------\n");
    printf("Transitions:\n");
    printf("------------------------------------\n");
    printf("From\tSymbol\tTo\n");
    printf("------------------------------------\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            if (new_transitions[i][j] != 0) {
                // Print the source state and the symbol
                printf("%d\t'%c'\t", i, alphabet[j]);
                // Print the set of destination states
                print_state_set(new_transitions[i][j]);
                printf("\n");
            }
        }
    }
    printf("------------------------------------\n");

}

