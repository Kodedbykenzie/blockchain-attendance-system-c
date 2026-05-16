#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>

#include "crypto.h"


// =========================
// SHA-256 HASH FUNCTION
// =========================
void calculate_hash(Block *block, char output[65]) {

    char data[512];

    sprintf(data,
        "%d%ld%s%s%s%s%s",
        block->index,
        block->timestamp,
        block->student_id,
        block->full_name,
        block->course_code,
        block->status,
        block->previous_hash
    );

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256((unsigned char*)data, strlen(data), hash);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(output + (i * 2), "%02x", hash[i]);
    }

    output[64] = '\0';
}


// =========================
// ECDSA KEY GENERATION
// =========================
EC_KEY* generate_keys() {

    EC_KEY *key = EC_KEY_new_by_curve_name(NID_secp256k1);

    if (key == NULL) {
        printf("Key creation failed\n");
        return NULL;
    }

    if (!EC_KEY_generate_key(key)) {
        printf("Key generation failed\n");
        return NULL;
    }

    return key;
}


// =========================
// SIGN BLOCK (ECDSA)
// =========================
int sign_block(
    EC_KEY *key,
    Block *block,
    unsigned char *signature,
    unsigned int *sig_len
) {

    if (!key) return 0;

    return ECDSA_sign(
        0,
        (unsigned char*)block->hash,
        64,
        signature,
        sig_len,
        key
    );
}


// =========================
// VERIFY SIGNATURE
// =========================
int verify_signature(
    EC_KEY *key,
    Block *block,
    unsigned char *signature,
    unsigned int sig_len
) {

    return ECDSA_verify(
        0,
        (unsigned char*)block->hash,
        64,
        signature,
        sig_len,
        key
    );
}