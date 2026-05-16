#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "blockchain.h"

extern Block *head;


// =========================
// SAVE CHAIN (FIXED SAFE VERSION)
// =========================
void save_chain() {

    FILE *file = fopen("attendance.dat", "wb");

    if (!file) {
        printf("Error opening file for saving.\n");
        return;
    }

    Block *temp = head;

    while (temp) {

        // Create a safe copy WITHOUT pointer corruption
        Block copy = *temp;
        copy.next = NULL;

        fwrite(&copy, sizeof(Block), 1, file);

        temp = temp->next;
    }

    fclose(file);
}


// =========================
// LOAD CHAIN (FIXED VERSION)
// =========================
void load_chain() {

    FILE *file = fopen("attendance.dat", "rb");

    if (!file) return;

    Block temp_block;

    Block *tail = NULL;

    while (fread(&temp_block, sizeof(Block), 1, file)) {

        Block *new_block = malloc(sizeof(Block));

        if (!new_block) {
            printf("Memory allocation failed\n");
            fclose(file);
            return;
        }

        *new_block = temp_block;
        new_block->next = NULL;

        if (!head) {
            head = new_block;
            tail = new_block;
        } else {
            tail->next = new_block;
            tail = new_block;
        }
    }

    fclose(file);
}