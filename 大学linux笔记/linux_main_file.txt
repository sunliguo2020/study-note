/boot/grub/grub.conf	GRUB configuration file Grub 配置文件
/boot/module-info-*	Module information for the Linux kernel
/boot/System.map-*	Map of the Linux kernel
/boot/vmlinuz-*	Linux kernel

/etc/rc or /etc/rc.d or /etc/rc?.d 
  Script or directories of scripts to run starup or when changing the run level.
/etc/aliases	Mail aliases
/etc/at.deny	User IDs of users forbidden to use the at command
/etc/auto.master	Configuration file for the autofs daemon, which automatically mounts filesystems
/etc/auto.misc	Automounter map file
/etc/bashrc	                Systemwide functions and aliases for the bash shell
/etc/cron.daily/*	Daily cron jobs
/etc/cron.hourly/*	Hourly cron jobs
/etc/cron.monthly/*	Monthly cron jobs
/etc/cron.weekly/*	Weekly cron jobs
/etc/crontab	System cron file
/etc/cups/*	Printer configuration files
/etc/default/useradd	Defaults for the useradd command
/etc/DIR_COLORS	Directory listing colors
/etc/exports	NFS exported directories
/etc/filesystems	Supported filesystem types
/etc/fstab	                Filesystems mounted or available for mounting
/etc/group	                System group definitions
/etc/host.conf	Resolver configuration file
/etc/hosts	        Map of IP numbers to hostnames
/etc/hosts.allow	Hosts allowed to access Internet services
/etc/hosts.deny	Hosts forbidden to access Internet services
/etc/httpd/conf/*	Apache configuration files
/etc/httpd/httpd.conf	Main Apache configuration file
/etc/init.d/*	SysV initialization scripts
/etc/initlog.conf	Logging configuration file
/etc/inittab	                Configuration for the init daemon, which controls executing processes
/etc/issue	                Linux kernel and distribution version (local users)用户在登录提示符前的输出信息.
/etc/issue/net	Linux kernel and distribution version (remote users)
/etc/ld.so.conf	Shared library configuration file
/etc/login.defs	Options for useradd and related commands login 命令的配置文件
/etc/logrotate.conf	Log rotation configuration file
/etc/logrotate.d/*	Scripts to rotate logs
/etc/magic
  The configuration file for file.Coutains the descriptions of various file formats based on which file guesses the type of the file.
/etc/mail/*	               Mail server configuration files
/etc/mailcap	metamail MIME information
/etc/man.config	man configuration file
/usr/share/file/magic  file 的配置文件。包含不同文件格式的说明，file基于它猜测文件类型。
/etc/mime.types	MIME types
/etc/mime-magic*	Magic numbers for MIME data
/etc/minicom.users	User IDs allowed to use minicom
/etc/modules.conf	Aliases and options for loadable kernel modules
/etc/motd	                Message of the day  用户成功登录后自动输出
/etc/mtab	                Mounted filesystems 当前安装的文件系统列表
/etc/nsswitch.conf	Resolver configuration file
/etc/openldap/*	Open LDAP configuration files
/etc/pam.d/*	PAM configuration files
/etc/paper.config	Paper sizes
/etc/passwd	User account information
/etc/ppp/*	                PPP configuration
/etc/printcap	Printer options and capabilities
/etc/profile	                Default environment for users of the bash shell 登录或启动shell时执行的文件。系统管理员为所有用户建立的全局缺省环境。
/etc/profile.d/*	Shell initialization
/etc/protocols	Protocol names and numbers
/etc/pwdb.conf	pwdb library configuration
/etc/rc	               Scripts for system and process startup and shutdown
/etc/rc.local	Local startup script
/etc/rc.sysinit	System initialization file
/etc/rc?.d/*	Service start/stop scripts
/etc/rpc	                RPC program number database
/etc/rpm/*	                RPM database and configuration files
/etc/samba/*	Samba configuration files
/etc/securetty	Secure tty configuration 确认安全终端，即那个终端允许root登录。
/etc/security/*	PAM configuration files
/etc/sensors.conf	libsensors configuration file
/etc/services	Standard service names and numbers
/etc/shadow	Secure user account information
/etc/shells     可信任的shell
/etc/skel	  Skeleton files used to establish new user accounts
           The /etc/skel directory contains default environment files for new
	   accountes. ls -al
/etc/ssh/*	                SSH configuration files
/etc/sysconfig/*	System configuration files
/etc/sysconfig/network-scripts/*	Network adapter configuration files
/etc/sysconfig/network  
    eg: 
       NETWORKING=yes
       NETWORKING_IPV6=yes
       HOSTNAME=slg

  服务器网络配置信息
/etc/sysctl.conf	sysctl configuration file
/etc/syslog.conf	System logging process configuration
/etc/termcap	Terminal capabilities and options 终端性能数据库。说明不同的终端用什么“转义序列”控制。
/etc/updatedb.conf	updatedb/locate configuration file
/etc/wvdial.conf	GNOME dialer configuration file
/etc/X11/applnk/*	X application shortcuts
/etc/X11/fs/config	X font server configuration
/etc/X11/gdm/*	GNOME display manager configuration
/etc/X11/prefdm	Display manager configuration file
/etc/X11/xdm/*	X display manager configuration file
/etc/X11/XF86Config	X configuration file
/etc/X11/xinit/Xclients	Default script for xinit
/etc/X11/xinit/xinitrc	X session initialization file
/etc/X11/Xmodmap	Key mappings used by xdm and xinit
/etc/xinetd.conf	General xinetd configuration file
/etc/xinetd.d/*	xinetd configuration files for specific servers
/home/*/public_html	User web pages
/root/.bash_history	bash command history for system administrator
/root/.bash_logout	bash logout script for system administrator
/root/.bash_profile	bash initialization script for system administrator
/root/.bashrc	bash options for system administrator
/root/.Xresources	X resources for system administrator
/usr/share/config/*	Miscellaneous configuration files
/usr/share/fonts/*	Fonts
/usr/share/ssl/openssl.cnf	SSL certificate configuration
/usr/X11R6/lib/X11/app-defaults/*	X application defaults
/usr/X11R6/lib/X11/fonts/*	X fonts
/var/log/cron	Log of cron activity
/var/log/httpd/access_log	Log of web server access
/var/log/httpd/error_log	Log of web server errors
/var/log/boot.log	Boot messages
/var/log/cron	Cron log
/var/log/dmesg	Kernel message log
/var/log/lastlog	Last login log
/var/log/maillog	Mail transfer log
/var/log/messages	System log
/var/log/samba/*	Samba logs
/var/log/secure	System security log
/var/log/up2date	Up2date log
/var/run  保存到下次引导前有效的关于系统的系统文件。
/var/run/utmp 包括当前登录的用户的信息。
/var/www/cgi-bin	CGI scripts
/var/www/html/*	Web pages
/proc/cpuinfo 处理器信息
/proc/devices 当前运行的核心配置的设备驱动的列表
/proc/dma 显示当前的DMA通道。
/proc/filesystems 核心配置的文件系统。
/proc/interrupts  显示使用的中断
/proc/ioports 当前使用的I/O端口
/proc/kmsg  核心输出的消息。也被送到syslog
/proc/net  网络协议状态信息。
/proc/version  核心版本
