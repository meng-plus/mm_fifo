/**
 * @file mm_fifo.h
 * COPYRIGHT (C) 2024,  chengmeng_2@outlook.com Co., Ltd.
 * All rights reserved.
 * @brief 环形队列管理器
 * @details 微型环形队列管理器，用于单片机等场景
 *  在串口数据首发中较为常用
 * @version ver2.0
 * @date 2024年2月27日
 * @author cmm
 * @note
 */
#include "mm_fifo.h"
struct _MM_FIFO
{

    size_t begin; /*!< 唤醒队列的数据起始地址 */
    size_t len;   /*!< 有效数据长度 */
    // 元素大小.单位: 字节
    size_t size;    /*!< 缓存区大小 */
    uint8_t data[]; /*!< 缓存区起始地址 */
};
#define INDEX_NEXT(self, offset, idx) ((idx + offset) % self->size)
#define INDEX_END(self) ((self->begin + self->len) % self->size)
mm_fifo_t *mm_fifo_init(void *data_ptr, size_t data_size)
{
    mm_fifo_t *self = (mm_fifo_t *)data_ptr;
    self->size = data_size - sizeof(mm_fifo_t);
    self->begin = 0;
    self->len = 0;
    return self;
}
bool mm_fifo_is_empty(mm_fifo_t *self)
{
    return self->len != 0;
}
bool mm_fifo_is_full(mm_fifo_t *self)
{
    return self->len == self->size;
}
bool mm_fifo_push(mm_fifo_t *self, uint8_t dat)
{
    if (self->len != self->size)
    {
        size_t index_next = INDEX_END(self);
        self->data[index_next] = dat;
        self->len++;
        return true;
    }
    return false;
}
uint8_t mm_fifo_pop(mm_fifo_t *self)
{
    uint8_t data_temp = 0;
    if (self->len)
    {
        data_temp = self->data[self->begin];
        self->begin = INDEX_NEXT(self, 1, self->begin);
    }
    return data_temp;
}
uint8_t mm_fifo_pop_peek(mm_fifo_t *self)
{
    uint8_t value;
    mm_fifo_t self_bak = *self;
    value = mm_fifo_pop(self);
    *self = self_bak;
    return value;
}
size_t mm_fifo_push_multi(mm_fifo_t *self, uint8_t *dat, size_t size)
{
    size_t i;
    for (i = 0; i < size; i++)
    {
        if (mm_fifo_push(self, dat[i]) == 0)
            return i;
    }
    return size;
}
size_t mm_fifo_pop_multi(mm_fifo_t *self, uint8_t *dat, size_t size)
{
    size_t i;
    size_t used = mm_fifo_get_used_space(self);
    if (used < size)
    {
        size = used;
    }
    for (i = 0; i < size; i++)
    {
        dat[i] = mm_fifo_pop(self);
    }
    return size;
}
/**
 * @brief 取出多个数据，不从队列中移除
 * @param self 队列的句柄
 * @param dat 取出数据存放空间
 * @param size 要取出的数据
 * @return 实际取出来的数据
 */
size_t mm_fifo_pop_multi_peek(mm_fifo_t *self, uint8_t *dat, size_t size)
{
    mm_fifo_t self_bak = *self;
    size_t len = mm_fifo_pop_multi(self, dat, size);
    *self = self_bak;
    return len;
}
size_t mm_fifo_get_valid_data_peek(mm_fifo_t *self, uint8_t **date_ptr)
{
    *date_ptr = &self->data[self->begin];
    if (self->size > self->begin + self->len)
    {
        return self->len;
    }
    else
    {
        return self->size - self->begin;
    }
}
size_t mm_fifo_get_free_data_peek(mm_fifo_t *self, uint8_t **date_ptr)
{
    size_t end = INDEX_END(self);
    *date_ptr = &self->data[end];
    if (end > self->begin)
    {
        return self->size - end;
    }
    else
    {
        return self->begin - end;
    }
}
size_t mm_fifo_get_used_space(mm_fifo_t *self)
{
    return self->len;
}
size_t mm_fifo_get_unused_space(mm_fifo_t *self)
{
    return self->size - self->len;
}

void mm_fifo_reset(mm_fifo_t *self)
{
    self->begin = 0;
    self->len = 0;
}

size_t mm_fifo_pop_quick(mm_fifo_t *self, size_t cnt)
{
    size_t len = mm_fifo_get_used_space(self);
    if (len > cnt)
    {
        self->begin = INDEX_NEXT(self, cnt, self->begin);
        return cnt;
    }
    else
    {
        self->begin = INDEX_NEXT(self, len, self->begin);
        self->len = 0;
        return len;
    }
}

size_t mm_fifo_push_quick(mm_fifo_t *self, size_t cnt)
{
    size_t len = mm_fifo_get_unused_space(self);
    if (len > cnt)
    {
        self->len = self->len + cnt;
        return cnt;
    }
    else
    {
        self->len = self->size;
        return len - 1;
    }
}
