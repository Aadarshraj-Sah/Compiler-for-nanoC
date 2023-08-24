%{
    #include <stdio.h>
    extern int yylex();
    extern char* yytext;
    extern int yylineno;
    void yyerror(char *s);
%}

%union {
    int int_value;
    char char_value;
    char *string_value;
}

%token CHAR
%token ELSE
%token FOR
%token IF
%token INT
%token RETURN
%token VOID

%token <string_value> IDENTIFIERS
%token <int_value> INTEGER_CONSTANT
%token <char_value> CHARACTER_CONSTANT
%token <string_value> STRING_LITERAL

%token LEFT_SQUARE_BRACKET
%token RIGHT_SQUARE_BRACKET
%token LEFT_PARENTHESIS
%token RIGHT_PARENTHESIS
%token LEFT_CURLY_BRACKET
%token RIGHT_CURLY_BRACKET 
%token DOT
%token ARROW
%token BITWISE_AND
%token MULTIPLY
%token ADD
%token SUBTRACT
%token BITWISE_NOR
%token NOT
%token DIVIDE
%token MODULO 
%token LESS_THAN
%token GREATER_THAN
%token LESS_THAN_EQUAL
%token GREATER_THAN_EQUAL
%token EQUAL
%token NOT_EQUAL
%token LOGICAL_AND
%token LOGICAL_OR
%token QUESTION_MARK
%token COLON
%token SEMICOLON
%token ASSIGN
%token COMMA

%nonassoc RIGHT_PARENTHESIS
%nonassoc ELSE

%start translation_unit

%%

primary_expression: IDENTIFIERS																										{ printf("yyline no.- %d, yytext- %s\t: primary-expression --> identifier\n",yylineno, yytext); }
                  | INTEGER_CONSTANT																								{ printf("yyline no.- %d, yytext- %s\t: primary-expression --> integer_constant\n",yylineno, yytext); }
				  | CHARACTER_CONSTANT																								{ printf("yyline no.- %d, yytext- %s\t: primary_expression --> character_constant\n",yylineno, yytext); }
                  | STRING_LITERAL																									{ printf("yyline no.- %d, yytext- %s\t: primary-expression --> string-literal\n",yylineno, yytext); }
                  | LEFT_PARENTHESIS expression RIGHT_PARENTHESIS																	{ printf("yyline no.- %d, yytext- %s\t: primary-expression --> ( expression )\n",yylineno, yytext); }
                  ;

argument_expression_list_opt: argument_expression_list																				{ printf("yyline no.- %d, yytext- %s\t: argument-expression-list-opt --> argument-expression-list\n",yylineno, yytext); }
                            |																										{ printf("yyline no.- %d, yytext- %s\t: argument-expression-list-opt --> epsilon\n",yylineno, yytext); }
                            ;

postfix_expression: primary_expression																								{ printf("yyline no.- %d, yytext- %s\t: postfix-expression --> primary-expression\n",yylineno, yytext); }
                  | postfix_expression LEFT_SQUARE_BRACKET expression RIGHT_SQUARE_BRACKET												{ printf("yyline no.- %d, yytext- %s\t: postfix-expression --> postfix-expression [ expression ]\n",yylineno, yytext); }
                  | postfix_expression LEFT_PARENTHESIS argument_expression_list_opt RIGHT_PARENTHESIS								{ printf("yyline no.- %d, yytext- %s\t: postfix-expression --> postfix-expression ( argument-expression-list-opt )\n",yylineno, yytext); }
                  | postfix_expression DOT IDENTIFIERS																				{ printf("yyline no.- %d, yytext- %s\t: postfix-expression --> postfix-expression . identifier\n",yylineno, yytext); }
                  | postfix_expression ARROW IDENTIFIERS																				{ printf("yyline no.- %d, yytext- %s\t: postfix-expression --> postfix-expression -> identifier\n",yylineno, yytext); }
                  ;

argument_expression_list: assignment_expression																						{ printf("yyline no.- %d, yytext- %s\t: argument-expression-list --> assignment-expression\n",yylineno, yytext); }
                        | argument_expression_list COMMA assignment_expression														{ printf("yyline no.- %d, yytext- %s\t: argument-expression-list --> argument-expression-list , assignment-expression\n",yylineno, yytext); }
                        ;

unary_expression: postfix_expression																								{ printf("yyline no.- %d, yytext- %s\t: unary-expression --> postfix-expression\n",yylineno, yytext); }
                | unary_operator unary_expression																					{ printf("yyline no.- %d, yytext- %s\t: unary-operator --> unary-expression\n",yylineno, yytext); }
                ;

