%{
    #include <iostream>
    #include "A5_30_translator.h"
    // #define DEBUG 1
    using namespace std;

    extern int yylex();         // From lexer
    void yyinfo(string s); 
    void yyerror(string s);     // Function to report errors
    extern char* yytext;        // From lexer, gives the text being currently scanned
    extern int yylineno;        // Used for keeping track of the line number
    extern string prevType;      // Used for storing the last encountered type

    Expression* tmpForBool;
%}

%union {
    int intval;             // For an integer value
    char* charval;          // For a char value
    int instr;              // A special type for instruction number, needed in backpatching
    char unaryOp;           // For unary operators
    int numParams;          // For number of parameters to a function
    Expression* expr;       // For an expression
    Statement* stmt;        // For a statement
    Symbol* symptr;           // For a symbol
    SymbolType* symType;    // For the type of a symbol
    Array* arr;             // For arrays
}

/*
    All tokens
*/
%token CHAR ELSE FOR IF INT RETURN VOID  
%token LEFT_SQR_BRACKET RIGHT_SQR_BRACKET LEFT_PAREN RIGHT_PAREN LEFT_CURLY_BRACE RIGHT_CURLY_BRACE 
%token DOT ARROW BITWISE_AND MULTIPLY ADD SUBTRACT NOT DIVIDE MODULO 
%token  LESS_THAN GREATER_THAN LESS_THAN_EQUALS GREATER_THAN_EQUALS EQUALS NOT_EQUALS   
%token LOGICAL_AND LOGICAL_OR QUESTION_MARK COLON SEMICOLON  
%token ASSIGNMENT COMMA 

// Identifiers are treated with type Symbol*
%token <symptr> IDENTIFIER

// Integer constants have a type intval
%token <intval> INT_CONSTANT

// Character constants have a type charval
%token <charval> CHAR_CONSTANT

// String literals have a type charval
%token <charval> STRING_LITERAL

// The start symbol is translation_unit
%start translation_unit

// Helps in removing the dangling else problem
%right THEN ELSE

// Non-terminals of type unaryOp (unary operator)
%type <unaryOp> unary_operator

// Non-terminals of type numParams (number of parameters)
%type <numParams> argument_expression_list argument_expression_list_opt

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
        expression_statement

// Non-terminals of type stmt (denoting statements)
%type <stmt>
        statement
        compound_statement
        loop_statement
        selection_statement
        iteration_statement
        jump_statement
        block_item
        block_item_list
        block_item_list_opt

// The pointer non-terminal is treated with type symbolType
%type <symType> pointer

// Non-terminals of type symp (Symbol*)
%type <symptr> constant initializer
%type <symptr> intermediate_identifier direct_declarator init_declarator intermediate_declarator declarator

// Non-terminals of type arr
%type <arr> postfix_expression unary_expression 

// Auxiliary non-terminal M of type instr to help in backpatching
%type <instr> M

// Auxiliary non-terminal N of type stmt to help in control flow statements
%type <stmt> N

%%

primary_expression: 
        IDENTIFIER
        {
            yyinfo("primary_expression -> IDENTIFIER\n");
            $$ = new Expression();  // Create new expression
            $$->addr = $1;           // Store pointer to entry in the symbol table
            $$->type = "non_bool";
        }
        | constant
        {
            yyinfo("primary_expression -> constant\n");
            $$ = new Expression();  // Create new expression
            $$->addr = $1;           // Store pointer to entry in the symbol table
        }
        | STRING_LITERAL
        {
            yyinfo("primary_expression -> STRING_LITERAL\n");
            $$ = new Expression();  // Create new expression
            $$->addr = SymbolTable::gentemp(new SymbolType("ptr"), $1);  // Create a new temporary, and store the value in that temporary
            $$->addr->sym_type->arrElementType = new SymbolType("char");
        }
        | LEFT_PAREN expression RIGHT_PAREN
        {
            yyinfo("primary_expression -> LEFT_PAREN expression RIGHT_PAREN\n");
            $$ = $2;    // Simple assignment
            if($2->type == "bool") 
                tmpForBool = $2;
        }
        ;

