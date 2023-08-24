#include <map>
#include <iomanip>
using namespace std;
// Header File for declaring Data Structures (Class Definitions) 
// & Global Function Prototypes

#ifndef __ASSN5_TRANSLATOR_H__
#define __ASSN5_TRANSLATOR_H__


#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;

// Declaration of size of basic data types

#define _SIZE_VOID      0        // void : 0 bytes
#define _SIZE_CHAR      1        // char : 1 byte
#define _SIZE_INT       4        // int  : 4 bytes
#define _SIZE_POINTER   4        // pointer: 4 bytes
#define _SIZE_FUNCTION  0        // function: 0 bytes


/* Class Declarations*/

class Symbol;        // An instance of Symbol class represents an element in the symbol table
class SymbolType;    // SymbolType class represents the type of a symbol
class SymbolTable;   // SymbolTable class represents the symbol table data structure

class Quad;          // An instance of Quad class represents a quadruple used in TAC generation
class QuadArray;     // represents the list of quads 

// class Expression;    // represents an expression used in the grammar as a non-terminal
// class Array;         // An instance of Array class represents an array type
// class Statement;    // represents a statement used in the grammar as a non-terminal

// Declaration of Global Variables

extern Symbol* currentSym;   // ptr to current symbol
extern SymbolTable* SymTbl_Global;   // ptr to global symbol table
extern SymbolTable* SymTbl_Current;    // ptr to currently active symbol table
extern QuadArray QuadList;  // list of Quads
extern int SymTbl_Count;    // count for naming nested symbol tables
extern string BlockName;    // variable for naming nested blocks in symbol table

extern  char* yytext;   // import the yytext variable (which stores the lexeme) from the lexer
extern  int yyparse();  // import the yyparse() function from bison parser


// ##################### Class definitions and member functions ##################

// class to represent symbol type
class SymbolType{
    public:
        string type;   // type of symbol (i.e, E.type)
        int width;     // width of symbol in bytes (i.e, E.width)
        SymbolType* arrElementType;   // type of array elements

        // constructor method
        SymbolType(string type_, SymbolType* arrElementType_ = NULL, int width_ = 1);

};

// class to represent symbol
class Symbol{
    public:
        string name;    // name of symbol
        SymbolType* sym_type;   // type of symbol
        string val; // value of symbol initially
        int size;   // size of symbol in bytes
        int offset; // offset of symbol in the symbol table
        SymbolTable *nestedTblPtr; // ptr to nested symbol table, to be used for functions and blocks

        // constructor method
        Symbol(string name_, string sym_type_ = "int", SymbolType* arrType_ = NULL, int width_ = 0);
        
        // method to update the attributes of a symbol
        Symbol* update_symbol(SymbolType* type_new);  // update changes made to symbol

};


// class to represent symbol table data structure
class SymbolTable{
public:
    string name;    // name of symbol
    int tempVarCount;   // count to keep track of the number of temporary variables in symbol table
    list<Symbol> symTable;  // list of all symbols in symbol table
    SymbolTable* parent;    // pointer to the parent symbol table of the current symbol table 

    // constructor
    SymbolTable(string name_ = "NULL");

    // method to lookup a symbol in symbol table using symbol's lexeme
    // returns a pointer to the symbol if found, else creates a new symbol and returns a pointer to it
    Symbol* lookup(string sym_name);  

    // static method to generate a new temporary variable, insert it in the symbol table and return a ptr to it 
    static Symbol* gentemp(SymbolType* type, string initial_val = "");   // method to generate a tenporary variable, store it in symbol table and return pointer to it

    void print();   // method to print contents of symbol table
    void update();  // update the offsets of existing entries in the symbol table
};

//class to represent a Quad
class Quad {
public:
    string op;  // operator of the TAC
    string arg1;    // 1st argument of the TAC
    string arg2;    // 2nd argument of the TAC(if any)
    string result;  // variable to store result of the TAC

    // overloaded constructors for Quad (for different types of arguments)
    Quad(string res, string arg1_, string operation = "=", string arg2_ = "");
    Quad(string res, int arg1_, string operation = "=", string arg2_ = "");

