%{
    #include <iostream>
    // #define DEBUG 1
    #include "A6_30_translator.h"
    using namespace std;

    extern int yylex();                     // From lexer
    void yyinfo(string s); 
    void yyerror(string s);                 // Function to report errors
    extern char* yytext;                    // From lexer, gives the text being currently scanned
    extern int yylineno;                    // Used for keeping track of the line number

    extern int nextinstr;                   // Used for keeping track of the next instruction
    extern quadArray quadList;              // List of all quads
    extern symbolTable globalST;            // Global symbol table
    extern symbolTable* ST;                 // Pointer to the current symbol table
    extern vector<string> stringConsts;     // List of all string constants

    int strCount = 0;                       // Counter for string constants
    expression* tmpForBool;
%}

%union {
    int intval;                     // For an integer value
    char charval;                   // For a char value
    float floatval;                 // For a float value
    void* ptr;                      // For a pointer
    string* str;                    // For a string
    symbolType* symType;            // For the type of a symbol
    symbol* symp;                   // For a symbol
    DataType types;                 // For the type of an expression
    opcode opc;                     // For an opcode
    expression* expr;               // For an expression
    declaration* dec;               // For a declaration
    vector<declaration*> *decList;  // For a list of declarations
    param* prm;                     // For a parameter
    vector<param*> *prmList;        // For a list of parameters
}

/*
    All tokens
*/
%token  CHAR_ ELSE FOR IF  INT_  RETURN_  VOID_  WHILE   
%token SQUARE_BRACE_OPEN SQUARE_BRACE_CLOSE PARENTHESIS_OPEN PARENTHESIS_CLOSE CURLY_BRACE_OPEN CURLY_BRACE_CLOSE 
%token DOT ARROW BITWISE_AND MULTIPLY ADD_ SUBTRACT BITWISE_NOR NOT DIVIDE MODULO 
%token LESS_THAN GREATER_THAN LESS_THAN_EQUAL GREATER_THAN_EQUAL EQUAL NOT_EQUAL  
%token LOGICAL_AND LOGICAL_OR QUESTION_MARK COLON SEMICOLON  
%token ASSIGN_  COMMA 

// Identifiers are treated with type str
%token <str> IDENTIFIER

// Integer constants have a type intval
%token <intval> INTEGER_CONSTANT

// Character constants have a type charval
%token <charval> CHAR_CONSTANT

// String literals have a type str
%token <str> STRING_LITERAL

// Non-terminals of type expr (denoting expressions)
%type <expr> 
        expression
        primary_expression 
        multiplicative_expression
        additive_expression
        relational_expression
        equality_expression
        logical_and_expression
        logical_or_expression
        conditional_expression
        assignment_expression
        postfix_expression
        unary_expression
        expression_statement
        statement
        compound_statement
        selection_statement
        iteration_statement
        jump_statement
        block_item
        block_item_list
        initializer
        M
        N

// Non-terminals of type charval (unary operator)
%type <charval> unary_operator

// The pointer non-terminal is treated with type intval
%type <intval> pointer

// Non-terminals of type DataType (denoting types)
%type <types> type_specifier 

// Non-terminals of type declaration
%type <dec> direct_declarator init_declarator declarator function_prototype intermediate_identifier intermediate_declarator

// Non-terminals of type decList
%type <decList> init_declarator_list

// Non-terminals of type param
%type <prm> parameter_declaration

// Non-terminals of type prmList
%type <prmList> parameter_list  parameter_list_opt argument_expression_list

// Helps in removing the dangling else problem
%expect 1
%nonassoc ELSE

// The start symbol is translation_unit
%start translation_unit

%%

primary_expression: 
        IDENTIFIER
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("primary_expression -> IDENTIFIER\n");
            $$ = new expression();  // Create new expression
            string s = *($1);
            ST->lookup(s);          // Store entry in the symbol table
            $$->loc = s;            // Store pointer to string identifier name
        }
        | INTEGER_CONSTANT
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("primary_expression -> INTEGER_CONSTANT\n");
            $$ = new expression();                  // Create new expression
            $$->loc = ST->gentemp(INT);             // Generate a new temporary variable
            emit($$->loc, $1, ASSIGN);
            symbolValue* val = new symbolValue();
            val->setInitVal($1);                    // Set the initial value
            ST->lookup($$->loc)->initVal = val;     // Store in symbol table
        }
        | CHAR_CONSTANT
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("primary_expression -> CHAR_CONSTANT\n");
            $$ = new expression();                  // Create new expression
            $$->loc = ST->gentemp(CHAR);            // Generate a new temporary variable
            emit($$->loc, $1, ASSIGN);
            symbolValue* val = new symbolValue();
            val->setInitVal($1);                    // Set the initial value
            ST->lookup($$->loc)->initVal = val;     // Store in symbol table
        }
        | STRING_LITERAL
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("primary_expression -> STRING_LITERAL\n");
            $$ = new expression();                  // Create new expression
            $$->loc = ".LC" + to_string(strCount++);
            stringConsts.push_back(*($1));          // Add to the list of string constants
        }
        | PARENTHESIS_OPEN expression PARENTHESIS_CLOSE
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("primary_expression -> PARENTHESIS_OPEN expression PARENTHESIS_CLOSE\n");
            $$ = $2;                                // Simple assignment
            // if($2->type == "bool") 
            //     tmpForBool = $2;
        }
        ;

