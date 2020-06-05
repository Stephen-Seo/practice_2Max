#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct SimpleVector {
    int *data;
    unsigned int capacity;
    unsigned int size;
} SimpleVector;

void sv_init(SimpleVector *sv, unsigned int capacity) {
    if(!sv->data) {
        sv->data = (int*)malloc(capacity * sizeof(int));
        sv->capacity = capacity;
        sv->size = 0;
    }
}

void sv_cleanup(SimpleVector *sv) {
    if(sv->data) {
        free(sv->data);
        sv->data = NULL;
        sv->capacity = 0;
        sv->size = 0;
    }
}

void sv_add(SimpleVector *sv, int value) {
    if(!sv->data || sv->capacity == 0) {
        return;
    }
    if(sv->size == sv->capacity) {
        int *new_data = (int*)malloc(sv->capacity * 2 * sizeof(int));
        memcpy(new_data, sv->data, sv->size * sizeof(int));
        free(sv->data);
        sv->data = new_data;
        sv->capacity *= 2;
    }

    sv->data[sv->size] = value;
    ++sv->size;
}

void sv_print(SimpleVector *sv) {
    if(!sv->data || sv->capacity == 0) {
        puts("Invalid SimpleVector, cannot print");
        return;
    } else if(sv->size == 0) {
        puts("SimpleVector is empty");
        return;
    }

    for(unsigned int i = 0; i < sv->size; ++i) {
        printf("%d ", sv->data[i]);
    }
    printf("\n");
}

int is_digit_sum_equal(int a, int b) {
    int sum_a = 0;
    int sum_b = 0;

    while(a > 0) {
        sum_a += a % 10;
        a /= 10;
    }
    while(b > 0) {
        sum_b += b % 10;
        b /= 10;
    }

    return sum_a == sum_b ? 1 : 0;
}

int main(int argc, char **argv) {
    SimpleVector sv;
    memset(&sv, 0, sizeof(SimpleVector));
    sv_init(&sv, 32);

    int temp_i;
    const char *temp_c;
    --argc; ++argv;
    while(argc > 0) {
        temp_i = 0;
        temp_c = argv[0];
        while(*temp_c != 0) {
            if(*temp_c < '0' || *temp_c > '9') {
                printf("ERROR: Input is not a digit!\n");
                return 1;
            }
            temp_i = temp_i * 10 + *temp_c - '0';
            ++temp_c;
        }
        sv_add(&sv, temp_i);
        --argc; ++argv;
    }
    sv_print(&sv);

    // Actually do the problem here
    temp_i = 0;
    int temp_sum;
    for(unsigned int i = 0; i < sv.size; ++i) {
        for(unsigned int j = i + 1; j < sv.size; ++j) {
            if(is_digit_sum_equal(sv.data[i], sv.data[j])) {
                temp_sum = sv.data[i] + sv.data[j];
                printf("%d and %d has sum of %d\n", sv.data[i], sv.data[j], temp_sum);
                if(temp_sum > temp_i) {
                    temp_i = temp_sum;
                }
            }
        }
    }

    printf("Got result %d\n", temp_i);

    sv_cleanup(&sv);
    return 0;
}
