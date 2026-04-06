# Elementary Cellular Automaton 🔲

A 1D binary cellular automata simulator built in C, implementing all 256 
of Wolfram's elementary rules. A single active cell evolves across 
generations in a 65-cell wrapped world, producing surprisingly complex 
patterns from simple rules.

## What is Cellular Automata?
Elementary cellular automata are one of the simplest models of computation 
— a row of cells, each either alive (1) or dead (0), evolves over time 
based on a rule applied to each cell and its two neighbors. Despite their 
simplicity, some rules (like the famous Rule 110) are capable of 
universal computation.

This project simulates all 256 possible rule sets, numbered 0–255 in 
Wolfram's classification system.

## Features
- Simulates all 256 Wolfram elementary rules (0–255)
- 65-cell world with wrap-around boundaries
- Starts from a single active center cell
- Prints each generation as a visual row of characters
- Compact, efficient implementation in C

## Example Output
```
Rule 30:
                                *
                               ***
                              **  *
                             ** ****
                            **  *   *
                           ** **** ***
```

## Concepts Demonstrated
- Bitwise operations and binary rule encoding
- Array-based state simulation
- Modular (wrap-around) indexing
- Iterative generation stepping
- Low-level C programming and memory efficiency

## How to Run
```bash
gcc -o automaton main.c
./automaton <rule_number>
# Example:
./automaton 30
./automaton 110
```

## Language
- **C**

## Why This Project Stands Out
Cellular automata sit at the intersection of computer science, mathematics, 
and complexity theory. Building this simulator required understanding binary 
rule encoding and clean state management using skills that transfer directly 
to systems programming and algorithm design.

---
