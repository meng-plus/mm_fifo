
#include <stdio.h>
#include "mm_fifo.h"

uint8_t buff[128];
uint8_t rebuff[128];
int main(int argc, char **argv)
{
    mm_fifo_t fif;
    mm_fifo_init(&fif, buff, sizeof(buff));
    printf("fifo init: %ld\n", sizeof(buff));
    printf("used_space: %ld\n", mm_fifo_get_used_space(&fif));
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(&fif));

    for (int i = 0; i < 10; i++)
    { // 装入数据
        mm_fifo_push(&fif, i);
    }
    printf("used_space: %ld\n", mm_fifo_get_used_space(&fif));
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(&fif));

    size_t result = mm_fifo_pop_multi_peek(&fif, rebuff, sizeof(rebuff));

    printf("pop: %ld\n", result);
    for (size_t i = 0; i < result; i++)
    {
        printf("%d ", rebuff[i]);
    }
    printf("\r\n");
    fif.begin = fif.end + 10;
    printf("fifo.addr:%x\r\n", fif.data_ptr);
    uint8_t *date_ptr;
    size_t len = mm_fifo_get_valid_data_peek(&fif, &date_ptr);
    printf("valid_data len:%ld  addr:%x\r\n", len, date_ptr);
    len = mm_fifo_get_free_data_peek(&fif, &date_ptr);
    printf("free_data len:%ld  addr:%x\r\n", len, date_ptr);

    len = mm_fifo_push_quick(&fif, 100);
    len = mm_fifo_get_free_data_peek(&fif, &date_ptr);
    printf("free_data len:%ld  addr:%x\r\n", len, date_ptr);
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(&fif));

    return 0;
}
