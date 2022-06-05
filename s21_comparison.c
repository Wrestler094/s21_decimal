#include "s21_decimal.h"

/**
 * Сравнивает меньше ли число 1, чем число 2
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_less(s21_decimal number1, s21_decimal number2) {
    int is_greater_or_equal = s21_is_greater_or_equal(number1, number2);

    return is_greater_or_equal == 0 ? 1 : 0;
}

/**
 * Сравнивает число 1 меньше или равно (<=), чем число 2
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_less_or_equal(s21_decimal number1, s21_decimal number2) {
    int is_greater = s21_is_greater(number1, number2);

    return is_greater == 0 ? 1 : 0;
}

/**
 * Сравнивает больше ли число 1, чем число 2
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_greater(s21_decimal number1, s21_decimal number2) {
    int is_greater = 0;
    int number1_scale = s21_get_scale(number1);
    int number2_scale = s21_get_scale(number2);
    int value1_sign = s21_get_sign(number1);
    int value2_sign = s21_get_sign(number2);

    if (number1_scale != number2_scale) {
        s21_equalize_scale(&number1, &number2);
    }

    // Если 2 положительных числа или 2 отрицательных числа
    if (value1_sign == value2_sign) {
        if (number1.bits[HIGH] != number2.bits[HIGH]) {
            // Старший бит одного из чисел больше
            // Если старший бит 1 числа больше и числа положительные или
            // старший бит меньше и числа отрицательные, то оно больше
            if ((number1.bits[HIGH] > number2.bits[HIGH] && value1_sign == 0) ||
                (number1.bits[HIGH] < number2.bits[HIGH] && value1_sign == 1)) {
                is_greater = 1;
            }
        } else {
            if (number1.bits[MID] != number2.bits[MID]) {
                // Старшие биты равны, средний бит одного из чисел больше
                // Если средний бит 1 числа больше и числа положительные или
                // средний бит меньше и числа отрицательные, то оно больше
                if ((number1.bits[MID] > number2.bits[MID] && value1_sign == 0) ||
                    (number1.bits[MID] < number2.bits[MID] && value1_sign == 1)) {
                    is_greater = 1;
                }
            } else {
                if (number1.bits[LOW] != number2.bits[LOW]) {
                    // Старшие и средние биты равны, младший бит одного из чисел больше
                    // Если младший бит 1 числа больше и числа положительные или
                    // младшйи бит меньше и числа отрицательные, то оно больше
                    if ((number1.bits[LOW] > number2.bits[LOW] && value1_sign == 0) ||
                        (number1.bits[LOW] < number2.bits[LOW] && value1_sign == 1)) {
                        is_greater = 1;
                    }
                }
            }
        }
    } else {
        // Если 1 положительное и 1 отрицательное
        // Если первое положительное, то оно больше
        if (value1_sign == 0) {
            is_greater = 1;
        }
    }

    return is_greater;
}

/**
 * Сравнивает число 1 больше или равно (>=), чем число 2
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_greater_or_equal(s21_decimal number1, s21_decimal number2) {
    int is_equal = s21_is_greater(number1, number2);
    int is_greater = s21_is_equal(number1, number2);

    return is_equal || is_greater ? 1 : 0;
}

/**
 * Сравнивает 2 числа на равенство
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_equal(s21_decimal number1, s21_decimal number2) {
    int number1_scale = s21_get_scale(number1);
    int number2_scale = s21_get_scale(number2);
    int value1_sign = s21_get_sign(number1);
    int value2_sign = s21_get_sign(number2);

    if (number1_scale != number2_scale) {
        s21_equalize_scale(&number1, &number2);
    }

    int is_sign_equal = value1_sign == value2_sign ? 1 : 0;
    int is_low_bits_equal = number1.bits[LOW] == number2.bits[LOW] ? 1 : 0;
    int is_mid_bits_equal = number1.bits[MID] == number2.bits[MID] ? 1 : 0;
    int is_high_bits_equal = number1.bits[HIGH] == number2.bits[HIGH] ? 1 : 0;

    return is_sign_equal && is_low_bits_equal && is_mid_bits_equal && is_high_bits_equal ? 1 : 0;
}

/**
 * Сравнивает 2 числа на неравенство
 * @return 0 - FALSE, 1 - TRUE
 */
int s21_is_not_equal(s21_decimal number1, s21_decimal number2) {
    int is_equal = s21_is_equal(number1, number2);

    return is_equal == 0 ? 1 : 0;
}
