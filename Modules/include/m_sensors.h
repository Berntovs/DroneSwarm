#include <stdbool.h>
#include <stdint.h>

void sensor_mngr_init(void);
void HTS221TR_start(void);
void get_lps22hb_data(void);

void ccs811_start(void);
void get_ccs811_data(void);