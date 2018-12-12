//杨卓宇 1652292 计算机2班
//时间 2018/12/05 20:48

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_PKT 1024
#define FILE_EXIST 0
#define RM_FAILURE -1

typedef unsigned int seq_nr; //发送序号

typedef struct
{
	unsigned char data[MAX_PKT];
} packet; //数据包 纯数据

typedef enum
{
	frame_arrival
} event_type; //只有接收端一种事件产生

typedef enum
{
	data,	 //数据包
	ack,	  //确认包
	nak		  //否定确认包
} frame_kind; //帧类型枚举量

typedef struct
{
	frame_kind kind; //帧类型
	seq_nr seq;		 //发送序号
	seq_nr ack;		 //接收序号
	packet info;	 //数据包
} frame;			 //帧结构
// 不考虑头尾的FLAG字节、校验和
// kind/seq/ack属于帧头的控制信息部分

void wait_for_event(event_type);

void from_network_layer(packet *);
void to_network_layer(packet *);

void to_physical_layer(frame *);
void from_physical_layer(frame *);
