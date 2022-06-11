Jose描述了如何着手配置调整xinetd。

xinetd取代了inetd，并且提供了访问控制、加强的日志和资源管理功能。xinetd已经成为Red Hat 7 和 Mandrake 7.2的Internet标准超级守护进程。这篇文章将引导你如何应用一些它的特性，这些特性基于xinetd 2.1.8.8 pre3版本。
导言

xinetd的最初的作者（Panagoitis Tsirigotis panos@cs.colorado.edu）好像已经停止了这个项目。 Rob Braun (bbraun@synack.net)继续了该项目，现在负责维护这个软件包。为了能使 select()在我的老的libc5系统上也可以使用，我不得不给当前的包添加几对头文件，这是我注意到的问题。或许你需要它们，如下：

    xinetd/internals.c.orig
    Fri Jun 16 19:00:15 2000
    +++ xinetd/internals.c
    Fri Jun 16 19:00:53 2000
    @@ -12,6 +12,8 @@
     #include <time.h>
     #include <fcntl.h>
     #include <syslog.h>
     #include <unistd.h>
     #include <sys/time.h>
     #include "sio.h"

关于 xinetd

xinetd用括号括起的、扩展了的语法取代了inetd中的通用的行。另外，还添加了日志和访问控制功能。 虽然inetd可以使用Venema的 tcp_wrappers 软件 (tcpd) 控制 TCP 的连接，但是你不能用它来控制 UDP 连接。此外，inetd对RPC(portmapper)类型的服务也处理不好。另外，虽然使用 inetd 你可以控制连接速度 ( 通过给wait或是no wait 变量附加一个数值，例如nowait.1表示每隔一秒钟一个实例)，你不能控制实例的最大数。这能导致进程表攻击（例如，一个有效的拒绝服务攻击）。通过使用xinetd，我们可以防止Dos。

我通常使用下面的命令启动xinetd，把它放在我的Internet服务启动脚本中：

    /usr/sbin/xinetd -filelog /var/adm/xinetd.log -f /etc/xinetd.conf

这告诉 xinetd 对所有的服务都进行纪录，日志保存到文件 /var/adm/xinetd.log中，并且使用配置文件/etc/xinetd.conf。这篇文章中的大量篇幅都将用在这个配置文件上。
编译时选项

你应该注意3个编译时的选项：libwrap、loadavg (用于监视负载均衡) 和 IPv6 support，它们提供了额外的访问控制。对于大多数libwrap"明白"的守护进程 (如portmapper 和sendmail)，在配置脚本中的"with-libwrap"选项告诉xinetd支持tcp_wrappers文件/etc/hosts.allow和/etc/hosts.deny。这些选项对xinetd作用就如同它们之于 inetd那样，并且支持所有的 xinetd控制的守护进程。注意如果你从零开始做xinetd的话，就可以做访问控制，不再需要tcpd。不管怎样。对libwrap 的支持是有用的--如果你从inetd/tcpd迁移并且也不想改变你的访问文件的话 。

第二个有趣的设置选项是支持负载均衡监控，通过在./configure脚本中使用with-loadavg选项可以达到。sendmail支持在高负载的时候停止连接--假定它已经脱离了控制并且正在当掉机器。用这个选项可以激活max_load 选项以限制任何连接或是基于负载均衡机器的所有服务。

最后，添加 IPv6支持 可以通过在 ./configure 脚本中使用 with-inet6 capability选项来完成。 这使xinetd 支持IPv6地址和连接。注意要使其生效的话你的核心（和网络）必须支持 IPv6。当然IPv4 仍然被支持。
配置文件

xinetd 配置文件，通常可以手工或是自动从inetd.conf文件生成。前者费时间且容易出错；后者可以通过 itox软件或者xconv.pl 脚本轻易完成。虽然itox软件正在被取消而倾向于使用 xconv.pl 脚本，它仍是很有用的。但是，要注意重复的运行它会覆盖原有的配置文件。itox和 xconv都以同样的方式工作，我们用 itox来进行演示：

    $ itox < /etc/inetd.conf > xinetd.conf

新一些的工具（xconv）可以理解注释，并且在对tcpd的使用上要比itox做得更好，使用itox，你不得不指定守护进程的路径 （如 /usr/sbin）。 你想要包含的第一段就是默认的段，就像名字暗示的那样，默认的xinetd服务。

    defaults
    {
       instances       = 25
       log_type        = FILE /var/adm/servicelog
       log_on_success  = PID HOST EXIT
       flags           = NORETRY
       log_on_failure  = HOST RECORD ATTEMPT
       only_from       = 129.22.0.0
       no_access       = 129.22.210.61 
       disabled        = nntp uucp tftp bootps who
                         shell login exec 
       disabled       += finger
    }

