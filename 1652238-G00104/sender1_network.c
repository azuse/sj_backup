//杨卓宇 1652292 计科2班
//2018/12/06 10:07
#include "../common/protocol.h"

int main()
{
	int fd = open("../common/love.rmvb", O_RDONLY);
	packet mypacket;
	ssize_t readlen = MAX_PKT, writelen;
	ssize_t outfile_no = 0;
	char outfile_name[64];
	// char zerobuf[MAX_PKT] = {0}

	while (readlen == MAX_PKT)
	{
		readlen = read(fd, mypacket.data, MAX_PKT);
		if (readlen > 0)
		{
			outfile_no = (outfile_no + 1) % 10000;
			sprintf(outfile_name, "../common/network_datalink.share.%04d", outfile_no);
			while (access(outfile_name, F_OK) == FILE_EXIST)
				sleep(1);
			int fd_out = open(outfile_name, O_WRONLY | O_CREAT);
			writelen = write(fd_out, mypacket.data, readlen);
			if (writelen != readlen)
			{
				perror("write error ");
				exit(1);
			}
			// if (MAX_PKT - writelen)//补0的操作
			// {
			// 	write(fd_out, zerobuf, MAX_PKT - writelen);
			// }
			close(fd_out);
		}
	}
	return 0;
}
