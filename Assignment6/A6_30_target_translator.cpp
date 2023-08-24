
#include "A6_30_translator.h"
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;

// External variables
extern symbolTable globalST;
extern symbolTable* ST;
extern quadArray quadList;

// Declare global variables
vector<string> stringConsts;
map<int, string> labels;
stack<pair<string, int>> parameters;
int labelCount = 0;
string funcRunning = "";
string asmFileName;


// Prints the global information to the assembly file
void printGlobal(ofstream& sfile) {
    vector<symbol*>::iterator it = globalST.symbols.begin();
    while( it != globalST.symbols.end()) {
        symbol* sym = *it;
        if(sym->type.type == INT && sym->name[0] != 't') {
            if(sym->initVal == NULL) 
            {
                sfile << "\t.comm\t" << sym->name << ",4,4" << "\n";
            }
            else
            {
                string toPrint = "";
                toPrint = "\t.globl\t"+sym->name;
                sfile << toPrint << "\n";
                toPrint ="\t.data";
                sfile << toPrint << "\n";
                toPrint = "\t.type\t" + sym->name + ", @object" ;
                sfile << toPrint << "\n";
                toPrint = "\t.size\t" + sym->name + ", 1" ;
                sfile << toPrint << "\n";
                toPrint = sym->name + ":" ;
                sfile << toPrint << "\n";
                toPrint = "\t.byte\t";
                sfile << toPrint << sym->initVal->i << "\n";
            }
        }
        else if(sym->type.type == CHAR && sym->name[0] != 't') {
            if(sym->initVal== NULL) 
            {
                sfile << "\t.comm\t" << sym->name << ",1,1" << "\n";
            }
            else
            {
                string toPrint = "";
                toPrint = "\t.globl\t"+sym->name;
                sfile << toPrint << "\n";
                toPrint ="\t.data";
                sfile << toPrint << "\n";
                toPrint = "\t.type\t" + sym->name + ", @object" ;
                sfile << toPrint << "\n";
                toPrint = "\t.size\t" + sym->name + ", 1" ;
                sfile << toPrint << "\n";
                toPrint = sym->name + ":" ;
                sfile << toPrint << "\n";
                toPrint = "\t.byte\t";
                sfile << toPrint << sym->initVal->c << "\n";
            }
        }
        it++;
    }
}

// Prints all the strings used in the program to the assembly file
void printStrings(ofstream& sfile) {
    sfile << ".section\t.rodata" << "\n";
    int i = 0;
    vector<string>::iterator it = stringConsts.begin(); 
    while(it != stringConsts.end()) {
        sfile << ".LC" << i++ << ":" << "\n";
        sfile << "\t.string " << *it << "\n";
        it++;
    }
}

// Generates labels for different targets of goto statements
void setLabels() {
    int i = 0;
    vector<quad>::iterator it = quadList.quads.begin();
    while( it != quadList.quads.end()) {
        if(it->op == GOTO) {
            int target = atoi((it->result.c_str()));
            if(!labels.count(target)) {
                string labelName = ".L" + to_string(labelCount++);
                labels[target] = labelName;
            }
            it->result = labels[target];
        }
        if(it->op >= GOTO_EQ && it->op <= IF_FALSE_GOTO){
            int target = atoi((it->result.c_str()));
            if(!labels.count(target)) {
                string labelName = ".L" + to_string(labelCount++);
                labels[target] = labelName;
            }
            it->result = labels[target];
        }
        it++;
    }
}

// Generates the function prologue to be printed before each function
// Generic tasks like allocating space for variables on the stack are performed here
void generatePrologue(int memBind, ofstream& sfile) {
    int width = 16;
    string toPrint = "";
    toPrint = "\t.text";
    sfile << "\n" << toPrint << "\n";
    toPrint = "\t.globl\t" + funcRunning;
    sfile << toPrint << "\n";
    sfile << "\t.type\t" << funcRunning << ", @function" << "\n";
    toPrint = funcRunning + ":";
    sfile << toPrint << "\n";
    toPrint = "\tpushq\t%rbp";
    sfile << toPrint << "\n";
    toPrint = "\tmovq\t%rsp, %rbp";
    sfile << toPrint << "\n";
    toPrint = "\tsubq\t$";
    sfile << toPrint << (memBind / width + 1) * width << ", %rsp" << "\n";
}

