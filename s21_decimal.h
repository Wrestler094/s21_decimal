#ifndef C5_S21_DECIMAL_0_SRC_S21_DECIMAL_H_
#define C5_S21_DECIMAL_0_SRC_S21_DECIMAL_H_

#include <stdio.h>
#include <math.h>

union float_value {
    int int_view;
    float float_view;
};

typedef struct {
    unsigned int bits[4];
} s21_decimal;

enum bits {
    LOW,
    MID,
    HIGH,
    SCALE
};

/*
 * Арифметические операторы
 */

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/*
 * Операторы сравнения
 */

int s21_is_less(s21_decimal number1, s21_decimal number2);
int s21_is_less_or_equal(s21_decimal number1, s21_decimal number2);
int s21_is_greater(s21_decimal number1, s21_decimal number2);
int s21_is_greater_or_equal(s21_decimal number1, s21_decimal number2);
int s21_is_equal(s21_decimal number1, s21_decimal number2);
int s21_is_not_equal(s21_decimal number1, s21_decimal number2);

/*
 * Преобразователи
 */

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/*
 * Другие функции
 */

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/*
 * Вспомогательные функции
 */

void print_decimal(s21_decimal number);

// SHIFT
void s21_shift_left(s21_decimal *number);
void s21_shift_right(s21_decimal *number);

// GET/SET BIT
int s21_get_bit(s21_decimal number, int bit_position);
int s21_get_highest_bit(s21_decimal number);
void s21_set_bit(unsigned int *source_number, int bit_position, int bit);

// GET/SET SIGN
int s21_get_sign(s21_decimal number);
void s21_set_sign(s21_decimal *number, int sign);

// GET/SET SCALE
int s21_get_scale(s21_decimal number);
void s21_set_scale(s21_decimal *number, int scale);

// EQUALIZE SCALE
void s21_equalize_scale(s21_decimal *number1, s21_decimal *number2);
int s21_is_multiply_possible(s21_decimal number);
void s21_multiply_by_10(s21_decimal *number);
int s21_add_without_scale(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
unsigned int s21_divide_by_10(s21_decimal *number);

#endif //C5_S21_DECIMAL_0_SRC_S21_DECIMAL_H_
