# Compiler-for-nanoC
In a series of four assignments we intend to implement a compiler for a C-like language. To keep the problem tractable, we present a very small subset nanoC of C that is easy to manage and yet has most of the key flavours of C.
The implementation of the compiler for nanoC is split into 4 assignments as follows:

* **Assignment 3** : Lexical Analyzer for nanoC using Flex. The lexical grammar specification is given here.  
* **Assignment 4** : Parser for nanoC using Bison. The phase structure grammar specification is given in Assignment 3.  
* **Assignment 5** : Machine-Independent Code Generator for nanoC using syntax-directed translation with Bison. Three-Address (intermediate) Code (TAC) used as target of translation is explained here.  
* **Assignment 6** : Target Code Generator for nanoC by simple code generation by table lookup. The target processor is taken to be x86 and a subset of its assembly language is presented here for use.  

### Lexical Analysis Using Flex:

**Tokenization:**  
Flex generates lexical analyzers for breaking code into tokens/lexemes.
Rules define patterns using regular expressions and associated actions.

**Regular Expressions:**  
Lexical rules utilize regular expressions to describe token patterns.
These patterns guide the recognition of tokens in the source code.

**Efficiency and Customization:**  
Flex-generated analyzers are efficient, employing techniques like finite automata.
Allows customization to adapt lexical analysis for specific language requirements.


### Parsing Using Bison:

**Syntax Analysis:**  
Bison generates parsers for syntax analysis in language processing.
Defines grammar rules to recognize the structure of source code.

**Grammar Rules:**  
Bison rules describe the syntax of the language using context-free grammar.
Specifies how different components of the language can be combined.
Bottom-up parsing with LALR (Look Ahead Left to Right parsing)

**Actions and Semantics:**  
Actions associated with grammar rules execute when parsing matches occur.
Handles semantic aspects, such as building an Abstract Syntax Tree (AST).


### Machine Independent Code Generation:

**Symbol Table generation:**   
Symbols anf their Address is stored. 
Global Symbol Table and Local Symbol Tables.
Various Functions like lookup, update etc.

**Three Address Code Generation (TAC):** 

**Quad Table Generation:** 
opcode , assignment1, assignment2, result.
Various Functions like emit, print etc.

### Target Code Generation:
target _translator.c file outputs the .asm file with the the help of Symbol Table and Quad Table.



