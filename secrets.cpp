
#include "secrets.h"

#include <stdint.h>
#include "tweetnacl.h"

static const uint8_t secretkey[crypto_secretbox_KEYBYTES] = {
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1
};

static const uint8_t nonce[crypto_secretbox_NONCEBYTES] = {
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3,4,5,6,7,8,9,
    0,1,2,3
};

const uint8_t * get_secret_key(void) {
    return secretkey;
}

const uint8_t * get_nonce(void) {
    return nonce;
}