void printmov(ofstream& sfile, string toPrint1){
     sfile << "\tmovl\t" << toPrint1 << ", %eax" << "\n";
}
void printcmpl(ofstream& sfile, string toPrint2){
    sfile << "\tcmpl\t" << toPrint2 << ", %eax" << "\n";
}
void printjmp(ofstream& sfile, string str){
    sfile << "\tjmp\t" << str << "\n";
}
// Main function which calls all other relevant functions for generating the target assembly code
void generateTargetCode(ofstream& sfile) {
    printGlobal(sfile);
    printStrings(sfile);
    symbolTable* currFuncTable = NULL;
    symbol* currFunc = NULL;
    setLabels();

    
    for(int i = 0; i < (int)quadList.quads.size(); i++) {
        // Print the quad as a comment in the assembly file
        string quadsp = "#";
        sfile << quadsp << quadList.quads[i].print() << "\n";
        if(labels.count(i)==0);
        else
            sfile << labels[i] << ":" << "\n";

        // Necessary tasks for a function
        if(quadList.quads[i].op != FUNC_BEG);
        else {
            if(quadList.quads[i+1].op == FUNC_END){i++;continue;}

            currFunc = globalST.searchGlobal(quadList.quads[i].result);
            currFuncTable = currFunc->nestedTable;
            int takingParam = 1, memBind = 16;
            ST = currFuncTable;
            for(int j = 0; j < (int)currFuncTable->symbols.size(); j++) {
                if(currFuncTable->symbols[j]->name == "RETVAL") {
                    takingParam = 0;
                    memBind = 0;
                    if(currFuncTable->symbols.size() > j + 1)
                        memBind = -currFuncTable->symbols[j + 1]->size;
                }
                else {
                    if(!takingParam) {
                        currFuncTable->symbols[j]->offset = memBind;
                        if(currFuncTable->symbols.size() > j + 1)
                            memBind -= currFuncTable->symbols[j + 1]->size;
                    }
                    else {
                        currFuncTable->symbols[j]->offset = memBind;
                        memBind += 8;
                    }
                }
            }
            if(memBind >= 0)
                memBind = 0;
            else
                memBind *= -1;
            funcRunning = quadList.quads[i].result;
            generatePrologue(memBind, sfile);
        }
        if(quadList.quads[i].op == FUNC_BEG);
        // Function epilogue (while leaving a function)
        else if(quadList.quads[i].op == FUNC_END) {
            ST = &globalST;
            funcRunning = "";
            sfile << "\tleave" << "\n";
            sfile << "\tret" << "\n";
            sfile << "\t.size\t" << quadList.quads[i].result << ", .-" << quadList.quads[i].result << "\n";
        }

        if(funcRunning != "")
        {
            quad q = quadList.quads[i];
            string strLabel = q.result;
            bool hasStrLabel = (q.result[0] == '.' && q.result[1] == 'L' && q.result[2] == 'C');
            string toPrint1 = "", toPrint2 = "", toPrintRes = "";
            int off1 = 0, off2 = 0, offRes = 0;

            symbol* loc1 = ST->lookup(q.arg1);
            symbol* loc2 = ST->lookup(q.arg2);
            symbol* loc3 = ST->lookup(q.result);
            symbol* glb1 = globalST.searchGlobal(q.arg1);
            symbol* glb2 = globalST.searchGlobal(q.arg2);
            symbol* glb3 = globalST.searchGlobal(q.result);

            if(ST != &globalST) {
                if(glb1 == NULL)
                    off1 = loc1->offset;
                if(glb2 == NULL)
                    off2 = loc2->offset;
                if(glb3 == NULL)
                    offRes = loc3->offset;

                if(q.arg1[0] < '0' || q.arg1[0] > '9') {
                    if(glb1 != NULL)
                        toPrint1 = q.arg1 + "(%rip)";
                    else
                        toPrint1 = to_string(off1) + "(%rbp)";
                }
                if(q.arg2[0] < '0' || q.arg2[0] > '9') {
                    if(glb2 != NULL)
                        toPrint2 = q.arg2 + "(%rip)";
                    else
                        toPrint2 = to_string(off2) + "(%rbp)";
                }
                if(q.result[0] < '0' || q.result[0] > '9') {
                    if(glb3 != NULL)
                        toPrintRes = q.result + "(%rip)";
                    else
                        toPrintRes = to_string(offRes) + "(%rbp)";
                }
            }
            else {
                toPrint1 = q.arg1;
                toPrint2 = q.arg2;
                toPrintRes = q.result;
            }

            if(hasStrLabel)
                toPrintRes = strLabel;

            if(q.op == ASSIGN) {
                if(q.result[0] != 't' || loc3->type.type == INT || loc3->type.type == POINTER) {
                    if(loc3->type.type != POINTER) {
                        if(q.arg1[0] < '0' || q.arg1[0] > '9')
                        {
                           printmov(sfile, toPrint1);
                            sfile << "\tmovl\t%eax, " << toPrintRes << "\n"; 
                        }
                        else
                            sfile << "\tmovl\t$" << q.arg1 << ", " << toPrintRes << "\n";
                    }
                    else {
                        sfile << "\tmovq\t" << toPrint1 << ", %rax" << "\n";
                        sfile << "\tmovq\t%rax, " << toPrintRes << "\n"; 
                    }
                }
                else {
                    int temp = q.arg1[0];
                    sfile << "\tmovb\t$" << temp << ", " << toPrintRes << "\n";
                }
            }
            else if(q.op == U_MINUS) {
               printmov(sfile, toPrint1);
                sfile << "\tnegl\t%eax" << "\n";
                sfile << "\tmovl\t%eax, " << toPrintRes << "\n";
            }
            else if(q.op == ADD) {
                if(q.arg1[0] > '0' && q.arg1[0] <= '9')
                    sfile << "\tmovl\t$" << q.arg1 << ", %eax" << "\n";
                else
                   printmov(sfile, toPrint1); 
                if(q.arg2[0] > '0' && q.arg2[0] <= '9')
                    sfile << "\tmovl\t$" << q.arg2 << ", %edx" << "\n";
                else
                    sfile << "\tmovl\t" << toPrint2 << ", %edx" << "\n"; 
                sfile << "\taddl\t%edx, %eax" << "\n";
                sfile << "\tmovl\t%eax, " << toPrintRes << "\n";
            }
            else if(q.op == SUB) {
                if(q.arg1[0] > '0' && q.arg1[0] <= '9')
                    sfile << "\tmovl\t$" << q.arg1 << ", %edx" << "\n";
                else
                    sfile << "\tmovl\t" << toPrint1 << ", %edx" << "\n"; 
                if(q.arg2[0]>'0' && q.arg2[0]<='9')
                    sfile << "\tmovl\t$" << q.arg2 << ", %eax" << "\n";
                else
                    sfile << "\tmovl\t" << toPrint2 << ", %eax" << "\n"; 
                sfile << "\tsubl\t%eax, %edx" << "\n";
                sfile << "\tmovl\t%edx, %eax" << "\n";
                sfile << "\tmovl\t%eax, " << toPrintRes << "\n";
            }
            else if(q.op == MULT) {
                if(q.arg1[0] > '0' && q.arg1[0] <= '9')
                    sfile << "\tmovl\t$" << q.arg1 << ", %eax" << "\n";
                else
                   printmov(sfile, toPrint1); 
                sfile << "\timull\t";
                if(q.arg2[0] > '0' && q.arg2[0] <= '9')
                    sfile << "$" << q.arg2 << ", %eax" << "\n";
                else
                    sfile << toPrint2 << ", %eax" << "\n";
                sfile << "\tmovl\t%eax, " << toPrintRes << "\n";
            }
            else if(q.op == DIV) {
               printmov(sfile, toPrint1);
                sfile << "\tcltd\n\tidivl\t" << toPrint2 << "\n";
                sfile << "\tmovl\t%eax, " << toPrintRes << "\n";
            }
            else if(q.op == MOD) {
               printmov(sfile, toPrint1);
                sfile << "\tcltd\n\tidivl\t" << toPrint2 << "\n";
                sfile << "\tmovl\t%edx, " << toPrintRes << "\n";
            }
            else if(q.op == GOTO)
                printjmp(sfile, q.result);
            else if(q.op == GOTO_LT) {
               printmov(sfile, toPrint1);
                printcmpl(sfile, toPrint2);
                sfile << "\tjge\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == GOTO_GT) {
               printmov(sfile, toPrint1);
                printcmpl(sfile, toPrint2);
                sfile << "\tjle\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == GOTO_GTE) {
               printmov(sfile, toPrint1);
                printcmpl(sfile, toPrint2);
                sfile << "\tjl\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == GOTO_LTE) {
               printmov(sfile, toPrint1);
                printcmpl(sfile, toPrint2);
                sfile << "\tjg\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == GOTO_GTE) {
               printmov(sfile, toPrint1);
                printcmpl(sfile, toPrint2);
                sfile << "\tjl\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == GOTO_EQ) {
               printmov(sfile, toPrint1);
                if(q.arg2[0] >= '0' && q.arg2[0] <= '9')
                    sfile << "\tcmpl\t$" << q.arg2 << ", %eax" << "\n";
                else
                    printcmpl(sfile, toPrint2);
                sfile << "\tjne\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == GOTO_NEQ) {
               printmov(sfile, toPrint1);
                printcmpl(sfile, toPrint2);
                sfile << "\tje\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == IF_GOTO) {
               printmov(sfile, toPrint1);
                sfile << "\tcmpl\t$0" << ", %eax" << "\n";
                sfile << "\tje\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == IF_FALSE_GOTO) {
               printmov(sfile, toPrint1);
                sfile << "\tcmpl\t$0" << ", %eax" << "\n";
                sfile << "\tjne\t.L" << labelCount << "\n";
                printjmp(sfile, q.result);
                sfile << ".L" << labelCount++ << ":" << "\n";
            }
            else if(q.op == ARR_IDX_ARG) {
                sfile << "\tmovl\t" << toPrint2 << ", %edx" << "\n";
                sfile << "cltq" << "\n";
                if(off1 < 0) {
                    sfile << "\tmovl\t" << off1 << "(%rbp,%rdx,1), %eax" << "\n";
                    sfile << "\tmovl\t%eax, " << toPrintRes << "\n";
                }
                else {
                    sfile << "\tmovq\t" << off1 << "(%rbp), %rdi" << "\n";
                    sfile << "\taddq\t%rdi, %rdx" << "\n";
                    sfile << "\tmovq\t(%rdx) ,%rax" << "\n";
                    sfile << "\tmovq\t%rax, " << toPrintRes << "\n";
                }
            }
            else if(q.op == ARR_IDX_RES) {
                sfile << "\tmovl\t" << toPrint2 << ", %edx" << "\n";
               printmov(sfile, toPrint1);
                sfile << "cltq" << "\n";
                if(offRes > 0) {
                    sfile << "\tmovq\t" << offRes << "(%rbp), %rdi" << "\n";
                    sfile << "\taddq\t%rdi, %rdx" << "\n";
                    sfile << "\tmovl\t%eax, (%rdx)" << "\n";
                }
                else
                    sfile << "\tmovl\t%eax, " << offRes << "(%rbp,%rdx,1)" << "\n";
            }
            else if(q.op == REFERENCE) {
                if(off1 < 0) {
                    sfile << "\tleaq\t" << toPrint1 << ", %rax" << "\n";
                    sfile << "\tmovq\t%rax, " << toPrintRes << "\n";
                }
                else {
                    sfile << "\tmovq\t" << toPrint1 << ", %rax" << "\n";
                    sfile << "\tmovq\t%rax, " << toPrintRes << "\n";
                }
            }
            else if(q.op == DEREFERENCE) {
                sfile << "\tmovq\t" << toPrint1 << ", %rax" << "\n";
                sfile << "\tmovq\t(%rax), %rdx" << "\n";
                sfile << "\tmovq\t%rdx, " << toPrintRes << "\n";
            }
            else if(q.op == L_DEREF) {
                sfile << "\tmovq\t" << toPrintRes << ", %rdx" << "\n";
               printmov(sfile, toPrint1);
                sfile << "\tmovl\t%eax, (%rdx)" << "\n";
            }
            else if(q.op == PARAM) {
                int paramSize;
                DataType t;
                if(glb3 != NULL)
                    t = glb3->type.type;
                else
                    t = loc3->type.type;
                if(t == INT)
                    paramSize = __INTEGER_SIZE;
                else if(t == CHAR)
                    paramSize = __CHARACTER_SIZE;
                else
                    paramSize = __POINTER_SIZE;
                stringstream ss;
                if(q.result[0] == '.')
                    ss << "\tmovq\t$" << toPrintRes << ", %rax" <<"\n";
                else if(q.result[0] >= '0' && q.result[0] <= '9')
                    ss << "\tmovq\t$" << q.result << ", %rax" <<"\n";
                else {
                    if(loc3->type.type != ARRAY) {
                        if(loc3->type.type != POINTER)
                            ss << "\tmovq\t" << toPrintRes << ", %rax" <<"\n";
                        else if(loc3 == NULL)
                            ss << "\tleaq\t" << toPrintRes << ", %rax" <<"\n";
                        else
                            ss << "\tmovq\t" << toPrintRes << ", %rax" <<"\n";
                    }
                    else {
                        if(offRes < 0)
                            ss << "\tleaq\t" << toPrintRes << ", %rax" <<"\n";
                        else {
                            ss << "\tmovq\t" << offRes << "(%rbp), %rdi" <<"\n";
                            ss << "\tmovq\t%rdi, %rax" <<"\n";
                        }
                    }
                }
                parameters.push(make_pair(ss.str(), paramSize));
            }
            else if(q.op == CALL) {
                int numParams = atoi(q.arg1.c_str());
                int totalSize = 0, k = 0;

                // We need different registers based on the parameters
                if(numParams > 6) {
                    for(int i = 0; i < numParams - 6; i++) {
                        string s = parameters.top().first;
                        sfile << s << "\tpushq\t%rax" << "\n";
                        totalSize += parameters.top().second;
                        parameters.pop();
                    }
                    sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %r9d" << "\n";
                    totalSize += parameters.top().second;
                    parameters.pop();
                    sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %r8d" << "\n";
                    totalSize += parameters.top().second;				
                    parameters.pop();
                    sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rcx" << "\n";
                    totalSize += parameters.top().second;
                    parameters.pop();
                    sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rdx" << "\n";
                    totalSize += parameters.top().second;
                    parameters.pop();
                    sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rsi" << "\n";
                    totalSize += parameters.top().second;
                    parameters.pop();
                    sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rdi" << "\n";
                    totalSize += parameters.top().second;
                    parameters.pop();
                }
                else {
                    while(!parameters.empty()) {
                        switch(parameters.size()){
                            case 1:sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rdi" << "\n";
                            totalSize += parameters.top().second;
                            parameters.pop();break;
                            case 2:sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rsi" << "\n";
                            totalSize += parameters.top().second;
                            parameters.pop();break;
                            case 3:sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rdx" << "\n";
                            totalSize += parameters.top().second;
                            parameters.pop();break;
                            case 4:sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %rcx" << "\n";
                            totalSize += parameters.top().second;
                            parameters.pop();break;
                            case 5:sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %r8d" << "\n";
                            totalSize += parameters.top().second;
                            parameters.pop();break;
                            case 6:
                            sfile << parameters.top().first << "\tpushq\t%rax" << "\n" << "\tmovq\t%rax, %r9d" << "\n";
                            totalSize += parameters.top().second;
                            parameters.pop();
                            break;
                            default:break;
                        }
                    }
                }
                sfile << "\tcall\t" << q.result << "\n";
                if(q.arg2 != "")
                    sfile << "\tmovq\t%rax, " << toPrint2 << "\n";
                sfile << "\taddq\t$" << totalSize << ", %rsp" << "\n";
            }
            else if(q.op == RETURN) {
                if(q.result != "")
                    sfile << "\tmovq\t" << toPrintRes << ", %rax" << "\n";
                sfile << "\tleave" << "\n";
                sfile << "\tret" << "\n";
            }

        }        
    }
}

int main(int argc, char* argv[]) {
    ST = &globalST;
    yyparse();

    asmFileName = "A6_30_" + string(argv[argc - 1]) + ".s";
    ofstream sfile;
    sfile.open(asmFileName);

    quadList.print();               // Print the three address quads

    ST->print("ST.global");         // Print the symbol tables

    ST = &globalST;

    generateTargetCode(sfile);      // Generate the target assembly code

    sfile.close();

    return 0;
}