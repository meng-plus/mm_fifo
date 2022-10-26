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

#ifndef __MM_FIFO_H_
#define __MM_FIFO_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct _MM_FIFO
    {

        size_t begin;
        size_t end;
        // 元素大小.单位: 字节
        size_t data_size;
        uint8_t *data_ptr;
    } mm_fifo_t;
    /**
     * @brief 初始化环形队列空间
     * @note 为了更好的兼容应用场景，内部不做内存申请
     * @param self object 队列句柄
     * @param data_ptr 缓存区地址
     * @param data_size 缓存区大小
     */
    void mm_fifo_init(mm_fifo_t *self, void *data_ptr, size_t data_size);
    /**
     * @brief 判断是否为空
     * @param self 队列的句柄
     * @return true:队列为空 false 不空
     */
    bool mm_fifo_is_empty(mm_fifo_t *self);
    /**
     * @brief 判断是否为满
     * @param self 队列的句柄
     * @return true:队列为满 false 不满
     */
    bool mm_fifo_is_full(mm_fifo_t *self);
    /**
     * @brief 存入一个数据
     * @param self 队列的句柄
     * @param dat 存入的数据
     * @return true:存入成功 false 失败
     */
    bool mm_fifo_push(mm_fifo_t *self, uint8_t dat);
    /**
     * @brief 取出一个数据
     * @note 未做空判定，用户自行调用
     * @param self 队列的句柄
     * @return 取出的数据
     */
    uint8_t mm_fifo_pop(mm_fifo_t *self);
    /**
     * @brief 取出一个数据
     * @note 取出数据,不从队列中清除
     * @param self 队列的句柄
     * @return 待取出的数据
     */
    uint8_t mm_fifo_pop_peek(mm_fifo_t *self);
    /**
     * @brief 存入多个数据
     * @param self 队列的句柄
     * @param dat 待存入的数据
     * @param data_size 数据数量
     * @return 实际存进去的数据数量
     */
    size_t mm_fifo_push_multi(mm_fifo_t *self, uint8_t *dat, size_t data_size);
    /**
     * @brief 取出多个数据
     * @param self 队列的句柄
     * @param dat 取出数据存放空间
     * @param data_size 要取出的数据
     * @return 实际取出来的数据
     */
    size_t mm_fifo_pop_multi(mm_fifo_t *self, uint8_t *dat, size_t data_size);
    /**
     * @brief 取出多个数据，不从队列中移除
     * @param self 队列的句柄
     * @param dat 取出数据存放空间
     * @param data_size 要取出的数据
     * @return 实际取出来的数据
     */
    size_t mm_fifo_pop_multi_peek(mm_fifo_t *self, uint8_t *dat, size_t data_size);
    /**
     * @brief 未使用空间
     * @param self 队列的句柄
     * @return 队列中元素的数量
     */
    size_t mm_fifo_get_used_space(mm_fifo_t *self);
    /**
     * @brief 使用的空间
     * @param self 队列的句柄
     * @return 队列中空闲的数量
     */
    size_t mm_fifo_get_unused_space(mm_fifo_t *self);

#ifdef __cplusplus
}
#endif

#endif //__MM_FIFO_H_
