/**
 * @file mm_fifo.h
 * COPYRIGHT (C) 2022,  chengmeng_2@outlook.com Co., Ltd.
 * All rights reserved.
 * @brief ���ζ��й�����
 * @details ΢�ͻ��ζ��й����������ڵ�Ƭ���ȳ���
 *  �ڴ��������׷��н�Ϊ����
 * @version ver1.0
 * @date 2022��10��13��
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
        // Ԫ�ش�С.��λ: �ֽ�
        size_t data_size;
        uint8_t *data_ptr;
    } mm_fifo_t;
    /**
     * @brief ��ʼ�����ζ��пռ�
     * @note Ϊ�˸��õļ���Ӧ�ó������ڲ������ڴ�����
     * @param self object ���о��
     * @param data_ptr ��������ַ
     * @param data_size ��������С
     */
    void mm_fifo_init(mm_fifo_t *self, void *data_ptr, size_t data_size);
    /**
     * @brief �ж��Ƿ�Ϊ��
     * @param self ���еľ��
     * @return true:����Ϊ�� false ����
     */
    bool mm_fifo_is_empty(mm_fifo_t *self);
    /**
     * @brief �ж��Ƿ�Ϊ��
     * @param self ���еľ��
     * @return true:����Ϊ�� false ����
     */
    bool mm_fifo_is_full(mm_fifo_t *self);
    /**
     * @brief ����һ������
     * @param self ���еľ��
     * @param dat ���������
     * @return true:����ɹ� false ʧ��
     */
    bool mm_fifo_push(mm_fifo_t *self, uint8_t dat);
    /**
     * @brief ȡ��һ������
     * @note δ�����ж����û����е���
     * @param self ���еľ��
     * @return ȡ��������
     */
    uint8_t mm_fifo_pop(mm_fifo_t *self);
    /**
     * @brief ȡ��һ������
     * @note ȡ������,���Ӷ��������
     * @param self ���еľ��
     * @return ��ȡ��������
     */
    uint8_t mm_fifo_pop_peek(mm_fifo_t *self);
    /**
     * @brief ����������
     * @param self ���еľ��
     * @param dat �����������
     * @param data_size ��������
     * @return ʵ�ʴ��ȥ����������
     */
    size_t mm_fifo_push_multi(mm_fifo_t *self, uint8_t *dat, size_t data_size);
    /**
     * @brief ȡ���������
     * @param self ���еľ��
     * @param dat ȡ�����ݴ�ſռ�
     * @param data_size Ҫȡ��������
     * @return ʵ��ȡ����������
     */
    size_t mm_fifo_pop_multi(mm_fifo_t *self, uint8_t *dat, size_t data_size);
    /**
     * @brief ȡ��������ݣ����Ӷ������Ƴ�
     * @param self ���еľ��
     * @param dat ȡ�����ݴ�ſռ�
     * @param data_size Ҫȡ��������
     * @return ʵ��ȡ����������
     */
    size_t mm_fifo_pop_multi_peek(mm_fifo_t *self, uint8_t *dat, size_t data_size);
    /**
     * @brief δʹ�ÿռ�
     * @param self ���еľ��
     * @return ������Ԫ�ص�����
     */
    size_t mm_fifo_get_used_space(mm_fifo_t *self);
    /**
     * @brief ʹ�õĿռ�
     * @param self ���еľ��
     * @return �����п��е�����
     */
    size_t mm_fifo_get_unused_space(mm_fifo_t *self);

#ifdef __cplusplus
}
#endif

#endif //__MM_FIFO_H_
