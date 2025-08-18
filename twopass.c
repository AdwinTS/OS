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
        start = (int)strtol(operand, NULL, 16);   // read as HEX
        fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\n", addr, label, opcode, operand);
        fprintf(objc, "H^%-6s^%06X^%06X\n", label, start, length);
        fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);
    } else {
        start = 0;
    }

    // Prepare text record buffer
    char textRec[500] = "";
    int textLen = 0;   // length in bytes
    int textStart = start;

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
                        char objCode[20];
                        sprintf(objCode, "%s%s", code, symaddr);
                        sprintf(textRec + strlen(textRec), "^%s", objCode);
                        textLen += 3;  // instruction size
                        fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n",
                                addr, label, opcode, operand, objCode);
                        sym_found = 1;
                        break;
                    }
                }
                if (!sym_found) {
                    char objCode[20];
                    sprintf(objCode, "%s0000", code);
                    sprintf(textRec + strlen(textRec), "^%s", objCode);
                    textLen += 3;
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n",
                            addr, label, opcode, operand, objCode);
                }
                break;
            }
        }

        // If not found in OPTAB (assembler directives)
        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                temp = atoi(operand);
                char objCode[20];
                sprintf(objCode, "%06X", temp);
                sprintf(textRec + strlen(textRec), "^%s", objCode);
                textLen += 3;
                fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%06X\n",
                        addr, label, opcode, operand, temp);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    char objCode[100] = "";
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        char hex[5];
                        sprintf(hex, "%02X", operand[i]);
                        strcat(objCode, hex);
                    }
                    sprintf(textRec + strlen(textRec), "^%s", objCode);
                    textLen += (strlen(operand) - 3);
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n",
                            addr, label, opcode, operand, objCode);
                } else if (operand[0] == 'X') {
                    char objCode[100] = "";
                    for (int i = 2; i < (int)strlen(operand) - 1; i++) {
                        char hex[5];
                        sprintf(hex, "%c", operand[i]);
                        strcat(objCode, hex);
                    }
                    sprintf(textRec + strlen(textRec), "^%s", objCode);
                    textLen += (strlen(operand) - 3) / 2;
                    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\t%s\n",
                            addr, label, opcode, operand, objCode);
                }
            } else {
                // RESW / RESB → no object code
                fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\n",
                        addr, label, opcode, operand);
            }
        }

        fscanf(inter, "%s %s %s %s", addr, label, opcode, operand);
    }

    // Write final text record with length
    fprintf(objc, "T^%06X^%02X%s\n", textStart, textLen, textRec);

    // END line
    fprintf(asml, "%-6s\t%-6s\t%-6s\t%-6s\n", addr, label, opcode, operand);
    fprintf(objc, "E^%06X\n", start);

    fclose(optab);
    fclose(symtab);
    fclose(asml);
    fclose(objc);
    fclose(inter);
    fclose(leng);

    printf("Pass 2 completed successfully.\n");
    return 0;
}
