// Client/Serverģ�͵ķ�������
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include "my_recv.h"	// �Զ����ͷ�ļ�

#define	SERV_PORT		4507	// �������˵Ķ˿�
#define	LISTENQ			12	// ����������е���󳤶�

#define	INVALID_USERINFO	'n'	// �û���Ϣ��Ч
#define	VALID_USERINFO		'y'	// �û���Ϣ��Ч

#define	USERNAME		0	// ���յ������û���
#define	PASSWORD		1	// ���յ���������

struct userinfo {  	// �����û���������Ľṹ��
	char username[32];
	char password[32];
};
struct userinfo users[ ] = {
	{"linux", "unix"},
	{"4507", "4508"},
	{"clh", "clh"},
	{"xl", "xl"},
	{" "," "}	   	// ��ֻ��һ���ո���ַ�����Ϊ����Ľ�����־
};

// �����û����Ƿ���ڣ����ڷ��ظ��û������±�,�������򷵻�-1��������-2
int find_name(const char *name)
{
	int i;
	
	if (name == NULL) {
		printf("in find_name, NULL pointer");
		return -2;
	}
	for (i=0; users[i].username[0] != ' ';i++) {
		if (strcmp(users[i].username, name) == 0) {
			return i;
		}
	}

	return -1;
}

// ��������
void send_data(int conn_fd, const char *string)
{
	if (send(conn_fd, string, strlen(string), 0) < 0) {
		my_err("send", __LINE__);  // my_err������my_recv.h������
	}
}

int main()
{
	int			sock_fd, conn_fd;
	int			optval;
	int			flag_recv = USERNAME; // ��ʶ���յ������û���������
	int			ret;
	int			name_num;
	pid_t			pid;
	socklen_t		cli_len;
	struct sockaddr_in	cli_addr, serv_addr;
	char			recv_buf[128];
	
	// ����һ��TCP�׽���
	sock_fd = socket(AF_INET, SOCK_STREAM,0);
	if (sock_fd < 0) {
		my_err("socket", __LINE__);
	}
	
	// ���ø��׽���ʹ֮�������°󶨶˿�
	optval = 1;
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, 
		(void *)&optval, sizeof(int)) < 0) {
		my_err("setsockopt", __LINE__);
	}
	
	// ��ʼ���������˵�ַ�ṹ
	memset(&serv_addr, 0, sizeof (struct sockaddr_in));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(SERV_PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	// ���׽��ְ󶨵����ض˿�
	if (bind(sock_fd, (struct sockaddr *)&serv_addr, 
		sizeof (struct sockaddr_in)) < 0) {
		my_err("bind", __LINE__);
	}
	
	// ���׽���ת��Ϊ�����׽���
	if (listen(sock_fd, LISTENQ) < 0) {
		my_err("listen", __LINE__);
	}

	cli_len = sizeof (struct sockaddr_in);
	while (1) {
		// ͨ��accept���ܿͻ��˵��������󣬲����������׽��������շ�����
		conn_fd = accept(sock_fd, (struct sockaddr *)&cli_addr, &cli_len);
		if (conn_fd < 0) {
			my_err("accept", __LINE__);
		}
		
		printf("accept a new client, ip:%s\n", inet_ntoa(cli_addr.sin_addr));
		// ����һ���ӽ��̴���ոս��ܵ���������
		if ( (pid = fork()) == 0 ) {	// �ӽ���
			while(1) {
				if ((ret = recv(conn_fd, recv_buf, sizeof (recv_buf), 0)) < 0) {
					perror("recv");
					exit(1);
				}
				recv_buf[ret-1] = '\0'; // �����ݽ�����־'\n'�滻���ַ���������־

				if (flag_recv == USERNAME) {	// ���յ������û���
					name_num = find_name(recv_buf);
					switch (name_num) {
						case -1:
							send_data(conn_fd, "n\n");
							break;
						case -2:
							exit(1);
							break;
						default:
							send_data(conn_fd, "y\n");
							flag_recv = PASSWORD;
							break;
					}
				} else if (flag_recv == PASSWORD) {	 // ���յ���������
					if (strcmp(users[name_num].password, recv_buf) == 0) {
						send_data(conn_fd, "y\n");
						send_data(conn_fd, "Welcome login my tcp server\n");
						printf("%s login\n", users[name_num].username);
						break; // ����whileѭ��
					} else 
						send_data(conn_fd, "n\n");
				}
			}
			close(sock_fd);
			close(conn_fd);
			exit(0);  // �����ӽ���
		} else {   // �����̹رոոս��ܵ���������ִ��accept�ȴ�������������
			close(conn_fd); 
		}
	}
	
	return 0;
}
