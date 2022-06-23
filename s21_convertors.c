#include "s21_decimal.h"

/**
 * @brief Конвертация из int в децимал
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int exit_status = 0;

    if (dst == NULL) {
        exit_status = 1;
    } else {
        dst->bits[0] = 0;
        dst->bits[1] = 0;
        dst->bits[2] = 0;
        dst->bits[3] = 0;

        if (src < 0) {
            src *= -1;
            s21_set_sign(dst, 1);
        }

        dst->bits[LOW] = src;
    }

    return exit_status;
}

/**
 * @brief Конвертация из float в decimal
 * @return 0 - OK
 * @return 1 - число слишком велико или равно бесконечности
 * @return 2 - число слишком мало или равно отрицательной бесконечности
 * @return 3 - деление на 0
 */
// int s21_from_float_to_decimal(float src, s21_decimal *dst) {
//     int exit_status = 0;

//     if (dst == NULL || isfinite(src) == 0) {
//         exit_status = 1;
//     } else {
//         dst->bits[0] = 0;
//         dst->bits[1] = 0;
//         dst->bits[2] = 0;
//         dst->bits[3] = 0;

//         union float_value float_number_bits;
//         float_number_bits.float_view = src;

//         // Считываем знак
//         // Исправить маску ???
//         int float_number_sign = (int) (float_number_bits.int_view & 0b10000000000000000000000000000);

//         // Считываем экспоненту
//         int exponent = 0;

//         for (int i = 0; i < 8; i++) {
//             int bit = (int) ((float_number_bits.int_view >> (30 - i)) & 1u);

//             exponent = exponent << 1;
//             s21_set_bit((unsigned int *) &exponent, 0, bit);
//         }

//         exponent = exponent - 127;

//         if (exponent > 95) {
//             exit_status = 1;
//         } else  if (exponent > -95) {
//             // Нормализуем число
//             int scale = 0;

//             // Если число меньше 1 
//             Исправить знак ???
//             while ((int) src > 1) {
//                 src *= 10;
//                 scale++;
//             }

//             // Если число больше 10
//             while (src > 10) {
//                 src /= 10;
//                 scale--;
//             }

//             int mask = 0x400000;
//             double result = 1;

//             // Возводим все биты в отрицательную степень двойки
//             for (int i = 1; mask != 0; i++) {
//                 if (float_number_bits.int_view & mask) {
//                     result += pow(2, -i);
//                 }

//                 mask >>= 1;
//             }

//             // Приводим число к 8-9 знакам перед запятой
//             result *= pow(2, exponent);
//             result *= pow(10, 8 + scale);

//             if (scale > 0) {
//                 while (result < 10000000) {
//                     result *= 10;
//                 }
//             }

//             long int tmp = round(result);
//             int remainder = 0;

//             while (tmp >= 10000000) {
//                 remainder = tmp % 10;
//                 tmp = round(tmp);
//                 tmp /= 10;
//             }

//             while (scale + 7 > 29) {
//                 remainder = tmp % 10;
//                 tmp /= 10;
//                 scale--;
//             }

//             if (remainder > 4) {
//                 tmp++;
//             }

//             while (tmp % 10 == 0) {
//                 tmp /= 10;
//                 scale--;
//             }

//             s21_from_int_to_decimal((int) tmp, dst);

//             while (scale + 7 <= 0) {
//                 s21_multiply_by_10(dst), scale++;
//             }

//             s21_set_sign(dst, float_number_sign);
//             s21_set_scale(dst, scale + 6);
//         }
//     }

//     return exit_status;
// }

