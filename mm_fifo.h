/**
 * @file mm_fifo.h
 * COPYRIGHT (C) 2024,  chengmeng_2@outlook.com Co., Ltd.
 * All rights reserved.
 * @brief ���ζ��й�����
 * @details ΢�ͻ��ζ��й����������ڵ�Ƭ���ȳ���
 *  �ڴ��������׷��н�Ϊ����
 * @version ver2.0
 * @date 2024��2��27��
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
    typedef struct mm_fifo
    {

        uint32_t out; /*!< ���Ѷ��е�������ʼ��ַ */
        uint32_t in;  /*!< ��Ч���ݳ��� */
        // Ԫ�ش�С.��λ: �ֽ�
        uint32_t size; /*!< ��������С */
        uint8_t *data; /*!< ��������ʼ��ַ */
    } mm_fifo_t;
    /**
     * @brief ��ʼ�����ζ��пռ�
     * @note Ϊ�˸��õļ���Ӧ�ó������ڲ������ڴ�����
     * @param self object ���о��
     * @param data_ptr ��������ַ
     * @param data_size ��������С
     * @return true:��ʼ���ɹ� false:��ʼ��ʧ��
     */
    bool mm_fifo_init(mm_fifo_t *self, void *data_ptr, size_t data_size);
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
     * @brief ǿ�ƴ������ݣ�����ռ䲻�㽫������������
     * @param self ���еľ��
     * @param dat �����������
     * @param data_size ��������
     * @return ʵ�ʴ��ȥ����������
     */
    size_t mm_fifo_push_multi_force(mm_fifo_t *self, uint8_t *dat, size_t data_size);

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
     * @brief �õ���ȡ�����ݵ������ڴ�Σ����Ӷ������Ƴ�
     * @param self ���еľ��
     * @param date_ptr ��Ч���ݵ���ʼ��ַ
     * @return ��Ч���ݵĳ���
     */
    size_t mm_fifo_get_valid_data_peek(mm_fifo_t *self, uint8_t **date_ptr);
    /**
     * @brief �õ������ݵ������ڴ�Σ����Ӷ������Ƴ�
     * @param self ���еľ��
     * @param date_ptr �յ���ʼ��ַ
     * @return �����ݵ���󳤶�
     */
    size_t mm_fifo_get_free_data_peek(mm_fifo_t *self, uint8_t **date_ptr);
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
    /**
     * @brief ���fifo
     * @param self ���еľ��
     */
    void mm_fifo_reset(mm_fifo_t *self);
    /**
     * @brief fifo���ٵ�����Ҫ������
     * @param self ���еľ��
     * @param cnt Ҫ����������
     * @return ʵ�ʵ���������
     */
    size_t mm_fifo_pop_quick(mm_fifo_t *self, size_t cnt);
    /**
     * @brief fifo����ѹ������ݣ�������ǰռ�ÿռ�
     * @param self ���еľ��
     * @param cnt Ҫѹ�������
     * @return ʵ��ѹ�������
     */
    size_t mm_fifo_push_quick(mm_fifo_t *self, size_t cnt);

#ifdef __cplusplus
}
#endif

#endif //__MM_FIFO_H_