unary_operator: BITWISE_AND																											{ printf("yyline no.- %d, yytext- %s\t: unary-operator --> &\n",yylineno, yytext); }
              | MULTIPLY																											{ printf("yyline no.- %d, yytext- %s\t: unary-operator --> *\n",yylineno, yytext); }
              | ADD																													{ printf("yyline no.- %d, yytext- %s\t: unary-operator --> +\n",yylineno, yytext); }
              | SUBTRACT																											{ printf("yyline no.- %d, yytext- %s\t: unary-operator --> -\n",yylineno, yytext); }
              | NOT																													{ printf("yyline no.- %d, yytext- %s\t: unary-operator --> !\n",yylineno, yytext); }
              ;

multiplicative_expression: unary_expression																							{ printf("yyline no.- %d, yytext- %s\t: multiplicative-expression --> unary-expression\n",yylineno, yytext); }
                         | multiplicative_expression MULTIPLY unary_expression														{ printf("yyline no.- %d, yytext- %s\t: multiplicative-expression --> multiplicative-expression * unary-expression\n",yylineno, yytext); }
                         | multiplicative_expression DIVIDE unary_expression															{ printf("yyline no.- %d, yytext- %s\t: multiplicative-expression --> multiplicative-expression / unary-expression\n",yylineno, yytext); }
                         | multiplicative_expression MODULO unary_expression															{ printf("yyline no.- %d, yytext- %s\t: multiplicative-expression --> multiplicative-expression %% unary-expression\n",yylineno, yytext); }
                         ;

additive_expression: multiplicative_expression																						{ printf("yyline no.- %d, yytext- %s\t: additive-expression --> multiplicative-expression\n",yylineno, yytext); }
                   | additive_expression ADD multiplicative_expression																{ printf("yyline no.- %d, yytext- %s\t: additive-expression --> additive-expression + multiplicative-expression\n",yylineno, yytext); }
                   | additive_expression SUBTRACT multiplicative_expression															{ printf("yyline no.- %d, yytext- %s\t: additive-expression --> additive-expression - multiplicative-expression\n",yylineno, yytext); }
                   ;

relational_expression: additive_expression																								{ printf("yyline no.- %d, yytext- %s\t: relational-expression --> additive-expression\n",yylineno, yytext); }
                     | relational_expression LESS_THAN additive_expression																{ printf("yyline no.- %d, yytext- %s\t: relational-expression --> relational-expression < additive-expression\n",yylineno, yytext); }
                     | relational_expression GREATER_THAN additive_expression															{ printf("yyline no.- %d, yytext- %s\t: relational-expression --> relational-expression > additive-expression\n",yylineno, yytext); }
                     | relational_expression LESS_THAN_EQUAL additive_expression														{ printf("yyline no.- %d, yytext- %s\t: relational-expression --> relational-expression <= additive-expression\n",yylineno, yytext); }
                     | relational_expression GREATER_THAN_EQUAL additive_expression													{ printf("yyline no.- %d, yytext- %s\t: relational-expression --> relational-expression >= additive-expression\n",yylineno, yytext); }
                     ;

equality_expression: relational_expression																							{ printf("yyline no.- %d, yytext- %s\t: equality-expression --> relational-expression\n",yylineno, yytext); }
                   | equality_expression EQUAL relational_expression																{ printf("yyline no.- %d, yytext- %s\t: equality-expression --> equality-expression == relational-expression\n",yylineno, yytext); }
                   | equality_expression NOT_EQUAL relational_expression															{ printf("yyline no.- %d, yytext- %s\t: equality-expression --> equality-expression != relational-expression\n",yylineno, yytext); }
                   ;

logical_and_expression: equality_expression																						{ printf("yyline no.- %d, yytext- %s\t: logical-AND-expression --> equality-expression\n",yylineno, yytext); }
                      | logical_and_expression LOGICAL_AND equality_expression													{ printf("yyline no.- %d, yytext- %s\t: logical-AND-expression --> logical-AND-expression && equality-expression\n",yylineno, yytext); }
                      ;

logical_or_expression: logical_and_expression																						{ printf("yyline no.- %d, yytext- %s\t: logical-OR-expression --> logical-AND-expression\n",yylineno, yytext); }
                     | logical_or_expression LOGICAL_OR logical_and_expression														{ printf("yyline no.- %d, yytext- %s\t: logical-OR-expression --> logical_or_expression || logical-AND-expression\n",yylineno, yytext); }
                     ;

conditional_expression: logical_or_expression																						{ printf("yyline no.- %d, yytext- %s\t: conditional-expression --> logical-OR-expression\n",yylineno, yytext); }
                      | logical_or_expression QUESTION_MARK expression COLON conditional_expression									{ printf("yyline no.- %d, yytext- %s\t: conditional-expression --> logical-OR-expression ? expression : conditional-expression\n",yylineno, yytext); }
                      ;

