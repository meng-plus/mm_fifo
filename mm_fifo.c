/**
 * @file mm_fifo.h
 * COPYRIGHT (C) 2022,  chengmeng_2@outlook.com Co., Ltd.
 * All rights reserved.
 * @brief 环形队列管理器
 * @details 微型环形队列管理器，用于单片机等场景
 *  在串口数据首发中较为常用
 * @version ver1.0
 * @date 2022年10月13日
 * @author cmm
 * @note
 */
#include "mm_fifo.h"

#define INDEX_NEXT(self, idx) ((idx + 1) % self->data_size)

void mm_fifo_init(mm_fifo_t *self, void *data_ptr, size_t data_size)
{
    self->data_size = data_size;
    self->data_ptr = data_ptr;
    self->begin = 0;
    self->end = 0;
}
bool mm_fifo_is_empty(mm_fifo_t *self)
{
    return self->begin == self->end;
}
bool mm_fifo_is_full(mm_fifo_t *self)
{
    return INDEX_NEXT(self, self->end) == self->begin;
}
bool mm_fifo_push(mm_fifo_t *self, uint8_t dat)
{
    size_t index_next = INDEX_NEXT(self, self->end);
    if (index_next != self->begin)
    {
        self->data_ptr[self->end] = dat;
        self->end = index_next;
        return true;
    }
    return false;
}
uint8_t mm_fifo_pop(mm_fifo_t *self)
{
    uint8_t data_temp = 0;
    if (self->begin != self->end)
    {
        data_temp = self->data_ptr[self->begin];
        self->begin = INDEX_NEXT(self, self->begin);
    }
    return data_temp;
}
uint8_t mm_fifo_pop_peek(mm_fifo_t *self)
{
    uint8_t value;
    mm_fifo_t n_self = *self;
    value = mm_fifo_pop(&n_self);
    return value;
}
size_t mm_fifo_push_multi(mm_fifo_t *self, uint8_t *dat, size_t data_size)
{
    size_t i;
    for (i = 0; i < data_size; i++)
    {
        if (mm_fifo_push(self, dat[i]) == 0)
            return i;
    }
    return data_size;
}
size_t mm_fifo_pop_multi(mm_fifo_t *self, uint8_t *dat, size_t data_size)
{
    size_t i;
    for (i = 0; i < data_size; i++)
    {
        if (mm_fifo_is_empty(self))
        {
            return i;
        }
        dat[i] = mm_fifo_pop(self);
    }
    return data_size;
}
/**
 * @brief 取出多个数据，不从队列中移除
 * @param self 队列的句柄
 * @param dat 取出数据存放空间
 * @param data_size 要取出的数据
 * @return 实际取出来的数据
 */
size_t mm_fifo_pop_multi_peek(mm_fifo_t *self, uint8_t *dat, size_t data_size)
{
    mm_fifo_t n_self = *self;
    return mm_fifo_pop_multi(&n_self, dat, data_size);
}
size_t mm_fifo_get_used_space(mm_fifo_t *self)
{
    return (self->data_size + self->end - self->begin) % self->data_size;
}
size_t mm_fifo_get_unused_space(mm_fifo_t *self)
{
    return (self->data_size + self->begin - self->end) % self->data_size;
}

void mm_fifo_reset(mm_fifo_t *self)
{
    self->begin = 0;
    self->end = 0;
}
