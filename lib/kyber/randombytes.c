#include "randombytes.h"
#include <esp_system.h> // For esp_random()

void randombytes(uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; i++) {
        buf[i] = (uint8_t)(esp_random() & 0xFF);
    }
}
