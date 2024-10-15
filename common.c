#include "common.h"
void init() {
    mkfifo(FIFO, 0666);
}
