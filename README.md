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

##  ** 📖 How to Run **

1. **Compilation**: Use the GCC compiler to build the executable.
   Download the file `main.c` and in the terminal input:

   ```bash
   gcc main.c -o nfa_converter
2. **Execution**: Run the generated program.
   
   ```bash
   ./nfa_converter

## ** 🚀 Example Run **

To help you test the program, here is a sample input and output and the expected interaction flow. You can follow this example to verify the Epsilon-NFA to NFA conversion.

### **Sample Input Data:**

<img width="3050" height="2274" alt="temp-20-43-31-image_upscayl_4x_upscayl-standard-4x" src="https://github.com/user-attachments/assets/c912a289-74a7-4332-8f8f-0f7ea6c89557" />

### **Sample Output Data:**

<img width="2646" height="2160" alt="Screenshot 2025-12-24 204710_upscayl_4x_upscayl-standard-4x" src="https://github.com/user-attachments/assets/16ff8cff-3e43-432f-87d8-182f256e9819" />
<img width="2450" height="21450" alt="temp-20-48-13-image_upscayl_4x_upscayl-standard-4x" src="https://github.com/user-attachments/assets/802e1160-fa94-4b74-ac63-aa844f0b1371" />




