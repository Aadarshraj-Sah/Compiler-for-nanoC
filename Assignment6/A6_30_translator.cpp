
#include "A6_30_translator.h"
#include <iomanip>
using namespace std;

// Initialize the global variables
int nextinstr = 0;

// Intiailize the static variables
int symbolTable::tempCount = 0;

quadArray quadList;
symbolTable globalST;
symbolTable* ST;


// Implementations of constructors and functions for the symbolValue class
void symbolValue::setInitVal(int val) {
    c = val;
    f = val;
    i = val;
    p = NULL;
}

void symbolValue::setInitVal(char val) {
    c = val;
    f = val;
    i = val;
    p = NULL;
}

void symbolValue::setInitVal(float val) {
    c = val;
    f = val;
    i = val;
    p = NULL;
}


// Implementations of constructors and functions for the symbol class
symbol::symbol(): nestedTable(NULL) {}


// Implementations of constructors and functions for the symbolTable class
symbolTable::symbolTable(): offset(0) {}

symbol* symbolTable::lookup(string name, DataType t, int pc) {
    
    if(table.count(name) != 0) {
        
    }
    else{
        symbol* sym = new symbol();
        sym->name = name;
        sym->type.type = t;
        sym->offset = offset;
        sym->initVal = NULL;

        if(pc != 0) {
            
            sym->size = __POINTER_SIZE;
            sym->type.nextType = t;
            sym->type.pointers = pc;
            sym->type.type = ARRAY;
        }
        else {
            sym->size = sizeOfType(t);
            offset += sym->size;
        }
        symbols.push_back(sym);
        table[name] = sym;
    }
    return table[name];
}

symbol* symbolTable::searchGlobal(string name) {
    return (table.count(name) ? table[name] : NULL);
}

string symbolTable::gentemp(DataType t) {
    // Create the name for the temporary
    string tempName = "t" + to_string(symbolTable::tempCount++);
    
    // Initialize the required attributes
    symbol* sym = new symbol();
    sym->name = tempName;
    sym->size = sizeOfType(t);
    sym->offset = offset;
    sym->type.type = t;
    sym->initVal = NULL;

    offset += sym->size;
    symbols.push_back(sym);
    table[tempName] = sym;  // Add the temporary to the symbol table

    return tempName;
}

void symbolTable::print(string tableName) {
    int i=0;
    while(i<120){
        cout << '-';
        i++;
    }
    cout << "\n";
    cout << "Symbol Table: " << setfill(' ') << left << setw(50) << tableName << "\n";
    for(int i = 0; i < 120; i++)
        cout << '-';
    cout << "\n";

    // Table Headers
    cout << setfill(' ') << left << setw(25) <<  "Name";
    cout << left << setw(25) << "Type";
    cout << left << setw(20) << "Initial Value";
    cout << left << setw(15) << "Size";
    cout << left << setw(15) << "Offset";
    cout << left << "Nested" << "\n";

    i=0;
    while(i<120){
        cout << '-';
        i++;
    }
    cout << "\n";

    // For storing nested symbol tables
    vector<pair<string, symbolTable*>> tableList;

    // Print the symbols in the symbol table
    i=0;
    while(i < (int)symbols.size()) {
        symbol* sym = symbols[i];
        cout << left << setw(25) << sym->name;
        cout << left << setw(25) << checkType(sym->type);
        cout << left << setw(20) << getInitVal(sym);
        cout << left << setw(15) << sym->size;
        cout << left << setw(15) << sym->offset;
        cout << left;

        if(sym->nestedTable != NULL) {
            string nestedTableName = tableName + "." + sym->name;
            cout << nestedTableName << "\n";
            tableList.push_back({nestedTableName, sym->nestedTable});
        }
        else
            cout << "NULL" << "\n";

        i++;
    }

    i=0;
    while(i<120){
        cout << '-';
        i++;
    }
    cout << "\n" << "\n";

    // Recursively call the print function for the nested symbol tables
    vector<pair<string, symbolTable*>>::iterator it = tableList.begin();
    while( it != tableList.end()) {
        pair<string, symbolTable*> p = (*it);
        p.second->print(p.first);
        it++;
    }

}


// Implementations of constructors and functions for the quad class
quad::quad(string res_, string arg1_, string arg2_, opcode op_): op(op_), arg1(arg1_), arg2(arg2_), result(res_) {}