    int print_quad();   // function to print quad
};


// class to represent array of quads
class QuadArray {
public:
    vector<Quad> quads;     // stores all generated quads in a vector
    
    int print();           // function to print all quads
};

// class to represent array type
class Array {
public:
    string arr_type;   // type of array
    Symbol* addr;      // base address of the array
    Symbol* array;     // pointer to the symbol table entry of the array
    SymbolType* type;  // type of the array, used for parsing of multi-dimensional arrays
};

// class to represent Statement, which is a non-terminal in the grammar
class Statement {
public:
    list<int> nextlist;     // statement's nextlist used for backpatching in control flow statements
};

//    Class to denote an Expression, which is a non-terminal in the grammar
class Expression {
public:
    string type;            // type of expression
    Symbol* addr;           // pointer to the symbol table entry of the expression
    list<int> truelist;     // expression's truelist used for backpatching for boolean expressions
    list<int> falselist;    // expression's falselist used for backpatching for boolean expressions
    list<int> nextlist;     // expression's nextlist used for backpatching in control flow statements
};


// ######################### Declaration of Helper Functions ######################

// function creates a new list containing an index i into the array of instructions
// and returns a pointer to the newly created list
list<int> makelist(int i);

// function merges two lists and returns a pointer to the merged list
list<int> merge(list<int> &list1, list<int> &list2);

// function to insert address as the target label for each of the instructions on the list l
void backpatch(list<int> l, int address);

//  An overloaded functon to add a new Quad of the form: result = arg1 op arg2 
//  overloaded for different types of arg1 (int, float or string)
void emit(string op, string result, string arg1 = "", string arg2 = "");
void emit(string op, string result, int arg1, string arg2 = "");


// function to check the compatibility of the types of symbols s1 and s2
// overloaded for symbol types t1 and t2
int typecheck(Symbol* &s1, Symbol* &s2);
int typecheck(SymbolType* t1, SymbolType* t2);

// function to print a type
string check_type(SymbolType* t);

//  function to convert an int to a bool
Expression* convertIntToBool(Expression* expr);

//  function to convert a bool to an int 
Expression* convertBoolToInt(Expression* expr);

// function to update the currently active symbol table to new_table
void switchTable(SymbolTable* new_table);

// function to return the count of the next instruction
int nextinstr();

// function to get the size of a type
int sizeOfType(SymbolType* t);

// Converts a symbol of one type to another and returns a pointer to the converted symbol
Symbol* convertType(Symbol* s, string t);


#endif

// Global variables as defined and explained in the header file
Symbol *currentSym;          // ptr to current symbol
SymbolTable *SymTbl_Global;  // ptr to global symbol table
SymbolTable *SymTbl_Current; // ptr to currently active symbol table
QuadArray QuadList;          // list of Quads
int SymTbl_Count;            // count for naming nested symbol tables
string BlockName;            // name of block
string prevType;             // Used for storing the last encountered type

// Implementations of constructors and functions for the SymbolType class
SymbolType::SymbolType(string type_, SymbolType *arrType_, int width_) : type(type_), arrElementType(arrType_), width(width_) {}

// Implementations of constructors and functions for the symbol class
Symbol::Symbol(string name_, string type_, SymbolType *arrType_, int width) : name(name_), val("-"), offset(0), nestedTblPtr(NULL)
{
    sym_type = new SymbolType(type_, arrType_, width);
    size = sizeOfType(sym_type);
}

Symbol *Symbol::update_symbol(SymbolType *type_)
{
    // Update the type and size for the symbol
    sym_type = type_;
    size = sizeOfType(type_);
    return this;
}

// Implementations of constructors and functions for the symbolTable class
SymbolTable::SymbolTable(string name_) : name(name_), tempVarCount(0) {}

