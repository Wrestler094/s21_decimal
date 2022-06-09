#include "s21_decimal.h"

/**
 * Сложение 2 децимал чисел
 * @return 0 - OK
 * @return 1 - число слишком велико или равно бесконечности
 * @return 2 - число слишком мало или равно отрицательной бесконечности
 * @return 3 - деление на 0
 */
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exit_status = 0;
    int value1_scale = s21_get_scale(value_1);
    int value2_scale = s21_get_scale(value_2);
    int value1_sign = s21_get_sign(value_1);
    int value2_sign = s21_get_sign(value_2);

    if (value1_scale != value2_scale) {
        s21_equalize_scale(&value_1, &value_2);
    }

    // Если знаки обоих чисел положительные или отрицательные
    if (value1_sign == value2_sign) {
        int new_scale = s21_get_scale(value_1);
        int add_result = s21_add_without_scale(value_1, value_2, result);
        s21_set_sign(result, value1_sign);

        // Если произошло переполнение, делим на 10 и уменьшаем Scale на 1. Затем складывем снова
        if (add_result == 1 && new_scale != 0) {
            s21_divide_by_10(&value_1);
            s21_divide_by_10(&value_2);

            s21_set_scale(&value_1, new_scale - 1);
            s21_set_scale(&value_2, new_scale - 1);

            s21_add_without_scale(value_1, value_2, result);
            s21_set_sign(result, value1_sign);
        } else if (add_result == 1 && value1_sign == 0) {
            exit_status = 1;
        } else if (add_result == 1 && value1_sign == 1) {
            exit_status = 2;
        }

        s21_set_scale(result, new_scale);
    } else {
        // Если 1 знак положительный, другой отрицательный
        // Меянем знак второго числа и вызываем функцию вычитания
        if (value2_sign == 0) {
            s21_set_sign(&value_2, 1);
        } else {
            s21_set_sign(&value_2, 0);
        }

        exit_status = s21_sub(value_1, value_2, result);
    }

    return exit_status;
}

