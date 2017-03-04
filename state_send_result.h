
#ifndef STATE_SEND_RESULT_H
#define STATE_SEND_RESULT_H

#include "state.h"

#include <stdint.h>

void transition_to_send_result(crypto_state_t * state, const char * res, uint16_t res_len);


#endif