/**
 * @brief Конвертация из децимал в int
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_decimal_to_int(s21_decimal src, int *dst) {
    // Считываем знак
    int sign = s21_get_sign(src);

    // Обрезаем дробную часть
    s21_decimal integer_number = {{0, 0, 0, 0}};
    s21_truncate(src, &integer_number);

    *dst = (int) src.bits[LOW];

    if (sign == 1) {
        *dst *= -1;
    }

    return 0;
}

/**
 * @brief Конвертация из децимал в float
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int exit_status = 0;

    if (dst == NULL) {
        exit_status = 1;
    } else {
        union float_value float_number_bits;
        float_number_bits.float_view = 0;

        int src_sign = s21_get_sign(src);
        s21_set_sign(&src, 0);

        s21_decimal integer_src = {{0, 0, 0, 0}};
        s21_decimal fractional_part_src = {{0, 0, 0, 0}};
        s21_decimal one_number = {{1, 0, 0, 0}};

        s21_truncate(src, &integer_src);
        s21_sub(src, integer_src, &fractional_part_src);

        int int_highest_bit = s21_get_highest_bit(integer_src);
        int fractional_highest_bit = s21_get_highest_bit(fractional_part_src);

        if (int_highest_bit != -1) {
            // Записываем экспоненту
            float_number_bits.int_view = 127 + int_highest_bit;

            if (int_highest_bit > 22) {
                // Если количстево битов целой части больше количества битов мантиссы
                // Записываем мантиссу
                for (int i = 0; i < 23; i++) {
                    int bit = s21_get_bit(integer_src, int_highest_bit - 1 - i);

                    float_number_bits.int_view <<= 1;

                    if (bit == 1) {
                        float_number_bits.int_view |= 1u;
                    }

                    if (i == 22) {
                        s21_shift_left(&fractional_part_src);

                        if (s21_is_greater_or_equal(fractional_part_src, one_number) == 1) {
                            float_number_bits.int_view += 1u;
                        }
                    }
                }
            } else {
                // Если количстево битов целой части меньше количества битов мантиссы
                // Записываем мантиссу
                for (int i = 0; i < int_highest_bit; i++) {
                    int bit = s21_get_bit(integer_src, int_highest_bit - 1 - i);

                    float_number_bits.int_view <<= 1;

                    if (bit == 1) {
                        float_number_bits.int_view |= 1u;
                    }
                }

                for (int i = 0; i < 23 - int_highest_bit; i++) {
                    s21_decimal sub_result = {{0, 0, 0, 0}};

                    float_number_bits.int_view <<= 1;
                    s21_shift_left(&fractional_part_src);

                    if (s21_is_greater_or_equal(fractional_part_src, one_number) == 1) {
                        float_number_bits.int_view |= 1u;
                        s21_sub(fractional_part_src, one_number, &sub_result);
                        fractional_part_src = sub_result;
                    }

                    // Если после последнего бита мантиссы идёт 1, то добавляем флоату 1u
                    if (i == 23 - int_highest_bit - 1) {
                        s21_shift_left(&fractional_part_src);

                        if (s21_is_greater_or_equal(fractional_part_src, one_number) == 1) {
                            float_number_bits.int_view += 1u;
                        }
                    }
                }
            }
        } else {
            // Нет целой части
            if (fractional_highest_bit != -1) {
                int exponent = 0;

                while (s21_is_greater_or_equal(fractional_part_src, one_number) != 1) {
                    s21_shift_left(&fractional_part_src);
                    exponent--;
                }

                s21_decimal sub_one_result = {{0, 0, 0, 0}};
                s21_sub(fractional_part_src, one_number, &sub_one_result);
                fractional_part_src = sub_one_result;

                float_number_bits.int_view = 127 + exponent;

                for (int i = 0; i < 23; i++) {
                    s21_decimal sub_result = {{0, 0, 0, 0}};

                    float_number_bits.int_view <<= 1;
                    s21_shift_left(&fractional_part_src);

                    if (s21_is_greater_or_equal(fractional_part_src, one_number) == 1) {
                        float_number_bits.int_view |= 1u;
                        s21_sub(fractional_part_src, one_number, &sub_result);
                        fractional_part_src = sub_result;
                    }

                    if (i == 22) {
                        s21_shift_left(&fractional_part_src);

                        if (s21_is_greater_or_equal(fractional_part_src, one_number) == 1) {
                            float_number_bits.int_view += 1u;
                        }
                    }
                }
            }
        }

        // Устанавливаем знак
        if (src_sign == 1) {
            float_number_bits.int_view |= 0b10000000000000000000000000000000;
        }

        *dst = float_number_bits.float_view;
    }

    return exit_status;
}