Symbol *SymbolTable::lookup(string name_)
{
    // Start searching for the symbol in the symbol table
    // for (auto it = symTable.begin(); it != symTable.end(); it++)
    // {
    //     if (it->name == name_)
    //     {
    //         return &(*it);
    //     }
    // }
    auto it = symTable.begin();
    while(it != symTable.end())
    {
        if (it->name == name_)
        {
            return &(*it);
        }
        it++;
    }

    // If not found, search for the variable in the parent symbol tables
    Symbol *s = NULL;
    if (this->parent == NULL)
    {
        
    }
    else{
        s = this->parent->lookup(name_);
    }

    if (SymTbl_Current == this && s == NULL)
    {
        // If the symbol is still not found,
        // create the new symbol, add it to the symbol table and return a pointer to it
        Symbol *sym = new Symbol(name_);
        symTable.push_back(*sym);
        return &(symTable.back());
    }
    else 
    {
        // If the symbol is found in one of the parent symbol tables, return it
        if (s != NULL)
            return s;
        else return NULL;
    }

    return NULL;
}

// function to generate a temporary variable for the current symbol table
Symbol *SymbolTable::gentemp(SymbolType *t, string initial_val)
{
    // Create the name for the temporary
    string name = "t" + to_string(SymTbl_Current->tempVarCount++);
    Symbol *sym = new Symbol(name);
    sym->sym_type = t;
    sym->val = initial_val; // Assign the initial value, if any
    sym->size = sizeOfType(t);

    // Add the temporary to the symbol table
    SymTbl_Current->symTable.push_back(*sym);
    return &(SymTbl_Current->symTable.back());
}

// function to print the symbol table in an appropriate format

void SymbolTable::print()
{
    int i=0;
    while (i < 120)
    {
        cout << '-';
        i++;
    }
    cout << "\n";
    cout << "SYMBOL TABLE : " << setfill(' ') << left << setw(20) << this->name<<"\n";
    cout << "PARENT TABLE : " << setfill(' ') << left << setw(20) << ((this->parent != NULL) ? this->parent->name : "NULL") << "\n";
    i=0;
    while (i < 120)
    {
        cout << '-';
        i++;
    }
    cout << "\n";

    // Table Headers
    cout << setfill(' ') << left << setw(25) << "NAME";
    cout << left << setw(25) << "TYPE";
    cout << left << setw(25) << "INITIAL VALUE";
    cout << left << setw(15) << "SIZE";
    cout << left << setw(15) << "OFFSET";
    cout << left << "NESTED TABLE" << "\n";

    i=0;
    while (i < 120)
    {
        cout << '=';
        i++;
    }
    cout << "\n";

    list<SymbolTable *> tableList;

    // Print the symbols in the symbol table
    auto it = this->symTable.begin(); 
    while (it != this->symTable.end())
    {
        cout << left << setw(25) << it->name;
        cout << left << setw(25) << check_type(it->sym_type);
        cout << left << setw(25) << (it->val != "" ? it->val : "-");
        cout << left << setw(15) << it->size;
        cout << left << setw(15) << it->offset;
        cout << left;

        if (it->nestedTblPtr != NULL)
        {
            cout << it->nestedTblPtr->name << "\n";
            tableList.push_back(it->nestedTblPtr);
        }
        else
        {
            cout << "NULL" << "\n";
        }
        it++;
    }
    i=0;
    while (i < 120)
    {
        cout << '=';
        i++;
    }
    cout<<"\n"<<"\n"<<"\n"<<"\n";

    // Recursively call the print function for the nested symbol tables
    list<SymbolTable*>::iterator it1 = tableList.begin();
    while (it1 != tableList.end())
    {
        (*it1)->print();
        it1++;
    }
}

// function to update the symbol table
void SymbolTable::update()
{
    list<SymbolTable *> tableList;
    int offset_;

    // Update the offsets of the symbols based on their sizes
    list<Symbol>::iterator it = symTable.begin();
    while (it != symTable.end())
    {
        if(it != symTable.begin())
        {
            it->offset = offset_;
            offset_ = it->offset + it->size;
        }
        else
        {
            it->offset = 0;
            offset_ = it->size;
        }

        if (it->nestedTblPtr != NULL)
        {
            tableList.push_back(it->nestedTblPtr);
        }
        it++;
    }
    // Recursively call the update function to update the offsets of symbols of the nested symbol tables

    auto iter = tableList.begin();
    while(iter != tableList.end())
    {
        (*iter)->update();
        iter++;
    }
}