constant: 
        INT_CONSTANT
        {
            yyinfo("constant -> INT_CONSTANT\n");
            $$ = SymbolTable::gentemp(new SymbolType("int"), to_string($1));   // Create a new temporary, and store the value in that temporary
            emit("=", $$->name, $1);
        }
        | CHAR_CONSTANT
        {
            yyinfo("constant -> CHAR_CONSTANT\n");
            $$ = SymbolTable::gentemp(new SymbolType("float"), string($1));     // Create a new temporary, and store the value in that temporary
            emit("=", $$->name, string($1));
        }
        ;

postfix_expression: 
        primary_expression
        {
            yyinfo("postfix_expression -> primary_expression\n");
            $$ = new Array();           // Create a new Array
            if($1->type != "bool")
            {$$->array = $1->addr;        // Store the location of the primary expression
            $$->type = $1->addr->sym_type;   // Update the type
            $$->addr = $$->array;}
            else
            {
                $$->arr_type = "bool_temporary";
            }

        }
        | postfix_expression LEFT_SQR_BRACKET expression RIGHT_SQR_BRACKET
        {
            yyinfo("postfix_expression -> postfix_expression LEFT_SQR_BRACKET expression RIGHT_SQR_BRACKET\n");
            $$ = new Array();               // Create a new Array
            $$->type = $1->type->arrElementType;   // Set the type equal to the element type
            $$->array = $1->array;          // Copy the base
            $$->addr = SymbolTable::gentemp(new SymbolType("int"));  // Store address of new temporary
            $$->arr_type = "arr";              // Set atype to "arr"

            if($1->arr_type == "arr") {        // If we have an "arr" type then, multiply the size of the sub-type of Array with the expression value and add
                Symbol* sym = SymbolTable::gentemp(new SymbolType("int"));
                int sz = sizeOfType($$->type);
                emit("*", sym->name, $3->addr->name, to_string(sz));
                emit("+", $$->addr->name, $1->addr->name, sym->name);
            }
            else {                          // Compute the size
                int sz = sizeOfType($$->type);
                emit("*", $$->addr->name, $3->addr->name, to_string(sz));
            }
        }
        | postfix_expression LEFT_PAREN argument_expression_list_opt RIGHT_PAREN
        {   
            yyinfo("postfix_expression -> postfix_expression LEFT_PAREN argument_expression_list_opt RIGHT_PAREN\n");
            // Corresponds to calling a function with the function name and the appropriate number of parameters
            $$ = new Array();
            $$->array = SymbolTable::gentemp($1->type);
            emit("call", $$->array->name, $1->array->name, to_string($3));
        }
        | postfix_expression DOT IDENTIFIER
        { yyinfo("postfix_expression -> postfix_expression DOT IDENTIFIER\n");/* Ignored */ }
        | postfix_expression ARROW IDENTIFIER
        { yyinfo("postfix_expression -> postfix_expression ARROW IDENTIFIER\n");/* Ignored */ }
        ;

argument_expression_list_opt: 
        argument_expression_list
        {
            yyinfo("argument_expression_list_opt -> argument_expression_list\n");
            $$ = $1;    // Assign $1 to $$
        }
        | %empty
        {
            yyinfo("argument_expression_list_opt -> \n");
            $$ = 0;     // No arguments, just equate to zero
        }
        ;

argument_expression_list: 
        assignment_expression
        {
            yyinfo("argument_expression_list -> assignment_expression\n");
            $$ = 1;                         // consider one argument
            emit("param", $1->addr->name);   // emit parameter
        }
        | argument_expression_list COMMA assignment_expression
        {
            yyinfo("argument_expression_list -> argument_expression_list COMMA assignment_expression\n");
            $$ = $1 + 1;                    // consider one more argument, so add 1
            emit("param", $3->addr->name);   // emit parameter
        }
        ;

