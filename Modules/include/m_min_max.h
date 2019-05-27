#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Returns value within upper and lower limits

float check_lower_upper_range(float value, float lower, float upper);

/**
 * @brief returns the lower value of the two
 *
 * @param[in] a  number
 * @param[in] b  number
 *
 * @return uint32_t the lower value
 */
uint32_t min(uint32_t a, uint32_t b);

/**
 * @brief returns the higher value of the two
 *
 * @param[in] a  number
 * @param[in] b  number
 *
 * @return uint32_t the higher value
 */
uint32_t max(uint32_t a, uint32_t b);