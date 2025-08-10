#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *fint, *ftab, *flen, *fsym;
    int i, length;
    char add[10], symadd[10], op[10], start[10];
    char label[20], mne[20], operand[20], symtab[20], opmne[20];

    // Open files
    fint = fopen("input2.txt", "r");
    flen = fopen("length2.txt", "r");
    ftab = fopen("optab2.txt", "r");
    fsym = fopen("symbol2.txt", "r");

    if (!fint || !flen || !ftab || !fsym) {
        printf("Error opening files.\n");
        return 1;
    }

    // Read first line from input
    fscanf(fint, "%s%s%s%s", add, label, mne, operand);

    // If START, store starting address and program length
    if (strcmp(mne, "START") == 0) {
        strcpy(start, operand);
        fscanf(flen, "%d", &length);
        fscanf(fint, "%s%s%s%s", add, label, mne, operand);
    }

    // Print header
    printf("H^%s^%s^%d\n", label, start, length);
    printf("T^00%s^", start);

    // Process each instruction until END
    while (strcmp(mne, "END") != 0) {
        int found = 0;

        // Search in OPTAB
        rewind(ftab);
        while (fscanf(ftab, "%s%s", opmne, op) == 2) {
            if (strcmp(mne, opmne) == 0) {
                // Found in OPTAB
                rewind(fsym);
                while (fscanf(fsym, "%s%s", symadd, symtab) == 2) {
                    if (strcmp(operand, symtab) == 0) {
                        printf("%s%s^", op, symadd);
                        break;
                    }
                }
                found = 1;
                break;
            }
        }

        // If not found in OPTAB, check BYTE/WORD
        if (!found) {
            if (strcmp(mne, "WORD") == 0) {
                printf("0000%s^", operand);
            } else if (strcmp(mne, "BYTE") == 0) {
                if (operand[0] == 'C' && operand[1] == '\'') {
                    for (i = 2; i < strlen(operand) - 1; i++) {
                        printf("%X", operand[i]); // hex
                    }
                    printf("^");
                }
            }
        }

        // Read next line
        fscanf(fint, "%s%s%s%s", add, label, mne, operand);
    }

    // End record
    printf("\nE^00%s\n", start);

    // Close files to finish lets goo😊
    fclose(fint);
    fclose(ftab);
    fclose(fsym);
    fclose(flen);

    return 0;
}
