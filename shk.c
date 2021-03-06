#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <linux/input-event-codes.h>

#define EVENT_FILE "/dev/input/event23"
#define EVCODE_DEPRESS 1
#define EVCODE_RELEASE 0

typedef struct {
    unsigned int keyNum;
    char inComm[256];
} Key;

#include "config.h"

int main(int argc, char **argv) {
    struct input_event ev;
    int fd = open(EVENT_FILE, O_RDONLY);

    while(1) {
        read(fd, &ev, sizeof(ev));
        if(ev.value == EVCODE_DEPRESS) {
            for(int j = 0; j <= (sizeof(keys) / sizeof(keys[0])); j++) {
                if(ev.code == keys[j].keyNum) {
                    system(keys[j].inComm);
                }
            }
        }
    }
    close(fd);

    return 0;
}
