#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * nodelay 标志位，正常情况下linux的阻塞式socket接收或者阻塞式信号量都会使线程进入阻塞态，
 * 当有消息到来时线程从阻塞态唤醒，唤醒操作会消耗数十微秒到上千微秒不等，如果消息实时性要求很高可以使用此标志位，
 * 使用此标志位后会尽量使线程不进入阻塞态，极大提升消息响应，不过会很占用CPU
 */
#define COMMU_FLAG_NODELAY  (1 << 0)
#define COMMU_FLAG_XXXXXXX  (1 << 1)

typedef void * mHandle;
typedef int (*usr_call)(void *arg, char *buf, int len);
typedef int (*connect_call)(int client_fd, void *arg);


/** @brief 成功返回值*/
#define SUCCESS         0
/** @brief 失败返回值*/
#define FAILURE         (-1)
/** @brief 非法值*/
#define INVALID         (-1)


/**
 * @brief 初版通信库V0.1，支持多个程序点对点通信,节点数量无限制，可自由组合通信链路
 * 
 * @param ip_lc 本地ip，可为空，为空时接收本机所有网卡、ip数据
 * @param port_lc 本地监听端口
 * @param ip_rt 远程ip，同一主机通信时填"127.0.0.1"，暂不支持解析主机名，不同主机通信时填对方实际ip
 * @param port_rt 远程端口，填写远程主机实际端口
 * @param func 用户回调函数，接收到远程主机消息时使用本函数通知使用者，用户回调函数需快进快出，否则容易丢消息
 * @param arg 用户回调函数参数
 * @param flag 标志位，可传COMMU_FLAG_NODELAY等，多个标志位使用|连接
 * @return mHandle 通信库操作句柄
 * 使用示例(不同主机)
 * pc1: commu_lib_init(NULL, 1234, "192.168.1.11", 4321, func, arg, COMMU_FLAG_NODELAY)
 * pc2: commu_lib_init(NULL, 4321, "192.168.1.12", 1234, func, arg, COMMU_FLAG_NODELAY)
 * 使用示例(本地主机)
 * app1: commu_lib_init(NULL, 1234, "127.0.0.1", 4321, func, arg, COMMU_FLAG_NODELAY)
 * app2: commu_lib_init(NULL, 4321, "127.0.0.1", 1234, func, arg, COMMU_FLAG_NODELAY)
 */
mHandle commu_init(char *ip_lc, uint16_t port_lc, char *ip_rt, uint16_t port_rt, usr_call func, void *arg, int flag);

/**
 * @brief 消息发送函数
 * 
 * @param _handle 通信库句柄
 * @param buf 消息地址
 * @param len 消息长度，理论最大为UDP报文长度65507，
 *            不过不建议这么长，超过1472长度会分包效率不高
 * @return int 返回发送长度
 */
int commu_send(mHandle _handle, void *buf, int len);

int commu_destroy(mHandle _handle);

/***********TCP**************/

/**
 * @brief                   服务端TCP通信初始化
 * @param  port             本地监听端口
 * @param  timeout          监听超时，单位秒
 * @param  buf_size         本地接收缓冲大小，取决于本机可用内存
 * @param  func             用户接收回调函数
 * @param  arg              用户接收回调函数参数
 * @param  flag             行为控制标志位，保留
 * @return mHandle          成功返回操作句柄，失败返回NULL
 */
mHandle tcp_commu_init_server(uint16_t port, uint32_t timeout, uint32_t buf_size,usr_call func,void *arg, uint32_t flag);

/**
 * @brief                   客户端TCP初始化
 * @param  port             远程主机端口
 * @param  ip               远程主机ip
 * @param  buf_size         同上
 * @param  func             同上
 * @param  arg              同上
 * @param  flag             同上
 * @return mHandle          同上
 */
mHandle tcp_commu_init_client(uint16_t port, const char *ip, uint32_t buf_size, usr_call func,void *arg, uint32_t flag);
int tcp_commu_send(mHandle _handle, void *buf, int len);
int tcp_commu_del(mHandle _handle);

/**
 * @brief                   初始化TCP监听线程
 * @param  port             监听端口
 * @param  call             客户端连接回调函数，当有客户端连接时会通过这个函数通知使用者，使用者使用传进来的client fd申请通信句柄
 * @param  arg              回调函数参数
 * @return int 
 */
int tcp_commu_listen_task_init(uint16_t port, connect_call call, void *arg);

/**
 * @brief                   通过这个函数申请通信句柄
 * @param  client_fd        客户端描述符
 * @param  buf_size         本地接收缓冲大小，取决于本机可用内存
 * @param  func             用户接收回调函数
 * @param  arg              用户接收回调函数参数
 * @param  flag             行为控制标志位，保留
 * @return mHandle          成功返回操作句柄，失败返回NULL
 */
mHandle tcp_commu_apply(int client_fd, uint32_t buf_size, usr_call func, void *arg, uint32_t flag);

/**
 * @brief                   通过描述符获取对端ip, port
 * @param  fd               描述符
 * @param  ip               对端ip,使用uint32格式
 * @param  port             对端ip
 * @return int 
 */
int tcp_get_peer_info(int fd, uint32_t *ip, uint16_t *port);

/**
 * @brief udp 组播发送初始化函数
 * 
 * @param ip 要进行组播发送的地址，建议直接使用224.0.0.1
 * @param port 进行组播的端口
 * @param flag 保留
 * @return mHandle 操作句柄
 */
mHandle udp_mult_tx_init(const char *ip, uint16_t port, int flag);

/**
 * @brief udp 组播接收初始化函数
 * 
 * @param ip 组播接收地址，与发送函数初始化地址相同
 * @param port 组播接收端口，与发送函数初始化端口相同
 * @param func 消息接收回调函数
 * @param arg 消息接收回调函数参数
 * @param flag 保留
 * @return mHandle 操作句柄
 */
mHandle udp_mult_rx_init(const char *ip, uint16_t port, usr_call func, void *arg, int flag);

/**
 * @brief udp 组播发送函数
 * 
 * @param _handle 操作句柄
 * @param buf 消息指针
 * @param len 消息长度，最长不超过udp包长
 * @return int 返回发送消息长度
 */
int udp_mult_send(mHandle _handle, void *buf, int len);

/**
 * @brief 删除组播tx rx接口
 * 
 * @param handle 操作句柄
 * @return int 成功返回0,失败返回其他
 */
int udp_mult_del(mHandle _handle);

#ifdef __cplusplus
}
#endif

#endif