/**
 * Вычитание из числа 1 числа 2
 * @return 0 - OK
 * @return 1 - число слишком велико или равно бесконечности
 * @return 2 - число слишком мало или равно отрицательной бесконечности
 * @return 3 - деление на 0
 */
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exit_status = 0;
    int value1_scale = s21_get_scale(value_1);
    int value2_scale = s21_get_scale(value_2);
    int value1_sign = s21_get_sign(value_1);
    int value2_sign = s21_get_sign(value_2);

    if (value1_scale != value2_scale) {
        s21_equalize_scale(&value_1, &value_2);
    }

    // Если оба числа не положительные или оба не отрицательные
    // Вызываем функцию сложения
    if (value1_sign != value2_sign) {
        // Меняем знак второго числа перед сложением
        if (value2_sign == 0) {
            s21_set_sign(&value_2, 1);
        } else {
            s21_set_sign(&value_2, 0);
        }

        exit_status = s21_add(value_1, value_2, result);
    } else {
        // Смотрим какое число больше и записываем указатели на них в соответсвующие переменные
        s21_decimal *bigger_number;
        s21_decimal *smaller_number;

        s21_set_sign(&value_1, 0);
        s21_set_sign(&value_2, 0);

        if (s21_is_greater(value_1, value_2) == 1) {
            bigger_number = &value_1;
            smaller_number = &value_2;
        } else {
            bigger_number = &value_2;
            smaller_number = &value_1;
        }

        s21_set_sign(&value_1, value1_sign);
        s21_set_sign(&value_2, value2_sign);

        // Вычитаем меньшее из большего
        if (bigger_number->bits[LOW] < smaller_number->bits[LOW]) {
            if (bigger_number->bits[MID] != 0) {
                bigger_number->bits[MID] -= 1u;
                result->bits[LOW] = 4294967295u - smaller_number->bits[LOW] + bigger_number->bits[LOW];
            } else {
                bigger_number->bits[HIGH] -= 1u;
                bigger_number->bits[MID] = 4294967295u;
                result->bits[LOW] = 4294967295u - smaller_number->bits[LOW] + bigger_number->bits[LOW];
            }
        } else {
            result->bits[LOW] = bigger_number->bits[LOW] - smaller_number->bits[LOW];
        }

        if (bigger_number->bits[MID] < smaller_number->bits[MID]) {
            bigger_number->bits[HIGH] -= 1u;
            result->bits[MID] = 4294967295u - smaller_number->bits[MID] + bigger_number->bits[MID];
        } else {
            result->bits[MID] = bigger_number->bits[MID] - smaller_number->bits[MID];
        }

        result->bits[HIGH] = bigger_number->bits[HIGH] - smaller_number->bits[HIGH];

        // Ставим нужный знак
        if (s21_is_greater(value_1, value_2) == 0) {
            s21_set_sign(result, 1);
        }

        // Ставим нужный Scale
        int new_scale = s21_get_scale(value_1);
        s21_set_scale(result, new_scale);
    }

    return exit_status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exit_status = 0;
    int final_sign = 0;

    int value1_scale = s21_get_scale(value_1);
    int value2_scale = s21_get_scale(value_2);
    int value1_sign = s21_get_sign(value_1);
    int value2_sign = s21_get_sign(value_2);

    s21_decimal buffer = {{0, 0, 0, 0}};

    // Определяем итоговый Scale
    int final_scale = value1_scale + value2_scale;

    // Определяем итоговый знак числа
    if (value1_sign != value2_sign) {
        final_sign = 1;
    }

    // Явно зануляем result
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;

    int value2_highest_bit = s21_get_highest_bit(value_2);

    // Итерируемся по количеству битов второго числа
    for (int i = 0; i < value2_highest_bit + 1 && exit_status == 0; i++) {
        s21_decimal tmp = value_1;
        s21_set_scale(&tmp, 0);
        s21_set_sign(&tmp, 0);

        // На каждой итерации, если бит первого числа 1,
        // сдвигаем tmp с value1 влево на номер итерации
        // и складываем его с буфером
        if (s21_get_bit(value_2, i) == 1) {
            for (int j = 0; j < i; j++) {
                s21_shift_left(&tmp);
            }

            int add_res = s21_add(tmp, buffer, result);

            if (add_res != 0 && final_sign == 1) {
                exit_status = 1;
            } else if (add_res != 0) {
                exit_status = 2;
            } else {
                buffer = *result;
            }
        }
    }

    // Устанавливаем итоговый scale
    s21_set_scale(result, final_scale);

    // Устанавливаем итоговый знак
    s21_set_sign(result, final_sign);

    return exit_status;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int exit_status = 0;
    float float_value_1, float_value_2;
    for (int i = 0; i < 4; i++)
        result->bits[i] = 0;
    s21_from_decimal_to_float(value_1, &float_value_1);
    s21_from_decimal_to_float(value_2, &float_value_2);
    exit_status = (float_value_2 == 0 ? 3 : 0);
    if (fmod(float_value_1, 1) && fmod(float_value_2, 1) && !exit_status) {
        s21_from_float_to_decimal((float_value_1 / float_value_2), result);
    } else if (!exit_status) {
        s21_from_int_to_decimal((float_value_1 / float_value_2), result);
    }
    return exit_status;
}

/**
 * Вычисляет остаток от деления
 */
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int final_sign = 0;
    int final_scale = 0;
    int value1_scale = s21_get_scale(value_1);
    int value2_scale = s21_get_scale(value_2);
    int value1_sign = s21_get_sign(value_1);
    s21_decimal buffer = {{0, 0, 0, 0}};

    // Определяем итоговый знак числа
    if (value1_sign == 1) {
        final_sign = 1;
    }

    // Определяем итоговый scale
    if (value1_scale > value2_scale) {
        final_scale = value1_scale;
    } else {
        final_scale = value2_scale;
    }

    int highest_bit_position = s21_get_highest_bit(value_1);

    for (int i = 0; i < highest_bit_position + 2; i++) {
        if (s21_is_greater_or_equal(buffer, value_2) == 1) {
            // Записываем 1 в результат
            s21_shift_left(result);
            s21_set_bit(&result->bits[LOW], 0, 1);

            s21_decimal tmp = {{0, 0, 0, 0}};
            s21_sub(buffer, value_2, &tmp);
            buffer = tmp;

            // Берём ещё бит
            int new_bit = s21_get_bit(value_1, highest_bit_position - i);
            s21_shift_left(&buffer);
            s21_set_bit(&buffer.bits[LOW], 0, new_bit);
        } else {
            // Записываем 0 в результат
            s21_shift_left(result);
            s21_set_bit(&result->bits[LOW], 0, 0);

            // Берём ещё бит
            int new_bit = s21_get_bit(value_1, highest_bit_position - i);
            s21_shift_left(&buffer);
            s21_set_bit(&buffer.bits[LOW], 0, new_bit);
        }
    }

    s21_shift_right(&buffer);
    *result = buffer;

    // Устанавливаем итоговый scale
    s21_set_scale(result, final_scale);

    // Устанавливаем итоговый знак
    s21_set_sign(result, final_sign);

    return 0;
}
