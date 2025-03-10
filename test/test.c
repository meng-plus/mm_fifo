#include <check.h>
#include <stdlib.h>
#include "mm_fifo.h"

START_TEST(test_mm_fifo_init)
{
    uint8_t buffer[100];
    mm_fifo_t fifo;
    ck_assert(mm_fifo_init(&fifo, buffer, sizeof(buffer)));
}
END_TEST

START_TEST(test_mm_fifo_push_pop)
{
    uint8_t buffer[100];
    mm_fifo_t fifo;
    ck_assert(mm_fifo_init(&fifo, buffer, sizeof(buffer)));

    ck_assert(mm_fifo_is_empty(&fifo));
    ck_assert(mm_fifo_push(&fifo, 0xAA));
    ck_assert(!mm_fifo_is_empty(&fifo));
    ck_assert_int_eq(mm_fifo_pop(&fifo), 0xAA);
    ck_assert(mm_fifo_is_empty(&fifo));
}
END_TEST

START_TEST(test_mm_fifo_push_multi)
{
    uint8_t buffer[100];
    mm_fifo_t fifo;
    ck_assert(mm_fifo_init(&fifo, buffer, sizeof(buffer)));
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04};

    size_t pushed = mm_fifo_push_multi(&fifo, data, sizeof(data));
    ck_assert_int_eq(pushed, sizeof(data));

    uint8_t popped[4];
    size_t popped_count = mm_fifo_pop_multi(&fifo, popped, sizeof(popped));
    ck_assert_int_eq(popped_count, sizeof(data));
    ck_assert_mem_eq(popped, data, sizeof(data));
}
END_TEST

START_TEST(test_mm_fifo_push_multi_force)
{
    uint8_t buffer[10];
    mm_fifo_t fifo;
    ck_assert(mm_fifo_init(&fifo, buffer, sizeof(buffer)));
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B};

    size_t pushed = mm_fifo_push_multi_force(&fifo, data, sizeof(data));
    ck_assert_int_eq(pushed, 9); // Buffer size is 10
    ck_assert_int_eq(mm_fifo_get_used_space(&fifo), 9);

    uint8_t expected[] = {0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A};
    uint8_t popped[10];
    size_t popped_count = mm_fifo_pop_multi(&fifo, popped, sizeof(popped));
    ck_assert_int_eq(popped_count, 9);
    ck_assert_mem_eq(popped, expected, sizeof(expected));
}
END_TEST

START_TEST(test_bulk_operations)
{
    uint8_t buffer[16];
    mm_fifo_t fifo;
    mm_fifo_init(&fifo, buffer, 16);

    // 多字节写入测试
    uint8_t write_data[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    ck_assert(mm_fifo_push_multi(&fifo, write_data, 10) == 10);
    ck_assert(mm_fifo_get_used_space(&fifo) == 10);
    ck_assert(mm_fifo_get_unused_space(&fifo) == (15 - 10));

    // 多字节读取测试
    uint8_t read_buf[20] = {0};
    ck_assert(mm_fifo_pop_multi(&fifo, read_buf, 5) == 5);
    ck_assert(memcmp(read_buf, write_data, 5) == 0);
    ck_assert(mm_fifo_get_used_space(&fifo) == 5);

    // 强制写入测试
    uint8_t force_data[15] = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE};
    ck_assert_int_eq(mm_fifo_push_multi_force(&fifo, force_data, 15), 15);
    ck_assert_int_eq(mm_fifo_get_used_space(&fifo), 15);
}
END_TEST

START_TEST(test_mm_fifo_get_used_unused_space)
{
    uint8_t buffer[40];
    mm_fifo_t fifo;
    ck_assert(mm_fifo_init(&fifo, buffer, sizeof(buffer)));

    ck_assert_int_eq(mm_fifo_get_used_space(&fifo), 0);
    ck_assert_int_eq(mm_fifo_get_unused_space(&fifo), 39);

    mm_fifo_push(&fifo, 0x01);
    ck_assert_int_eq(mm_fifo_get_used_space(&fifo), 1);
    ck_assert_int_eq(mm_fifo_get_unused_space(&fifo), 38);

    mm_fifo_pop(&fifo);
    ck_assert_int_eq(mm_fifo_get_used_space(&fifo), 0);
    ck_assert_int_eq(mm_fifo_get_unused_space(&fifo), 39);
}
END_TEST

Suite *mm_fifo_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("mm_fifo");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_mm_fifo_init);
    tcase_add_test(tc_core, test_mm_fifo_push_pop);
    tcase_add_test(tc_core, test_mm_fifo_push_multi);
    tcase_add_test(tc_core, test_mm_fifo_push_multi_force);
    tcase_add_test(tc_core, test_bulk_operations);
    tcase_add_test(tc_core, test_mm_fifo_get_used_unused_space);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s  = mm_fifo_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
