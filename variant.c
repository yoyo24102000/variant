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

// Function to display the content of a variant
void variant_display(const struct variant *v) {
    switch (v->type) {
        case TYPE_INT:
            printf("%d\n", v->type_any.integer);
            break;
        case TYPE_FLOAT:
            printf("%f\n", v->type_any.floating);
            break;
        case TYPE_CHAR:
            printf("%c\n", v->type_any.character);
            break;
        case TYPE_STRING:
            printf("%s\n", v->type_any.string);
            break;
        case TYPE_NULL:
            printf("NULL\n");
            break;
        default:
            // Handle invalid type
            break;
    }
}

// Function to check if two variants are equal
bool variant_equal(const struct variant *left, const struct variant *right) {
    if (left->type != right->type) {
        return false;
    }

    switch (left->type) {
        case TYPE_INT:
            return left->type_any.integer == right->type_any.integer;
        case TYPE_FLOAT:
            return left->type_any.floating == right->type_any.floating;
        case TYPE_CHAR:
            return left->type_any.character == right->type_any.character;
        case TYPE_STRING:
            return strcmp(left->type_any.string, right->type_any.string) == 0;
        case TYPE_NULL:
            return true; // Two NULL variants are equal
        default:
            // Handle invalid type
            return false;
    }
}

// Function to find an element in a variant array
int variant_find(const struct variant *array, size_t len, enum type type, union type_any value) {
    for (size_t i = 0; i < len; ++i) {
        if (array[i].type == type) {
            switch (type) {
                case TYPE_INT:
                    if (array[i].type_any.integer == value.integer) {
                        return i;
                    }
                    break;
                case TYPE_FLOAT:
                    if (array[i].type_any.floating == value.floating) {
                        return i;
                    }
                    break;
                case TYPE_CHAR:
                    if (array[i].type_any.character == value.character) {
                        return i;
                    }
                    break;
                case TYPE_STRING:
                    if (strcmp(array[i].type_any.string, value.string) == 0) {
                        return i;
                    }
                    break;
                case TYPE_NULL:
                    return i; // NULL variants are considered equal
                default:
                    // Handle invalid type
                    return -1;
            }
        }
    }
    return -1; // Element not found
}

// Function to calculate the sum of numeric elements in a variant array
float variant_sum(const struct variant *array, size_t len) {
    float sum = 0.0;

    for (size_t i = 0; i < len; ++i) {
        switch (array[i].type) {
            case TYPE_INT:
                sum += array[i].type_any.integer;
                break;
            case TYPE_FLOAT:
                sum += array[i].type_any.floating;
                break;
            default:
                // Ignore non-numeric types
                break;
        }
    }

    return sum;
}
