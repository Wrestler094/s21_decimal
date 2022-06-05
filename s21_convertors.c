#include "s21_decimal.h"

/**
 * Конвертация из int в децимал
 * @return 0 - OK, 1 - ошибка конвертации
 */
int s21_from_int_to_decimal(int src, s21_decimal *dst) {
    int result = 0;

    if (dst == NULL) {
        result = 1;
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

    return result;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
    int exit_status = 0;

    if (dst == NULL) {
        exit_status = 1;
    } else {
        int float_number_bits = (((*(int *) &src)));
        int float_number_sign = (int) ((float_number_bits >> 31) & 1u);
        int exponent = 0;

        // Записываем знак в децимал
        s21_set_sign(dst, float_number_sign);

        // Считываем экспоненту
        for (int i = 0; i < 8; i++) {
            int bit = (int) ((float_number_bits >> (30 - i)) & 1u);

            exponent = exponent << 1;
            s21_set_bit((unsigned int *) &exponent, 0, bit);
        }

        exponent = exponent - 127;
        //    printf("exp - %d\n", exponent);

        unsigned int int_part = 0;
        float scale_part = src;
        scale_part = scale_part - (float) (int) scale_part;

        if (exponent > 95) {
            exit_status = 1;
        } else {
            int degree = exponent;

            for (int i = 0; i < 24 && degree != -1; i++, degree--) {
                int bit = 1;

                if (i != 0) {
                    bit = (int) ((float_number_bits >> (23 - i)) & 1u);
                }

                if (degree > 0) {
                    int tmp = 1;

                    for (int j = 0; j < degree; j++) {
                        tmp *= 2;
                    }

                    int_part += tmp * bit;
                } else if (degree == 0) {
                    if (bit == 1) {
                        int_part += 1;
                    }
                }
            }

            //        printf("int_part - %d\n", int_part);
            scale_part *= 1000000;
            //        printf("scale_part - %d\n", (unsigned int) scale_part);

            s21_decimal res = {{0, 0, 0, 0}};
            s21_decimal tmp = {{0, 0, 0, 0}};
            tmp.bits[LOW] = (unsigned int) scale_part;
            dst->bits[LOW] = int_part;

            for (int k = 0; k < 6; k++) {
                s21_multiply_by_10(dst);
            }

            s21_add(tmp, *dst, &res);
            *dst = res;

            s21_set_scale(dst, 6);
        }
    }

    // Печать float числа
//    char binary_number[33];
//
//    for (int j = 0; j < 32; j++) {
//        binary_number[31 - j] = (char) ((((unsigned int) float_number_bits >> j) & 1u) + 48);
//    }
//
//    binary_number[32] = '\0';
//    printf("[%s]", binary_number);
//    printf("\n");

    return exit_status;
}

/**
 * Конвертация из децимал в int
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

// TODO: Выставить знак
int s21_from_decimal_to_float(s21_decimal src, float *dst) {
    int exit_status = 0;

    if (dst == NULL) {
        exit_status = 1;
    } else {
        union float_value float_number_bits;
        float_number_bits.float_view = 0;

        int src_sign = s21_get_sign(src);
        s21_decimal integer_src = {{0, 0, 0, 0}};
        s21_decimal fractional_part_src = {{0, 0, 0, 0}};
        s21_decimal one_number = {{1,0,0,0}};

        s21_truncate(src, &integer_src);
        s21_sub(src, integer_src, &fractional_part_src);

        int int_highest_bit = s21_get_highest_bit(integer_src);
        printf("high bit - %d\n", int_highest_bit);

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
                    s21_decimal sub_result = {{0,0,0,0}};

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
            // Все биты 0
            // Нет целой части

            printf("---111---\n");
        }





        // ---

        float test2 = 2000000000;
        int float_number_bits2 = (((*(int *) &test2)));
        char binary_number2[33];

        for (int j = 0; j < 32; j++) {
            binary_number2[31 - j] = (char) ((((unsigned int) float_number_bits2 >> j) & 1u) + 48);
        }

        binary_number2[32] = '\0';
        printf("[%s]", binary_number2);
        printf("\n");

        // ---

        char binary_number[33];

        for (int j = 0; j < 32; j++) {
            binary_number[31 - j] = (char) ((((unsigned int) float_number_bits.int_view >> j) & 1u) + 48);
        }

        binary_number[32] = '\0';
        printf("[%s]", binary_number);
        printf("\n");

        // ---

        printf("-----\n");
        print_decimal(src);
        print_decimal(integer_src);
        print_decimal(fractional_part_src);

        // Устанавливаем знак
        if (src_sign == 1) {
            float_number_bits.int_view |= 0b10000000000000000000000000000000;
        }

        *dst = float_number_bits.float_view;
    }

    return exit_status;
}
