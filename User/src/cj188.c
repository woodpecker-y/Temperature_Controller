#include "adf.h"
#include "sysparams.h"
#include "cj188.h"
#include "protocol.h"

/*! \brief
*      CJ188Э�����
* \param pkg[IN]           - CJ188Э��֡����ṹ��
* \param out_data[IN]      - ���������ݰ�
* \param out_size[IN]      - ���������ݰ�����
*
* \return
*      0                   - �ɹ�
* \note
*
*/
u8 cj188_pack(CJ188Pkg *pkg, u8 *out_data, u8 *out_size)
{
    u8 offset = 0;
    u16 desn = 0x0000;

    // assert_param(*out_size > pkg->msg_size+10);
    /* ��ʼ�� */
    out_data[offset] = 0x3A;
    offset += 1;
    /* �汾�� */
    out_data[offset] = 0x70;
    offset += 1;
    /* SN */
    memcpy(out_data+offset, &pkg->sn, sizeof(pkg->sn));
    offset += sizeof(pkg->sn);
    /* DESN */
    memcpy(out_data+offset, &desn, 2);
    offset += 2;
    /* GN */
    memcpy(out_data+offset, &pkg->gn, sizeof(pkg->gn));
    offset += sizeof(pkg->gn);
    /* ������ */
    out_data[offset] = pkg->ctrl_code;
    offset += 1;
    /* �����򳤶� */
    out_data[offset] = pkg->msg_size;
    offset += 1;
    /* ���ݸ��� */
    memcpy(out_data+offset, pkg->msg_data, pkg->msg_size);
    offset += pkg->msg_size;
    /* У��� */
    out_data[offset] = check_sum(out_data, offset);
    offset += 1;
    /* ������ */
    out_data[offset] = 0xAA;
    offset += 1;

    *out_size = offset;

    return 0;


//////    /* �Ǳ��ַ */
//////    memcpy(out_data+offset, pkg->addr, sizeof(pkg->addr));
//////    bytes_reverse(out_data+offset, sizeof(pkg->addr));
//////    offset += sizeof(pkg->addr);
//////    /* ������ */
//////    out_data[offset] = pkg->ctrl_code;
//////    offset += 1;
//////    /* �����򳤶� */
//////    out_data[offset] = pkg->msg_size;
//////    offset += 1;
//////    /* ���ݸ��� */
//////    memcpy(out_data+offset, pkg->msg_data, pkg->msg_size);
//////    offset += pkg->msg_size;
//////    /* У��� */
//////    out_data[offset] = check_sum(out_data, offset);
//////    offset += 1;
//////
//////    *out_size = offset;
//////
//////    return 0;
}

/*! \brief
*      CJ188Э����
* \param pkg[IN]           - �����洢���ݽṹ
* \param in_data[IN]       - ԭʼ����
* \param in_size[IN]       - ԭʼ���ĳ���
*
* \return
*      0                           - �ɹ�
*      CJ188_ERR_INVALID_STX_ETX   - ֡ͷ��֡β����
*      CJ188_ERR_CHECKSUM          - У��ʹ���
*      CJ188_ERR_LENGTH            - ���ȴ���
* \note
*
*/
u8 cj188_unpack(CJ188Pkg *pkg, u8 *in_data, u8 in_size)
{
    u8 offset = 0;
    u8 sum = 0;
    u32 sn_data = 0;
    u16 gn_data = 0;

    /* ��ȡ��������������������ݣ����ŵ�pkg���棬���Ǵ洢���� */
    /* У��ͼ�� */
    sum = check_sum(in_data, in_size-2);
    //printf("sum=%x\r\n",sum);
    //printf("in_data[in_size-1]=%x\r\n",in_data[in_size-1]);
    if (sum != in_data[in_size-2])
    {
        return CJ188_ERR_CHECKSUM;
    }

    /* �����ж� */
    //printf("in_data[6]=%d\r\n",in_data[6]);
    //printf("in_size-8=%d\r\n",in_size-8);
    if (in_data[11] != in_size-14)
    {
        //printf("size1:%d, size2:%d\r\n", in_data[6], in_size-8);
        return CJ188_ERR_LENGTH;
    }
    /* SNǰ��Ŀ�ʼ��Ͱ汾�� */
    offset = 2;
    /* SN */
    memcpy(&sn_data, in_data+offset, sizeof(pkg->sn));
    sn_data = LittleANDBig_ModeCON4(&sn_data);

//    if((DOWNLOAD_ID_CHANNEL/10) == ((sn_data|0x0000f000)>12))     //ֻ�е�����ID��ͨ���ź����ص�Ƶ����һ��Ƶ�β�����Ч
//    {
        memcpy(&(pkg->sn), &(sn_data), sizeof(pkg->sn));
        offset += 4;
//    }
//    else
//        return CJ188_ERR_ADDR;
    /* ����DESN����Ϊһ�㶼��0x0000 */
    offset += 2;
    /* GN */
    memcpy(&gn_data, in_data+offset, sizeof(pkg->gn));
    gn_data = LittleANDBig_ModeCON2(&gn_data);
    memcpy(&(pkg->gn), &(gn_data), sizeof(pkg->gn));
    offset += 2;
    /* ������ */
    pkg->ctrl_code = in_data[offset];
    offset += 1;
    /* ���ݸ��س��� */
    pkg->msg_size = in_data[offset];
    offset += 1;
    /* ���ݸ��� */
    memcpy(pkg->msg_data, in_data+offset, pkg->msg_size);
    offset += pkg->msg_size;
//    printf("pkg->sn = %lu\r\n", pkg->sn);
//    printf("pkg->gn = %u\r\n", pkg->gn);
//    printf("pkg->ctrl_code = %02x\r\n", pkg->ctrl_code);
//    printf("pkg->msg_size = %02x\r\n", pkg->msg_size);

    return 0;




//    /* У��ͼ�� */
//    sum = check_sum(in_data, in_size-1);
//    //printf("sum=%x\r\n",sum);
//    //printf("in_data[in_size-1]=%x\r\n",in_data[in_size-1]);
//    if (sum != in_data[in_size-1])
//    {
//        return CJ188_ERR_CHECKSUM;
//    }
//
//    /* �����ж� */
//    //printf("in_data[6]=%d\r\n",in_data[6]);
//    //printf("in_size-8=%d\r\n",in_size-8);
//    if (in_data[6] != in_size-8)
//    {
//        //printf("size1:%d, size2:%d\r\n", in_data[6], in_size-8);
//        return CJ188_ERR_LENGTH;
//    }
//
//    offset = 0;
//
//    /* ��ַ�� */
//    memcpy(pkg->addr, in_data+offset, sizeof(pkg->addr));
//    bytes_reverse(pkg->addr, sizeof(pkg->addr));
//    offset += sizeof(pkg->addr);
//    /* ������ */
//    pkg->ctrl_code = in_data[offset];
//    offset += 1;
//    /* ���ݸ��س��� */
//    pkg->msg_size = in_data[offset];
//    offset += 1;
//    /* ���ݸ��� */
//    memcpy(pkg->msg_data, in_data+offset, pkg->msg_size);
//    offset += pkg->msg_size;
//
//    return 0;
}

