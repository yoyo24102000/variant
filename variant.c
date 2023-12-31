#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>

// Enum representing the type of the variant
enum type {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_NULL
};

// Union to hold different types
union type_any {
    int integer;
    float floating;
    char character;
    const char* string;
};

// Struct representing the variant
struct variant {
    enum type type;
    union type_any type_any;
};


#include "variant.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
void variant_display(const struct variant *e)
{
    switch (e->type)
    {
    case TYPE_FLOAT:
        printf("%f\n", e->value.float_v);
        break;
    case TYPE_CHAR:
        printf("%c\n", e->value.char_v);
        break;
    case TYPE_INT:
        printf("%d\n", e->value.int_v);
        break;
    case TYPE_STRING:
        printf("%s\n", e->value.str_v);
        break;
    default:
        break;
    }
}
bool variant_equal(const struct variant *left, const struct variant *right)
{
    if (right->type != left->type)
        return false;
    switch (left->type)
    {
    case TYPE_STRING:
        if (strcmp(left->value.string, right->value.string))
            return false;
        return true;
        break;
    case TYPE_CHAR:
        if (right->value.char_v == left->value.char_v)
            return true;
        break;
    case TYPE_INT:
        if (right->value.int_v == left->value.int_v)
            return true;
        break;
    case TYPE_FLOAT:
        if (right->value.float_v == left->value.float_v)
            return true;
        break;
    default:
        return false;
    }
}
int variant_find(const struct variant *array, size_t len, enum type type,
                 union type_any value)
{
    for (size_t j = 0; j < len; j++)
    {
        if (array[j].type != type)
            continue;
        switch (type)
        {
        case TYPE_CHAR:
            if (array[j].value.char_v == value.char_v)
                return j;
            break;
        case TYPE_STRING:
            if (!(strcmp(array[j].value.str_v, value.str_v)))
                return j;
            break;
        case TYPE_INT:
            if (array[j].value.int_v == value.int_v)
                return j;
            break;
        case TYPE_FLOAT:
            if (array[j].value.float_v == value.float_v)
                return j;
            break;
        default:
            return -1;
        }
    }
    return -1;
}

float variant_sum(const struct variant *array, size_t len)
{
    float total;
    total = 0;
    for (size_t j = 0; j < len; ++j)
    {
        switch (array[j].type)
        {
        case TYPE_FLOAT:
            total = total + array[j].value.float_v;
            break;
        case TYPE_INT:
            total = total + array[j].value.int_v;
            break;
        default:
            break;
        }
    }
    return total;
}
