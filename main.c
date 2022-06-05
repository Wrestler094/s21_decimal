#include "s21_decimal.h"

int main(void) {
    float test = 0;
    float test2 = 2000000000;
    s21_decimal test3 = {{2000000000,0,0,0}};
//    s21_set_scale(&test3, 1);
//    s21_set_sign(&test3, 1);

    s21_from_decimal_to_float(test3, &test);

    printf("%f\n", test2);
    printf("%f\n", test);

    return 0;
}