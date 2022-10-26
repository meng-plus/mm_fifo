
#include <stdio.h>
#include "mm_fifo.h"

uint8_t buff[512];
uint8_t rebuff[128];
int main(int argc, char **argv)
{
    mm_fifo_t fif;
    mm_fifo_init(&fif, buff, sizeof(buff));
    printf("fifo init: %ld\n", sizeof(buff));
    printf("used_space: %ld\n", mm_fifo_get_used_space(&fif));
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(&fif));

    for (int i = 0; i < 10; i++)
    { //装入数据
        mm_fifo_push(&fif, i);
    }
    printf("used_space: %ld\n", mm_fifo_get_used_space(&fif));
    printf("unused_space: %ld\n", mm_fifo_get_unused_space(&fif));

    size_t result = mm_fifo_pop_multi(&fif, rebuff, sizeof(rebuff));

    printf("pop: %ld\n", result);
    for (size_t i = 0; i < result; i++)
    {
        printf("%d ", rebuff[i]);
    }
    printf("\r\n");
    return 0;
}