postfix_expression: 
        primary_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("postfix_expression -> primary_expression\n");}
        | postfix_expression SQUARE_BRACE_OPEN expression SQUARE_BRACE_CLOSE
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("postfix_expression -> postfix_expression SQUARE_BRACE_OPEN expression SQUARE_BRACE_CLOSE\n");
            symbolType to = ST->lookup($1->loc)->type;      // Get the type of the expression
            string f = "";
            if(!($1->fold)) {
                f = ST->gentemp(INT);                       // Generate a new temporary variable
                emit(f, 0, ASSIGN);
                $1->folder = new string(f);
            }
            string temp = ST->gentemp(INT);

            // Emit the necessary quads
            emit(temp, $3->loc, "", ASSIGN);
            emit(temp, temp, "4", MULT);
            emit(f, temp, "", ASSIGN);
            $$ = $1;
        }
        | postfix_expression PARENTHESIS_OPEN PARENTHESIS_CLOSE
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("postfix_expression -> postfix_expression PARENTHESIS_OPEN PARENTHESIS_CLOSE\n");
            // Corresponds to calling a function with the function name but without any arguments
            symbolTable* funcTable = globalST.lookup($1->loc)->nestedTable;
            emit($1->loc, "0", "", CALL);
        }
        | postfix_expression PARENTHESIS_OPEN argument_expression_list PARENTHESIS_CLOSE
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("postfix_expression -> postfix_expression PARENTHESIS_OPEN argument_expression_list PARENTHESIS_CLOSE\n");
            // Corresponds to calling a function with the function name and the appropriate number of arguments
            symbolTable* funcTable = globalST.lookup($1->loc)->nestedTable;
            vector<param*> parameters = *($3);                          // Get the list of parameters
            vector<symbol*> paramsList = funcTable->symbols;

            for(int i = 0; i < (int)parameters.size(); i++) {
                emit(parameters[i]->name, "", "", PARAM);               // Emit the parameters
            }

            DataType retType = funcTable->lookup("RETVAL")->type.type;  // Add an entry in the symbol table for the return value
            if(retType == VOID)                                         // If the function returns void
                emit($1->loc, (int)parameters.size(), CALL);
            else {                                                      // If the function returns a value
                string retVal = ST->gentemp(retType);
                emit($1->loc, to_string(parameters.size()), retVal, CALL);
                $$ = new expression();
                $$->loc = retVal;
            }
        }
        | postfix_expression DOT IDENTIFIER
        {yyinfo(yytext );yyinfo(":     ");yyinfo("postfix_expression -> postfix_expression DOT IDENTIFIER\n");}
        | postfix_expression ARROW IDENTIFIER
        {yyinfo(yytext );yyinfo(":     ");yyinfo("postfix_expression -> postfix_expression DOT IDENTIFIER\n");}
        ;

argument_expression_list: 
        assignment_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("argument_expression_list -> assignment_expression\n");
            param* first = new param();                 // Create a new parameter
            first->name = $1->loc;
            first->type = ST->lookup($1->loc)->type;
            $$ = new vector<param*>;
            $$->push_back(first);                       // Add the parameter to the list
        }
        | argument_expression_list COMMA assignment_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("argument_expression_list -> argument_expression_list COMMA assignment_expression\n");
            param* next = new param();                  // Create a new parameter
            next->name = $3->loc;
            next->type = ST->lookup(next->name)->type;
            $$ = $1;
            $$->push_back(next);                        // Add the parameter to the list
        }
        ;

unary_expression: 
        postfix_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("unary_expression -> postfix_expression\n");}
        | unary_operator unary_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("unary_expression -> unary_operator unary_expression\n");
            // Case of unary operator
            switch($1) {
                case '&':   // Address
                    $$ = new expression();
                    $$->loc = ST->gentemp(POINTER);                 // Generate temporary of the same base type
                    emit($$->loc, $2->loc, "", REFERENCE);          // Emit the quad
                    break;
                case '*':   // De-referencing
                    $$ = new expression();
                    $$->loc = ST->gentemp(INT);                     // Generate temporary of the same base type
                    $$->fold = 1;
                    $$->folder = new string($2->loc);
                    emit($$->loc, $2->loc, "", DEREFERENCE);        // Emit the quad
                    break;
                case '-':   // Unary minus
                    $$ = new expression();
                    $$->loc = ST->gentemp();                        // Generate temporary of the same base type
                    emit($$->loc, $2->loc, "", U_MINUS);            // Emit the quad
                    break;
                case '!':   // Logical not 
                    $$ = new expression();
                    $$->loc = ST->gentemp(INT);                     // Generate temporary of the same base type
                    int temp = nextinstr + 2;
                    emit(to_string(temp), $2->loc, "0", GOTO_EQ);   // Emit the quads
                    temp = nextinstr + 3;
                    emit(to_string(temp), "", "", GOTO);
                    emit($$->loc, "1", "", ASSIGN);
                    temp = nextinstr + 2;
                    emit(to_string(temp), "", "", GOTO);
                    emit($$->loc, "0", "", ASSIGN);
                    break;
            }
        }
        ;

