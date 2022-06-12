ssh 连接过程

ssh有两个版本。介绍版本2.
一.安装
#gzip -cd ssh-2.3.0.tar.gz|tar xvf -
#cd ssh-2.3.0
#./configure       ;希望通过tcp_wrappers来控制SSH,那么在configure时要加上选项"--with-libwrap=/path/to/libwrap",来告诉SSH关于libwrap.a和tcpd.h的位置.
#make
#make install

二,配置
#rm /etc/ssh2/hostkey*
#ssh-keygen2 -P /etc/ssh/hostkey

三,启动sshd2 
#/usr/local/bin/sshd2&

四,用tcp_wrappers控制SSH
安装SSH的站点可以用tcp_wrappers来限制那些ip地址来访问自己.比如在/etc/hosts.allow中加入:
sshd,sshd2:10.0.0.1
那么只有10.0.0.1可以通过ssh来访问该主机.

五,基本应用

#ssh-keygen

本地:~/.ssh2#echo "idkeyid_dsa_1024_a" >identification

远程:~/.ssh2#echo "keylocal.pub" >authorization

然后：ssh remote.pku.edu.cn

经过几个阶段协商实现认证连接。
第一阶段：
由客户端向服务器发出tcp连接请求。连接建立后，客户端进入等待。服务器向客户端发送第一个报文，宣告自己的版本号，包括协议版本号和软件版本号。协议版本号由主版本号和次版本号两部分组成。它和软件版本号一起构成形如："ssh-<主协议版本号>.<次协议版本号>-<软件版本号>\n"的字符串。

　　第二阶段: 
　　
　　协商解决版本问题后，双方就开始采用二进制数据包进行通讯。由服务器向客户端发送第一个包，内容为自己的 RSA主 
　　机密钥(host key)的公钥部分、RSA服务密钥(server key)的公钥部分、支持的加密方法、支持的认证方法、次协议版本 
　　标志、以及一个 64 位的随机数(cookie)。这个包没有加密，是明文发送的。客户端接收包后，依据这两把密钥和被称 
　　为cookie的 64 位随机数计算出会话号(session id)和用于加密的会话密钥(session key)。随后客户端回送一个包给服 
　　务器，内容为选用的加密方法、cookie的拷贝、客户端次协议版本标志、以及用服务器的主机密钥的公钥部分和服务密钥 
　　的公钥部分进行加密的用于服务器计算会话密钥的32 字节随机字串。除这个用于服务器计算会话密钥的 32字节随机字串 
　　外，这个包的其他内容都没有加密。之后，双方的通讯就是加密的了，服务器向客户端发第二个包（双方通讯中的第一个 
　　加密的包）证实客户端的包已收到。 

第三阶段: 
　　
　　双方随后进入认证阶段。可以选用的认证的方法有： 
　　
　　(1) ~/.rhosts 或 /etc/hosts.equiv 认证（缺省配置时不容许使用它）; 
　　(2) 用 RSA 改进的 ~/.rhosts 或 /etc/hosts.equiv 认证； 
　　(3) RSA 认证； 
　　(4) 口令认证。 
　　
　　如果是使用 ~/.rhosts 或 /etc/hosts.equiv 进行认证，客户端使用的端口号必须小于1024。 
　　
　　认证的第一步是客户端向服务器发 SSH_CMSG_USER 包声明用户名，服务器检查该用户是否存在，确定是否需要进行认证。 
　　如果用户存在，并且不需要认证，服务器回送一个SSH_SMSG_SUCCESS 包，认证完成。否则，服务器会送一个 
　　SSH_SMSG_FAILURE 包，表示或是用户不存在，或是需要进行认证。注意，如果用户不存在，服务器仍然保持读取从客户端 
　　发来的任何包。除了对类型为 SSH_MSG_DISCONNECT、SSH_MSG_IGNORE 以及 SSH_MSG_DEBUG 的包外，对任何类型的包都以 
　　SSH_SMSG_FAILURE 包。用这种方式，客户端无法确定用户究竟是否存在。 
　　
　　如果用户存在但需要进行认证，进入认证的第二步。客户端接到服务器发来的 SSH_SMSG_FAILURE 包后，不停地向服务器 
　　发包申请用各种不同的方法进行认证，直到时限已到服务器关闭连接为止。时限一般设定为 5 分钟。对任何一个申请， 
　　如果服务器接受，就以 SSH_SMSG_SUCCESS 包回应；如果不接受，或者是无法识别，则以 SSH_SMSG_FAILURE 包回应。

