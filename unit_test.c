#include <check.h>
#include <string.h>
#include "s21_decimal.h"

START_TEST(test_s21_add_int) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(1899999, &test_value_1);
    s21_from_int_to_decimal(100001, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 2000000);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(199421, &test_value_1);
    s21_from_int_to_decimal(-4433, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 199421 + (-4433));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-199421, &test_value_1);
    s21_from_int_to_decimal(4433, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -199421 + 4433);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-199421, &test_value_1);
    s21_from_int_to_decimal((-4433), &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-199421) + (-4433));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(467, &test_value_1);
    s21_from_int_to_decimal(3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 467 + 3668);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(467, &test_value_1);
    s21_from_int_to_decimal(-3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 467 + (-3668));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-467, &test_value_1);
    s21_from_int_to_decimal(3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -467 + 3668);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-467, &test_value_1);
    s21_from_int_to_decimal(-3668, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-467) + (-3668));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    s21_decimal test_value_3 = {{123453u, 654u, 0xFFFFFFFF, 80000000}};
    s21_decimal test_value_4 = {{123456u, 654u, 0xFFFFFFFF, 80000000}};
    s21_add(test_value_3, test_value_4, &result_dec);
}
END_TEST

START_TEST(test_s21_add_float) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    float result_float;
    s21_from_float_to_decimal(1899.999, &test_value_1);
    s21_from_float_to_decimal(100.021, &test_value_2);
    s21_add(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_float(result_dec, &result_float);
    ck_assert_float_eq(result_float, 1899.999 + 100.021);
}
END_TEST

START_TEST(test_s21_sub_int) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(1899999, &test_value_1);
    s21_from_int_to_decimal(100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1899999 - 100001);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(1899999, &test_value_1);
    s21_from_int_to_decimal(-100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1899999 - (-100001));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-1899999, &test_value_1);
    s21_from_int_to_decimal(100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-1899999) - 100001);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-1899999, &test_value_1);
    s21_from_int_to_decimal(-100001, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-1899999) - (-100001));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(1994214, &test_value_1);
    s21_from_int_to_decimal(77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1994214 - 77443333);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(1994214, &test_value_1);
    s21_from_int_to_decimal(-77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 1994214 - (-77443333));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-1994214, &test_value_1);
    s21_from_int_to_decimal(77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -1994214 - 77443333);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-1994214, &test_value_1);
    s21_from_int_to_decimal(-77443333, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-1994214) - (-77443333));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19999445, &test_value_1);
    s21_from_int_to_decimal(6, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 19999445 - 6);
}
END_TEST

START_TEST(test_s21_sub_float) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    float result_float;
    s21_from_float_to_decimal(1899.999, &test_value_1);
    s21_from_float_to_decimal(100.021, &test_value_2);
    s21_sub(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_float(result_dec, &result_float);
    ck_assert_float_eq(result_float, 1899.999 - 100.021);
}
END_TEST

START_TEST(test_s21_mul_int) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(18999, &test_value_1);
    s21_from_int_to_decimal(1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (18999 * 1001));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(18999, &test_value_1);
    s21_from_int_to_decimal(-1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (18999 * (-1001)));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-18999, &test_value_1);
    s21_from_int_to_decimal(1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (-18999 * 1001));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-18999, &test_value_1);
    s21_from_int_to_decimal(-1001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, ((-18999) * (-1001)));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(191, &test_value_1);
    s21_from_int_to_decimal(57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 191 * 57443);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(191, &test_value_1);
    s21_from_int_to_decimal(-57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, 191 * (-57443));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-191, &test_value_1);
    s21_from_int_to_decimal(57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, -191 * 57443);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-191, &test_value_1);
    s21_from_int_to_decimal(-57443, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, ((-191) * (-57443)));
}
END_TEST

START_TEST(test_s21_mul_float) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    float result_float;

    s21_from_float_to_decimal(1899.999, &test_value_1);
    s21_from_float_to_decimal(100.001, &test_value_2);
    s21_mul(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_float(result_dec, &result_float);
    ck_assert_int_eq(result_float, 1899.999 * 100.001);
}
END_TEST

START_TEST(test_s21_div_int) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(100000, &test_value_1);
    s21_from_int_to_decimal(1000, &test_value_2);
    s21_div(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (100000 / 1000));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(456800, &test_value_1);
    s21_from_int_to_decimal(456800, &test_value_2);
    s21_div(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (456800 / 456800));

    // result_dec.bits[LOW] = 0;
    // result_dec.bits[MID] = 0;
    // result_dec.bits[HIGH] = 0;
    // result_dec.bits[SCALE] = 0;
    // test_value_1.bits[SCALE] = 0;
    // test_value_2.bits[SCALE] = 0;
    // s21_from_int_to_decimal(8900, &test_value_1);
    // s21_from_int_to_decimal(2, &test_value_2);
    // s21_div(test_value_1, test_value_2, &result_dec);
    // s21_from_decimal_to_int(result_dec, &result_int);
    // ck_assert_int_eq(result_int, (8900 / 2));
}
END_TEST


START_TEST(test_s21_mol_int) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result_int;
    s21_from_int_to_decimal(100000, &test_value_1);
    s21_from_int_to_decimal(1000, &test_value_2);
    s21_mod(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (100000 % 1000));

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(1, &test_value_1);
    s21_from_int_to_decimal(3, &test_value_2);
    s21_mod(test_value_1, test_value_2, &result_dec);
    s21_from_decimal_to_int(result_dec, &result_int);
    ck_assert_int_eq(result_int, (1 % 3));
}
END_TEST