unary_operator:
        BITWISE_AND
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("unary_operator -> BITWISE_AND\n");
            $$ = '&';
        }
        | MULTIPLY
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("unary_operator -> MULTIPLY\n");
            $$ = '*';
        }
        | ADD_
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("unary_operator -> ADD_\n");
            $$ = '+';
        }
        | SUBTRACT
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("unary_operator -> SUBTRACT\n");
            $$ = '-';
        }
        | NOT
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("unary_operator -> NOT\n");
            $$ = '!';
        }
        ;

multiplicative_expression: 
        unary_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("multiplicative_expression -> unary_expression\n");
            $$ = new expression();                                  // Generate new expression
            symbolType tp = ST->lookup($1->loc)->type;
            if(tp.type == ARRAY) {                                  // If the type is an array
                string t = ST->gentemp(tp.nextType);                // Generate a temporary
                if($1->folder != NULL) {
                    emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);   // Emit the necessary quad
                    $1->loc = t;
                    $1->type = tp.nextType;
                    $$ = $1;
                }
                else
                    $$ = $1;        // Simple assignment
            }
            else
                $$ = $1;            // Simple assignment
        }
        | multiplicative_expression MULTIPLY unary_expression
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("multiplicative_expression -> multiplicative_expression MULTIPLY unary_expression\n");
            // Indicates multiplication
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }

            // Assign the result of the multiplication to the higher data type
            DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
            $$->loc = ST->gentemp(final);                       // Store the final result in a temporary
            emit($$->loc, $1->loc, $3->loc, MULT);
        }
        | multiplicative_expression DIVIDE unary_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("multiplicative_expression -> multiplicative_expression DIVIDE unary_expression\n");
            // Indicates division
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }

            // Assign the result of the division to the higher data type
            DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
            $$->loc = ST->gentemp(final);                       // Store the final result in a temporary
            emit($$->loc, $1->loc, $3->loc, DIV);
        }
        | multiplicative_expression MODULO unary_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("multiplicative_expression -> multiplicative_expression MODULO unary_expression\n");
            // Indicates modulo
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }

            // Assign the result of the modulo to the higher data type
            DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
            $$->loc = ST->gentemp(final);                       // Store the final result in a temporary
            emit($$->loc, $1->loc, $3->loc, MOD);
        }
        ;

additive_expression: 
        multiplicative_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("additive_expression -> multiplicative_expression\n");}
        | additive_expression ADD_ multiplicative_expression
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("additive_expression -> additive_expression ADD_ multiplicative_expression\n");
            // Indicates addition
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }

            // Assign the result of the addition to the higher data type
            DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
            $$->loc = ST->gentemp(final);                       // Store the final result in a temporary
            emit($$->loc, $1->loc, $3->loc, ADD);
        }
        | additive_expression SUBTRACT multiplicative_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("additive_expression -> additive_expression SUBTRACT multiplicative_expression\n");
            // Indicates subtraction
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }

            // Assign the result of the subtraction to the higher data type
            DataType final = ((one->type.type > two->type.type) ? (one->type.type) : (two->type.type));
            $$->loc = ST->gentemp(final);                       // Store the final result in a temporary
            emit($$->loc, $1->loc, $3->loc, SUB);
        }
        ;


