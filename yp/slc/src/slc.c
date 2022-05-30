#include "slc.h"
#include "udp_create_socket.h"
#include "udp_thread.h"

/**
 * @brief 初版通信库V0.1，支持多个程序点对点通信，同一程序最多创建十个通信节点
 * 
 * @param ip_lc 本地ip，可为空，为空时接收本机所有网卡、ip数据
 * @param port_lc 本地监听端口
 * @param ip_rt 远程ip，同一主机通信时填"127.0.0.1"，暂不支持解析主机名，不同主机通信时填对方实际ip
 * @param port_rt 远程端口，填写远程主机实际端口
 * @param func 用户回调函数，接收到远程主机消息时使用本函数通知使用者，用户回调函数需快进快出，否则容易丢消息
 * @param arg 用户回调函数参数
 * @param flag 标志位，可传COMMU_FLAG_NODELAY等，多个标志位使用|连接，目前暂时只支持NODELAY
 * @return mHandle 通信库操作句柄
 * 使用示例(不同主机)
 * pc1: commu_lib_init(NULL, 1234, "192.168.1.11", 4321, func, arg, COMMU_FLAG_NODELAY)
 * pc2: commu_lib_init(NULL, 4321, "192.168.1.12", 1234, func, arg, COMMU_FLAG_NODELAY)
 * 使用示例(本地主机)
 * app1: commu_lib_init(NULL, 1234, "127.0.0.1", 4321, func, arg, COMMU_FLAG_NODELAY)
 * app2: commu_lib_init(NULL, 4321, "127.0.0.1", 1234, func, arg, COMMU_FLAG_NODELAY)
 */
mHandle commu_init(char *ip_lc, uint16_t port_lc, char *ip_rt, uint16_t port_rt, usr_call func, void *arg, int flag)
{
    // printf("ip_lc:%s\n", ip_lc);
    // printf("port_lc:%d\n", port_lc);
    // printf("ip_rt:%s\n", ip_rt);
    // printf("port_rt:%d\n", port_rt);
    // printf("func:0x%x\n", func);
    // printf("arg:0x%x\n", arg);
    // printf("flag:%d\n", flag);

    return udp_commu_init(ip_lc, port_lc, ip_rt, port_rt, func, arg, flag);
}

int commu_destroy(mHandle _handle)
{
    return udp_commu_del(_handle);
}

/**
 * @brief 消息发送函数
 * 
 * @param _handle 通信库句柄
 * @param buf 消息地址
 * @param len 消息长度，理论最大为UDP报文长度65507，
 *            不过不建议这么长，超过1472长度会分包效率不高
 * @return int 返回发送长度
 */
int commu_send(mHandle _handle, void *buf, int len)
{
    udp_commu_t *handle = (udp_commu_t *)_handle;
    return udp_interface_send(handle->udp_tx, buf, len);
}