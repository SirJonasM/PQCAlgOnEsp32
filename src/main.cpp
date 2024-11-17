#include <Arduino.h>
extern "C" {
    #include "kem.h"
    #include "indcpa.h"
}


void setup() {
    // Initialize the serial communication
    Serial.begin(115200); // Set the baud rate to 115200
    while (!Serial) {
        ; // Wait for the serial port to be ready (optional for some setups)
    }
    Serial.println("Starting PQClean Kyber512 Test...");
    Serial.println("Initializing PQClean Kyber512 Test...");
    uint8_t *pk = (uint8_t *)malloc(KYBER_PUBLICKEYBYTES);
    uint8_t *sk = (uint8_t *)malloc(KYBER_SECRETKEYBYTES);
    uint8_t *ct = (uint8_t *)malloc(KYBER_CIPHERTEXTBYTES);
    uint8_t *ss = (uint8_t *)malloc(KYBER_SSBYTES);
    uint8_t *dec_ss = (uint8_t *)malloc(KYBER_SSBYTES);
    // Keypair generation
    if (!pk || !sk || !ct || !ss || !dec_ss) {
    Serial.println("Memory allocation failed!");
    while (1); // Halt
    }

    Serial.print("Heap before keypair generation: ");
    Serial.println(esp_get_free_heap_size());
    PQCLEAN_KYBER512_CLEAN_crypto_kem_keypair(pk, sk);
    Serial.print("Heap after keypair generation: ");
    Serial.println(esp_get_free_heap_size());

    Serial.print("Heap before encapsulation: ");
    Serial.println(esp_get_free_heap_size());
    PQCLEAN_KYBER512_CLEAN_crypto_kem_enc(ct, ss, pk);
    Serial.print("Heap after encapsulation: ");
    Serial.println(esp_get_free_heap_size());

    Serial.print("Heap before decapsulation: ");
    Serial.println(esp_get_free_heap_size());
    PQCLEAN_KYBER512_CLEAN_crypto_kem_dec(dec_ss, ct, sk);
    Serial.print("Heap after decapsulation: ");
    Serial.println(esp_get_free_heap_size());

    if (memcmp(ss, dec_ss, KYBER_SSBYTES) == 0) {
        Serial.println("Key exchange successful!");
    } else {
        Serial.println("Key exchange failed!");
    }

    // Print "Hello, World!" to the serial monitor
    Serial.println("Hello, World!");

    // Don't forget to free the memory at the end
    free(pk);
    free(sk);
    free(ct);
    free(ss);
    free(dec_ss);
}

void loop() {
  // Do nothing here
}
