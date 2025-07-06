#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef uint8_t bit;

static inline bit toffoli_gate(bit control1, bit control2, bit target) {
    return target ^ (control1 & control2);
}


static inline void fredkin_gate(bit control, bit *bit1, bit *bit2) {
    if (control) {
        bit temp = *bit1;
        *bit1 = *bit2;
        *bit2 = temp;
    }
}

static inline bit reversible_and(bit a, bit b, bit c_in) {
    return toffoli_gate(a, b, c_in);
}

static inline bit reversible_or(bit a, bit b, bit c_in) {
    bit na = !a;
    bit nb = !b;
    bit and_result = toffoli_gate(na, nb, c_in);
    return !and_result;
}

static inline bit reversible_not(bit x) {
    return !x;
}

int main(void) {
    bit a = 1;
    bit b = 0;
    bit c = 0;

    bit and_result = reversible_and(a, b, c);

    bit or_result = reversible_or(a, b, c);

    bit not_a = reversible_not(a);
  
    bit b_swap = b;
    bit c_swap = c;
    fredkin_gate(a, &b_swap, &c_swap);

    printf("Inputs: a=%u b=%u c=%u\n", a, b, c);
    printf("AND(a,b) = %u\n", and_result);
    printf("OR(a,b) = %u\n", or_result);
    printf("NOT(a) = %u\n", not_a);
    printf("Fredkin gate with control a=%u swaps b=%u and c=%u\n", a, b_swap, c_swap);

    return 0;
}
