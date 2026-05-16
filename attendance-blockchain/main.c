#include <stdio.h>
#include <string.h>
#include <openssl/ec.h>

#include "blockchain.h"
#include "registry.h"
#include "crypto.h"
#include "storage.h"
EC_KEY *key;

int main() {

    if (!load_students("students.txt")) {
        return 1;
    }

    load_chain();

    if (!head) {
        head = create_genesis_block();
    }

    // INIT CRYPTO KEY
    key = generate_keys();

    if (!key) {
        printf("Crypto key generation failed\n");
        return 1;
    }

    int choice;

    while (1) {

        printf("\n===== Attendance Blockchain =====\n");
        printf("1. Mark Attendance\n");
        printf("2. View Records\n");
        printf("3. Validate Blockchain\n");
        printf("4. Tamper Block\n");
        printf("5. Exit\n");

        scanf("%d", &choice);

        if (choice == 1) {

            char id[20];
            char status[10];

            printf("Enter Student ID: ");
            scanf("%s", id);

            Student *student = find_student(id);

            if (!student) {
                printf("ERROR: Student ID not found\n");
                continue;
            }

            printf("Enter Status (PRESENT/ABSENT/LATE): ");
            scanf("%s", status);

            Block *new_block = create_block(
                student->student_id,
                student->full_name,
                student->course_code,
                status
            );

            // SIGN BLOCK
            unsigned int sig_len;
            sign_block(key, new_block, new_block->signature, &sig_len);

            append_block(new_block);
            save_chain();

            printf("Attendance Recorded.\n");
        }

        else if (choice == 2) {
            print_chain();
        }

        else if (choice == 3) {

            if (validate_chain()) {
                printf("Blockchain VALID\n");
            } else {
                printf("Blockchain TAMPERED\n");
            }
        }

        else if (choice == 4) {

            if (head && head->next) {

                strcpy(head->next->status, "TAMPERED");
                strcpy(head->next->student_id, "HACKED");

                printf("Tampering done.\n");
            }
        }

        else if (choice == 5) {
            break;
        }
    }

    return 0;
}