relational_expression: 
        additive_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("relational_expression -> additive_expression\n");}
        | relational_expression LESS_THAN additive_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("relational_expression -> relational_expression LESS_THAN additive_expression\n");
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }
            $$ = new expression();
            $$->loc = ST->gentemp();
            $$->type = BOOL;                                    // Assign the result of the relational expression to a boolean
            emit($$->loc, "1", "", ASSIGN);
            $$->truelist = makelist(nextinstr);                 // Set the truelist to the next instruction
            emit("", $1->loc, $3->loc, GOTO_LT);                // Emit "if x < y goto ..."
            emit($$->loc, "0", "", ASSIGN);
            $$->falselist = makelist(nextinstr);                // Set the falselist to the next instruction
            emit("", "", "", GOTO);                             // Emit "goto ..."
        }
        | relational_expression GREATER_THAN additive_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("relational_expression -> relational_expression GREATER_THAN additive_expression\n");
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }
            $$ = new expression();
            $$->loc = ST->gentemp();
            $$->type = BOOL;                                    // Assign the result of the relational expression to a boolean
            emit($$->loc, "1", "", ASSIGN);
            $$->truelist = makelist(nextinstr);                 // Set the truelist to the next instruction
            emit("", $1->loc, $3->loc, GOTO_GT);                // Emit "if x > y goto ..."
            emit($$->loc, "0", "", ASSIGN);
            $$->falselist = makelist(nextinstr);                // Set the falselist to the next instruction
            emit("", "", "", GOTO);                             // Emit "goto ..."
        }
        | relational_expression LESS_THAN_EQUAL additive_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("relational_expression -> relational_expression LESS_THAN_EQUAL additive_expression\n");
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }
            $$ = new expression();
            $$->loc = ST->gentemp();
            $$->type = BOOL;                                    // Assign the result of the relational expression to a boolean
            emit($$->loc, "1", "", ASSIGN);
            $$->truelist = makelist(nextinstr);                 // Set the truelist to the next instruction
            emit("", $1->loc, $3->loc, GOTO_LTE);               // Emit "if x <= y goto ..."
            emit($$->loc, "0", "", ASSIGN);
            $$->falselist = makelist(nextinstr);                // Set the falselist to the next instruction
            emit("", "", "", GOTO);                             // Emit "goto ..."
        }
        | relational_expression GREATER_THAN_EQUAL additive_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("relational_expression -> relational_expression GREATER_THAN_EQUAL additive_expression\n");
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }
            $$ = new expression();
            $$->loc = ST->gentemp();
            $$->type = BOOL;                                    // Assign the result of the relational expression to a boolean
            emit($$->loc, "1", "", ASSIGN);
            $$->truelist = makelist(nextinstr);                 // Set the truelist to the next instruction
            emit("", $1->loc, $3->loc, GOTO_GTE);               // Emit "if x >= y goto ..."
            emit($$->loc, "0", "", ASSIGN);
            $$->falselist = makelist(nextinstr);                // Set the falselist to the next instruction
            emit("", "", "", GOTO);                             // Emit "goto ..."
        }
        ;

equality_expression: 
        relational_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("equality_expression -> relational_expression\n");
            $$ = new expression();
            $$ = $1;                // Simple assignment
        }
        | equality_expression EQUAL relational_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("equality_expression -> equality_expression EQUAL relational_expression\n");
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }
            $$ = new expression();
            $$->loc = ST->gentemp();
            $$->type = BOOL;                                    // Assign the result of the relational expression to a boolean
            emit($$->loc, "1", "", ASSIGN);
            $$->truelist = makelist(nextinstr);                 // Set the truelist to the next instruction
            emit("", $1->loc, $3->loc, GOTO_EQ);                // Emit "if x == y goto ..."
            emit($$->loc, "0", "", ASSIGN);
            $$->falselist = makelist(nextinstr);                // Set the falselist to the next instruction
            emit("", "", "", GOTO);                             // Emit "goto ..."
        }
        | equality_expression NOT_EQUAL relational_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("equality_expression -> equality_expression NOT_EQUAL relational_expression\n");
            $$ = new expression();
            symbol* one = ST->lookup($1->loc);                  // Get the first operand from the symbol table
            symbol* two = ST->lookup($3->loc);                  // Get the second operand from the symbol table
            if(two->type.type == ARRAY) {                       // If the second operand is an array, perform necessary operations
                string t = ST->gentemp(two->type.nextType);
                emit(t, $3->loc, *($3->folder), ARR_IDX_ARG);
                $3->loc = t;
                $3->type = two->type.nextType;
            }
            if(one->type.type == ARRAY) {                       // If the first operand is an array, perform necessary operations
                string t = ST->gentemp(one->type.nextType);
                emit(t, $1->loc, *($1->folder), ARR_IDX_ARG);
                $1->loc = t;
                $1->type = one->type.nextType;
            }
            $$ = new expression();
            $$->loc = ST->gentemp();
            $$->type = BOOL;                                    // Assign the result of the relational expression to a boolean
            emit($$->loc, "1", "", ASSIGN);
            $$->truelist = makelist(nextinstr);                 // Set the truelist to the next instruction
            emit("", $1->loc, $3->loc, GOTO_NEQ);               // Emit "if x != y goto ..."
            emit($$->loc, "0", "", ASSIGN);
            $$->falselist = makelist(nextinstr);                // Set the falselist to the next instruction
            emit("", "", "", GOTO);                             // Emit "goto ..."
        }
        ;

logical_and_expression: 
        equality_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("logical_and_expression -> equality_expression\n");}
        | logical_and_expression LOGICAL_AND M equality_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("logical_and_expression -> logical_and_expression LOGICAL_AND M equality_expression\n");
            /*
                Here, we have augmented the grammar with the non-terminal M to facilitate backpatching
            */
            backpatch($1->truelist, $3->instr);                     // Backpatching
            $$->falselist = merge($1->falselist, $4->falselist);    // Generate falselist by merging the falselists of $1 and $4
            $$->truelist = $4->truelist;                            // Generate truelist from truelist of $4
            $$->type = BOOL;                                        // Set the type of the expression to boolean
        }
        ;

