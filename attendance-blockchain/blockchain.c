#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"
#include "crypto.h"

Block *head = NULL;

Block* create_genesis_block() {

    Block *genesis = malloc(sizeof(Block));

    genesis->index = 0;
    genesis->timestamp = time(NULL);

    strcpy(genesis->student_id, "GENESIS");
    strcpy(genesis->full_name, "GENESIS");
    strcpy(genesis->course_code, "NONE");
    strcpy(genesis->status, "NONE");

    memset(genesis->previous_hash, '0', 64);
    genesis->previous_hash[64] = '\0';

    calculate_hash(genesis, genesis->hash);

    genesis->next = NULL;

    return genesis;
}

Block* create_block(
    const char *student_id,
    const char *full_name,
    const char *course_code,
    const char *status
) {

    Block *new_block = malloc(sizeof(Block));

    Block *temp = head;

    while (temp->next) {
        temp = temp->next;
    }

    new_block->index = temp->index + 1;
    new_block->timestamp = time(NULL);

    strcpy(new_block->student_id, student_id);
    strcpy(new_block->full_name, full_name);
    strcpy(new_block->course_code, course_code);
    strcpy(new_block->status, status);

    strcpy(new_block->previous_hash, temp->hash);

    calculate_hash(new_block, new_block->hash);

    new_block->next = NULL;

    return new_block;
}

void append_block(Block *new_block) {

    Block *temp = head;

    while (temp->next) {
        temp = temp->next;
    }

    temp->next = new_block;
}

void print_chain() {

    Block *temp = head;

    while (temp) {

        printf("\nBlock %d\n", temp->index);
        printf("Student ID: %s\n", temp->student_id);
        printf("Name: %s\n", temp->full_name);
        printf("Course: %s\n", temp->course_code);
        printf("Status: %s\n", temp->status);
        printf("Hash: %s\n", temp->hash);

        temp = temp->next;
    }
}

int validate_chain() {

    Block *temp = head;

    while (temp->next) {

        char recalculated_hash[65];

        calculate_hash(temp, recalculated_hash);

        if (strcmp(temp->hash, recalculated_hash) != 0) {
            return 0;
        }

        if (strcmp(temp->next->previous_hash, temp->hash) != 0) {
            return 0;
        }

        temp = temp->next;
    }

    return 1;
}