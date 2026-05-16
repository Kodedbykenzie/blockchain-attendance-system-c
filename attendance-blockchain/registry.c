#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registry.h"

Student students[MAX_STUDENTS];
int student_count = 0;

int load_students(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        printf("ERROR: students.txt missing\n");
        return 0;
    }

    char line[128];

    while (fgets(line, sizeof(line), file)) {

        line[strcspn(line, "\n")] = 0;

        char *token = strtok(line, ",");

        if (!token) continue;
        strcpy(students[student_count].student_id, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(students[student_count].full_name, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(students[student_count].course_code, token);

        student_count++;
    }

    fclose(file);

    if (student_count == 0) {
        printf("ERROR: Registry empty\n");
        return 0;
    }

    return 1;
}

Student* find_student(const char *id) {

    for (int i = 0; i < student_count; i++) {

        if (strcmp(students[i].student_id, id) == 0) {
            return &students[i];
        }
    }

    return NULL;
}