assignment_expression: conditional_expression																						{ printf("yyline no.- %d, yytext- %s\t: assignment-expression --> conditional-expression\n",yylineno, yytext); }
                     | unary_expression ASSIGN assignment_expression													            { printf("yyline no.- %d, yytext- %s\t: assignment-expression --> unary-expression assignment-operator assignment-expression\n",yylineno, yytext); }
                     ;

expression: assignment_expression																									{ printf("yyline no.- %d, yytext- %s\t: expression --> assignment-expression\n",yylineno, yytext); }
          ;

declaration: type_specifier init_declarator SEMICOLON																                { printf("yyline no.- %d, yytext- %s\t: declaration --> type-specifier init-declarator ;\n",yylineno, yytext); }
           ;

init_declarator: declarator																											{ printf("yyline no.- %d, yytext- %s\t: init-declarator --> declarator\n",yylineno, yytext); }
               | declarator ASSIGN initializer 																						{ printf("yyline no.- %d, yytext- %s\t: init-declarator --> declarator = initializer\n",yylineno, yytext); }
               ;

type_specifier: VOID																												{ printf("yyline no.- %d, yytext- %s\t: type-specifier --> void\n",yylineno, yytext); }
              | CHAR																												{ printf("yyline no.- %d, yytext- %s\t: type-specifier --> char\n",yylineno, yytext); }
              | INT																													{ printf("yyline no.- %d, yytext- %s\t: type-specifier --> int\n",yylineno, yytext); }
              ;

identifier_opt: IDENTIFIERS																											{ printf("yyline no.- %d, yytext- %s\t: identifier-opt --> identifier\n",yylineno, yytext); }
              |																														{ printf("yyline no.- %d, yytext- %s\t: identifier-opt --> epsilon\n",yylineno, yytext); }
              ;

declarator: pointer_opt direct_declarator																							{ printf("yyline no.- %d, yytext- %s\t: declarator --> pointer-opt direct-declarator\n",yylineno, yytext); }
          ;

pointer_opt: pointer																												{ printf("yyline no.- %d, yytext- %s\t: pointer-opt --> pointer\n",yylineno, yytext); }
           |																														{ printf("yyline no.- %d, yytext- %s\t: pointer-opt --> epsilon\n",yylineno, yytext); }
           ;

direct_declarator: IDENTIFIERS																										{ printf("yyline no.- %d, yytext- %s\t: direct-declarator --> identifier\n",yylineno, yytext); }
                | IDENTIFIERS LEFT_SQUARE_BRACKET INTEGER_CONSTANT RIGHT_SQUARE_BRACKET											    { printf("yyline no.- %d, yytext- %s\t: direct-declarator --> identifier [ integer_constant ]\n",yylineno, yytext); }
                | IDENTIFIERS LEFT_PARENTHESIS parameter_list_opt RIGHT_PARENTHESIS											        { printf("yyline no.- %d, yytext- %s\t: direct-declarator --> identifier ( parameter-list-opt )\n",yylineno, yytext); }
                 ;

pointer: MULTIPLY 																							                        { printf("yyline no.- %d, yytext- %s\t: pointer --> *\n",yylineno, yytext); }
       ;

parameter_list: parameter_declaration																								{ printf("yyline no.- %d, yytext- %s\t: parameter-list --> parameter-declaration\n",yylineno, yytext); }
              | parameter_list COMMA parameter_declaration																			{ printf("yyline no.- %d, yytext- %s\t: parameter-list --> parameter-list , parameter-declaration\n",yylineno, yytext); }
              ;

parameter_list_opt: parameter_list                                                                                                  { printf("yyline no.- %d, yytext- %s\t: parameter-list-opt --> parameter-list\n",yylineno, yytext); }
                    |                                                                                                               { printf("yyline no.- %d, yytext- %s\t: parameter-list-opt --> epsilon\n",yylineno, yytext); }
                    ;

parameter_declaration: type_specifier pointer_opt identifier_opt                                                                       { printf("yyline no.- %d, yytext- %s\t: parameter-declaration --> type_specifier pointer_opt identifier_opt\n",yylineno, yytext); }
                     ;


initializer: assignment_expression																									{ printf("yyline no.- %d, yytext- %s\t: initializer --> assignment-expression\n",yylineno, yytext); }
           ;


statement: compound_statement																										{ printf("yyline no.- %d, yytext- %s\t: statement --> compound-statement\n",yylineno, yytext); }
         | expression_statement																										{ printf("yyline no.- %d, yytext- %s\t: statement --> expression-statement\n",yylineno, yytext); }
         | selection_statement																										{ printf("yyline no.- %d, yytext- %s\t: statement --> selection-statement\n",yylineno, yytext); }
         | iteration_statement																										{ printf("yyline no.- %d, yytext- %s\t: statement --> iteration-statement\n",yylineno, yytext); }
         | jump_statement																											{ printf("yyline no.- %d, yytext- %s\t: statement --> jump-statement\n",yylineno, yytext); }
         ;

