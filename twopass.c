#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int start, length, temp;
    char addr[10], label[10], opcode[10], operand[10];
    char mnemonic[10], code[10];
    char symbol[10], symaddr[10];

    FILE *inter, *optab, *symtab, *asml, *objc, *leng;

    inter = fopen("input2.txt", "r");
    optab = fopen("optab2.txt", "r");
    symtab = fopen("symbol2.txt", "r");
    asml = fopen("asml.txt", "w");
    objc = fopen("obj.txt", "w");
    leng = fopen("length2.txt", "r");

    if (!inter || !optab || !symtab || !asml || !objc || !leng) {
        printf("Error: Could not open one or more files.\n");
        return 1;
    }

    fscanf(leng, "%d", &length);

    // Read first line
    fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);

    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\n", addr, label, opcode, operand);
        fprintf(objc, "H^%-6s^%06d^%06X\n", label, start, length);
        fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);
    } else {
        start = 0;
    }

    // Start text record
    fprintf(objc, "T^%06d^", start);

    while (strcmp(opcode, "END") != 0) {
        int found = 0;
        rewind(optab);

        // Search opcode in OPTAB
        while (fscanf(optab, "%s %s", mnemonic, code) != EOF) {
            if (strcmp(mnemonic, opcode) == 0) {
                found = 1;
                rewind(symtab);
                int sym_found = 0;

                while (fscanf(symtab, "%s %s", symbol, symaddr) != EOF) {
                    if (strcmp(symbol, operand) == 0) {
                        fprintf(objc, "%s%s^", code, symaddr);
                        fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s%s\n",
                                addr, label, opcode, operand, code, symaddr);
                        sym_found = 1;
                        break;
                    }
                }
                if (!sym_found) {
                    fprintf(objc, "%s0000^", code);
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s0000\n",
                            addr, label, opcode, operand, code);
                }
                break;
            }
        }

        // If not found in OPTAB (assembler directives)
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                temp = atoi(operand);
                fprintf(objc, "%06d^", temp);
                fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%06d\n",
                        addr, label, opcode, operand, temp);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        fprintf(objc, "%02d", operand[i]);
                    }
                    fprintf(objc, "^");
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n",
                            addr, label, opcode, operand, operand);
                } else if (operand[0] == 'X') {
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        fprintf(objc, "%c", operand[i]);
                    }
                    fprintf(objc, "^");
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n",
                            addr, label, opcode, operand, operand);
                }
            } else {
                // RESW / RESB or unknown → no object code
                fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\n",
                        addr, label, opcode, operand);
            }
        }

        fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);
    }

    // END line
    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\n", addr, label, opcode, operand);
    fprintf(objc, "\nE^%06d\n", start);

    fclose(optab);
    fclose(symtab);
    fclose(asml);
    fclose(objc);
    fclose(inter);
    fclose(leng);

    printf("Pass 2 completed successfully.\n");
    return 0;
}