unary_expression: 
        postfix_expression
        {
            yyinfo("unary_expression -> postfix_expression\n");
            $$ = $1;    // Assign $1 to $$
        }
        | unary_operator unary_expression
        {
            yyinfo("unary_expression -> unary_operator unary_expression\n");
            // Case of unary operator
            $$ = new Array();
            switch($1) {
                case '&':   // Address
                    $$->array = SymbolTable::gentemp(new SymbolType("ptr"));    // Generate a pointer temporary
                    $$->array->sym_type->arrElementType = $2->array->sym_type;                 // Assign corresponding type
                    emit("= &", $$->array->name, $2->array->name);              // Emit the quad
                    break;
                case '*':   // De-referencing
                    $$->arr_type = "ptr";
                    $$->addr = SymbolTable::gentemp($2->array->sym_type->arrElementType);   // Generate a temporary of the appropriate type
                    $$->array = $2->array;                                      // Assign
                    emit("= *", $$->addr->name, $2->array->name);                // Emit the quad
                    break;
                case '+':   // Unary plus
                    $$ = $2;    // Simple assignment
                    break;
                case '-':   // Unary minus
                    $$->array = SymbolTable::gentemp(new SymbolType($2->array->sym_type->type));    // Generate temporary of the same base type
                    emit("= -", $$->array->name, $2->array->name);                              // Emit the quad
                    break;
                case '!':   // Logical not 
                    if($2->arr_type == "bool_temporary")
                    {
                        list<int> l = tmpForBool->falselist;
                        tmpForBool->falselist = tmpForBool->truelist;
                        tmpForBool->truelist = l;
                        $$->arr_type = "bool_temporary";
                    }
                    else
                    {
                        $$->array = SymbolTable::gentemp(new SymbolType($2->array->sym_type->type));    // Generate temporary of the same base type
                        emit("= !", $$->array->name, $2->array->name);                              // Emit the quad
                    }
                    break;
            }
        }

        ;

unary_operator:
        BITWISE_AND
        {
            yyinfo("unary_operator -> BITWISE_AND\n");$$ = '&';
        }
        | MULTIPLY
        {
            yyinfo("unary_operator -> MULTIPLY\n");$$ = '*';
        }
        | ADD
        {
            yyinfo("unary_operator -> ADD\n");$$ = '+';
        }
        | SUBTRACT
        {
            yyinfo("unary_operator -> SUBTRACT\n");$$ = '-';
        }
        | NOT
        {
            yyinfo("unary_operator -> NOT\n");$$ = '!';
        }
        ;

