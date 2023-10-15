# MARIE-SIM
A constantly WIP Simulator for the MARIE architecture

# What is MARIE?
MARIE, standing for Machine Architecture that is Really Intuitive and Easy, is an educational, theoretical machine architecture
created by Linda Null and Julia Lobur. 

# Why are you making this?
As of the initial commit in October of 2023, I'm in a Computer Systems and Architecture course at Northern Illinois University
that is taking a look at this architecture, and I'm working on this simulation for my own self-improvement to understand
the architecture more deeply and to work on my C++ skills. 

# Other Options
As of the initial posting, this software only supports hex machine code in a strict format (now there's an assembler!), and a lack of bugs is far from guaranteed.
For more robust options including an assembly language, check out https://marie.js.org/

# ASSEMBLER INSTRUCTIONS
The code is wonky and needs a lot of work, but the assembler WIP will assemble code in the right format successfully. It's based loosely on IBM Assembler format but modified
for my own purposes and to make it easier to work.

## Format
- Labels go in column 1, prefaced with a hashtag(#)
- Operations go in column 10, in all CAPS:
-    Possible instructions are: JNS, LOAD, STORE, ADD, SUBT, INPUT, OUTPUT, HALT, SKIPCOND, JUMP, CLEAR, ADDI, JUMPI
- Addresses go in column 20, in 3-hex digit format, or indirectly as a label, prefaced with a hashtag(#)
- Constants or machine code go in column 10, just like operations, but prefaced with a bang(!)
- Lines starting with a * are ignored, this is exclusive to comments
- Blank lines are NOT ALLOWED, including at the end of the file!

You can find an example of this Marie Assembly I've Cooked Up (MAICU) in the .mra files in the assembler folder. The multassembler.mra is the best example of how to format
assembly code for this all-too-basic assembler.
