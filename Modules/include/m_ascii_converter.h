
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Returns a hex array as an array on the ASCII format.

uint16_t hex_array_to_ascii(char *hex_array, uint8_t *ascii_array);

/**
 * @brief simple function for converting a number of tupe uint32_t to a string of ascii characers
 *
 * @param data the data to be processed
 *
 * @return returns the string
 *
 * @warning!! not working
 */
void uint_to_ascii(uint32_t data, char * out_data);