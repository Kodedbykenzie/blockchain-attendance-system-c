#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <time.h>

// =========================
// BLOCK STRUCT MUST COME FIRST
// =========================
typedef struct Block {

    int index;
    time_t timestamp;

    char student_id[20];
    char full_name[50];
    char course_code[10];
    char status[10];

    char previous_hash[65];

    unsigned char signature[72];
    unsigned int sig_len;

    char hash[65];

    struct Block *next;

} Block;


// =========================
// GLOBAL HEAD DECLARATION
// =========================
extern Block *head;


// =========================
// FUNCTION DECLARATIONS
// =========================
Block* create_genesis_block();

Block* create_block(
    const char *student_id,
    const char *full_name,
    const char *course_code,
    const char *status
);

void append_block(Block *new_block);

void print_chain();

int validate_chain();

#endif