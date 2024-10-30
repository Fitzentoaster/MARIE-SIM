# MARIE-SIM
A Simulator and Assembler for the MARIE architecture
https://www.youtube.com/watch?v=V6Am1hbYUD4

# What is MARIE?
MARIE, standing for Machine Architecture that is Really Intuitive and Easy, is an educational, theoretical machine architecture
created by Linda Null and Julia Lobur. 

# Why are you making this?
As of the initial commit(s) in October of 2023, I was in a Computer Systems and Architecture course at Northern Illinois University
that was taking a look at this architecture. I'm working on this simulation for my own self-improvement to understand
the architecture more deeply, to learn more about assembly and computer architecture in general, and to work on my C++ skills. 

# SIMULATOR INSTRUCTIONS
Once it's compiled (I haven't included binaries but it should compile with anything, I've tested it using G++ on Windows and Linux) it's a simple command line program where the first argument is the machine language code to run.
I've called them .mri files for now, but it should take any extension you like. The program should run the machine code provided, and output
any output to the console, then dump the main memory and registers upon completion. 

# ASSEMBLER INSTRUCTIONS
The assembly language is based loosely on IBM Assembler format but modified
for my own purposes and to make it easier to work with on my end. To use it once it's compiled, the first argument is the input file (the assembly code to assemble) and the second argument is the output location.

## Format
- Labels go in column 1, prefaced with a hashtag(#)
- Operations go in column 10, in all CAPS:
-    Possible instructions are: JNS, LOAD, STORE, ADD, SUBT, INPUT, OUTPUT, HALT, SKIPCOND, JUMP, CLEAR, ADDI, JUMPI
- Addresses go in column 20, in 3-hex digit format, or indirectly as a label, prefaced with a hashtag(#)
- Constants or machine code go in column 10, just like operations, but prefaced with a bang(!)
- Lines starting with a * are ignored, this is exclusive to comments
- Blank lines are NOT ALLOWED, including at the end of the file!
- Addresses are not required for INPUT, OUTPUT, HALT, and CLEAR
- SKIPCOND is an interesting instruction: it only uses the beginning of the address provided. So the valid 'addresses' are 000 for skip on neg, 400 for skip on zero, and 800 for skip on pos, respectively.

You can find an example of this Marie Assembly I've Cooked Up (MAICU) in the .mra files in the assembler folder. The files betterintdivision.mra (for integer division) and gosub2.mra (for subroutines) will give you
examples of most of what you need to program in MAICU
