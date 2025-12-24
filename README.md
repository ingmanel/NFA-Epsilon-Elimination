# Elimination of Epsilon Transitions (ε-NFA to NFA)

##  ** Project Overview **

This project is a C implementation for the **Compiler Design** course.
It provides a tool to convert a Non-deterministic Finite Automaton with Epsilon transitions (ε-NFA) into an equivalent NFA without Epsilon transitions.

##  ** 👥 Team Members **

* **MALEG MANEL** - SEC G2
* **Wissal Hadjira** - SEC G2
* **Nadjah Belgouchi** - SEC G1

##  ** 🛠️ Key Features **

- **Epsilon Closure Calculation**: Uses a recursive DFS algorithm to find all reachable states.
- **Bitmask Representation**: Efficiently handles sets of states using bitwise operations.
- **Automata Transformation**: Implements the formal transformation rules for transition functions.
- **Interactive CLI**: Allows users to input their own NFA or run a pre-defined example.

##  ** 🚀 How to Run **

1. **Compilation**: Use the GCC compiler to build the executable.
   Download the file `main.c` and in the terminal input:

   ```bash
   gcc main.c -o nfa_converter
2. **Execution**: Run the generated program.
   
   ```bash
   ./nfa_converter
