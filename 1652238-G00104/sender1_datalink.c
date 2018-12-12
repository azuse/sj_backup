//杨卓宇 1652292 计科2班
//2018/12/06 16:13
#include "../common/protocol.h"

int main()
{
	ssize_t infile_no = 1, outfile_no = 1;
	int fd, readlen, fd_out;
	frame myframe;
	packet mypacket;
	char infile_name[64];
	char outfile_name[64];
	sprintf(infile_name, "../common/network_datalink.share.%04d", infile_no);

	while (1)
	{
		if ((fd = open(infile_name, O_RDONLY)) != -1)
		{
			readlen = read(fd, myframe.data, MAX_PKT); //从network_datalink.share文件中读数据赋给帧的数据段

			if (readlen == MAX_PKT) //把帧写入datalink_physical.share文件 全部都是1024+12=1036字节
			{
				sprintf(outfile_name, "../common/datalink_physical.share.%04d", outfile_no);
				while (access(outfile_name, F_OK) == FILE_EXIST)
					sleep(1);
				fd_out = open(outfile_name, O_WRONLY | O_CREAT);
				writelen = write(fd_out, (char *)&myframe, MAX_PKT + 12);
				if (writelen != MAX_PKT + 12)
				{
					perror("sender1_datalink write error ");
					exit(1);
				}
				close(fd_out); //
				outfile_no = (outfile_no + 1) % 10000;
			}

			close(fd); //关闭infile的fd
			if (remove(infile_name) == RM_FAILURE)
			{
				perror("sender remove network_datalink error ");
				exit(1);
			} //删除network_datalink.share文件

			infile_no = (infile_no + 1) % 10000;
			sprintf(infile_name, "../common/network_datalink.share.%04d", infile_no);
		}
		else
			sleep(1);
	}

	return 0;
}
