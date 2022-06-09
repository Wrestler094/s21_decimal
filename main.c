#include "s21_decimal.h"

int main(void) {
    s21_decimal num1 = {{123,0,0,0}};

    s21_decimal num2 = {{123,0,0,0}};
    s21_set_scale(&num2, 1);

    s21_decimal num3 = {{0,0,0,0}};

    s21_mod(num1, num2, &num3);

    print_decimal(num1);
    print_decimal(num2);
    print_decimal(num3);
    printf("---\n");

    return 0;
}