string quad::print() {
    string out = "";
    if(op >= ADD && op <= BW_XOR) {                 // Binary operators
        out += (result + " = " + arg1 + " ");
        if (op == ADD) {
            out += "+";
        } else if (op == SUB) {
            out += "-";
        } else if (op == MULT) {
            out += "*";
        } else if (op == DIV) {
            out += "/";
        } else if (op == MOD) {
            out += "%";
        } else if (op == SL) {
            out += "<<";
        } else if (op == SR) {
            out += ">>";
        } else if (op == BW_AND) {
            out += "&";
        } else if (op == BW_OR) {
            out += "|";
        } else if (op == BW_XOR) {
            out += "^";
        }
        out += (" " + arg2);
    }
    else if(op >= BW_U_NOT && op <= U_NEG) {        // Unary operators
        out += (result + " = ");
        if (op == BW_U_NOT) {
            out += "~";
        } else if (op == U_PLUS) {
            out += "+";
        } else if (op == U_MINUS) {
            out += "-";
        } else if (op == REFERENCE) {
            out += "&";
        } else if (op == DEREFERENCE) {
            out += "*";
        } else if (op == U_NEG) {
            out += "!";
        }
        out += arg1;
    }
    else if(op >= GOTO_EQ && op <= IF_FALSE_GOTO) { // Conditional operators
        out += ("if " + arg1 + " ");
        if (op == GOTO_EQ) {
            out += "==";
        } else if (op == GOTO_NEQ) {
            out += "!=";
        } else if (op == GOTO_GT) {
            out += ">";
        } else if (op == GOTO_GTE) {
            out += ">=";
        } else if (op == GOTO_LT) {
            out += "<";
        } else if (op == GOTO_LTE) {
            out += "<=";
        } else if (op == IF_GOTO) {
            out += "!= 0";
        } else if (op == IF_FALSE_GOTO) {
            out += "== 0";
        }
        out += (" " + arg2 + " goto " + result);
    }
    else if(op >= CtoI && op <= CtoF) {             // Type Conversion functions
        out += (result + " = ");

        if (op == CtoI) {
            out += "CharToInt";
        } else if (op == ItoC) {
            out += "IntToChar";
        } else if (op == FtoI) {
            out += "FloatToInt";
        } else if (op == ItoF) {
            out += "IntToFloat";
        } else if (op == FtoC) {
            out += "FloatToChar";
        } else if (op == CtoF) {
            out += "CharToFloat";
        }

        out += ("(" + arg1 + ")");
    }

    else if(op == ASSIGN)                       // Assignment operator
        out += (result + " = " + arg1);
    else if(op == GOTO)                         // Goto
        out += ("goto " + result);
    else if(op == RETURN)                       // Return from a function
        out += ("return " + result);
    else if(op == PARAM)                        // Parameters for a function
        out += ("param " + result);
    else if(op == CALL) {                       // Call a function
        if(arg2.size() > 0)
            out += (arg2 + " = ");
        out += ("call " + result + ", " + arg1);
    }
    else if(op == ARR_IDX_ARG)                  // Array indexing
        out += (result + " = " + arg1 + "[" + arg2 + "]");
    else if(op == ARR_IDX_RES)                  // Array indexing
        out += (result + "[" + arg2 + "] = " + arg1);
    else if(op == FUNC_BEG)                     // Function begin
        out += (result + ": ");
    else if(op == FUNC_END) {                   // Function end
        out += ("function " + result + " ends");
    }
    else if(op == L_DEREF)                      // Dereference
        out += ("*" + result + " = " + arg1);

    return out;
}


// Implementations of constructors and functions for the quadArray class
void quadArray::print() {
    int i = 0;
    while (i < 120) {
        cout << '-';
        i++;
    }

    cout << "\n";
    cout << "THREE ADDRESS CODE (TAC):" << "\n";
    i = 0;
    while (i < 120) {
        cout << '-';
        i++;
    }
    cout << "\n";

    // Print each of the quads one by one
    i=0;
    while(i < (int)quads.size()) {
        if(quads[i].op != FUNC_BEG && quads[i].op != FUNC_END)
            cout << left << setw(4) << i << ":    ";
        else if(quads[i].op == FUNC_BEG)
            cout << "\n" << left << setw(4) << i << ": ";
        else if(quads[i].op == FUNC_END)
            cout << left << setw(4) << i << ": ";
        cout << quads[i].print() << "\n";
        i++;
    }
    cout << "\n";
}