// Implementations of constructors and functions for the Quad class
Quad::Quad(string res, string arg1_, string operation, string arg2_) : result(res), arg1(arg1_), op(operation), arg2(arg2_) {}

Quad::Quad(string res, int arg1_, string operation, string arg2_) : result(res), op(operation), arg2(arg2_)
{
    arg1 = to_string(arg1_);
}



int Quad::print_quad()
{
    
    string pRemover="";
    if (op != "=") 
    {
        if(op != "=[]")
        {
            if (op != "*=")
            {
            if (op != "[]=")
                {
                    if (op == "goto" || op == "param" || op == "return")
                        pRemover = op + " " + result;
                    else if (op == "call")
                        pRemover = result + " = "
                            + "call " + arg1 + ", " + arg2;
                    else if (op == "label")
                        pRemover = result + ": ";

                    // Format to print unary operators
                    else if (op == "= &" || op == "= *" || op == "= -" || op == "= !")
                        pRemover = result + " " + op + arg1;

                    // Format to print binary operators
                    else if (op == "+" || op == "-" || op == "*" || op == "/" || op == "%" || op == "|" || op == "&" )
                        pRemover = result + " = " + arg1 + " " + op + " " + arg2;

                    // Format to print relational operators
                    else if (op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=")
                        pRemover = "if " + arg1 + " " + op + " " + arg2 + " goto " + result;
                    else
                        pRemover = "Invalid operator";
                }else pRemover = result + "[" + arg1 + "]" + " = " + arg2;
            }else pRemover = "*" + result + " = " + arg1;
        }
        else pRemover = result + " = " + arg1 + "[" + arg2 + "]";
    }
    else pRemover = result + " = " + arg1;
    cout<<pRemover;
    return 1;
}

// Implementations of constructors and functions for the quadArray class
int QuadArray::print()
{
    int x=0;
    while(x<30)
    {
        cout << '*';
        x++;
    }
    cout << "\n";
    cout << "GENERATED THREE-ADDRESS CODE :-" << "\n";
    x=0;
    while(x<30)
    {
        cout << '*';
        x++;
    }
    cout << "\n";

    int count = 0;

    // Print each of the quads one by one
    auto it = this->quads.begin();
    while (it != this->quads.end())
    {
        if (it->op != "label")
        {
            cout << left << setw(4) << count << ":    ";
            it->print_quad();
        }
        else
        {
            cout << "\n"
                 << left << setw(4) << count << ": ";
            it->print_quad();
        }
        cout << endl;
        it++; count++;
    }
    return 1;
}

// Implementation of the makelist function
list<int> makelist(int i)
{
    list<int> l(1, i);
    return l;
}

// Implementation of the merge function
list<int> merge(list<int> &list1, list<int> &list2)
{
    list1.merge(list2);
    return list1;
}

// Implementation of the backpatch function
void backpatch(list<int> l, int address)
{
    auto it = l.begin(); 
    while (it != l.end())
    {
        QuadList.quads[*it].result = to_string(address);
        it++;
    }

}

// Overloaded emit functions
void emit(string op, string result, string arg1, string arg2)
{
    Quad *q = new Quad(result, arg1, op, arg2);
    QuadList.quads.push_back(*q);
}

void emit(string op, string result, int arg1, string arg2)
{
    Quad *q = new Quad(result, arg1, op, arg2);
    QuadList.quads.push_back(*q);
}



// Implementation of the typecheck functions
int typecheck(Symbol *&s1, Symbol *&s2)
{
    SymbolType *t1 = s1->sym_type;
    SymbolType *t2 = s2->sym_type;

    if (typecheck(t1, t2))
        return 1;
    if (s1 = convertType(s1, t2->type))
        return 1;
    if (s2 = convertType(s2, t1->type))
        return 1;
    return 0;
}

int typecheck(SymbolType *t1, SymbolType *t2)
{

    if (t1 == NULL && t2 == NULL)
        return 1;
    if (t1 == NULL)
        return 0;
    if(t2 == NULL)
        return 0;
    if (t1->type != t2->type)
        return 0;

    return typecheck(t1->arrElementType, t2->arrElementType);
}

string check_type(SymbolType *type_)
{
    bool type1 = (type_->type == "void" || type_->type == "char" || type_->type == "int" || type_->type == "block" || type_->type == "func");
    bool type2 = (type_->type == "ptr");
    bool type3 = (type_->type == "arr");
    if (type_ == NULL)
        return "null";

    else if (type1)
        return type_->type;

    else if (type2)
        return "ptr(" + check_type(type_->arrElementType) + ")";

    else if (type3)
        return "arr(" + to_string(type_->width) + ", " + check_type(type_->arrElementType) + ")";

    else
        return "unknown";

}


// Implementation of the convertIntToBool functionS
Expression *convertIntToBool(Expression *expr)
{

    if (expr->type == "bool");
    else 
    {
        expr->falselist = makelist(nextinstr()); // Add falselist for boolean expressions
        emit("==", expr->addr->name, "0");
        expr->truelist = makelist(nextinstr()); // Add truelist for boolean expressions
        emit("goto", "");
    }
    return expr;
}

// Implementation of the convertBoolToInt function
Expression *convertBoolToInt(Expression *expr)
{
    if (expr->type != "bool");
    else if(expr->type == "bool")
    {
        expr->addr = SymbolTable::gentemp(new SymbolType("int"));
        backpatch(expr->truelist, nextinstr());
        emit("=", expr->addr->name, "true");
        emit("goto", to_string(nextinstr() + 1));
        backpatch(expr->falselist, nextinstr());
        emit("=", expr->addr->name, "false");
    }
    return expr;
}

void switchTable(SymbolTable *newTable)
{
    SymTbl_Current = newTable;
}

int nextinstr()
{
    int x = QuadList.quads.size();
    return x;
}

int sizeOfType(SymbolType *t)
{
    int ty = -1;
    if(t->type == "void")ty=0;
    if(t->type == "char")ty=1;
    if(t->type == "int")ty=2;
    if(t->type == "ptr")ty=3;
    if(t->type == "func")ty=4;


    int ret = -1;

    switch (ty)
    {
        case 0:
        ret =  _SIZE_VOID;
        break;

        case 1:
        ret = _SIZE_CHAR;
        break;

        case 2:
        ret = _SIZE_INT;
        break;

        case 3:
        ret = _SIZE_POINTER;
        break;

        case 4:
        ret = _SIZE_FUNCTION;
        break;


        default: 
        ret = -1;

    }
    return ret;
    
}

// Implementation of the convertType function
Symbol *convertType(Symbol *s, string t)
{
    Symbol *temp = SymbolTable::gentemp(new SymbolType(t));

    if(s->sym_type->type != "int")
    {
        if (s->sym_type->type != "char");
        else
        {
            
             if (t == "int")
            {
                emit("=", temp->name, "char2int(" + s->name + ")");
                return temp;
            }
            return s;
        }
    }
    else
    {
        
         if (t == "char")
        {
            emit("=", temp->name, "int2char(" + s->name + ")");
            return temp;
        }
        return s;
    }

    return s;
}

int main()
{
    SymTbl_Count = 0;                          // Initialize STCount to 0
    SymTbl_Global = new SymbolTable("Global"); // Create global symbol table
    SymTbl_Current = SymTbl_Global;            // Make global symbol table the currently active symbol table
    BlockName = "";

    yyparse();
    SymTbl_Global->update();
    QuadList.print(); // Print Three Address Code
    cout << "\n" << "\n";

    for (int i = 0; i < 40; i++)
    {
        cout << '*';
    }
    cout << "\n";
    cout << "GENERATED SYMBOL TABLES FOR EACH SCOPE:-" << "\n";
    for (int i = 0; i < 40; i++)
    {
        cout << '*';
    }
    cout << "\n" << "\n" << "\n";

    SymTbl_Global->print(); // Print symbol tables

    return 0;
}
