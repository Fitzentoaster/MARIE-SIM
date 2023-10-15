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

# SIMULATOR INSTRUCTIONS
Once it's compiled (I haven't included binaries but it should compile with anything, I've tested it using G++ on Windows) it's a simple command line program where the first argument is the machine language code to run.
I've called them .mri files for now, but it should take any extension you like. I might change the extension, I have no idea if it's already in use. The program should run the machine code provided, and output
any output to the console, then dump the main memory and registers upon completion. 

# ASSEMBLER INSTRUCTIONS
The code is wonky and needs a lot of work, but the assembler WIP will assemble code in the right format successfully. It's based loosely on IBM Assembler format but modified
for my own purposes and to make it easier to work. To use it once it's compiled, the first argument is the input file (the assembly code to assemble) and the second argument is the output location.
NOTE The assembler is in a very early testing phase. Don't get mad that the code is so wonky!

## Format
- Labels go in column 1, prefaced with a hashtag(#)
- Operations go in column 10, in all CAPS:
-    Possible instructions are: JNS, LOAD, STORE, ADD, SUBT, INPUT, OUTPUT, HALT, SKIPCOND, JUMP, CLEAR, ADDI, JUMPI
- Addresses go in column 20, in 3-hex digit format, or indirectly as a label, prefaced with a hashtag(#)
- Constants or machine code go in column 10, just like operations, but prefaced with a bang(!)
- Lines starting with a * are ignored, this is exclusive to comments
- Blank lines are NOT ALLOWED, including at the end of the file!
- Addresses are required, even for instructions that don't use them... this is going to change
- SKIPCOND is an interesting instruction: it only uses the beginning of the address provided. So the valid 'addresses' are 000 for skip on neg, 400 for skip on zero, and 800 for skip on pos, respectively.

You can find an example of this Marie Assembly I've Cooked Up (MAICU) in the .mra files in the assembler folder. The multassembler.mra is the best example of how to format
assembly code for this all-too-basic assembler.
