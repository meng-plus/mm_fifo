# mm_fifo ΢�͵Ļ��ζ���
## ��Ҫ

FIFO: First in, First out

�����Ƚ��������ȳ� ����������ݺ����

## Ϊʲô��ҪFIFO��

FIFO�洢����ϵͳ�Ļ��廷�ڣ����û��FIFO�洢��������ϵͳ�Ͳ���������������

FIFO�Ĺ��ܿ��Ը���Ϊ

��1�������������������л��棬��ֹ�ڽ����ʹ洢����ʱ��ʧ���ݣ�

��2�����ݼ����������н����ʹ洢���ɱ���Ƶ�������߲���������CPU�ĸ�����

��3������ϵͳ����DMA������������ݵĴ����ٶȡ�����������Ҫ��һ�㣬���������DMA���������ݴ��佫�ﲻ������Ҫ�󣬶��Ҵ������CPU�ĸ������޷�ͬʱ������ݵĴ洢������



΢�͵Ļ��ζ��У������ܼ��ݶ���Ӧ�û���,���ͻ������� 

## ��������


```C
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

```

## demo

```C

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
    { //װ������
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
	
```

