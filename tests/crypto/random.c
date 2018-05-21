#include "crypto/random.c"

#include "crypto-tests.h"

void setup_random(void) {
    memset(&state, 42, sizeof(union hash_state));
}