logical_or_expression: 
        logical_and_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("logical_or_expression -> logical_and_expression\n");}
        | logical_or_expression LOGICAL_OR M logical_and_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("logical_or_expression -> logical_or_expression LOGICAL_OR M logical_and_expression\n");
            backpatch($1->falselist, $3->instr);                    // Backpatching
            $$->truelist = merge($1->truelist, $4->truelist);       // Generate falselist by merging the falselists of $1 and $4
            $$->falselist = $4->falselist;                          // Generate truelist from truelist of $4
            $$->type = BOOL;                                        // Set the type of the expression to boolean
        }
        ;

conditional_expression: 
        logical_or_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("conditional_expression -> logical_or_expression\n");
            $$ = $1;    // Simple assignment
        }
        | logical_or_expression N QUESTION_MARK M expression N COLON M conditional_expression
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("conditional_expression -> logical_or_expression N QUESTION_MARK M expression N COLON M conditional_expression\n");
            /*
                Note the augmented grammar with the non-terminals M and N
            */
            symbol* one = ST->lookup($5->loc);
            $$->loc = ST->gentemp(one->type.type);      // Create a temporary for the expression
            $$->type = one->type.type;
            emit($$->loc, $9->loc, "", ASSIGN);         // Assign the conditional expression
            list<int> temp = makelist(nextinstr);
            emit("", "", "", GOTO);                     // Prevent fall-through
            backpatch($6->nextlist, nextinstr);         // Backpatch with nextinstr
            emit($$->loc, $5->loc, "", ASSIGN);
            temp = merge(temp, makelist(nextinstr));
            emit("", "", "", GOTO);                     // Prevent fall-through
            backpatch($2->nextlist, nextinstr);         // Backpatch with nextinstr
            convertIntToBool($1);                       // Convert the expression to boolean
            backpatch($1->truelist, $4->instr);         // When $1 is true, control goes to $4 (expression)
            backpatch($1->falselist, $8->instr);        // When $1 is false, control goes to $8 (conditional_expression)
            backpatch($2->nextlist, nextinstr);         // Backpatch with nextinstr
        }
        ;

M: %empty
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("M\n");
            // Stores the next instruction value, and helps in backpatching
            $$ = new expression();
            $$->instr = nextinstr;
        }
        ;

N: %empty
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("N\n");
            // Helps in control flow
            $$ = new expression();
            $$->nextlist = makelist(nextinstr);
            emit("", "", "", GOTO);
        }
        ;

assignment_expression: 
        conditional_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("assignment_expression -> conditional_expression\n");}
        | unary_expression assignment_operator assignment_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("assignment_expression -> unary_expression assignment_operator assignment_expression\n");
            symbol* sym1 = ST->lookup($1->loc);         // Get the first operand from the symbol table
            symbol* sym2 = ST->lookup($3->loc);         // Get the second operand from the symbol table
            if($1->fold == 0) {
                if(sym1->type.type != ARRAY)
                    emit($1->loc, $3->loc, "", ASSIGN);
                else
                    emit($1->loc, $3->loc, *($1->folder), ARR_IDX_RES);
            }
            else
                emit(*($1->folder), $3->loc, "", L_DEREF);
            $$ = $1;        // Assignment 
        }
        ;

assignment_operator: 
        ASSIGN_
        {yyinfo(yytext );yyinfo(":     ");yyinfo("assignment_operator -> ASSIGN_\n");}
        ;

expression: 
        assignment_expression
        {yyinfo(yytext );yyinfo(":     ");yyinfo("expression -> ASSIGN_\n");}
        ;


declaration: 
        type_specifier init_declarator_list SEMICOLON
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("declaration -> type_specifier init_declarator_list SEMICOLON\n");
            DataType currType = $1;
            int currSize = -1;
            // Assign correct size for the data type
            if(currType == INT)
                currSize = __INTEGER_SIZE;
            else if(currType == CHAR)
                currSize = __CHARACTER_SIZE;
            vector<declaration*> decs = *($2);
            for(vector<declaration*>::iterator it = decs.begin(); it != decs.end(); it++) {
                declaration* currDec = *it;
                if(currDec->type == FUNCTION) {
                    ST = &globalST;
                    emit(currDec->name, "", "", FUNC_END);
                    symbol* one = ST->lookup(currDec->name);        // Create an entry for the function
                    symbol* two = one->nestedTable->lookup("RETVAL", currType, currDec->pointers);
                    one->size = 0;
                    one->initVal = NULL;
                    continue;
                }

                symbol* three = ST->lookup(currDec->name, currType);        // Create an entry for the variable in the symbol table
                three->nestedTable = NULL;
                if(currDec->li == vector<int>() && currDec->pointers == 0) {
                    three->type.type = currType;
                    three->size = currSize;
                    if(currDec->initVal != NULL) {
                        string rval = currDec->initVal->loc;
                        emit(three->name, rval, "", ASSIGN);
                        three->initVal = ST->lookup(rval)->initVal;
                    }
                    else
                        three->initVal = NULL;
                }
                else if(currDec->li != vector<int>()) {         // Handle array types
                    three->type.type = ARRAY;
                    three->type.nextType = currType;
                    three->type.dims = currDec->li;
                    vector<int> temp = three->type.dims;
                    int sz = currSize;
                    for(int i = 0; i < (int)temp.size(); i++)
                        sz *= temp[i];
                    ST->offset += sz;
                    three->size = sz;
                    ST->offset -= 4;
                }
                else if(currDec->pointers != 0) {               // Handle pointer types
                    three->type.type = POINTER;
                    three->type.nextType = currType;
                    three->type.pointers = currDec->pointers;
                    ST->offset += (__POINTER_SIZE - currSize);
                    three->size = __POINTER_SIZE;
                }
            }
        }

        ;



