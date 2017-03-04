import serial
import time
import sys

RESET_DELAY = 2
DELAY = 0.1


def main():
    s = serial.Serial("/dev/ttyUSB1", 115200)
    time.sleep(RESET_DELAY)
    input = "Riley"

    print input

    while True:
        input_fmtd = "E"+input+"\n"
        s.write(input_fmtd)
        time.sleep(DELAY)
        response = ""
        while s.inWaiting():
            response += s.read()
        encrypted = response
        print [x for x in encrypted]

        time.sleep(DELAY)

        to_decrypt = "D"+encrypted+"\n"
        print "Sent", s.write(to_decrypt), "of", len(to_decrypt)
        time.sleep(DELAY)
        response = ""
        while s.inWaiting():
            response += s.read()
        decrypted = response
        print [x for x in decrypted]

        assert decrypted==input

if __name__ == "__main__":
    main()
