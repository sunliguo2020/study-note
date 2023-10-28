System information
arch			show architecture of machine
uname -r		show used kernel version
dmidecode -q		show hardware system components - (SMBIOS / DMI)
hdaparm -i /dev/hda	displays the characteristics of a hard-disk
hdparm -tT /dev/sda	perform test reading on a hard-disk
cat /proc/cpuinfo	show information CPU info
cat /proc/interrupts	show interrupts
cat /proc/meminfo	verify memory use
cat /proc/swaps		show file(s) swap
cat /proc/version	show version of the kernel
cat /proc/net/dev	show network adpters and statistics 
cat /proc/mounts	show mounted file system(s)
lspci -tv		display PCI devices
lsusb -tv		show USB devices
date			show system date
cal 2007		show the timetable of 2007
date 041217002007.00 	set date and time - MonthDayhoursMinutesYear.Secondi
clock -w 		save changes on BIOS

Shutdown, Restart of a system and Logout 
shutdown -h now			shutdown system
init 0 
shutdown -r hours:minutes &	planned shutdown of the system
shutdown -c			cancel a planned shutdown of the system
shutdown -r now			reboot
reboot
logout				leaving session

Files and Directory 
cd /home			enter to directory '/ home'
cd ..				go back one level
cd ../..			go back two levels
cd				go to home directory
cd ~utente			go to home directory
cd -				go to previous directory
pwd				show the path of work directory
ls				view files of directory
ls -F				view files of directory
ls -l				show details of files and directory
ls -a				show hidden files
ls *[0-9]*			show files and directory containing numbers
lstree				show files and directories in a tree starting from root
mkdir dir1			create a directory called 'dir1'
mkdir dir1 dir2			create two directories simultaneously
mkdir -p /tmp/dir1/dir2		create a directory tree
rm -f file1			delete file called 'file1'
rmdir dir1 			delete directory called 'dir1'
rm -rf dir1			remove a directory called 'dir1' and contents recursively
rm -rf dir1 dir2		remove two directories and their contents recursively
mv dir1 new_dir			rename / move a file or directory 
cp file1 file2			copying a file
cp dir/* .			copy all files of a directory within the current work directory
cp -a /tmp/dir1 .		copy a directory within the current work directory
cp -a dir1 dir2			copy a directory
ln -s file1 lnk1 		create a symbolic link to file or directory
ln file1 lnk1			create a physical link to file or directory
touch -t 0712250000 fileditest	modify timestamp of a file or directory - (YYMMDDhhmm)

File search 
find / -name file1		search file and directory into root filesystem from '/'
find / -user user1		search files and directories belonging to 'user1'
find /home/user1 -name *.bin	search files with '. bin' extension within directory '/ home/user1' 
find /usr/bin -type f -atime +100	search bynary files are not used in the last 100 days
find /usr/bin -type f -mtime -10	search files created or changed within 10 days
find / -name *.rpm -exec chmod 755 {} ;	search files with '.rpm' extension and modify permits
find / -name *.rpm -xdev	search files with  '.rpm' extension ignoring removable partitions as cdrom, pen-drive, etc.…
locate *.ps			find files with the '.ps' extension - first run 'updatedb' command
whereis halt			show location of a binary file, source or man
which halt			show full path to a binary / executable

Mounting a Filesystem 
mount /dev/hda2 /mnt/hda2	mount disk called hda2 - verify existence of the directory '/ mnt/hda2'
umount /dev/hda2		unmount disk called hda2 - exit from mount point '/ mnt/hda2' first
fuser -km /mnt/hda2		force umount when the device is busy
umount -n /mnt/hda2		run umount without writing the file /etc/mtab - useful when the file is read-only or the hard disk is full
mount /dev/fd0 /mnt/floppy	mount a floppy disk
mount /dev/cdrom /mnt/cdrom	mount a cdrom / dvdrom
mount /dev/hdc /mnt/cdrecorder	mount a cdrw / dvdrom
mount /dev/hdb /mnt/cdrecorder	mount a cdrw / dvdrom
mount -o loop file.iso /mnt/cdrom	mount a file or iso image
mount -t vfat /dev/hda5 /mnt/hda5	mount a Windows FAT32 file system
mount /dev/sda1 /mnt/usbdisk	mount a usb pen-drive or flash-drive
mount -t smbfs -o username=user,password=pass //winclient/share /mnt/share	mount a windows network share

Disk Space 
df -h				show list of partitions mounted
ls -lSr |more			show size of the files and directories ordered by size
du -sh dir1			estimate space used by directory 'dir1'
du -sh * | sort -rn 		show size of the files and directories sorted by size
rpm -q -a --qf '%10{SIZE}\t%{NAME}\n' | sort -k1,1n	show space used by rpm packages installed sorted by size (fedora, redhat and like)
dpkg-query -W -f='${Installed-Size;10}\t${Package}\n' | sort -k1,1n	show space used by deb packages installed sorted by size (ubuntu, debian and like)

Users and Groups 
groupadd group_name		create a new group
groupdel group_name		delete a group
groupmod -n new_group_name old_group_name	rename a group
useradd -c "Nome Cognome" -g admin -d /home/user1 -s /bin/bash user1	create a new user belongs "admin" group
useradd user1	create a new user
userdel -r user1	delete a user ( '-r' eliminates home directory)
usermod -c "User FTP" -g system -d /ftp/user1 -s /bin/nologin user1	change user attributes
passwd	change password
passwd user1	change a user password (only by root)
chage -E 2005-12-31 user1	set deadline for user password
pwck	check correct syntax and file format of '/etc/passwd'  and users existence
grpck	check correct syntax and file format of '/etc/group'  and groups existence
newgrp group_name	log in to a new group to change default group of newly created files

Permits on File - use "+" to set permissions and "-" to remove 
ls -lh	show permits
ls /tmp | pr -T5 -W$COLUMNS	divide terminal into 5 columns
chmod ugo+rwx directory1	set permissions reading (r), write (w) and (x) access to users owner (u) group (g) and others (o)
chmod go-rwx directory1	remove permits reading (r), write (w) and (x) access to users group (g) and others (or
chown user1 file1	change owner of a file
chown user1 -R directory1	change user owner of a directory and all the files and directories contained inside
chgrp gruppo1 file1	change group of files
chown user1:gruppo1 file1	change user and group ownership of a file
find / -perm -u+s	view all files on the system with SUID configured
chmod u+s /bin/file_eseguibile	set SUID bit on a binary file - the user that running that file gets same privileges as owner
chmod u-s /bin/file_binario	disable SUID bit on a binary file
chmod g+s /home/public	set SGID bit on a directory - similar to SUID but for directory
chmod g-s /home/public	disable SGID bit on a directory
chmod o+t /home/comune	set STIKY bit on a directory - allows files deletion only to legitimate owners
chmod o-t /home/comune	disable STIKY bit on a directory

Special Attributes on file - use "+" to set permissions and "-" to remove 
chattr +a file1	allows write opening of a file only append mode
chattr +c file1	allows that a file is compressed / decompressed automatically by the kernel
chattr +d file1	makes sure that the program ignores Dump the files during backup
chattr +i file1	makes it an immutable file, which can not be removed, altered, renamed or linked
chattr +s file1	allows a file to be deleted safely
chattr +S  file1	makes sure that if a file is modified changes are written in synchronous mode as with sync
chattr +u file1	allows you to recover the contents of a file even if it is canceled
lsattr	show specials attributes

Archives and compressed files 
bunzip2 file1.bz2	decompress a file called 'file1.bz2'
bzip2 file1	compress a file called 'file1'
gunzip file1.gz	decompress a file called 'file1.gz'
gzip file1	compress a file called 'file1'
gzip -9 file1	compress with maximum compression
rar a file1.rar test_file	create an archive rar called 'file1.rar'
rar a file1.rar file1 file2 dir1	compress 'file1', 'file2' and 'dir1' simultaneously
rar x file1.rar	decompress rar archive
unrar x file1.rar	decompress rar archive
tar -cvf archive.tar file1	create a uncompressed tarball
tar -cvf archive.tar file1 file2 dir1	create an archive containing 'file1', 'file2' and 'dir1'
tar -tf archive.tar	show contents of an archive
tar -xvf archive.tar	extract a tarball
tar -xvf archive.tar -C /tmp	extract a tarball into / tmp
tar -cvfj archive.tar.bz2 dir1	create a tarball compressed into bzip2
tar -xvfj archive.tar.bz2	decompress a compressed tar archive in bzip2
tar -cvfz archive.tar.gz dir1	create a tarball compressed into gzip
tar -xvfz archive.tar.gz	decompress a compressed tar archive in gzip
zip file1.zip file1	create an archive compressed in zip
zip -r file1.zip file1 file2 dir1	compress in zip several files and directories simultaneously
unzip file1.zip	decompress a zip archive

RPM Packages - Fedora, Red Hat and like 
rpm -ivh package.rpm	install a rpm package
rpm -ivh --nodeeps package.rpm	install a rpm package ignoring dependencies requests
rpm -U package.rpm	upgrade a rpm package without changing configuration files
rpm -F package.rpm	upgrade a rpm package only if it is already installed
rpm -e package_name.rpm	remove a rpm package
rpm -qa	show all rpm packages installed on the system
rpm -qa | grep httpd	show all rpm packages with the name "httpd"
rpm -qi package_name	obtain information on a specific package installed
rpm -qg "System Environment/Daemons"	show rpm packages of a group software
rpm -ql package_name	show list of files provided by a rpm package installed
rpm -qc package_name	show list of configuration files provided by a rpm package installed
rpm -q package_name --whatrequires	show list of dependencies required for a rpm packet
rpm -q package_name --whatprovides	show capability provided by a rpm package
rpm -q package_name --scripts	show scripts started during installation / removal
rpm -q package_name --changelog	show history of revisions of a rpm package
rpm -qf /etc/httpd/conf/httpd.conf	verify which rpm package belongs to a given file
rpm -qp package.rpm  -l	show list of files provided by a rpm package not yet installed
rpm --import /media/cdrom/RPM-GPG-KEY	import public-key digital signature
rpm --checksig package.rpm	verify the integrity of a rpm package
rpm -qa gpg-pubkey	verify integrity of all rpm packages installed
rpm -V package_name	check file size, permissions, type, owner, group, MD5 checksum and last modification
rpm -Va	check all rpm packages installed on the system - use with caution
rpm -Vp package.rpm	verify a rpm package not yet installed
rpm2cpio package.rpm | cpio --extract --make-directories  *bin*	extract executable file from a rpm package
rpm -ivh /usr/src/redhat/RPMS/`arch`/package.rpm	install a package built from a rpm source
rpmbuild --rebuild package_name.src.rpm	build a rpm package from a rpm source

YUM packages updater - Fedora, RedHat and like 
yum install package_name	download and install a rpm package
yum update	update all rpm packages installed on the system
yum update package_name	upgrade a rpm package
yum remove package_name	remove a rpm package
yum list	list all packages installed on the system
yum search package_name	find a package on rpm repository
yum clean packages	clean up rpm cache erasing downloaded packages
yum clean headers	remove all files headers that the system uses to resolve dependency
yum clean all	remove from the cache packages and headers files

DEB packages - Debian, Ubuntu and like 
dpkg -i package.deb	install / upgrade a deb package
dpkg -r package_name	remove a deb package from the system
dpkg -l	show all deb packages installed on the system
dpkg -l | grep httpd	show all rpm packages with the name "httpd"
dpkg -s package_name	obtain information on a specific package installed on system
dpkg -L package_name	show list of files provided by a package installed on system
dpkg --contents package.deb	show list of files provided by a package not yet installed
dpkg -S /bin/ping	verify which package belongs to a given file

APT packages updater - Debian, Ubuntu e like 
apt-get install package_name	install / upgrade a deb package
apt-cdrom install package_name	install / upgrade a deb package from cdrom
apt-get update	update all deb packages installed on system
apt-get remove package_name	remove a deb package from system
apt-get check	verify correct resolution of dependencies
apt-get clean	clean up cache from packages downloaded

View file content 
cat file1	view the contents of a file starting from the first row
tac file1	view the contents of a file starting from the last line
more file1	view content of a file along
less file1	similar to 'more' command but which allows backward movement in the file as well as forward movement
head -2 file1	view first two lines of a file
tail -2 file1	view last two lines of a file
tail -f /var/log/messages	view in real time what is added to a file
 
 Text Manipulation 
 cat file_test | [operation: sed, grep, awk, grep, etc] > result.txt	syntax to elaborate the text of a file, and write result to a new file
 cat file_originale | [operazione: sed, grep, awk, grep, etc] >> result.txt	syntax to elaborate the text of a file and append result in existing file
 grep Aug /var/log/messages	look up words "Aug" on file '/var/log/messages'
 grep ^Aug /var/log/messages	look up words that begin with "Aug" on file '/var/log/messages'
 grep [0-9] /var/log/messages	select from file '/var/log/messages' all lines that contain numbers
 grep Aug -R /var/log/*	search string "Aug" at directory '/var/log' and below
 grep Aug /var/log/messages	write result of a search within a file
 sed 's/stringa1/stringa2/g' example.txt	replace "string1" with "string2" in example.txt
 sed '/^$/d' example.txt	remove all blank lines from example.txt
 sed '/ *#/d; /^ *$/d' example.txt	remove comments and blank lines from example.txt
 echo 'esempio' | tr '[:lower:]' '[:upper:]'	convert from lower case in upper case
 sed -e '1d' result.txt	eliminates the first line from file example.txt
 sed -n '/stringa1/p'	view only lines that contain the word "string1"
 sed -e 's/ *$//' example.txt	remove empty characters at the end of each row
 sed -e 's/stringa1//g' example.txt	remove only the word "string1" from text and leave intact all
 sed -n '1,5p;5q' example.txt	view from 1th to 5th row
 sed -n '5p;5q' example.txt	view row number 5
 sed -e 's/00*/0/g' example.txt	replace more zeros with a single zero
 cat -n file1	number row of a file
 cat example.txt | awk 'NR%2==1'	remove all even lines from example.txt
 echo a b c | awk '{print $1}'	view the first column of a line
 echo a b c | awk '{print $1,$3}'	view the first and third column of a line
 paste file1 file2	merging contents of two files for columns
 paste  -d  '+' file1 file2	merging contents of two files for columns with '+' delimiter on the center
 sort file1 file2	sort contents of two files
 sort file1 file2 | uniq	sort contents of two files omitting lines repeated
 sort file1 file2 | uniq -u	sort contents of two files by viewing only unique line
 sort file1 file2 | uniq -d	sort contents of two files by viewing only duplicate line
 comm -1 file1 file2	compare contents of two files by deleting only unique lines from 'file1'
 comm -2 file1 file2	compare contents of two files by deleting only unique lines from 'file2'
 comm -3 file1 file2	compare contents of two files by deleting only the lines that appear on both files

 Character set and Format file conversion 
 dos2unix filedos.txt fileunix.txt	convert a text file format from MSDOS to UNIX
 unix2dos fileunix.txt filedos.txt	convert a text file format from UNIX to MSDOS
 recode ..HTML < page.txt > page.html	convert a text file to html
 recode -l | more	show all available formats conversion

 Filesystem Analysis 
 badblocks  -v  /dev/hda1	check bad blocks in disk hda1
 fsck  /dev/hda1	repair / check integrity of linux filesystem on disk hda1
 fsck.ext2  /dev/hda1	repair / check integrity of ext2 filesystem on disk hda1
 e2fsck  /dev/hda1	repair / check integrity of ext2 filesystem on disk hda1
 e2fsck -j /dev/hda1	repair / check integrity of ext3 filesystem on disk hda1
 fsck.ext3  /dev/hda1	repair / check integrity of ext3 filesystem on disk hda1
 fsck.vfat  /dev/hda1	repair / check integrity of fat filesystem on disk hda1
 fsck.msdos  /dev/hda1	repair / check integrity of dos filesystem on disk hda1
 dosfsck  /dev/hda1	repair / check integrity of dos filesystems on disk hda1

 Format a Filesystem 
 mkfs /dev/hda1	create a filesystem type linux on hda1 partition
 mke2fs /dev/hda1	create a filesystem type linux ext2 on hda1 partition
 mke2fs -j /dev/hda1	create a filesystem type linux ext3 (journal) on hda1 partition
 mkfs -t vfat 32 -F /dev/hda1	create a FAT32 filesystem
 fdformat  -n /dev/fd0	format a floppy disk
 mkswap /dev/hda3	create a swap filesystem

 SWAP filesystem 
 mkswap /dev/hda3	create a swap filesystem
 swapon /dev/hda3	activating a new swap partition
 swapon /dev/hda2 /dev/hdb3 	activate two swap partitions

 Backup 
 dump -0aj -f /tmp/home0.bak /home 	make a full backup of directory '/home'
 dump -1aj -f /tmp/home0.bak /home 	make a incremental backup of directory '/home'
 restore -if /tmp/home0.bak	restoring a backup interactively
 rsync -rogpav --delete /home /tmp	synchronization between directories
 rsync -rogpav -e ssh --delete /home ip_address:/tmp 	rsync via SSH tunnel
 rsync -az -e ssh --delete ip_addr:/home/public /home/local	synchronize a local directory with a remote directory via ssh and compression
 rsync -az -e ssh --delete /home/local ip_addr:/home/public	synchronize a remote directory with a local directory via ssh and compression
 dd bs=1M if=/dev/hda | gzip | ssh user@ip_addr 'dd of=hda.gz'	make a backup of a local hard disk on remote host via ssh
 tar -Puf backup.tar /home/user	make a incremental backup of directory '/home/user'
 ( cd /tmp/local/ && tar c . ) | ssh -C user@ip_addr 'cd /home/share/ && tar x -p'	copy content of a directory on remote directory via ssh
 ( tar c /home ) | ssh -C user@ip_addr 'cd /home/backup-home && tar x -p' 	copy a local directory on remote directory via ssh
 tar cf - . | (cd /tmp/backup ; tar xf - )	local copy preserving permits and links from a directory to another
 find /home/user1 -name '*.txt' | xargs cp -av --target-directory=/home/backup/ --parents	find and copy all files with '.txt' extention from a directory to another
 find /var/log -name '*.log' | tar cv --files-from=- | bzip2 > log.tar.bz2	find all files with '.log' extention and make an bzip archive
 dd if=/dev/hda of=/dev/fd0 bs=512 count=1	make a copy of MBR (Master Boot Record) to floppy
 dd if=/dev/fd0 of=/dev/hda bs=512 count=1	restore MBR from backup copy saved to floppy

 CDROM 
 cdrecord -v gracetime=2 dev=/dev/cdrom -eject blank=fast -force	clean a rewritable cdrom
 mkisofs /dev/cdrom > cd.iso	create an iso image of cdrom on disk
 mkisofs /dev/cdrom | gzip > cd_iso.gz	create a compressed iso image of cdrom on disk
 mkisofs -J -allow-leading-dots -R -V "Label CD" -iso-level 4 -o ./cd.iso data_cd	create an iso image of a directory
 cdrecord -v dev=/dev/cdrom cd.iso	burn an ISO image
 gzip -dc cd_iso.gz | cdrecord dev=/dev/cdrom -	burn a compressed ISO image
 mount -o loop cd.iso /mnt/iso	mount an ISO image
 cd-paranoia -B	rip audio tracks from a CD to wav files
 cd-paranoia -- "-3"	rip first three audio tracks from a CD to wav files
 cdrecord --scanbus	scan bus to identify the channel scsi

 Networking - LAN and WiFi 
 ifconfig eth0	show configuration of an ethernet network card
 ifup eth0	activate an interface 'eth0'
 ifdown eth0	disable an interface 'eth0'
 ifconfig eth0 192.168.1.1 netmask 255.255.255.0	configure IP Address
 ifconfig eth0 promisc	configure 'eth0' in promiscuous mode to gather packets (sniffing)
 dhclient eth0	active interface 'eth0' in dhcp mode
 route -n	show routing table
 route add -net 0/0 gw IP_Gateway	configura default gateway
 route add -net 192.168.0.0 netmask 255.255.0.0 gw 192.168.1.1	configure static route to reach network '192.168.0.0/16'
 route del 0/0 gw IP_gateway	remove static route
 echo "1" > /proc/sys/net/ipv4/ip_forward	activate ip routing
 hostname	show hostname
 host www.linuxguide.it	lookup hostname to resolve name to ip address and viceversa
 ip link show	show link status of all interfaces
 mii-tool eth0	show link status of 'eth0'
 ethtool eth0	show statistics of network card 'eth0'
 netstat -tup	show all active network connections and their PID
 netstat -tupl	show all network services listening on the system and their PID
 tcpdump tcp port 80	show all HTTP traffic
 iwlist scan	show wireless networks
 iwconfig eth1	show configuration of a wireless network card

 Microsoft Windows networks - SAMBA 
 nbtscan ip_addr	netbios name resolution
 nmblookup -A ip_addr	netbios name resolution
 smbclient -L ip_addr/hostname	show remote shares of a windows host
 smbget -Rr smb://ip_addr/share	like wget can download files from a host windows via smb
 mount -t smbfs -o username=user,password=pass //winclient/share /mnt/share	mount a windows network share

 IPTABLES - firewall 
 iptables -t filter -L	show all chains of filtering table
 iptables -t nat -L	show all chains of nat table
 iptables -t filter -F	clear all rules from filtering table
 iptables -t nat -F	clear all rules from table nat
 iptables -t filter -X	delete any chains created by user
 iptables -t filter -A INPUT -p tcp --dport telnet -j ACCEPT	allow telnet connections to input
 iptables -t filter -A OUTPUT -p tcp --dport http -j DROP	block HTTP connections to output
 iptables -t filter -A FORWARD -p tcp --dport pop3 -j ACCEPT	allow POP3 connections to forward chain
 iptables -t filter -A INPUT -j LOG --log-prefix "DROP INPUT"	logging sulla chain di input  Logging on chain input
 iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE	configure a PAT (Port Address Traslation) on eth0 masking outbound packets
 iptables -t nat -A PREROUTING -d 192.168.0.1 -p tcp -m tcp --dport 22 -j DNAT --to-destination 10.0.0.2:22	redirect packets addressed to a host to another host

 Monitoring and debugging 
 top	display linux tasks using most cpu
 ps -eafw	displays linux tasks
 ps -e -o pid,args --forest	displays linux tasks in a hierarchical mode
 pstree 	mostra un albero dei processi sistema Shows a tree system processes
 kill -9 ID_Processo	force closure of the process and finish it
 kill -1 ID_Processo	force a process to reload configuration
 lsof -p $$	display a list of files opened by processes
 lsof /home/user1	displays a list of open files in a given path system
 strace -c ls >/dev/null	display system calls made and received by a process
 strace -f -e open ls >/dev/null	display library calls
 watch -n1 'cat /proc/interrupts'	display interrupts in real-time
 last reboot	show history reboot
 lsmod	display kernel loaded
 free -m	displays status of RAM in megabytes
 smartctl -A /dev/hda	monitoring reliability of a hard-disk through SMART
 smartctl -i /dev/hda	check if SMART is active on a hard-disk
 tail /var/log/dmesg	show events inherent to the process of booting kernel
 tail /var/log/messages	show system events

 Other useful commands 
 mkbootdisk --device /dev/fd0 `uname -r`	create a boot floppy
 gpg -c file1	encrypt a file with GNU Privacy Guard
 gpg file1.gpg	decrypt a file with GNU Privacy Guard
 wget -r www.example.com	download an entire web site
 wget -c www.example.com/file.iso	download a file with the ability to stop the download and resume later
 echo 'wget -c www.example.com/files.iso' | at 09:00	start a download at any given time
 ldd ssh 	show shared libraries required by ssh program
 alias hh='history'	set an alias for a command - hh = history