START_TEST(test_s21_is_less) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(10, &test_value_1);
    s21_from_int_to_decimal(15, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(111, &test_value_1);
    s21_from_int_to_decimal(111, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(711995, &test_value_1);
    s21_from_int_to_decimal(711996, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-9993, &test_value_1);
    s21_from_int_to_decimal(-9993, &test_value_2);
    ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(111, &test_value_1);
    s21_from_int_to_decimal(111, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(711995, &test_value_2);
    ck_assert_int_eq(s21_is_greater(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(11881, &test_value_1);
    s21_from_int_to_decimal(11881, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(701995, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(0, &test_value_1);
    s21_from_int_to_decimal(0, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_from_int_to_decimal(239, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(0, &test_value_1);
    s21_from_int_to_decimal(0, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(701995, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(-9993, &test_value_1);
    s21_from_int_to_decimal(-9993, &test_value_2);
    ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(11881, &test_value_1);
    s21_from_int_to_decimal(11881, &test_value_2);
    ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_from_int_to_decimal(-9993, &test_value_1);
    s21_from_int_to_decimal(-9993, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_from_int_to_decimal(-6739, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(711996, &test_value_1);
    s21_from_int_to_decimal(701995, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(11881, &test_value_1);
    s21_from_int_to_decimal(11881, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);

    test_value_1.bits[SCALE] = 0;
    test_value_2.bits[SCALE] = 0;
    s21_from_int_to_decimal(6739, &test_value_1);
    s21_from_int_to_decimal(19993, &test_value_2);
    ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_floor) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result;

    s21_from_int_to_decimal(673988, &test_value_1);
    s21_set_scale(&test_value_1, 5);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 6);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    s21_from_int_to_decimal(-2744406, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, -275);
}
END_TEST

START_TEST(test_s21_round) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result;

    s21_from_int_to_decimal(673988, &test_value_1);
    s21_set_scale(&test_value_1, 5);
    s21_round(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 7);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    s21_from_int_to_decimal(19993, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 1);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    s21_from_int_to_decimal(-19993, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_floor(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, -2);
}
END_TEST

START_TEST(test_s21_truncate) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result;
    s21_from_int_to_decimal(673988, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_truncate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 67);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    s21_from_int_to_decimal(-2744406, &test_value_1);
    s21_set_scale(&test_value_1, 4);
    s21_truncate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, -274);
}
END_TEST

START_TEST(test_s21_negate) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal result_dec = {{0, 0, 0, 0}};
    int result;
    s21_from_int_to_decimal(711996, &test_value_1);
    s21_negate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, -711996);

    result_dec.bits[LOW] = 0;
    result_dec.bits[MID] = 0;
    result_dec.bits[HIGH] = 0;
    result_dec.bits[SCALE] = 0;
    test_value_1.bits[SCALE] = 0;
    s21_from_int_to_decimal(-279, &test_value_1);
    s21_negate(test_value_1, &result_dec);
    s21_from_decimal_to_int(result_dec, &result);
    ck_assert_int_eq(result, 279);
}
END_TEST

START_TEST(test_s21_equalize_scale) {
    s21_decimal test_value_1 = {{0, 0, 0, 0}};
    s21_decimal test_value_2 = {{0, 0, 0, 0}};
    s21_decimal result_1 = {{0, 0, 0, 0}};
    s21_decimal result_2 = {{0, 0, 0, 0}};
    int ires_1, ires_2;
    s21_from_int_to_decimal(673988, &test_value_1);
    s21_from_int_to_decimal(673988, &test_value_2);
    s21_set_scale(&test_value_1, 2);
    s21_set_scale(&test_value_2, 4);
    s21_equalize_scale(&test_value_1, &test_value_2);
    s21_truncate(test_value_1, &result_1);
    s21_truncate(test_value_2, &result_2);
    s21_from_decimal_to_int(result_1, &ires_1);
    s21_from_decimal_to_int(result_1, &ires_2);
    ck_assert_int_eq(ires_1, ires_2);
}
END_TEST

int main() {
    Suite *s1 = suite_create("s21_decimal: ");
    TCase *tc1_1 = tcase_create("s21_decimal: ");
    SRunner *sr = srunner_create(s1);
    int result;
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, test_s21_add_int);
    tcase_add_test(tc1_1, test_s21_add_float);
    tcase_add_test(tc1_1, test_s21_sub_int);
    tcase_add_test(tc1_1, test_s21_sub_float);
    tcase_add_test(tc1_1, test_s21_mul_int);
    tcase_add_test(tc1_1, test_s21_mul_float);
    tcase_add_test(tc1_1, test_s21_div_int);
    tcase_add_test(tc1_1, test_s21_mol_int);
    tcase_add_test(tc1_1, test_s21_is_less);
    tcase_add_test(tc1_1, test_s21_is_less_or_equal);
    tcase_add_test(tc1_1, test_s21_is_greater);
    tcase_add_test(tc1_1, test_s21_is_greater);
    tcase_add_test(tc1_1, test_s21_is_greater_or_equal);
    tcase_add_test(tc1_1, test_s21_is_equal);
    tcase_add_test(tc1_1, test_s21_is_not_equal);
    tcase_add_test(tc1_1, test_s21_floor);
    tcase_add_test(tc1_1, test_s21_round);
    tcase_add_test(tc1_1, test_s21_truncate);
    tcase_add_test(tc1_1, test_s21_negate);
    tcase_add_test(tc1_1, test_s21_equalize_scale);

    srunner_run_all(sr, CK_ENV);
    result = srunner_ntests_failed(sr);
    srunner_free(sr);
    return result == 0 ? 0 : 1;
}