// Implementations of constructors and functions for the expression class
expression::expression(): fold(0), folder(NULL) {}


// Overloaded emit functions
void emit(string result, string arg1, string arg2, opcode op) {
    quad q(result, arg1, arg2, op);
    quadList.quads.push_back(q);
    nextinstr++;
}

void emit(string result, int constant, opcode op) {
    quad q(result, to_string(constant), "", op);
    quadList.quads.push_back(q);
    nextinstr++;
}

void emit(string result, char constant, opcode op) {
    quad q(result, to_string(constant), "", op);
    quadList.quads.push_back(q);
    nextinstr++;
}

void emit(string result, float constant, opcode op) {
    quad q(result, to_string(constant), "", op);
    quadList.quads.push_back(q);
    nextinstr++;
}


// Implementation of the makelist function
list<int> makelist(int i) {
    list<int> l(1, i);
    return l;
}

// Implementation of the merge function
list<int> merge(list<int> list1, list<int> list2) {
    list1.merge(list2);
    return list1;
}

// Implementation of the backpatch function
void backpatch(list<int> l, int address) {
    string str = to_string(address);
    list<int>::iterator it = l.begin();
    while(it != l.end()) {
        quadList.quads[*it].result = str;
        it++;
    }
}


// Implementation of the overloaded convertToType functions
void convertToType(expression* arg, expression* res, DataType toType) {
    if(res->type == toType)
        return;

    switch (res->type) {
        case INT:
            switch (toType) {
                case CHAR:
                    emit(arg->loc, res->loc, "", ItoC);
                    break;
            }
            break;
        case CHAR:
            switch (toType) {
                case INT:
                    emit(arg->loc, res->loc, "", CtoI);
                    break;
            }
            break;
        default:
            break;
    }


}

void convertToType(string t, DataType to, string f, DataType from) {
    if(to == from)
        return;  
    switch (from) {
        case INT:
            switch (to) {
                case CHAR:
                    emit(t, f, "", ItoC);
                    break;
            }
            break;
        case CHAR:
            switch (to) {
                case INT:
                    emit(t, f, "", CtoI);
                    break;
            }
            break;
    }

}

// Implementation of the convertIntToBool function
void convertIntToBool(expression* expr) {
    if(expr->type != BOOL) {
        expr->type = BOOL;
        expr->falselist = makelist(nextinstr);    // Add falselist for boolean expressions
        emit("", expr->loc, "", IF_FALSE_GOTO);
        expr->truelist = makelist(nextinstr);     // Add truelist for boolean expressions
        emit("", "", "", GOTO);
    }
}

// Implementation of the sizeOfType function
int sizeOfType(DataType t) {

    switch (t) {
        case VOID:
            return __VOID_SIZE;
        case CHAR:
            return __CHARACTER_SIZE;
        case INT:
            return __INTEGER_SIZE;
        case POINTER:
            return __POINTER_SIZE;
        case FUNCTION:
            return __FUNCTION_SIZE;
        default:
            return 0;
    }

}

// Implementation of the checkType function
string checkType(symbolType t) {

    switch(t.type) {
        case VOID:
            return "void";
        case CHAR:
            return "char";
        case INT:
            return "int";
        case FUNCTION:
            return "function";
        case POINTER:
            {
                string tp = "";
                if(t.nextType == CHAR)
                    tp += "char";
                else if(t.nextType == INT)
                    tp += "int";
                tp += string(t.pointers, '*');
                return tp;
            }
        case ARRAY:
            {
                string tp = "";
                if(t.nextType == CHAR)
                    tp += "char";
                else if(t.nextType == INT)
                    tp += "int";
                vector<int> dim = t.dims;
                for(int i = 0; i < (int)dim.size(); i++) {
                    if(dim[i])
                        tp += "[" + to_string(dim[i]) + "]";
                    else
                        tp += "[]";
                }
                if((int)dim.size() == 0)
                    tp += "[]";
                return tp;
            }
        default:
            return "unknown";
    }

}

// Implementation of the getInitVal function
string getInitVal(symbol* sym) {
    if(sym->initVal != NULL) {
        switch(sym->type.type) {
            case CHAR:
                return to_string(sym->initVal->c);
            case INT:
                return to_string(sym->initVal->i);
            default:
                return "-";
            }
        
    }
    else{
        return "-";
    }
        
}