init_declarator_list: 
        init_declarator
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("init_declarator_list -> init_declarator\n");
            $$ = new vector<declaration*>;      // Create a vector of declarations and add $1 to it
            $$->push_back($1);
        }
        | init_declarator_list COMMA init_declarator
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("init_declarator_list -> init_declarator_list COMMA init_declarator\n");
            $1->push_back($3);                  // Add $3 to the vector of declarations
            $$ = $1;
        }
        ;

init_declarator: 
        declarator
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("init_declarator -> declarator\n");
            $$ = $1;
            $$->initVal = NULL;         // Initialize the initVal to NULL as no initialization is done
        }
        | declarator ASSIGN_ initializer
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("init_declarator -> declarator ASSIGN_ initializer\n");
            $$ = $1;
            $$->initVal = $3;           // Initialize the initVal to the value provided
        }
        ;

type_specifier: 
        VOID_
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("type_specifier -> VOID_\n");
            $$ = VOID;
        }
        | CHAR_
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("type_specifier -> CHAR_\n");
            $$ = CHAR;
        }
        | INT_
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("type_specifier -> INT_\n");
            $$ = INT; 
        }
        ;


declarator: 
        pointer direct_declarator
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("declarator -> pointer direct_declarator\n");
            $$ = $2;
            $$->pointers = $1;
        }
        | direct_declarator
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("declarator -> direct_declarator\n");
            $$ = $1;
            $$->pointers = 0;
        }
        ;

intermediate_identifier:
        IDENTIFIER
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("intermediate_identifier -> IDENTIFIER\n");
            $$ = new declaration();
            $$->name = *($1);
        }
        ;

direct_declarator: 
        IDENTIFIER
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("direct_declarator -> IDENTIFIER\n");
            $$ = new declaration();
            $$->name = *($1);
        }
        | intermediate_identifier SQUARE_BRACE_OPEN INTEGER_CONSTANT SQUARE_BRACE_CLOSE
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("direct_declarator -> intermediate_identifier SQUARE_BRACE_OPEN INTEGER_CONSTANT SQUARE_BRACE_CLOSE\n");
            $1->type = ARRAY;       // Array type
            $1->nextType = INT;     // Array of ints
            $$ = $1;
            // int index = ST->lookup($3->loc)->initVal->i;
            int index = $3;   //-->changed

            $$->li.push_back(index);
        }
        | intermediate_identifier PARENTHESIS_OPEN parameter_list_opt PARENTHESIS_CLOSE
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("direct_declarator -> intermediate_identifier PARENTHESIS_OPEN parameter_list_opt PARENTHESIS_CLOSE\n");
            $$ = $1;
            $$->type = FUNCTION;    // Function type
            symbol* funcData = ST->lookup($$->name, $$->type);
            symbolTable* funcTable = new symbolTable();
            funcData->nestedTable = funcTable;
            vector<param*> paramList = *($3);   // Get the parameter list
            for(int i = 0; i < (int)paramList.size(); i++) {
                param* curParam = paramList[i];
                if(curParam->type.type == ARRAY) {          // If the parameter is an array
                    funcTable->lookup(curParam->name, curParam->type.type);
                    funcTable->lookup(curParam->name)->type.nextType = INT;
                    funcTable->lookup(curParam->name)->type.dims.push_back(0);
                }
                else if(curParam->type.type == POINTER) {   // If the parameter is a pointer
                    funcTable->lookup(curParam->name, curParam->type.type);
                    funcTable->lookup(curParam->name)->type.nextType = INT;
                    funcTable->lookup(curParam->name)->type.dims.push_back(0);
                }
                else                                        // If the parameter is a anything other than an array or a pointer
                    funcTable->lookup(curParam->name, curParam->type.type);
            }
            ST = funcTable;         // Set the pointer to the symbol table to the function's symbol table
            emit($$->name, "", "", FUNC_BEG);
        }
        ;