马上，我们可以了解 xinetd 设置参数的语法：<指示（directive）> <操作符（operator）> <值（value）>。xinetd所能理解的指示列在表一中，在这里我们将忽略 flags、type、env 和passenv指示符。 我对将对 only_from 和 no_access以及额外的日志选项加以更多的讨论

    表 1. xinetd的指示符
    指示符 	描述
    socket_type 	网络套接字类型, 流或者数据包
    socket_type 	网络套接字类型, 流或者数据包
    protocol 	IP 协议, 通常是TCP或者 UDP
    wait 	yes/no, 等同于inetd的wait/nowait
    user 	运行进程的用户 ID
    server 	执行的完整路径
    server_args 	传递给server的变量,或者是值
    instances 	可以启动的实例的最大的值
    start max_load 	负载均衡
    log_on_success 	成功启动的登记选项
    log_on_failure 	联机失败的时候的日志信息
    only_from 	接受的网络或是主机
    no_access 	拒绝访问的网络或是主机
    disabled 	用在默认的 {} 中 禁止服务
    log_type 	日志的类型和路径 FILE /SYSLOG
    nice 	运行服务的优先级
    id 	日志中使用的服务名

操作符非常简单，“=”或者“+=”。用 =，右边给定的值传给左边的指示符。+=也是非常直接的，用于给一个已经指定的指示符添加一个值。没有它，原先的指示符就会被覆盖，这样可以用来展开访问列表，或者跨越多行。

用如下的格式描述服务：

服务名　
{
指示符 = 值
指示符 += 值
}

服务名一定要在 /etc/services列出 ，并且要使用合适的socket和协议。
关于访问控制

关于访问控制的有几句话。 首先，xinetd控制连接而不是控制数据分组，它只是个用户方的守护进程，如同inetd 一样。同样的，可以打断一个被服务器禁止的主机的SYN或是connect()。但不能中止象FIN [端口扫描使用带有FIN 标志位的TCP包，通常是nmap这样的工具运行产生的]这样的"秘密" 扫描。不要把xinetd 当作一个firewall 用以阻止端口扫描。一个有经验的入侵者能够用这些信息收集你的不同服务的访问控制列表。幸运的是, 这些可以被xinetd纪录。当你看到日志的时候你的疑虑会消除的。

第二，xinetd（2.1.8.8pre3版本），当一个系统试图连接的时候进行名字查找。以前，它在启动的时候进行查找， 但是现在已经改变。

使用访问控制真的很简单。第一个指示符是 only_from, 列出了我们可以接受从哪一个网络或是主机的连接。这个规则可以被 no_access覆盖。 你可以使用网络号，如 10.0.0.0 或者 10或者是网络名（包括 .my.com 或者 .my.com）。主机名或者主机的 IP地址也可以在这里使用指示符0.0.0.0 匹配所有的主机并监听所有的地址。通过使用 no_access一旦符合标准拒绝就会被解析。再说一遍，网络和主机可以指定。
服务配置

让我们看一些基本的应用。我们先看第一个基本的服务echo，它是inetd 和xinetd固有的服务。

    service echo
    {
            socket_type     = stream
            protocol        = tcp
            wait            = no
            user            = root
            type            = INTERNAL
            id              = echo-stream
    }

echo 以root权限运行, 是一个tcp 流并在内部处理。echo-stream指示符将出现在日志中。如果没有only_from或是 no_access在指示符中,对这个服务的访问的配置将是不受限制的。

现在，让我们看一个正规的服务，daytime：

    service daytime
    {
            socket_type     = stream
            protocol        = tcp
            wait            = no
            user            = nobody
            server          = /usr/sbin/in.date
            instances       = 1
            nice            = 10
            only_from       = 0.0.0.0
    }

再说一次，任何人都可以连接, 不过我们指明它以nobody的身份运行来返回信息。和前一个例子相比，这个并没有额外的什么。现在我们看另一个服务 secure shell version 1。下面的设置可以防止sshd所带来的资源耗尽问题。

    service ssh1
    {
            socket_type     = stream
            protocol        = tcp
            instances       = 10
            nice            = 10
            wait            = no
            user            = root
            server          = /usr/local/sbin/sshd1
            server_args     = -i
            log_on_failure  += USERID
            only_from       = 192.168.0.0
            no_access       = 192.168.54.0 
            no_access       += 192.168.33.0
    }