multiplicative_expression: 
        unary_expression
        {
            yyinfo("multiplicative_expression -> unary_expression\n");
            $$ = new Expression();          // Generate new expression
            if($1->arr_type == "arr") {        // atype "arr"
                $$->addr = SymbolTable::gentemp($1->addr->sym_type);  // Generate new temporary
                emit("=[]", $$->addr->name, $1->array->name, $1->addr->name);     // Emit the quad
            }
            else if($1->arr_type == "ptr") {   // atype "ptr"
                $$->addr = $1->addr;          // Assign the symbol table entry
            }
            else if($1->arr_type == "bool_temporary")
            {
                $$ = tmpForBool;
            } else {
                $$->addr = $1->array;
            }
        }
        | multiplicative_expression MULTIPLY unary_expression
        {   yyinfo("multiplicative_expression -> multiplicative_expression MULTIPLY unary_expression\n");
            // Indicates multiplication
            if(typecheck($1->addr, $3->array)) {     // Check for type compatibility
                $$ = new Expression();                                                  // Generate new expression
                $$->addr = SymbolTable::gentemp(new SymbolType($1->addr->sym_type->type));    // Generate new temporary
                emit("*", $$->addr->name, $1->addr->name, $3->array->name);               // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
        | multiplicative_expression DIVIDE unary_expression
        {
            yyinfo("multiplicative_expression -> multiplicative_expression DIVIDE unary_expression\n");
            // Indicates division
            if(typecheck($1->addr, $3->array)) {     // Check for type compatibility
                $$ = new Expression();                                                  // Generate new expression
                $$->addr = SymbolTable::gentemp(new SymbolType($1->addr->sym_type->type));    // Generate new temporary
                emit("/", $$->addr->name, $1->addr->name, $3->array->name);               // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
        | multiplicative_expression MODULO unary_expression
        {
            yyinfo("multiplicative_expression -> multiplicative_expression MODULO unary_expression\n");
            // Indicates modulo
            if(typecheck($1->addr, $3->array)) {     // Check for type compatibility
                $$ = new Expression();                                                  // Generate new expression
                $$->addr = SymbolTable::gentemp(new SymbolType($1->addr->sym_type->type));    // Generate new temporary
                emit("%", $$->addr->name, $1->addr->name, $3->array->name);               // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
        ;

additive_expression: 
        multiplicative_expression
        {
            yyinfo("additive_expression -> multiplicative_expression\n");
            $$ = $1;    // Simple assignment
        }
        | additive_expression ADD multiplicative_expression
        {   
            yyinfo("additive_expression -> additive_expression ADD multiplicative_expression\n");
            // Indicates addition
            if(typecheck($1->addr, $3->addr)) {       // Check for type compatibility
                $$ = new Expression();                                                  // Generate new expression
                $$->addr = SymbolTable::gentemp(new SymbolType($1->addr->sym_type->type));    // Generate new temporary
                emit("+", $$->addr->name, $1->addr->name, $3->addr->name);                 // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
        | additive_expression SUBTRACT multiplicative_expression
        {
            yyinfo("additive_expression -> additive_expression SUBTRACT multiplicative_expression\n");
            // Indicates subtraction
            if(typecheck($1->addr, $3->addr)) {       // Check for type compatibility
                $$ = new Expression();                                                  // Generate new expression
                $$->addr = SymbolTable::gentemp(new SymbolType($1->addr->sym_type->type));    // Generate new temporary
                emit("-", $$->addr->name, $1->addr->name, $3->addr->name);                 // Emit the quad
            }
            else {
                yyerror("Type Error");
            }
        }
        ;


relational_expression: 
        additive_expression
        {
            yyinfo("relational_expression -> additive_expression\n");
            $$ = $1;    // Simple assignment
        }
        | relational_expression LESS_THAN additive_expression
        {
            yyinfo("relational_expression -> relational_expression LESS_THAN additive_expression\n");
            if(typecheck($1->addr, $3->addr)) {                   // Check for type compatibility
                $$ = new Expression();                          // Generate new expression of type bool
                $$->type = "bool";
                $$->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                $$->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("<", "", $1->addr->name, $3->addr->name);    // Emit "if x < y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
        | relational_expression GREATER_THAN additive_expression
        {
            yyinfo("relational_expression -> relational_expression GREATER_THAN additive_expression\n");
            if(typecheck($1->addr, $3->addr)) {                   // Check for type compatibility
                $$ = new Expression();                          // Generate new expression of type bool
                $$->type = "bool";
                $$->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                $$->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit(">", "", $1->addr->name, $3->addr->name);    // Emit "if x > y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
        | relational_expression LESS_THAN_EQUALS additive_expression
        {
            yyinfo("relational_expression -> relational_expression LESS_THAN_EQUALS additive_expression\n");
            if(typecheck($1->addr, $3->addr)) {                   // Check for type compatibility
                $$ = new Expression();                          // Generate new expression of type bool
                $$->type = "bool";
                $$->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                $$->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("<=", "", $1->addr->name, $3->addr->name);   // Emit "if x <= y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
        | relational_expression GREATER_THAN_EQUALS additive_expression
        {
            yyinfo("relational_expression -> relational_expression GREATER_THAN_EQUALS additive_expression\n");
            if(typecheck($1->addr, $3->addr)) {                   // Check for type compatibility
                $$ = new Expression();                          // Generate new expression of type bool
                $$->type = "bool";
                $$->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                $$->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit(">=", "", $1->addr->name, $3->addr->name);   // Emit "if x >= y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
        ;

equality_expression: 
        relational_expression
        {
            $$ = $1;    // Simple assignment
        }
        | equality_expression EQUALS relational_expression
        {
            if(typecheck($1->addr, $3->addr)) {                   // Check for type compatibility
                convertBoolToInt($1);                           // Convert bool to int
                convertBoolToInt($3);
                $$ = new Expression();                          // Generate new expression of type bool
                $$->type = "bool";
                $$->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                $$->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("==", "", $1->addr->name, $3->addr->name);   // Emit "if x == y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
        | equality_expression NOT_EQUALS relational_expression
        {
            if(typecheck($1->addr, $3->addr)) {                   // Check for type compatibility
                convertBoolToInt($1);                           // Convert bool to int
                convertBoolToInt($3);
                $$ = new Expression();                          // Generate new expression of type bool
                $$->type = "bool";
                $$->truelist = makelist(nextinstr());           // Create truelist for boolean expression
                $$->falselist = makelist(nextinstr() + 1);      // Create falselist for boolean expression
                emit("!=", "", $1->addr->name, $3->addr->name);   // Emit "if x != y goto ..."
                emit("goto", "");                               // Emit "goto ..."
            }
            else {
                yyerror("Type Error");
            }
        }
        ;


logical_and_expression: 
        equality_expression
        {
            $$ = $1;    // Simple assignment
        }
        | logical_and_expression LOGICAL_AND M equality_expression
        {
            /*
                Here, we have augmented the grammar with the non-terminal M to facilitate backpatching
            */
            convertIntToBool($1);                                   // Convert the expressions from int to bool
            convertIntToBool($4);
            $$ = new Expression();                                  // Create a new bool expression for the result
            $$->type = "bool";
            backpatch($1->truelist, $3);                            // Backpatching
            $$->truelist = $4->truelist;                            // Generate truelist from truelist of $4
            $$->falselist = merge($1->falselist, $4->falselist);    // Generate falselist by merging the falselists of $1 and $4
        }
        ;

logical_or_expression: 
        logical_and_expression
        {
            $$ = $1;    // Simple assignment
        }
        | logical_or_expression LOGICAL_OR M logical_and_expression
        {
            convertIntToBool($1);                                   // Convert the expressions from int to bool
            convertIntToBool($4);
            $$ = new Expression();                                  // Create a new bool expression for the result
            $$->type = "bool";
            backpatch($1->falselist, $3);                           // Backpatching
            $$->falselist = $4->falselist;                          // Generate falselist from falselist of $4
            $$->truelist = merge($1->truelist, $4->truelist);       // Generate truelist by merging the truelists of $1 and $4
        }
        ;

conditional_expression: 
        logical_or_expression
        {
            $$ = $1;    // Simple assignment
        }
        | logical_or_expression N QUESTION_MARK M expression N COLON M conditional_expression
        {   
            /*
                Note the augmented grammar with the non-terminals M and N
            */
            // printf("here");
            $$->addr = SymbolTable::gentemp($5->addr->sym_type);      // Generate temporary for the expression
            $$->addr->update_symbol($5->addr->sym_type);
            emit("=", $$->addr->name, $9->addr->name);            // Assign the conditional expression
            list<int> l1 = makelist(nextinstr());
            emit("goto", "");                                   // Prevent fall-through
            backpatch($6->nextlist, nextinstr());               // Make list with next instruction
            emit("=", $$->addr->name, $5->addr->name);
            list<int> l2 = makelist(nextinstr());               // Make list with next instruction
            l1 = merge(l1, l2);                                 // Merge the two lists
            emit("goto", "");                                   // Prevent fall-through
            backpatch($2->nextlist, nextinstr());               // Backpatching
            convertIntToBool($1);                               // Convert expression to bool
            backpatch($1->truelist, $4);                        // When $1 is true, control goes to $4 (expression)
            backpatch($1->falselist, $8);                       // When $1 is false, control goes to $8 (conditional_expression)
            backpatch(l1, nextinstr());
        }
        ;

M: %empty
        {   
            // Stores the next instruction value, and helps in backpatching
            $$ = nextinstr();
        }
        ;

N: %empty
        {
            // Helps in control flow
            $$ = new Statement();
            $$->nextlist = makelist(nextinstr());
            emit("goto", "");
        }
        ;

assignment_expression: 
        conditional_expression
        {
            $$ = $1;    // Simple assignment
        }
        | unary_expression assignment_operator assignment_expression
        {
            if($1->arr_type == "arr") {        // If atype is "arr", convert and emit
                $3->addr = convertType($3->addr, $1->type->type);
                emit("[]=", $1->array->name, $1->addr->name, $3->addr->name);
            }
            else if($1->arr_type == "ptr") {   // If atype is "ptr", emit 
                emit("*=", $1->array->name, $3->addr->name);
            }
            else {
                $3->addr = convertType($3->addr, $1->array->sym_type->type);
                emit("=", $1->array->name, $3->addr->name);
            }
            $$ = $3;
        }
        ;

assignment_operator: 
        ASSIGNMENT
        { /* Ignored */ }
        
        ;

expression: 
        assignment_expression
        {
            $$ = $1;
        }
        ;



declaration: 
        type_specifier init_declarator SEMICOLON
        { /* Ignored */ }
        ;
        


init_declarator: 
        declarator
        {
            $$ = $1;
        }
        | declarator ASSIGNMENT initializer
        {   
            // Find out the initial value and emit it
            if($3->val != "") {
                $1->val = $3->val;
            }
            emit("=", $1->name, $3->name);
        }
        ;

type_specifier: 
        VOID
        {
            prevType = "void";   // Store the latest encountered type in prevType
        }
        | CHAR
        {
            prevType = "char";   // Store the latest encountered type in prevType
        }
        | INT
        {
            prevType = "int";    // Store the latest encountered type in prevType
        }
        ;


declarator: 
        pointer direct_declarator
        {
            SymbolType* t = $1;
            // In case of multi-dimesnional arrays, keep on going down in a hierarchial fashion to get the base type
            while(t->arrElementType != NULL) {
                t = t->arrElementType;
            }
            t->arrElementType = $2->sym_type;  // Store the base type
            $$ = $2->update_symbol($1);    // Update
        }
        | direct_declarator
        {/* Ignored */}
        ;
intermediate_identifier:
        IDENTIFIER
        {
            $$ = $1->update_symbol(new SymbolType(prevType));   // For an identifier, update the type to prevType
            currentSym = $$;                         // Update pointer to current symbol
        }
        ;
direct_declarator: 
        IDENTIFIER
        {
            $$ = $1->update_symbol(new SymbolType(prevType));   // For an identifier, update the type to prevType
            currentSym = $$;                         // Update pointer to current symbol
        }
        | IDENTIFIER LEFT_SQR_BRACKET INT_CONSTANT RIGHT_SQR_BRACKET
        {
            SymbolType* t = $1->sym_type;
            SymbolType* prev = NULL;
            // Keep moving recursively to get the base type
            while(t->type == "arr") {
                prev = t;
                t = t->arrElementType;
            }
            if(prev == NULL) {
                // int temp = atoi($3->addr->val.c_str());                // Get initial value
                int temp = $3;         // Get initial value
                SymbolType* tp = new SymbolType("arr", $1->sym_type, temp); // Create that type
                $$ = $1->update_symbol(tp);                                    // Update the symbol table for that symbol
            }
            else {
                // int temp = atoi($3->addr->val.c_str());                // Get initial value
                int temp = $3;         // Get initial value
                prev->arrElementType = new SymbolType("arr", t, temp);         // Create that type
                $$ = $1->update_symbol($1->sym_type);                              // Update the symbol table for that symbol
            }
        }

        | intermediate_identifier LEFT_PAREN change_table parameter_list RIGHT_PAREN
        {
            SymTbl_Current->name = $1->name;
            if($1->sym_type->type != "void") {
                Symbol* s = SymTbl_Current->lookup("return");    // Lookup for return value
                s->update_symbol($1->sym_type);
            }
            $1->nestedTblPtr = SymTbl_Current;
            SymTbl_Current->parent = SymTbl_Global;   // Update parent symbol table
            switchTable(SymTbl_Global);          // Switch current table to point to the global symbol table
            currentSym = $$;             // Update current symbol
        }
        | intermediate_identifier LEFT_PAREN change_table RIGHT_PAREN
        {
            SymTbl_Current->name = $1->name;
            if($1->sym_type->type != "void") {
                Symbol* s = SymTbl_Current->lookup("return");    // Lookup for return value
                s->update_symbol($1->sym_type);
            }
            $1->nestedTblPtr = SymTbl_Current;
            SymTbl_Current->parent = SymTbl_Global;   // Update parent symbol table
            switchTable(SymTbl_Global);          // Switch current table to point to the global symbol table
            currentSym = $$;             // Update current symbol                       // Update pointer to current symbol
        }
        ;


pointer: 
        MULTIPLY 
        {
            $$ = new SymbolType("ptr");     //  Create new type "ptr"
        }
        ;


parameter_list: 
        parameter_declaration
        { /* Ignored */ }
        | parameter_list COMMA parameter_declaration
        { /* Ignored */ }
        ;

intermediate_declarator: 
        pointer intermediate_identifier
        {
            SymbolType* t = $1;
            // In case of multi-dimesnional arrays, keep on going down in a hierarchial fashion to get the base type
            while(t->arrElementType != NULL) {
                t = t->arrElementType;
            }
            t->arrElementType = $2->sym_type;  // Store the base type
            $$ = $2->update_symbol($1);    // Update
        }
        | intermediate_identifier
        {/* Ignored */}
        ;

parameter_declaration: 
        type_specifier intermediate_declarator
        { /* Ignored */ }
        | type_specifier
        { /* Ignored */ }
        ;



initializer: 
        assignment_expression
        {
            $$ = $1->addr;   // Simple assignment
        }
        ;

statement: 
        compound_statement
        {
            yyinfo("compound_statement\n");
            $$ = $1;    // Simple assignment
        }
        | expression_statement
        {
            yyinfo("expression_statement\n");
            $$ = new Statement();           // Create new statement
            $$->nextlist = $1->nextlist;    // Assign same nextlist
        }
        | selection_statement
        {
            yyinfo("selection_statement\n");
            $$ = $1;    // Simple assignment
        }
        | iteration_statement
        {
            yyinfo("iteration_statement\n");
            $$ = $1;    // Simple assignment
        }
        | jump_statement
        {
            yyinfo("jump_statement\n");
            $$ = $1;    // Simple assignment
        }
        ;

/* New non-terminal that has been added to facilitate the structure of loops */
loop_statement:
        expression_statement
        {
            yyinfo("loop_statement -> expression_statement\n");
            $$ = new Statement();           // Create new statement
            $$->nextlist = $1->nextlist;    // Assign same nextlist
        }
        | selection_statement
        {
            yyinfo("loop_statement -> selection_statement\n");
            $$ = $1;    // Simple assignment
        }
        | iteration_statement
        {
            yyinfo("loop_statement -> iteration_statement\n");
            $$ = $1;    // Simple assignment
        }
        | jump_statement
        {
            yyinfo("loop_statement -> jump_statement\n");
            $$ = $1;    // Simple assignment
        }
        ;


compound_statement: 
        LEFT_CURLY_BRACE X change_table block_item_list_opt RIGHT_CURLY_BRACE
        {
            /*
                Here, the grammar has been augmented with non-terminals like X and change_table to allow creation of nested symbol tables
            */
            $$ = $4;
            switchTable(SymTbl_Current->parent);     // Update current symbol table
        }
        ;

block_item_list_opt: 
        block_item_list
        {
            $$ = $1;    // Simple assignment
        }
        | %empty
        {
            $$ = new Statement();   // Create new statement
        }
        ;

block_item_list: 
        block_item
        {
            $$ = $1;    // Simple assignment
        }
        | block_item_list M block_item
        {   
            /*
                This production rule has been augmented with the non-terminal M
            */
            $$ = $3;
            backpatch($1->nextlist, $2);    // After $1, move to block_item via $2
        }
        ;

block_item: 
        declaration
        {
            $$ = new Statement();   // Create new statement
        }
        | statement
        {
            $$ = $1;    // Simple assignment
        }
        ;

expression_statement: 
        expression SEMICOLON
        {
            $$ = $1;    // Simple assignment
        }
        | SEMICOLON
        {
            $$ = new Expression();  // Create new expression
        }
        ;

selection_statement: 
        IF LEFT_PAREN expression N RIGHT_PAREN M statement N %prec THEN
        {
            /*
                This production rule has been augmented for control flow
            */
            backpatch($4->nextlist, nextinstr());                   // nextlist of N now has nextinstr
            convertIntToBool($3);                                   // Convert expression to bool
            $$ = new Statement();                                   // Create new statement
            backpatch($3->truelist, $6);                            // Backpatching - if expression is true, go to M
            // Merge falselist of expression, nextlist of statement and nextlist of the last N
            list<int> temp = merge($3->falselist, $7->nextlist);
            $$->nextlist = merge($8->nextlist, temp);
        }
        | IF LEFT_PAREN expression N RIGHT_PAREN M statement N ELSE M statement
        {
            /*
                This production rule has been augmented for control flow
            */
            backpatch($4->nextlist, nextinstr());                   // nextlist of N now has nextinstr
            convertIntToBool($3);                                   // Convert expression to bool
            $$ = new Statement();                                   // Create new statement
            backpatch($3->truelist, $6);                            // Backpatching - if expression is true, go to first M, else go to second M
            backpatch($3->falselist, $10);
            // Merge nextlist of statement, nextlist of N and nextlist of the last statement
            list<int> temp = merge($7->nextlist, $8->nextlist);
            $$->nextlist = merge($11->nextlist, temp);
        }

        ;

iteration_statement: 
        FOR F LEFT_PAREN X change_table expression_statement M expression_statement M expression N RIGHT_PAREN M loop_statement
        {
            /*
                This production rule has been augmented with non-terminals like F, X, change_table and M to handle the control flow, 
                backpatching, detect the kind of loop, create a separate symbol table for the loop block and give it an appropriate name
            */
            $$ = new Statement();                   // Create a new statement
            convertIntToBool($8);                   // Convert expression to bool
            backpatch($8->truelist, $13);           // Go to M3 if expression is true
            backpatch($11->nextlist, $7);           // Go back to M1 after N
            backpatch($14->nextlist, $9);           // Go back to expression after loop_statement
            emit("goto", to_string($9));   // Emit to prevent fall-through
            $$->nextlist = $8->falselist;           // Exit loop if expression_statement is false
            BlockName = "";
            switchTable(SymTbl_Current->parent);
        }
        | FOR F LEFT_PAREN X change_table expression_statement M expression_statement M expression N RIGHT_PAREN M LEFT_CURLY_BRACE block_item_list_opt RIGHT_CURLY_BRACE
        {
            /*
                This production rule has been augmented with non-terminals like F, X, change_table and M to handle the control flow, 
                backpatching, detect the kind of loop, create a separate symbol table for the loop block and give it an appropriate name
            */
            $$ = new Statement();                   // Create a new statement
            convertIntToBool($8);                   // Convert expression to bool
            backpatch($8->truelist, $13);           // Go to M3 if expression is true
            backpatch($11->nextlist, $7);           // Go back to M1 after N
            backpatch($15->nextlist, $9);           // Go back to expression after loop_statement
            emit("goto", to_string($9));            // Emit to prevent fall-through
            $$->nextlist = $8->falselist;           // Exit loop if expression_statement is false
            BlockName = "";
            switchTable(SymTbl_Current->parent);
        }
        ;

F: %empty
        {   
            /*
            This non-terminal indicates the start of a for loop
            */
            BlockName = "FOR";
        }
        ;


X: %empty
        {   
            // Used for creating new nested symbol tables for nested blocks
            string newST = SymTbl_Current->name + "." + BlockName + "$" + to_string(SymTbl_Count++);  // Generate name for new symbol table
            Symbol* sym = SymTbl_Current->lookup(newST);
            sym->nestedTblPtr = new SymbolTable(newST);  // Create new symbol table
            sym->name = newST;
            sym->nestedTblPtr->parent = SymTbl_Current;
            sym->sym_type = new SymbolType("block");    // The type will be "block"
            currentSym = sym;    // Change the current symbol pointer
        }
        ;

change_table: %empty
        {   
            // Used for changing the symbol table on encountering functions
            if(currentSym->nestedTblPtr != NULL) {
                // If the symbol table already exists, switch to that table
                switchTable(currentSym->nestedTblPtr);
                emit("label", SymTbl_Current->name);
            }
            else {
                // If the symbol table does not exist already, create it and switch to it
                switchTable(new SymbolTable(""));
            }
        }
        ;

jump_statement: 
        RETURN expression SEMICOLON
        {
            $$ = new Statement();
            emit("return", $2->addr->name);  // Emit return alongwith return value
        }
        | RETURN SEMICOLON
        {
            $$ = new Statement();
            emit("return", "");             // Emit return without any return value
        }
        ;

translation_unit: 
        external_declaration
        { /* Ignored */ }
        | translation_unit external_declaration
        { /* Ignored */ }
        ;

external_declaration: 
        function_definition
        { /* Ignored */ }
        | declaration
        { /* Ignored */ }
        ;

function_definition: 
        type_specifier declarator declaration_list_opt change_table LEFT_CURLY_BRACE block_item_list_opt RIGHT_CURLY_BRACE
        {   
            SymTbl_Current->parent = SymTbl_Global;
            SymTbl_Count = 0;
            switchTable(SymTbl_Global);          // After reaching end of a function, change cureent symbol table to the global symbol table
        }
        ;

declaration_list_opt: 
        declaration_list
        { /* Ignored */ }
        | %empty
        { /* Ignored */ }
        ;

declaration_list: 
        declaration
        { /* Ignored */ }
        | declaration_list declaration
        { /* Ignored */ }
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
