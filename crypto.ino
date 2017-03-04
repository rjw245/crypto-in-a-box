#include "tweetnacl.h"

#include "state_idle.h"

#define BUFF_SIZE   256+crypto_box_ZEROBYTES

#define STATUS_LED  13


crypto_state_t state_machine;


void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(STATUS_LED, OUTPUT);

    transition_to_idle(&state_machine);
}


void loop() {
    if(Serial.available()) {
        state_machine.recv_char(&state_machine, Serial.read());
    }
    state_machine.fsm_step(&state_machine);
}

void print(const char * buf, uint16_t len) {
    Serial.write(buf, len);
}