在这里，我们建立了前面我们所作的。当作为超级用户inetd或者 xinetd重新调用sshd 需要用 -i 参数， 所以我们把它放在了 server_args 指示符后。注意：把这个标记添加到server标识符出会导致失败。在任何时候只有十个人可以同时使用，在这个服务器上这不是问题，这个例子我们从日志得到。另外作为默认信息，如果不能连接的话，连接方的用户 ID在RFC 1413中描述。最后，我们列出了两个网络不能访问这个服务。
日志和 xinetd

日志中有几个值可以用于得到你的服务器的信息

    表2 不同的日志指示值
    值 	成功/失败 	描述
    PID 	success 	当一个连接成功时登记产生的进程的pid
    HOST 	both 	登记远程主机地址
    USERID 	both 	登记远程用户的RFC 1413 ID
    EXIT 	success 	登记产生的进程的完成
    DURATION 	success 	登记任务持续的时间
    ATTEMPT 	failure 	登记连接失败的原因
    RECORD 	failure 	关于连接失败的额外的信息

这样，可以添加一些标准的行指明日志，就像下面的样子。对一个成功连接的服务，我们通常想登记服务产生的进程id，连接的主机和退出的时间：

    log_on_success = PID HOST EXIT

这样可以给出我们用来排错的有用的信息和正常的服务器操做信息。针对失败，我们可以记录我们想要的：

    log_on_failure = HOST RECORD ATTEMPT

我们记录了连接的主机、拒绝连接的原因和关于连接中的主机的额外的信息(有的时候是那些试图连接的用户ID)。推荐你这样做，可以对你的服务器有一个好的把握。

还看上面，在我们的默认段中，我们的日志写在/var/adm/servicelog中。我们指定所有信息，成功和失败的都要被xinetd记录。我们的大多数信息看起来像这样：

    00/9/13@16:05:07: START: pop3 pid=25679 from=192.168.152.133
    00/9/13@16:05:09: EXIT: pop3 status=0 pid=25679
    00/10/3@19:28:18: USERID: telnet OTHER :www

使用这个信息，可以轻易对 xinetd 排错和进行和正常操作。也可以容易发现安全问题（如你试图阻止的连接企图），在日志中简单的用 grep 作 ''FAIL'' 过滤，这些项显示如下：

    00/10/4@17:04:58: FAIL: telnet address from=216.237.57.154
    00/10/8@22:25:09: FAIL: pop2 address from=202.112.14.184

真正的安全问题需要另外的文章，但是，这足以说明，既然地址可以伪造，不要把地址报告看作固定的信息。xinetd.log文件（包含了从 xinetd得到的信息）在连接出错的时候作为排错信息很有用。

    00/10/25@21:10:48 xinetd[50]: ERROR: service echo-stream,
    accept:
    Connection reset by peer

重配置 xinetd

在xinetd.conf运行的时候，你可以编辑 xinetd.conf 文件。要重新配置，发送一个信号SIGUSR1 给 xinetd 进程：

    # ps -ax | grep xinetd
    50 ? S 5:47 /usr/sbin/xinetd -filelog /var/adm/xinetd.log -f /etc/xinetd.conf
    # kill -SIGUSR1 50

察看日志文件的尾部（用tail命令）确保你的配置和改动已经生效。如果你是个远程用户的话要确保你退出后还可以重新登陆进来。注意使用-HUP对xinetd重新配置，会实际导致 xinetd 停止操作。从设计的角度看，这可以阻止黑客重新配置你的xinetd并且在无需理解文档的情况下就可以重新载入它。
何时使用xinetd

以我个人而言，对所有的服务我都使xinetd；唯一一个对性能有影响的服务是我的Apache web 守护进程。太多的进程不得不启动，对它来说这太快了从而时间效率是个问题。DNS 服务也不应该用 xinetd，性能消耗太大。

对sendmail 服务我也使用了xinetd。这样对于允许连接的客户，我能够进行完美的控制。针对 sendmail我的设置如下：

    service smtp
    {
            socket_type   = stream
            protocol      = tcp
            wait          = no
            user          = root
            server        = /usr/sbin/sendmail
            server_args   = -bs
            instances     = 20
            nice          = 10
            only_from     += 0.0.0.0
            no_access     += 129.22.122.84 204.0.224.254
    }

