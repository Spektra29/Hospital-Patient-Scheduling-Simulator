#include "cjson.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// -------- helpers --------

static char *strdup_local(const char *s) {
    char *p = malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

static void skip_ws(const char **p) {
    while (**p == ' ' || **p == '\n' || **p == '\r' || **p == '\t')
        (*p)++;
}

// -------- creation --------

cJSON *cJSON_CreateObject() {
    cJSON *item = calloc(1, sizeof(cJSON));
    item->type = CJSON_OBJECT;
    return item;
}

cJSON *cJSON_CreateArray() {
    cJSON *item = calloc(1, sizeof(cJSON));
    item->type = CJSON_ARRAY;
    return item;
}

cJSON *cJSON_CreateString(const char *str) {
    cJSON *item = calloc(1, sizeof(cJSON));
    item->type = CJSON_STRING;
    item->valuestring = strdup_local(str);
    return item;
}

cJSON *cJSON_CreateNumber(double num) {
    cJSON *item = calloc(1, sizeof(cJSON));
    item->type = CJSON_NUMBER;
    item->valuedouble = num;
    item->valueint = (int)num;
    return item;
}

// -------- add --------

void cJSON_AddItemToObject(cJSON *object, const char *key, cJSON *item) {
    item->string = strdup_local(key);

    if (!object->child)
        object->child = item;
    else {
        cJSON *c = object->child;
        while (c->next) c = c->next;
        c->next = item;
    }
}

void cJSON_AddItemToArray(cJSON *array, cJSON *item) {
    if (!array->child)
        array->child = item;
    else {
        cJSON *c = array->child;
        while (c->next) c = c->next;
        c->next = item;
    }
}

// -------- parsing --------

static cJSON *parse_value(const char **p);

static char *parse_string(const char **p) {
    (*p)++; // skip "
    const char *start = *p;

    while (**p && **p != '"') (*p)++;

    int len = *p - start;
    char *out = malloc(len + 1);
    memcpy(out, start, len);
    out[len] = 0;

    (*p)++; // skip ending "
    return out;
}

static double parse_number(const char **p) {
    double val = atof(*p);
    while (isdigit(**p) || **p == '.') (*p)++;
    return val;
}

static cJSON *parse_array(const char **p) {
    (*p)++; // skip '['
    skip_ws(p);

    cJSON *arr = cJSON_CreateArray();

    while (**p && **p != ']') {
        cJSON *value = parse_value(p);
        cJSON_AddItemToArray(arr, value);

        skip_ws(p);
        if (**p == ',') {
            (*p)++;
            skip_ws(p);
        }
    }
    (*p)++; // skip ']'
    return arr;
}

static cJSON *parse_object(const char **p) {
    (*p)++; // skip '{'
    skip_ws(p);

    cJSON *obj = cJSON_CreateObject();

    while (**p && **p != '}') {
        // key
        char *key = parse_string(p);
        skip_ws(p);

        if (**p == ':') (*p)++;
        skip_ws(p);

        // value
        cJSON *val = parse_value(p);
        cJSON_AddItemToObject(obj, key, val);
        free(key);

        skip_ws(p);
        if (**p == ',') {
            (*p)++;
            skip_ws(p);
        }
    }
    (*p)++; // skip '}'
    return obj;
}

static cJSON *parse_value(const char **p) {
    skip_ws(p);

    if (**p == '"') {
        char *s = parse_string(p);
        cJSON *item = cJSON_CreateString(s);
        free(s);
        return item;
    }

    if (**p == '{') return parse_object(p);
    if (**p == '[') return parse_array(p);

    if (isdigit(**p) || **p == '-') {
        double num = parse_number(p);
        return cJSON_CreateNumber(num);
    }

    return NULL;
}

cJSON *cJSON_Parse(const char *json) {
    const char *p = json;
    return parse_value(&p);
}

// -------- lookup --------

cJSON *cJSON_GetObjectItem(const cJSON *object, const char *key) {
    if (!object || object->type != CJSON_OBJECT) return NULL;

    cJSON *c = object->child;
    while (c) {
        if (c->string && strcmp(c->string, key) == 0)
            return c;
        c = c->next;
    }
    return NULL;
}

int cJSON_GetArraySize(const cJSON *array) {
    if (!array || array->type != CJSON_ARRAY) return 0;

    int count = 0;
    cJSON *c = array->child;
    while (c) {
        count++;
        c = c->next;
    }
    return count;
}

cJSON *cJSON_GetArrayItem(const cJSON *array, int index) {
    if (!array || array->type != CJSON_ARRAY) return NULL;

    cJSON *c = array->child;
    for (int i = 0; i < index && c; i++)
        c = c->next;

    return c;
}

// -------- delete --------

void cJSON_Delete(cJSON *item) {
    if (!item) return;

    cJSON *child = item->child;
    while (child) {
        cJSON *next = child->next;
        cJSON_Delete(child);
        child = next;
    }

    free(item->string);
    free(item->valuestring);
    free(item);
}
