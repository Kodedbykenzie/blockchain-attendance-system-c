#ifndef CRYPTO_H
#define CRYPTO_H

#include "blockchain.h"
#include <openssl/ec.h>

void calculate_hash(Block *block, char output[65]);

// ECDSA functions
EC_KEY* generate_keys();

int sign_block(
    EC_KEY *key,
    Block *block,
    unsigned char *signature,
    unsigned int *sig_len
);

int verify_signature(
    EC_KEY *key,
    Block *block,
    unsigned char *signature,
    unsigned int sig_len
);

#endif