即使是在一个高流量的邮件服务器上，对性能的影响也是可以忽略不计的。我还把 sshd 载入到 xinetd 以便阻止对它的进程表攻击。
结论

希望这篇文章对你配置或是根据需要调整inetd能有帮助。正如你所看到的，它提供的特性要比inetd大得多，甚至包含了tcp_wrappers。Solar Designer (http://www.openwall.com/) 提供一个针对稍旧一点的xinetd的版本的（2.2.1版本）的补丁，允许基于IP的实例控制，这有助于阻止简单的进程表攻击。注意，不管怎样，简单的伪造可以绕过它。我不知道是否这个包对以后的 xinetd是否也适用。

附：xinetd 代表 Extended Internet Services Daemon 下面附上一个xinetd.conf手册页上的参考设置：

    	#
    	# Sample configuration file for xinetd
    	#

    	defaults
    	{
    	     log_type		 = FILE /var/log/servicelog
    	     log_on_success	 = PID
    	     log_on_failure	 = HOST RECORD
    	     only_from		 = 128.138.193.0 128.138.204.0
    	     only_from		 = 128.138.252.1
    	     instances		 = 10
    	     disabled		 = rstatd
        }

    	#
        # Note 1: the protocol attribute is not required
        # Note 2: the instances attribute overrides the default
        #
         
    	service login
        {
    	    socket_type	 = stream
    	    protocol		 = tcp
    	    wait		 = no
    	    user		 = root
    	    server		 = /usr/etc/in.rlogind
    	    instances		 = UNLIMITED
        }

        #
        # Note 1: the instances attribute overrides the default
        # Note 2: the log_on_success flags are augmented
        #

        service shell
        {
    	     socket_type	 = stream
    	     wait		 = no
    	     user		 = root
    	     instances		 = UNLIMITED
    	     server		 = /usr/etc/in.rshd
    	     log_on_success	 += HOST RECORD
        }

        service ftp
        {
    	     socket_type	 = stream
    	     wait		 = no
    	     nice		 = 10
    	     user		 = root
    	     server		 = /usr/etc/in.ftpd
    	     server_args	 = -l
    	     instances		 = 4
    	     log_on_success	 += DURATION HOST USERID
    	     access_times	 = 2:00-9:00 12:00-24:00
        }

        # Limit telnet sessions to 8 Mbytes of memory and a total
        # 20 CPU seconds for child processes.

        service telnet
        {
    	     socket_type	 = stream
    	     wait		 = no
    	     nice		 = 10
    	     user		 = root
    	     server		 = /usr/etc/in.telnetd
    	     rlimit_as		 = 8M
    	     rlimit_cpu		 = 20
        }

        #
        # This entry and the next one specify internal services. Since
        # this is the same service using a different socket type, the
        # id attribute is used to uniquely identify each entry
        #
        
    	service echo
        {
    	     id			 = echo-stream
    	     type		 = INTERNAL
    	     socket_type	 = stream
    	     user		 = root
    	     wait		 = no
        }
        
        service echo
        {
    	     id			 = echo-dgram
    	     type		 = INTERNAL
    	     socket_type	 = dgram
    	     user		 = root
    	     wait		 = no
        }

        service servers
    	{
    	     type		 = INTERNAL UNLISTED
    	     protocol		 = tcp
    	     port		 = 9099
    	     socket_type	 = stream
    	     wait		 = no
        }

        #
        # Sample RPC service
        #
        service rstatd
        {
    	     type		 = RPC
    	     socket_type	 = dgram
    	     protocol		 = udp
    	     server		 = /usr/etc/rpc.rstatd
    	     wait		 = yes
    	     user		 = root
    	     rpc_version	 = 2-4
    	     env		 = LD_LIBRARY_PATH=/etc/securelib
        }

        #
        # Sample unlisted service
        #
        
    	service unlisted
        {
    	     type		 = UNLISTED
    	     socket_type	 = stream
    	     protocol		 = tcp
    	     wait		 = no
    	     server		 = /home/user/some_server
    	     port		 = 20020
        }

翻译后记：一日在网上看到自己在2年前的这个翻译文档，细读一下，发现谬误不少，遂找到原文，更正了一些不当之处。翻译不当之处肯定还是存在的，欢迎指出!