compound_statement: LEFT_CURLY_BRACKET block_item_list_opt RIGHT_CURLY_BRACKET															{ printf("yyline no.- %d, yytext- %s\t: compound-statement --> { block-item-list-opt }\n",yylineno, yytext); }
                  ;

block_item_list_opt: block_item_list																								{ printf("yyline no.- %d, yytext- %s\t: block-item-list-opt --> block-item-list\n",yylineno, yytext); }
                   |																												{ printf("yyline no.- %d, yytext- %s\t: block-item-list-opt --> epsilon\n",yylineno, yytext); }
                   ;

block_item_list: block_item																											{ printf("yyline no.- %d, yytext- %s\t: block-item-list --> block-item\n",yylineno, yytext); }
               | block_item_list block_item																							{ printf("yyline no.- %d, yytext- %s\t: block-item-list --> block-item-list block-item\n",yylineno, yytext); }
               ;

block_item: declaration																												{ printf("yyline no.- %d, yytext- %s\t: block-item --> declaration\n",yylineno, yytext); }
          | statement																												{ printf("yyline no.- %d, yytext- %s\t: block-item --> statement\n",yylineno, yytext); }
          ;

expression_statement: expression_opt SEMICOLON																						{ printf("yyline no.- %d, yytext- %s\t: expression-statement --> expression-opt ;\n",yylineno, yytext); }
                    ;

expression_opt: expression																											{ printf("yyline no.- %d, yytext- %s\t: expression-opt --> expression\n",yylineno, yytext); }
              |																														{ printf("yyline no.- %d, yytext- %s\t: expression-opt --> epsilon\n",yylineno, yytext); }
              ;

selection_statement: IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement														{ printf("yyline no.- %d, yytext- %s\t: selection-statement --> if ( expression ) statement\n",yylineno, yytext); }
                   | IF LEFT_PARENTHESIS expression RIGHT_PARENTHESIS statement ELSE statement										{ printf("yyline no.- %d, yytext- %s\t: selection-statement --> if ( expression ) statement else statement\n",yylineno, yytext); }
                   ;

iteration_statement: FOR LEFT_PARENTHESIS expression_opt SEMICOLON expression_opt SEMICOLON expression_opt RIGHT_PARENTHESIS statement							{ printf("yyline no.- %d, yytext- %s\t: iteration-statement --> for ( expression-opt ; expression-opt ; expression-opt ) statement\n",yylineno, yytext); }
                   ;

jump_statement: RETURN expression_opt SEMICOLON																						{ printf("yyline no.- %d, yytext- %s\t: jump-statement --> return expression-opt ;\n",yylineno, yytext); }
              ;

translation_unit: external_declaration																								{ printf("yyline no.- %d, yytext- %s\t: translation-unit --> external-declaration\n",yylineno, yytext); }
                | translation_unit external_declaration																				{ printf("yyline no.- %d, yytext- %s\t: translation-unit --> translation-unit external-declaration\n",yylineno, yytext); }
                ;

external_declaration: function_definition																							{ printf("yyline no.- %d, yytext- %s\t: external-declaration --> function-definition\n",yylineno, yytext); }
                    | declaration																									{ printf("yyline no.- %d, yytext- %s\t: external-declaration --> declaration\n",yylineno, yytext); }
                    ;
function_definition: type_specifier declarator  declaration_list_opt  compound_statement			                                { printf("yyline no.- %d, yytext- %s\t: function-definition --> declaration-specifiers declarator declaration-list-opt compound-statement\n",yylineno, yytext); }
                   ;

declaration_list_opt: declaration_list																								{ printf("yyline no.- %d, yytext- %s\t: declaration-list-opt --> declaration-list\n",yylineno, yytext); }
                    |																												{ printf("yyline no.- %d, yytext- %s\t: declaration-list-opt --> epsilon\n",yylineno, yytext); }
                    ;

declaration_list: declaration																										{ printf("yyline no.- %d, yytext- %s\t: declaration-list --> declaration\n",yylineno, yytext); }
                | declaration_list declaration																						{ printf("yyline no.- %d, yytext- %s\t: declaration-list --> declaration-list declaration\n",yylineno, yytext); }
                ;

%%

void yyerror(char *s) {
    printf("Error occured!      yyline no.: %d       Error: %s      Unable to parse: %s\n",yylineno, s, yytext);  
    printf("Parsing process terminated due to error.");
}