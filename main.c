
 #include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VARS 100
#define MAX_CLAUSES 100


typedef struct {
    int vars[MAX_VARS];
    int num_vars;
} Clause;


Clause clauses[MAX_CLAUSES];
int num_clauses = 0;
int num_vars = 0;


bool read_formula(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Nu am putut deschide fisierul.\n");
        return false;
    }


    fscanf(file, "%d %d", &num_vars, &num_clauses);

    int var;
    int i;
    for (i = 0; i < num_clauses; i++) {
        clauses[i].num_vars = 0;
        while (1) {
            fscanf(file, "%d", &var);
            if (var == 0) break;
            clauses[i].vars[clauses[i].num_vars++] = var;
        }
    }

    fclose(file);
    return true;
}


bool is_satisfied(int assignment[]) {
    int i;
    for ( i = 0; i < num_clauses; i++) {
        bool clause_satisfied = false;
        int j;
        for ( j = 0; j < clauses[i].num_vars; j++) {
            int var = clauses[i].vars[j];
            if ((var > 0 && assignment[abs(var) - 1] == 1) ||
                (var < 0 && assignment[abs(var) - 1] == 0)) {
                clause_satisfied = true;
                break;
            }
        }
        if (!clause_satisfied) {
            return false;
        }
    }
    return true;
}


bool dpll(int assignment[], int index) {
    if (index == num_vars) {
        return is_satisfied(assignment);
    }


    assignment[index] = 1;
    if (dpll(assignment, index + 1)) return true;


    assignment[index] = 0;
    if (dpll(assignment, index + 1)) return true;

    return false;
}

int main() {

    if (!read_formula("mpi.txt")) {
        return -1;
    }


    int assignment[MAX_VARS] = {0};


    if (dpll(assignment, 0)) {
        printf("Formula este satisfiabila.\n");
    } else {
        printf("Formula nu este satisfiabila.\n");
    }

    return 0;
}
