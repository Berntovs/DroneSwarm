#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "cJSON.h"

#include "m_JSON.h"


char * location_parser(uint16_t _address, int16_t _x_cor, int16_t _y_cor, char *p_out)
{
   cJSON *root = cJSON_CreateObject();
   cJSON_AddNumberToObject(root, "addr", _address);
   cJSON_AddNumberToObject(root, "x", _x_cor);
   cJSON_AddNumberToObject(root, "y", _y_cor);
   return cJSON_Print(root);
   cJSON_Delete(root);
}

void data_parser(uint16_t _address, uint16_t _data, char *p_out)
{
   cJSON *root = cJSON_CreateObject();
   cJSON_AddNumberToObject(root, "addr", _address);
   cJSON_AddNumberToObject(root, "data", _data);
   p_out = cJSON_Print(root);
   cJSON_Delete(root);
}
