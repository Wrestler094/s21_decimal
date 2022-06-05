#include "s21_decimal.h"

/**
 * Округляет число до ближайшего целого числа в сторону отрицательной бесконечности
 * @return 0 - ОК
 */
int s21_floor(s21_decimal value, s21_decimal *result) {
    int value_scale = s21_get_scale(value);
    int value_sign = s21_get_sign(value);
    unsigned int buffer = 0;

    for (int i = 0; i < value_scale; i++) {
        unsigned int remainder = s21_divide_by_10(&value);
        buffer += remainder;

        if (i == value_scale - 1 && value_sign == 1 && buffer != 0) {
            if (value.bits[LOW] + 1u < value.bits[LOW]) {
                if (value.bits[MID] + 1u < value.bits[MID]) {
                    value.bits[HIGH] += 1u;
                } else {
                    value.bits[MID] += 1u;
                }
            } else {
                value.bits[LOW] += 1u;
            }
        }
    }

    *result = value;
    s21_set_sign(result, value_sign);
    s21_set_scale(result, 0);

    return 0;
}

/**
 * Округляет до ближайшего целого числа
 * @return 0 - ОК
 */
int s21_round(s21_decimal value, s21_decimal *result) {
    int value_scale = s21_get_scale(value);
    int value_sign = s21_get_sign(value);

    for (int i = 0; i < value_scale; i++) {
        if (i == value_scale - 1) {
            unsigned int remainder = s21_divide_by_10(&value);

            // Если остаток от деления больше или равен 5 добавляем 1
            if (remainder >= 5) {
                if (value.bits[LOW] + 1u < value.bits[LOW]) {
                    if (value.bits[MID] + 1u < value.bits[MID]) {
                        value.bits[HIGH] += 1u;
                    } else {
                        value.bits[MID] += 1u;
                    }
                } else {
                    value.bits[LOW] += 1u;
                }
            }
        } else {
            s21_divide_by_10(&value);
        }
    }

    *result = value;
    s21_set_sign(result, value_sign);
    s21_set_scale(result, 0);

    return 0;
}

/**
 * Возвращает целые цифры указанного Decimal числа
 * Любые дробные цифры отбрасываются, включая конечные нули
 * @return 0 - ОК
 */
int s21_truncate(s21_decimal value, s21_decimal *result) {
    int value_scale = s21_get_scale(value);
    int value_sign = s21_get_sign(value);

    for (int i = 0; i < value_scale; i++) {
        s21_divide_by_10(&value);
    }

    *result = value;
    s21_set_sign(result, value_sign);
    s21_set_scale(result, 0);

    return 0;
}

/**
 * Возвращает результат умножения указанного Decimal на -1
 * @return 0 - ОК
 */
int s21_negate(s21_decimal value, s21_decimal *result) {
    int value_sign = s21_get_sign(value);

    *result = value;

    if (value_sign == 1) {
        s21_set_sign(result, 0);
    } else {
        s21_set_sign(result, 1);
    }

    return 0;
}