parameter_list_opt:
        parameter_list
        {yyinfo(yytext );yyinfo(":     ");yyinfo("parameter_list_opt -> parameter_list\n");}
        | %empty
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("parameter_list_opt -> \n");
            $$ = new vector<param*>;
        }
        ;

pointer: 
        MULTIPLY
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("pointer -> MULTIPLY\n");
            $$ = 1;
        }
        ;

parameter_list: 
        parameter_declaration
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("parameter_list -> parameter_declaration\n");
            $$ = new vector<param*>;         // Create a new vector of parameters
            $$->push_back($1);              // Add the parameter to the vector
        }
        | parameter_list COMMA parameter_declaration
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("parameter_list -> parameter_list COMMA parameter_declaration\n");
            $1->push_back($3);              // Add the parameter to the vector
            $$ = $1;
        }
        ;
intermediate_declarator:
        pointer intermediate_identifier
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("intermediate_declarator -> pointer intermediate_identifier\n");
            $$ = $2;
            $$->pointers = $1;
        }
        | intermediate_identifier
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("intermediate_declarator -> intermediate_identifier\n");
            $$ = $1;
            $$->pointers = 0;
        }
        ;

parameter_declaration: 
        type_specifier intermediate_declarator
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("parameter_declaration -> type_specifier intermediate_declarator\n");
            $$ = new param();
            $$->name = $2->name;
            if($2->type == ARRAY) {
                $$->type.type = ARRAY;
                $$->type.nextType = $1;
            }
            else if($2->pc != 0) {
                $$->type.type = POINTER;
                $$->type.nextType = $1;
            }
            else
                $$->type.type = $1;
        }
        | type_specifier
        {yyinfo(yytext );yyinfo(":     ");yyinfo("parameter_declaration -> type_specifier\n");}
        ;


initializer: 
        assignment_expression
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("initializer -> assignment_expression\n");
            $$ = $1;   // Simple assignment
        }
        ;


statement: 
        compound_statement{yyinfo(yytext );yyinfo(":     ");yyinfo("statement -> compound_statement\n");}
        | expression_statement{yyinfo(yytext );yyinfo(":     ");yyinfo("statement -> expression_statement\n");}
        | selection_statement{yyinfo(yytext );yyinfo(":     ");yyinfo("statement -> selection_statement\n");}
        | iteration_statement{yyinfo(yytext );yyinfo(":     ");yyinfo("statement -> iteration_statement\n");}
        | jump_statement{yyinfo(yytext );yyinfo(":     ");yyinfo("statement -> jump_statement\n");}
        ;



compound_statement: 
        CURLY_BRACE_OPEN CURLY_BRACE_CLOSE
        {yyinfo(yytext );yyinfo(":     ");yyinfo("compound_statement -> CURLY_BRACE_OPEN CURLY_BRACE_CLOSE\n");}
        | CURLY_BRACE_OPEN block_item_list CURLY_BRACE_CLOSE
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("compound_statement -> CURLY_BRACE_OPEN block_item_list CURLY_BRACE_CLOSE\n");
            $$ = $2;
        }
        ;

block_item_list: 
        block_item
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("block_item_list -> block_item\n");
            $$ = $1;    // Simple assignment
            backpatch($1->nextlist, nextinstr);
        }
        | block_item_list M block_item
        {   
            yyinfo(yytext );yyinfo(":     ");yyinfo("block_item_list -> block_item_list M block_item\n");
            /*
                This production rule has been augmented with the non-terminal M
            */
            $$ = new expression();
            backpatch($1->nextlist, $2->instr);    // After $1, move to block_item via $2
            $$->nextlist = $3->nextlist;
        }
        ;

block_item: 
        declaration
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("block_item -> declaration\n");
            $$ = new expression();   // Create new expression
        }
        | statement{yyinfo(yytext );yyinfo(":     ");yyinfo("block_item -> statement\n");}
        ;

expression_statement: 
        expression SEMICOLON
        {yyinfo(yytext );yyinfo(":     ");yyinfo("expression_statement -> expression SEMICOLON\n");}
        | SEMICOLON
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("expression_statement -> SEMICOLON\n");
            $$ = new expression();  // Create new expression
        }
        ;

selection_statement: 
        IF PARENTHESIS_OPEN expression N PARENTHESIS_CLOSE M statement N
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("selection_statement -> IF PARENTHESIS_OPEN expression N PARENTHESIS_CLOSE M statement N\n");
            /*
                This production rule has been augmented for control flow
            */
            backpatch($4->nextlist, nextinstr);         // nextlist of N now has nextinstr
            convertIntToBool($3);                       // Convert expression to bool
            backpatch($3->truelist, $6->instr);         // Backpatching - if expression is true, go to M
            $$ = new expression();                      // Create new expression
            // Merge falselist of expression, nextlist of statement and nextlist of the last N
            $7->nextlist = merge($8->nextlist, $7->nextlist);
            $$->nextlist = merge($3->falselist, $7->nextlist);
        }
        | IF PARENTHESIS_OPEN expression N PARENTHESIS_CLOSE M statement N ELSE M statement N
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("selection_statement -> IF PARENTHESIS_OPEN expression N PARENTHESIS_CLOSE M statement N ELSE M statement N\n");
            /*
                This production rule has been augmented for control flow
            */
            backpatch($4->nextlist, nextinstr);         // nextlist of N now has nextinstr
            convertIntToBool($3);                       // Convert expression to bool
            backpatch($3->truelist, $6->instr);         // Backpatching - if expression is true, go to first M, else go to second M
            backpatch($3->falselist, $10->instr);
            $$ = new expression();                      // Create new expression
            // Merge nextlist of statement, nextlist of N and nextlist of the last statement
            $$->nextlist = merge($7->nextlist, $8->nextlist);
            $$->nextlist = merge($$->nextlist, $11->nextlist);
            $$->nextlist = merge($$->nextlist, $12->nextlist);
        }
        ;

