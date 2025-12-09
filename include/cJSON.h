#ifndef CJSON_H
#define CJSON_H

#include <stddef.h>

typedef enum {
    CJSON_NULL,
    CJSON_NUMBER,
    CJSON_STRING,
    CJSON_OBJECT,
    CJSON_ARRAY
} cJSON_Type;

typedef struct cJSON {
    cJSON_Type type;

    char *string;        // object key
    char *valuestring;   // string value
    double valuedouble;  // number value
    int valueint;        // integer value

    struct cJSON *child; // array/object children
    struct cJSON *next;  // next sibling
} cJSON;

// Creation
cJSON *cJSON_CreateObject();
cJSON *cJSON_CreateArray();
cJSON *cJSON_CreateString(const char *str);
cJSON *cJSON_CreateNumber(double num);

// Adding
void cJSON_AddItemToObject(cJSON *object, const char *key, cJSON *item);
void cJSON_AddItemToArray(cJSON *array, cJSON *item);

// Parsing
cJSON *cJSON_Parse(const char *json);

// Lookup
cJSON *cJSON_GetObjectItem(const cJSON *object, const char *key);
int cJSON_GetArraySize(const cJSON *array);
cJSON *cJSON_GetArrayItem(const cJSON *array, int index);

// Print
char *cJSON_Print(const cJSON *item);

// Cleanup
void cJSON_Delete(cJSON *item);

#endif
