#define	MY_RECV_C

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "my_recv.h"

/*�Զ���Ĵ�������*/
void my_err(const char * err_string, int line)
{
	fprintf(stderr, "line:%d  ", line);
	perror(err_string);
	exit(1);
}

/*
* ������: my_recv
* �� �� : ���׽����϶�ȡһ������(��'\n'Ϊ������־)
* �� �� : conn_fd 	-- �Ӹ������׽����Ͻ�������
*	  data_buf 	-- ��ȡ�������ݱ����ڴ˻�����
*	  len 		-- data_buf��ָ��Ŀռ䳤��
* ����ֵ: ������-1�� ���������ѹر������򷵻�0�� �ɹ����ض�ȡ���ֽ���
*/
int my_recv(int conn_fd, char *data_buf, int len)
{
	static  char	recv_buf[BUFSIZE]; 	// �Զ��建������BUFSIZE������my_recv.h��
	static  char	*pread;			// ָ����һ�ζ�ȡ���ݵ�λ��
	static  int	len_remain = 0;	 	// �Զ��建������ʣ���ֽ���
	int			i;
	
	// ����Զ��建������û�����ݣ�����׽��ֶ�ȡ����
	if (len_remain <= 0) {
		if ((len_remain =recv(conn_fd, recv_buf, sizeof (recv_buf), 0)) < 0) {
			my_err("recv", __LINE__);
		} else if (len_remain == 0) {	// Ŀ�ļ�����˵�socket���ӹر�
			return 0;
		}
		pread = recv_buf;	// ���³�ʼ��preadָ��
	}
	
	// ���Զ��建�����ж�ȡһ������
	for (i=0; *pread != '\n'; i++) {
		if (i > len) {	// ��ָֹ��Խ��
			return -1;
		}
		data_buf[i] = *pread++;
		len_remain--;
	}

	// ȥ��������־
	len_remain--;
	pread++;
	
	return i;	// ��ȡ�ɹ�
}