iteration_statement: 
         FOR PARENTHESIS_OPEN expression_statement M expression_statement N M expression N PARENTHESIS_CLOSE M statement
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("iteration_statement -> FOR PARENTHESIS_OPEN expression_statement M expression_statement N M expression N PARENTHESIS_CLOSE M statement\n");
            /*
                This production rule has been augmented with non-terminals like M and N to handle the control flow and backpatching
            */
            $$ = new expression();                   // Create a new expression
            emit("", "", "", GOTO);
            $12->nextlist = merge($12->nextlist, makelist(nextinstr - 1));
            backpatch($12->nextlist, $7->instr);    // Backpatching - go to the beginning of the loop
            backpatch($9->nextlist, $4->instr);     
            backpatch($6->nextlist, nextinstr);     
            convertIntToBool($5);                   // Convert expression to bool
            backpatch($5->truelist, $11->instr);    // Backpatching - if expression is true, go to M
            $$->nextlist = $5->falselist;           // Exit loop if expression is false
        }
        ;

jump_statement: 
        RETURN_ SEMICOLON
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("jump_statement -> RETURN_ SEMICOLON\n");
            if(ST->lookup("RETVAL")->type.type == VOID) {
                emit("", "", "", RETURN);           // Emit the quad when return type is void
            }
            $$ = new expression();
        }
        | RETURN_ expression SEMICOLON
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("jump_statement -> RETURN_ expression SEMICOLON\n");
            if(ST->lookup("RETVAL")->type.type == ST->lookup($2->loc)->type.type) {
                emit($2->loc, "", "", RETURN);      // Emit the quad when return type is not void
            }
            $$ = new expression();
        }
        ;

translation_unit: 
        external_declaration
        {yyinfo(yytext );yyinfo(":     ");yyinfo("translation_unit -> external_declaration\n");}
        | translation_unit external_declaration
        {yyinfo(yytext );yyinfo(":     ");yyinfo("translation_unit -> translation_unit external_declaration\n");}
        ;

external_declaration: 
        function_definition
        {yyinfo(yytext );yyinfo(":     ");yyinfo("external_declaration -> function_definition\n");}
        | declaration
        {yyinfo(yytext );yyinfo(":     ");yyinfo("external_declaration -> declaration\n");}
        ;

function_definition: 
        type_specifier declarator declaration_list compound_statement
        {yyinfo(yytext );yyinfo(":     ");yyinfo("function_definition -> type_specifier declarator declaration_list compound_statement\n");}
        | function_prototype compound_statement
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("function_definition -> unction_prototype compound_statement\n");
            ST = &globalST;                     // Reset the symbol table to global symbol table
            emit($1->name, "", "", FUNC_END);
        }
        ;

function_prototype:
        type_specifier declarator
        {
            yyinfo(yytext );yyinfo(":     ");yyinfo("function_prototype -> type_specifier declarator\n");
            DataType currType = $1;
            int currSize = -1;
            if(currType == CHAR)
                currSize = __CHARACTER_SIZE;
            if(currType == INT)
                currSize = __INTEGER_SIZE;
            declaration* currDec = $2;
            symbol* sym = globalST.lookup(currDec->name);
            if(currDec->type == FUNCTION) {
                symbol* retval = sym->nestedTable->lookup("RETVAL", currType, currDec->pointers);   // Create entry for return value
                sym->size = 0;
                sym->initVal = NULL;
            }
            $$ = $2;
        }
        ;

declaration_list: 
        declaration
        {yyinfo(yytext );yyinfo(":     ");yyinfo("declaration_list -> declaration\n");}
        | declaration_list declaration
        {yyinfo(yytext );yyinfo(":     ");yyinfo("declaration_list -> declaration_list declaration\n");}
        ;

%%

void yyerror(string s) {
    /*
        This function prints any error encountered while parsing
    */
    cout << "Error occurred: " << s << endl;
    cout << "Line no.: " << yylineno << endl;
    cout << "Unable to parse: " << yytext << endl; 
}

void yyinfo(string s) {
    #ifdef DEBUG
        cout << s;
    #endif
}
