
#include <stdio.h>
#include "mm_fifo.h"

uint8_t buff[128];
uint8_t rebuff[128];
int main(int argc, char **argv)
{
    mm_fifo_t fifo, *pfifo = &fifo;
    mm_fifo_init(&fifo, buff, sizeof(buff));
    printf("fifo init: %ld\n", sizeof(buff));
    printf("used_space: %ld\n", mm_fifo_get_used_space(pfifo));
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(pfifo));

    for (int i = 0; i < 50; i++)
    { // 装入数据
        mm_fifo_push(pfifo, i);
    }
    printf("used_space: %ld\n", mm_fifo_get_used_space(pfifo));
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(pfifo));

    size_t result = mm_fifo_pop_multi_peek(pfifo, rebuff, sizeof(rebuff));

    printf("pop: %ld\n", result);
    for (size_t i = 0; i < result; i++)
    {
        printf("%d ", rebuff[i]);
    }
    printf("\r\n");

    uint8_t *date_ptr;
    size_t len = mm_fifo_get_valid_data_peek(pfifo, &date_ptr);
    printf("valid_data len:%ld  addr:%x  value(%d)\r\n", len, date_ptr, *date_ptr);
    len = mm_fifo_get_free_data_peek(pfifo, &date_ptr);
    printf("free_data len:%ld  addr:%x  value(%d)\r\n", len, date_ptr, *date_ptr);

    len = mm_fifo_push_quick(pfifo, 2);
    len = mm_fifo_get_free_data_peek(pfifo, &date_ptr);
    printf("free_data len:%ld  addr:%x\r\n", len, date_ptr);
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(pfifo));

    return 0;
}
