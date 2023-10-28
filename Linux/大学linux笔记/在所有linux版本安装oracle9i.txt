在所有linux版本安装oracle9i 

--------------------------------------------------------------------------------
 
http://www.chinaunix.net 作者:txfy  发表于：2003-12-29 14:27:42 
【发表评论】【查看原文】【Oracle讨论区】【关闭】  

名人名作，据说按照这个装绝对没问题！就是长了点，不过打印出来作为工作手册也是不错的！我就有好几本工作手册！呵呵                     
     Werner Puschitz  
            
Sr. AIX/Linux Systems Analyst and Administrator  
             Home Page of Werner Puschitz  



Installing Oracle 9i on RedHat Linux 7.1, 7.2, 7.3, 8.0, 9, Red Hat Advanced Server 2.1, and on Red Hat Enterprise Linux Advanced Server 3 (RHEL AS 3) 

Oracle on Red Hat Linux Portal  



Here is a summary (HOWTO) of how I installed:  
Oracle 9iR2 (9.2.0) Database on Red Hat Advanced Server 3 (kernel 2.4.21-4.EL, glibc 2.3.2-95.3)  
Oracle 9iR2 (9.2.0) Database on Red Hat Advanced Server 2.1 (kernel 2.4.9-e.3, glibc 2.2.4-26)  
Oracle 9iR2 (9.2.0) Database on Red Hat 9 (kernel kernel-2.4.20-6, glibc 2.3.2-5)  
Oracle 9iR2 (9.2.0) Database on Red Hat 8.0 (kernel 2.4.18-18.8.0, glibc 2.2.93-5)  
Oracle 9iR2 (9.2.0) Database on Red Hat 7.3 (kernel 2.4.18-3, glibc 2.2.5-34)  
Oracle 9iR1 (9.0.1) Database on Red Hat 7.3 (kernel 2.4.18-3, glibc 2.2.5-34)  
Oracle 9iR1 (9.0.1) Database on Red Hat 7.2 (kernel 2.4.7-10, glibc 2.2.4-13)  
Oracle 9iR1 (9.0.1) Database on Red Hat 7.1 (kernel 2.4.2-2, glibc 2.2.2-10)  

Validation/Certification:  

For Validations/Certifications, check the following links:  
Oracle's Certification Matrices  
Oracle Products on Red Hat Linux  
Red Hat Enterprise Linux Application List  

Errors and Problems:  
Some of the Oracle errors and problems covered here were only experienced in connection with 9i (9.0.1) and some only with 9iR2 (9.2.0). But since I cannot say for sure that a 9i (9.0.1) installation error will never show up during 9iR2 (9.2.0) installation, I simply kept all errors and problems listed together, see Oracle Installation Errors and Oracle Installation Problems, Important Tips and Hints.  

Red Hat Enterprise Linux Advanced Server 3 (RHEL AS 3)  
In order to install an Oracle9iR2 database on RH AS 3, the "Oracle9iR2 Patch Set 3 9.2.0.4.0" patchset and some other patches must be applied. Some errors can only be fixed by applying the 9.2.0.4 patchset. For more information, see Running Oracle Installation on Red Hat Enterprise Linux Advanced Server 3.  

Red Hat 9:  
Red Hat 9 includes now the the Native POSIX Thread Library (NPTL) which is an improved implementation of POSIX threads for Linux. But using NPTL will cause several problems for Oracle applications. Note that Oracle9i has not been certified on Red Hat 9!  
So to fix this problem, you can set the environment variable LD_ASSUME_KERNEL to 2.4.1, which means that the old "Linuxthreads with floating stacks" implementation will be used. Otherwise the Oracle installer runInstaller will hang, the Database Configuration Assistant dbca won't start etc.; see Oracle Installation Errors for more information. To see where this environment variable can be set, see Set Oracle Environments. For more information on LD_ASSUME_KERNEL, see Red Hat Linux 9 Release Notes.  
NOTE: Before you install Oracle9iR2, make sure that you first read the information about the error message "Error in invoking target install of make file /opt/oracle/product/9.2.0/network/lib/ins_oemagent.mk" in the Oracle Installation Errors section!  

Red Hat 8.0:  
The only problem I experienced with Oracle 9iR2 (9.2.0) on Red Hat 8.0 was:  
"Error in invoking target install of makefile /opt/oracle/product/9.2.0/ctx/lib/ins_ctx.mk"  
But this does not necessarily mean that you won't see other problems described here. See Oracle Installation Errors for more information.  
  

This article covers the following subjects and steps:  

* Documentations 
* Downloading and Installing Red Hat Linux 7.1, 7.2, 7.3, 8.0, 9 
* Unpacking Downloaded Oracle9i Installation Files and Burning Oracle9i CDs 
* Setting Swap Space 
* Setting Shared Memory 
* Checking /tmp Space 
* Sizing Oracle Disk Space 
* The "binutils" Issue 
* Checking Development Packages (RPMs) 
* JDK 
* Creating Oracle User Accounts 
* Creating Oracle Directories 
* Setting Oracle Environments 
* Starting runInstaller 
* Running Oracle Installation on RH 7.1, 7.2, 7.3, 8.0, 9, and on RH AS 2.1 
* Running Oracle Installation on Red Hat Enterprise Linux Advanced Server 3 
* Startup and Shutdown of the Oracle 9i Database 
* Oracle Installation Problems, Tips and Hints 
* Oracle Installation Errors 



Documentations 
Oracle9i Database Documentation for Linux  
Tuning and Optimizing Red Hat Linux Advanced Server for Oracle9i Database  
Oracle9iR2 on Linux: Performance, Reliability and Manageability Enhancements on Red Hat Linux Advanced Server 2.1  
An Overview of Red Hat Advanced Server V2.1 Reliability, Availability, Scalability, and Manageability (RASM) Features  


Downloading and Installing Red Hat Linux 7.1, 7.2, 7.3, 8.0, 9  
To download Red Hat Linux 7.x, 8.0, 9, check the links at http://www.puschitz.com/RedhatDownload.html  
You can find the installation guides for installing Red Hat Linux under Red Hat Linux Manuals.  

NOTE: You cannot download Red Hat Linux Advanced Server 2.1, you can only download the source code. If you want to get the binary CDs, you will have to buy it at http://www.redhat.com/software/linux/advanced/.  

Installing Software Packages (RPMs) 

You don't have to install all RPMs when you want to run an Oracle9i database on Red Hat Linux.  

For instance, if you install Red Hat Advanced Server, you are fine when you select the Installation Type "Advanced Server" and when you don't select the Package Group "Software Development". There are only a few other RPMs that are required for installing Oracle9i. These other RPMs are covered in this article.  

Or when you install Oracle9i on Red Hat Linux 7.x, 8.0, or 9, you are fine when you select the installation type "Server".  


Unpacking Downloaded Oracle9i Installation Files and Burning Oracle9i CDs 

Download Oracle9i for Linux from the following web site:  
http://otn.oracle.com/software/products/oracle9i/htdocs/linuxsoft.html  

Uncompress and unpack downloaded files:  

For Oracle9i (9.2.0):  

One step procedure (uses less disk space and is faster): 

  zcat lnx_920_disk1.cpio.gz | cpio -idmv 
  zcat lnx_920_disk2.cpio.gz | cpio -idmv 
  zcat lnx_920_disk3.cpio.gz | cpio -idmv 
Two step procedure: 

  # Uncompress 
  gunzip lnx_920_disk1.cpio.gz lnx_920_disk2.cpio.gz lnx_920_disk3.cpio.gz Linux9i_Disk3.cpio.gz 

  # Unpack the downloaded files: 
  cpio -idmv < lnx_920_disk1.cpio 
  cpio -idmv < lnx_920_disk2.cpio 
  cpio -idmv < lnx_920_disk3.cpio 

For Oracle9i (9.0.1):  

One step procedure (uses less disk space and is faster): 

  zcat Linux9i_Disk1.cpio.gz | cpio -idmv 
  zcat Linux9i_Disk2.cpio.gz | cpio -idmv 
  zcat Linux9i_Disk3.cpio.gz | cpio -idmv 
Two step procedure: 

  # Uncompress 
  gunzip Linux9i_Disk1.cpio.gz Linux9i_Disk2.cpio.gz Linux9i_Disk3.cpio.gz 

  # Unpack the downloaded files: 
  cpio -idmv < Linux9i_Disk1.cpio 
  cpio -idmv < Linux9i_Disk2.cpio 
  cpio -idmv < Linux9i_Disk3.cpio 

Now you should have 3 directories containing installation files:  

Disk1 
Disk2 
Disk3 
I executed the following commands when I burned the 3 CDs:  
mkisofs -r Disk1 | cdrecord -v --eject dev=0,0,0 speed=15 - 
mkisofs -r Disk2 | cdrecord -v --eject dev=0,0,0 speed=15 - 
mkisofs -r Disk3 | cdrecord -v --eject dev=0,0,0 speed=15 - 
(You can get the dev numbers when you execute cdrecord -scanbus).  


Setting Swap Space 

In order to perform a typical Oracle 9i installation and to create a simple prototype database, Oracle says that you need a minimum of 512MB of RAM for the Oracle9i (9.0.1) Server, and the amount of disk space (swap space) should be equal to twice the amount of RAM or at least 400 MB, whichever is greater.  
I tried to test the limits on an older PC with 256 MB of RAM and with 600 MB of swap space. I was able to install Oracle 9i (9.0.1 & 9.2.0) and Oracle's default database without any problems. But when I used less swap space on this PC (256MB RAM), I was runnig out of memory. So I definitely recommend to use more RAM and/or more swap space as specified in the Oracle installation guide.  

NOTE: If you do not have enough swap space or RAM during the Oracle installation, in particular during the database creation, your Oracle server (Linux) will temporarily become unresponsive to any events for several minutes.  

For more information on correctly sizing the swap space for your database, see Sizing Swap Space.  

To check the memory, run:  
grep MemTotal /proc/meminfo 
To check the swap space, run:  
cat /proc/swaps 

You can also add temporary swap space by creating a temporary swap file instead of using a raw device. Here is the procedure:  
su - root 
dd if=/dev/zero of=tmpswap bs=1k count=900000 
chmod 600 tmpswap 
mkswap tmpswap 
swapon tmpswap 
To disable the temporary swap space execute the following commands:  
su - root 
swapoff tmpswap 
rm tmpswap 


Setting Shared Memory 

For Oracle 9i (9.2.0) installation I had to increase the maximum shared memory size on my Linux server for all Red Hat versions. The Oracle Database Configuration Assistant displayed the following error message on my server: 

ORA-27123: unable to attach to shared memory segment. 
I temporarely increased the shmmax setting for the kernel by executing the following command:  
$ su - root 
# cat /proc/sys/kernel/shmmax 
33554432 
# echo `expr 1024 \* 1024 \* 1024` >; /proc/sys/kernel/shmmax 
# cat /proc/sys/kernel/shmmax 
1073741824 
It is recommended to increase the shmmax setting permanently for Oracle. For more information, see Setting Shared Memory.  

For more information on optimizing shared memory settings for Oracle databases on Linux, see Setting Shared Memory. These parameters apply to all Red Hat Linux versions. But note that except for the shmmax parameter, these parameter do not need to be changed for installing Oracle on Linux. But you might want to adjust all shared memory settings later to optimize the server for Oracle.  


Checking /tmp Space 

The Oracle Universal Installer requires up to 400 MB of free space in the /tmp directory.  

To check the space in /tmp, run:  
$ df /tmp 
If you do not have enough space in the /tmp directory, you can temporarily create a tmp directory in another filesystem. Here is how you can do this:  
su - root 
mkdir /<AnotherFilesystem>;/tmp 
chown root.root /<AnotherFilesystem>;/tmp 
chmod 1777 /<AnotherFilesystem>;/tmp 
export TEMP=/<AnotherFilesystem>;           # used by Oracle 
export TMPDIR=/<AnotherFilesystem>;         # used by Linux programs like the linker "ld" 
When you are done with your Oracle installation, shutdown Oracle and remove the temporary directory:  
su - root 
rmdir /<AnotherFilesystem>;/tmp 
unset TEMP 
unset TMPDIR 


Sizing Oracle Disk Space 

You will need about 2.5 GB for the database software. If you perform a typical database installation and not a customized database installation, then you will need about 3.5 GB of disk space.  


The "binutils" Issue 

Skip this step for Oracle9iR2. 

I did not experience this problem with Oracle 9i (9.2.0), but only with Oracle 9i (9.0.1).  

The binutils package that comes with Red Hat 7.1, 7.2, 7.3, and with RedHat 2.1 Advanced Server doesn't work with Oracle 9i (9.0.1) Universal Installer. Here are the options you have for 9.0.1:  

I recommend the following approach: 

Wait for the following Oracle installation error:  
"Error invoking target install of makefile /opt/oracle/product/9.0.1/plsql/lib/ins_plsql.mk" 
And fix this problem as described in Oracle Installation Errors.  
I recommend this approach since it obviates the need to change binutils.  
I do not recommend the following approach: 

Download the following binutil RPM version and downgrade binutil on the Oracle server: 
ftp://ftp.redhat.com/pub/redhat/linux/7.0/en/os/i386/RedHat/RPMS/binutils-2.10.0.18-1.i386.rpm  

su - root 
rpm -Uvh --force --nodeps binutils-2.10.0.18-1.i386.rpm 
When you are done with the Oracle installation, you upgrade your binutil RPM back to the version you had before you downgraded. E.g. on the Red Hat 7.2 server I did:  
rpm -Uvh --force --nodeps binutils-2.11.90.0.8-9.i386.rpm 
Here is Oracle's official solution for Oracle 9iR1 or 9iR1 iAS on RedHat 2.1 Advanced Server which I don't like:  
http://otn.oracle.com/software/products/oracle9i/files/binutils_readme.html  


Checking Development Packages (RPMs) 

You will need some RPM development packages for the Oracle installer to build the Oracle modules, otherwise you will get an error messages similar to this one:  
Error in invoking target ntcontab.o of makefile  
/opt/oracle/product/9.2.0/network/lib/ins_net_client.mk 

Development Packages (RPMs) for RH 7.1, 7.2, and RH AS 2.1: 

To see if these development packages are installed on your server, run the following command:  
rpm -q gcc cpp compat-libstdc++ glibc-devel kernel-headers binutils 
For instance, most of these packages will be missing when you installed RedHat 2.1 Advanced Server and if you did not select the "Software Development" package. For the RedHat 2.1 Advanced Server I executed the following commands to install the missing RPMs from the two CDs:  
su - root 
rpm -ivh cpp-2.96-108.1.i386.rpm \ 
glibc-devel-2.2.4-26.i386.rpm \ 
kernel-headers-2.4.9-e.3.i386.rpm \ 
gcc-2.96-108.1.i386.rpm \ 
binutils-2.11.90.0.8-12.i386.rpm 

Development Packages (RPMs) for RH 7.3, 8.0, and 9: 

To see if these development packages are installed on your server, run the following command:  
rpm -q gcc cpp compat-libstdc++ glibc-devel glibc-kernheaders binutils 
For instance, when I installed Red Hat 9.0 and when I used the default packages for the Installation Type "Server", I had to install the following RPMs afterwards:  
su - root 
rpm -ivh binutils-2.13.90.0.18-9.i386.rpm \ 
cpp-3.2.2-5.i386.rpm \ 
gcc-3.2.2-5.i386.rpm \ 
glibc-devel-2.3.2-5.i386.rpm \ 
glibc-kernheaders-2.4-8.10.i386.rpm  

Development Packages (RPMs) for Red Hat Enterprise Linux Advanced Server 3 (RHEL AS 3): 

To see if these development packages are installed on your server, run the following command:  
rpm -q gcc cpp compat-libstdc++ glibc-devel glibc-headers glibc-kernheaders binutils 

NOTE: Before you install Oracle9iR2, make sure that you also read the information about the error message "Error in invoking target install of make file /opt/oracle/product/9.2.0/network/lib/ins_oemagent.mk" in the Oracle Installation Errors section!  


JDK 

Skip this step for Oracle9iR2. 

I successfully installed Oracle9iR2 without installing JDK on the system. Oracle comes now with its own Java. This means that you don't have to execute the following steps which were required for older Oracle versions:  

Download JDK 1.3.1 or Blackdown 1.1.8_v3: (I usually used Blackdown) 
http://www.blackdown.org 
http://java.sun.com 

According to the JDK documentation, install JDK under /usr/local. Then create a symbolic link to the JDK under /usr/local/java:  
su - root 
bzip2 -dc jdk118_v3-glibc-2.1.3.tar.bz2 | tar xf - -C  /usr/local 
ln -s /usr/local/jdk118_v3 /usr/local/java 


Creating Oracle User Accounts 

su - root 
groupadd dba          # group of users to be granted with SYSDBA system privilege 
groupadd oinstall     # group owner of Oracle files 
useradd -c "Oracle software owner" -g oinstall -G dba oracle 
passwd oracle 
For more information on the "oinstall" group account, see When to use "OINSTALL" group during install of oracle.  


Creating Oracle Directories 

In this example, make sure that the /opt filesystem is large enough, see Oracle Disk Space for more information. If /opt is not on a separate filesystem, then make sure the root filesystem "/" has enough space.  

su - root 
mkdir /opt/oracle 
mkdir /opt/oracle/product 
mkdir /opt/oracle/product/9.2.0 
chown -R oracle.oinstall /opt/oracle 
                                            
mkdir /var/opt/oracle 
chown oracle.dba /var/opt/oracle 
chmod 755 /var/opt/oracle 


Setting Oracle Environments 

Set the following Oracle environment variables before you start runInstaller.  

As the oracle user execute the following commands:  
# Set the LD_ASSUME_KERNEL environment variable only for Red Hat 9 and 
# for Red Hat Enterprise Linux Advanced Server 3 (RHEL AS 3) !! 
# Use the "Linuxthreads with floating stacks" implementation instead of NPTL: 
export LD_ASSUME_KERNEL=2.4.1 

# Oracle Environment 
export ORACLE_BASE=/opt/oracle 
export ORACLE_HOME=/opt/oracle/product/9.2.0 
export ORACLE_SID=test 
export ORACLE_TERM=xterm 
# export TNS_ADMIN= Set if sqlnet.ora, tnsnames.ora, etc. are not in $ORACLE_HOME/network/admin 
export NLS_LANG=AMERICAN; 
export ORA_NLS33=$ORACLE_HOME/ocommon/nls/admin/data 
LD_LIBRARY_PATH=$ORACLE_HOME/lib:/lib:/usr/lib 
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib 
export LD_LIBRARY_PATH 

# Set shell search paths 
export PATH=$PATH:$ORACLE_HOME/bin 

I successfully installed Oracle9iR2 without setting the following CLASSPATH environment variable:  
# CLASSPATH=$ORACLE_HOME/JRE:$ORACLE_HOME/jlib:$ORACLE_HOME/rdbms/jlib 
# CLASSPATH=$CLASSPATH:$ORACLE_HOME/network/jlib 
# export CLASSPATH 

You can put these environment settings at the end of the ~oracle/.bash_profile file if you use bash. By this way you don't have to set the environment variables again when you login as "oracle", or when you switch to the user "oracle" by executing "su - oracle".  


Starting runInstaller 

Before you continue, make sure you have set the Oracle environment variables, see above.  

Oracle no longer supports a character mode installer. Therefore, in order to execute runInstaller directly from a console of a machine you are logged into (in this example the node name where Oracle is running is called "oracleserver"), you need to set the DISPLAY environment variable. Before you do that, make sure that you also allow runInstaller on "oracleserver" to display X information on your Linux desktop machine (in this example, the PC name where you are running X Windows like KDE or GNOME is called "yourdesktop"), because programs running on remote machines cannot display information to your screen unless you give them the authority to do so. Note that the X display relink mechanism does not work for NT desktop machines unless you use Exceed. 

Before you run runInstaller, execute e.g. 'xterm' to see if your X setup is really working! If you install Oracle on your desktop PC and not on a remote node, then you can skip step 1 and 3. 

Step 1: Allow "oracleserver" to display X information to your desktop PC "yourdesktop": 

  yourdesktop:user$ xhost +oracleserver 
Step 2: Open a new window and login to the Oracle server "oracleserver" as root. This window will be used for mounting and unmounting the Oracle CDs.  
  oracleserver:$ su - root 
  oracleserver:root# mount /mnt/cdrom 

Step 3: From the console of your Oracle server "oracleserver" where you will run runInstaller, execute the following commands:  
  oracleserver:$ su - oracle 
  oracleserver:oracle$ export DISPLAY=yourdesktop:0.0 
Step 4: Now execute runInstaller as "oracle". Do not cd to /mnt/cdrom !!  
  oracleserver:oracle$ /mnt/cdrom/runInstaller 


NOTE: 
Don't run runInstaller for Red Hat Enterprise Linux Advanced Server 3 (RHEL AS 3) yet! See Running Oracle Installation on Red Hat Enterprise Linux Advanced Server 3 for more information.  


Running Oracle Installation on RH 7.1, 7.2, 7.3, 8.0, 9, and on RH AS 2.1 

Keep in mind that you will get one or more errors here during the Oracle installation! See Oracle Installation Errors for more information. 

This is how I answered the questions for the runInstaller: 

- What would you like as the base directory (Inventory Location): 

  /opt/oracle/oraInventory 
- UNIX Group Name (permission for updating Oracle software): 

  oinstall 
  You could also use "dba" which I do not recommend for security reasons. 
  For more information on the "oinstall" group account, see 
  When to use "OINSTALL" group during install of oracle. 
   
- Full path name for Oracle Home:  
  /opt/oracle/product/9.2.0 
etc. 


Running Oracle Installation on Red Hat Enterprise Linux Advanced Server 3 

In order to install an Oracle9iR2 database on RH AS 3, the "Oracle9iR2 Patch Set 3 9.2.0.4.0" patchset and some other patches must be applied. Some errors can only be fixed by applying the 9.2.0.4 patchset.  


Installing Oracle9iR2 

Install the following RPMs (see Oracle Note:252217.1 for more information):  
su - root 
rpm -ivh \ 
compat-db-4.0.14-5.i386.rpm \ 
compat-gcc-7.3-2.96.122.i386.rpm \ 
compat-gcc-c++-7.3-2.96.122.i386.rpm \ 
compat-libstdc++-7.3-2.96.122.i386.rpm \ 
compat-libstdc++-devel-7.3-2.96.122.i386.rpm \ 
openmotif21-2.1.30-8.i386.rpm \ 
setarch-1.3-1.i386.rpm \ 
tcl-8.3.5-92.i386.rpm 
Relink gcc so that the older gcc will be used during the Oracle installation (see Oracle Note:252217.1 for more information):  
su - root 
mv /usr/bin/gcc /usr/bin/gcc323 
ln -s /usr/bin/gcc296 /usr/bin/gcc 
mv /usr/bin/g++ /usr/bin/g++323      # if g++ doesn't exist, then gcc-c++ was not installed 
ln -s /usr/bin/g++296 /usr/bin/g++ 

When you execute runInstaller from the Oracle 9iR2 (9.2.0) CD, you will get the following error message:  
Error occurred during initialization of VM 
Unable to load native library: /tmp/OraInstall2003-10-25_03-14-57PM/jre/lib/i386/libjava.so: 
    symbol __libc_wait, version GLIBC_2.0 not defined in file libc.so.6 with link time reference 


To resolve resolve the __libc_wait symbol issue, download the patch p3006854_9204_LINUX.zip from http://metalink.oracle.com. See bug 3006854 for more information.  

To apply the patch, run  
su - root 
# unzip p3006854_9204_LINUX.zip 
Archive:  p3006854_9204_LINUX.zip 
   creating: 3006854/ 
  inflating: 3006854/rhel3_pre_install.sh 
  inflating: 3006854/README.txt 

# cd 3006854 
# sh rhel3_pre_install.sh 
Applying patch... 
Patch successfully applied 
#  
NOTE: If you get the following error when you run rhel3_pre_install.sh:  
  rhel3_pre_install.sh: line 36: gcc: command not found 
Then you forgot to install or link gcc, see above. This means you can't start any binaries any more:  
# ls 
ls: error while loading shared libraries: /etc/libcwait.so: cannot open shared object file: No such file or directory 
# rm /etc/ld.so.preload 
rm: error while loading shared libraries: /etc/libcwait.so: cannot open shared object file: No such file or directory 
# 
To fix that, run the echo command which is a built-in shell command:  
# echo "" >; /etc/ld.so.preload 
rm /etc/ld.so.preload 
And start over again.  


Now runInstaller can be started from the CD:  
su - oracle 
$ echo $LD_ASSUME_KERNEL    # it is important that this variable is set! 
2.4.1 
$ /mnt/cdrom/runInstaller 

 - Welcome Screen:       Click Next 
 - Inventory Location:   Click Next 
 - Unix Group Name:      Use "oinstall" and click Next 
                         When asked to run /tmp/orainstRoot.sh, run it before you click Continue 
 - File Locations:       Use default values 
 - Available Products:   Select "Oracle9i Database 9.2.0.1.0" 
 - Installation Types:   Select Custom since we only want to install the software for now 
 - Available Products:   Click Next or add some more components. 
 - Components Locations: Accept default values and click Next 
 - Privileged Operating System Groups: 
                         I used the default values: OSDBA Group = dba, OSOPER Group = dba 
 - Oracle Managent Server Repository: 
                         I used the default choice 
 - Create database:      Select NO since we first have to patch Oracle before a database can be created! 
 - Summary:              Start the Install 
 - Configuration tools:  Tools won't come up. Simply ignore it. 
 - At the end of the installation, exit runInstaller. 

  
You may get the following errors: 

Error in invoking target install of makefile /opt/oracle/product/9.2.0/network/lib/ins_oemagent.mk.  

The /opt/oracle/product/9.2.0/install/make.log file reads:  
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcln.o)(.text+0xa4e): In function `Nls_FormatCmd': 
  : undefined reference to `__ctype_b' 
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcln.o)(.text+0x159d): In function `Nls_ScanCmd': 
  : undefined reference to `__ctype_b' 
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcln.o)(.text+0x1603): more undefined references to `__ctype_b' follow 
  collect2: ld returned 1 exit status 
  make: *** [dbsnmp] Error 1 

Click ignore. This will be fixed by applying the patch 3119415 after the 9.2.0.4 patchset has been applied. You won't be able to apply the patch 3119415 at this time since the file /opt/oracle/oraInventory/ContentsXML/comps.xml doesn't exist yet.  


Error in invoking target install of makefile /opt/oracle/product/9.2.0/ctx/lib/ins_ctx.mk.  

The /opt/oracle/product/9.2.0/install/make.log file reads:  
  /usr/bin/ld: ctxhx: hidden symbol `stat' in /usr/lib/libc_nonshared.a(stat.oS) is referenced by DSO 
  collect2: ld returned 1 exit status 
  make: *** [ctxhx] Error 1 

Click ignore. This is fixed by applying the 9.2.0.4 patchset.  


Patching Oracle9iR2: 

To patch Oracle9iR2, download the Oracle 9i Release 2 Patch Set 3 Version 9.2.0.4.0 for Linux x86 from http://metalink.oracle.com.  

Copy the downloaded "p3095277_9204_LINUX.zip" file to e.g. /tmp and run the following command:  
su - oracle 
$ cp p3095277_9204_LINUX.zip /tmp 
$ cd /tmp 
$ unzip p3095277_9204_LINUX.zip 
Archive:  p3095277_9204_LINUX.zip 
  inflating: 9204_lnx32_release.cpio 
  inflating: README.html 
  inflating: patchnote.css 
$ 
$ cpio -idmv < 9204_lnx32_release.cpio 
Disk1/stage/locks 
Disk1/stage/Patches/oracle.apache.isqlplus/9.2.0.4.0/1/DataFiles/bin.1.1.jar 
Disk1/stage/Patches/oracle.apache.isqlplus/9.2.0.4.0/1/DataFiles/lib.1.1.jar 
... 


To patch the runInstaller, run:  
su - oracle 
$ echo $LD_ASSUME_KERNEL    # it is important that this variable is set! 
2.4.1 
$ cd /tmp/Disk1/ 
$ ./runInstaller 

 - Welcome Screen:       Click Next 
 - File Locations:       Use default values 
 - Available Products:   Select "Oracle Universial Installer 2.2.0.18.0 !" 
 - Components Locations: Accept default values and click Next 
 - Summary:              Start the Install 
 - At the end of the installation, you must exit runInstaller! 


To patch Oracle9iR2, run:  
su - oracle 
$ echo $LD_ASSUME_KERNEL    # it is important that this variable is set! 
2.4.1 
$ cd $ORACLE_HOME/bin 
$ ./runInstaller 

 - Welcome Screen:       Click Next 
 - File Locations:       Use default values 
 - Available Products:   Select "Oracle9iR2 Patch Set 3 9.2.0.4.0 !" 
 - Summary:              Start the Install 
 - At the end of the installation, exit runInstaller 


You may get the following error: 

Error in invoking target install of makefile /opt/oracle/product/9.2.0/network/lib/ins_oemagent.mk.  

The /opt/oracle/product/9.2.0/install/make.log file reads:  
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcl.o)(.text+0x1cc): In function `get_ora_stmt_handle': 
  : undefined reference to `__ctype_b' 
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcl.o)(.text+0x124e): In function `OraProcess_Oid': 
  : undefined reference to `__ctype_b' 
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcl.o)(.text+0x176c): more undefined references to `__ctype_b' follow 
  collect2: ld returned 1 exit status 
  make: *** [dbsnmp] Error 1 

Click ignore. This will be fixed by applying the patch 3119415 after the 9.2.0.4 patchset has been applied. The patch 3119415 cannot be applied while the patch process for the 9.2.0.4 patchset is running.  


After the 9.2.0.4 patchset has been applied, download the patch p3119415_9204_LINUX.zip from http://metalink.oracle.com. See bug 3119415 for more information. Also, download the opatch Release 2.2.0 utility from http://metalink.oracle.com. See bug 2617419 for more information.  

To install opatch, run:  
su - oracle 
$ cp p2617419_210_GENERIC.zip /tmp 
$ cd /tmp 
$ unzip p2617419_210_GENERIC.zip 
Before you apply the 3119415 patch, you need to make sure the fuser binary can be found by the oracle user, see the PATH environment variable below. Otherwise the patch can't be applied because the fuser binary is used by opatch.  

To apply the 3119415 patch, run  
su - oracle 
$ unzip p3119415_9204_LINUX.zip 
$ cd 3119415 
$ export PATH=$PATH:/tmp/OPatch 
$ export PATH=$PATH:/sbin        # the patch needs "fuser" which is located in /sbin 
$ which opatch 
/tmp/OPatch/opatch 
$ opatch apply 


Now you should be able to create a database with dbca:  
su - oracle 
dbca 

And don't forget to undo the changes (links) to /usr/bin/gcc and /usr/bin/g++ if you don't need it any more. Also don't forget the /etc/ld.so.preload file.  


Startup and Shutdown of the Oracle 9i Database 

sqlplus:  

svrmgrl is not supported any more. You can now do everything with sqlplus.  

For instance, to startup the database, run the following commands:  

oracle$ sqlplus /nolog 
SQL>; connect / as sysdba 
SQL>; startup 
The slash connects you to the schema owned by SYS. So in this example you will be connected to the schema owned by SYS with the privilege SYSDBA. SYSDBA gives you the following privileges:  
  - sysoper privileges WITH ADMIN OPTION 
  - create database 
  - recover database until 

$ORACLE_HOME/bin/dbstart and $ORACLE_HOME/bin/dbshut 

You can also use $ORACLE_HOME/bin/dbstart to startup the database, and $ORACLE_HOME/bin/dbshut to shutdown the database. You can place $ORACLE_HOME/bin/dbstart into the /etc/rc.d/rc.local boot script to automatically bring up the database at system boot time. To get $ORACLE_HOME/bin/dbstart and $ORACLE_HOME/bin/dbshut working, you need to change the third field for your Oracle SID in /etc/oratab from "N" to "Y". 

For example, for the Oracle SID "test" I changed the line in /etc/oratab from: 

 test:/opt/oracle/product/9.2.0:N 
to read:  
 test:/opt/oracle/product/9.2.0:Y 

In some cases for 9.2.0 I also had to copy the init file for my SID "test" from /opt/oracle/admin/test/pfile to $ORACLE_HOME/dbs to get dbstart and dbshut working:  
cp /opt/oracle/admin/test/pfile/inittest.ora.642002224936 $ORACLE_HOME/dbs/inittest.ora 
But first make sure if your init file already exists in $ORACLE_HOME/dbs! 


Oracle Installation Problems, Tips and Hints 

Some of these problems apply only to 9.0.1!  
Do not cd to /mnt/cdrom to run ./runInstaller! 
If you do so, the installation will fail because you won't be able to change the CDs. 


If you forgot to set the DISPLAY environment variable (e.g. export DISPLAY=oracleserver:0.0), or if you forgot to give the remote console - your Oracle Server - authority to display X information on your desktop PC (e.g. xhost +oracleserver), then you will get the following error:  
Xlib: connection to ":0.0" refused by server 
Xlib: Client is not authorized to connect to Server 
In this case, I always had to kill runInstaller in Oracle9iR1 (9.0.1) which was still running in the background. If I didn't do this in 9.0.1, runInstaller didn't completely come up any more without displaying any error messages. You might also want to clean up /tmp/OraInstall.  

When runInstaller starts to configure the tools ("Configuration Tools"), the "Oracle Net Configuration Assistant" will sometimes hang. Simply stop the Assistant and restart it, or continue the installation. When the rest of the installation is finished, do a "Retry" for "Oracle Net Configuration Assistant". This always worked for me.  
When the system stops responding during the Oracle installation in particular during the database creation, then that's probably because you don't have enough RAM or enough swap space. I saw the whole system not responding or to "hang" for several minutes when I did not have enough swap space. If this happens, simply wait until the system starts to respond again.  
The Oracle installation also runs make etc. In a production environment you might not have compilers and other development packages installed. Therefore make sure you have temporarily the following packages installed: gcc, cpp, glibc-devel, compat-libstdc++, kernel-headers (for RH 7.1, 7.2, 2.1AS), glibc-kernheaders (for RH 7.3, 8.0, 9.0), binutils. See also Development Packages for more information.  

If for any reason the Oracle9i installation didn't finish successfully, you might want to clean up the following files and directories before you start over again: /etc/oraInst.loc /etc/oratab /tmp/<OtherOracleOwnedFiles>; $ORACLE_BASE/*  
Other Problems:  
You might want to check out the Oracle on Linux Discussion Forum.  


Oracle Installation Errors 

Here is a list of Oracle 9i (9.0.1 & 9.2.0) installation problems and issues. Some issues, errors, problems, and solutions apply only to 9.0.1 and some only to 9.2.0. Since I did not experience all of the problems here, I am not able to verify the correctness of all the solutions. However, I experienced almost all of the problems listed here. If you have other problems and you were able to resolve them, then please drop me an email at webmaster_at_puschitz.com so that I can add it to the list here.  

Here is a list of issues issues, errors, problems and solutions:  
Log Files  
First check always the error logs for 9.2.0 in /tmp/OraInstall (e.g /tmp/OraInstall2002-07-04_09-50-19PM), and for 9.0.1 in /tmp/OraInstall. When you get make problems, check also the file $ORACLE_HOME/install/make.log. 


"Various make Problems"  
Make sure that gcc is installed on your system:  
$ which gcc 
/usr/bin/gcc 

Here is the command to find the RPM package name for /usr/bin/gcc:  
$ rpm -qf /usr/bin/gcc 
gcc-2.96-98 

Check also the other error messages below. See also Development Packages for more information.  


"Error in invoking target install of makefile /opt/oracle/product/9.2.0/ctx/lib/ins_ctx.mk"  
I saw this error only when I installed Oracle9iR2 (9.2.0). This was also the only problem I experienced with Oracle 9i R2 on Red Hat 8.0. However, this does not necessarily mean that you won't experience other problems described here.  

When I had this problem, the following errors showed up in $ORACLE_HOME/install/make.log:  
  /lib/libdl.so.2: undefined reference to `_dl_addr@GLIBC_PRIVATE' 
  /lib/libdl.so.2: undefined reference to `_dl_open@GLIBC_PRIVATE' 
  /lib/libdl.so.2: undefined reference to `_dl_close@GLIBC_PRIVATE' 
  /lib/libdl.so.2: undefined reference to `_dl_sym@GLIBC_PRIVATE' 
  /lib/libdl.so.2: undefined reference to `_dl_vsym@GLIBC_PRIVATE' 

This error comes up when the following step is executed:  
  /usr/bin/make -f ins_ctx.mk install ORACLE_HOME=/opt/oracle/product/9.2.0 

Edit the file $ORACLE_HOME/ctx/lib/env_ctx.mk, go to "INSO_LINK =", and add a "$(LDLIBFLAG)dl" to the line and save it.  

Here is the full line with the added "$(LDLIBFLAG)dl" flag:  

INSO_LINK = -L$(CTXLIB) $(LDLIBFLAG)m $(LDLIBFLAG)dl $(LDLIBFLAG)sc_ca $(LDLIBFLAG)sc_fa $(LDLIBFLAG)sc_ex $(LDLIBFLAG)sc_da $(LDLIBFLAG)sc_ut $(LDLIBFLAG)sc_ch $(LDLIBFLAG)sc_fi $(LLIBCTXHX) $(LDLIBFLAG)c -Wl,-rpath,$(CTXHOME)lib $(CORELIBS) $(COMPEOBJS)  

After that hit retry in the error popup.  


If this didn't work, then try the following: 

Edit the file $ORACLE_HOME/ctx/lib/env_ctx.mk again, go to "INSO_LINK =", remove the above entry you made and add a "`cat $(LIBHOME)/sysliblist`" to the line and save it.  

Here is the full line with the added "`cat $(LIBHOME)/sysliblist`" string:  

INSO_LINK = -L$(CTXLIB) $(LDLIBFLAG)m `cat $(LIBHOME)/sysliblist` $(LDLIBFLAG)sc_ca $(LDLIBFLAG)sc_fa $(LDLIBFLAG)sc_ex $(LDLIBFLAG)sc_da $(LDLIBFLAG)sc_ut $(LDLIBFLAG)sc_ch $(LDLIBFLAG)sc_fi $(LLIBCTXHX) $(LDLIBFLAG)c -Wl,-rpath,$(CTXHOME)lib $(CORELIBS) $(COMPEOBJS)  

After that hit retry in the error popup.  


ORA-27123: unable to attach to shared memory segment. 

I saw this error only when I installed Oracle 9i R2 (9.2.0).  

This error message came up when the Oracle Database Configuration Assistant was running. I executed the following command to temporarily increase the maximum shared memory size:  
su - root 
# cat /proc/sys/kernel/shmmax 
33554432 
# echo `expr 1024 \* 1024 \* 1024` >; /proc/sys/kernel/shmmax 
# cat /proc/sys/kernel/shmmax 
1073741824 
# 
Then click "Retry" for the Oracle Database Configuration Assistant. 

It is recommended to increase the shmmax setting permanently for Oracle9i. So if you want to increase the maximum shared memory size permanently, add the following line to the /etc/sysctl.conf file: 

kernel.shmmax=1073741824 
For more information on setting shared memory parameters for Oracle, see Setting Shared Memory.  


ORA-03113: end-of-file on communication channel  
I saw this error when I've run the "Database Configuration Assistant" and "sqlplus". When the "Database Configuration Assistant" gave me this error during Oracle9iR2 (9.2.0) installation on Red Hat 2.1 AS, I simply removed the shared memory segments owned by the Oracle user and I restarted the "Database Configuration Assistant". I'm not sure if this is the right way but it always worked for me. Here is what I did to get the "Database Configuration Assistant" running again: 

Database Configuration Assistant: 

I executed the ipcs command to get the address of the shared memory segments that have been allocated by Oracle:  
$ su - root 
# ipcs 

------ Shared Memory Segments -------- 
key        shmid      owner      perms      bytes      nattch     status 
0x00000000 0          root      600        196608     2 
0x00000001 32769      root      600        655360     2 
0x00000000 458755     oracle    660        4194304    0 
0x00000000 491524     oracle    660        33554432   0 
0x00000000 524293     oracle    660        33554432   0 
0x00000000 557062     oracle    660        33554432   0 
0x00000000 589831     oracle    660        33554432   0 
0x00000000 622600     oracle    660        33554432   0 
0x00000000 655369     oracle    660        33554432   0 
0x00000000 688138     oracle    660        33554432   0 
0x3ecee0b0 720907     oracle    660        4194304    0 

------ Semaphore Arrays -------- 
key        semid      owner      perms      nsems      status 

------ Message Queues -------- 
key        msqid      owner      perms      used-bytes   messages 

# 
Then I removed all shared memory segments that were owned by the Oracle user during the installation with the following command:  
# ipcrm shm 458755 491524 524293 557062 589831 622600 655369 688138 720907 
After that I restarted the "Database Configuration Assistant". Once the installation was done I immediately restarted the DB as well. 
Caveat: I'm not sure if this procedure can cause any further problems if this is done during the installation. But so far I haven't seen any issues with this approach. 

sqlplus: 

If you get this problem in connection with sqlplus, then simply make sure that the database is down and exit sqlplus. After that, follow the procedure above by removing all shared memory segments that belong to the Oracle user. To my knowledge, this should not cause any problems.  

For more information on shared memory segments, see Determining Which Semaphore Sets and Shared Memory Segments Belong to Each Oracle Database or Instance.  

NOTE: 
To solve this problem permanently, increase the kernel shmmax size. For more information, see Setting Shared Memory and Setting Shared Memory.  


"Error invoking target install of makefile /opt/oracle/product/9.0.1/plsql/lib/ins_plsql.mk" 
"Error invoking target install of makefile /opt/oracle/product/9.0.1/precomp/lib/ins-precomp.mk" 
"Error invoking target install of makefile /opt/oracle/product/9.0.1/precomp/lib/ins-net-client" 

I saw this error only when I installed Oracle 9i (9.0.1). People have sent me emails pointing out that the following solution also works for Mandrake 8.1, Mandrake 8.2, and for SuSE 8.0.  

Edit the file $ORACLE_HOME/bin/genclntsh and change the following line:  
  LD_SELF_CONTAINED="-z defs" 
to read:  
  LD_SELF_CONTAINED="" 
After that run the script $ORACLE_HOME/bin/genclntsh as the user "oracle" and not as the user "root". Also make sure you have all the Oracle environments set correctly!  
$ su - oracle 
$ $ORACLE_HOME/bin/genclntsh 
Created /opt/oracle/product/9.0.1/lib/libclntst9.a 
$ 
After that hit Retry in the error dialog window. This always worked for me.  

Here is Oracle's official solution for Oracle 9iR1 and 9iR1 iAS on RedHat 2.1 Advanced Server:  
http://otn.oracle.com/software/products/oracle9i/files/binutils_readme.html  


"Error in invoking target install of make file /opt/oracle/product/9.2.0/network/lib/ins_oemagent.mk" 

I saw this error only on Red Hat 9. The ORACLE_HOME/install/make.log file contains the following error messages:  
  ... 
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcln.o)(.text+0x159d): In function `Nls_ScanCmd': 
  : undefined reference to `__ctype_b' 
  /opt/oracle/product/9.2.0/network/lib/libnmi.a(snmitcln.o)(.text+0x1603): more undefined references to `__ctype_b' follow 


The issue here is that __ctype_b() is actually gone for __ctype_b_loc() because Red Hat uses a new locale model. However, in libc.so, __ctype_b is still exported as compatibility symbol; at least that's the case with RH 9 glibc-2.3.2-5. And here is the reason why some people have this problem with Red Hat 9 and why some don't: 

When you bought the Red Hat 9 CDs in a store, then you will probably find glibc-2.3.2-5.i686.rpm on the first CD. This glibc version exports __ctype_b():  
$ rpm -ql glibc-2.3.2-5 | grep libc.so 
/lib/i686/libc.so.6 
/lib/libc.so.6 
/lib/tls/libc.so.6 
$ nm -a /lib/i686/libc.so.6 | grep __ctype_b 
001315f8 D __ctype_b 
00022340 T __ctype_b_loc 
$ nm -a /lib/libc.so.6 | grep __ctype_b 
00133c58 D __ctype_b 
000223a0 T __ctype_b_loc 
$ 
But when you downloaded Red Hat 9 from redhat.com or from one of the mirror sites, then you will find glibc-2.3.2-11.9.i686.rpm on the image. This glibc version does not export __ctype_b(). This is also the case with glibc-devel-2.3.2-27.9.i386.rpm.  
$ rpm -ql glibc-2.3.2-11.9 | grep libc.so 
/lib/i686/libc.so.6 
/lib/libc.so.6 
/lib/tls/libc.so.6 
$ nm -a /lib/i686/libc.so.6 | grep __ctype_b 
00131718 D __ctype_b@GLIBC_2.0 
000223a0 T __ctype_b_loc 
$ nm -a /lib/libc.so.6 | grep __ctype_b 
00133d58 D __ctype_b@GLIBC_2.0 
000223f0 T __ctype_b_loc 
$ 

Check the glibc version on your system:  

First check if the glibc packages on your RH 9 system work with the Oracle installer:  
$ rpm -q glibc-2.3.2-5 glibc-common-2.3.2-5 glibc-devel-2.3.2-5 

If you got the following error mesages:  
 package glibc-2.3.2-5 is not installed 
 package glibc-common-2.3.2-5 is not installed 
 package glibc-devel-2.3.2-5 is not installed 

then you have glibc packages on your system that don't work with the Oracle installer and you need to follow the "Work Around" procedure here.  
But if your system has the 2.3.2-5 glibc versions installed, then you are fine and you don't need to follow the described "Work Around" procedure!  


Work Around Procedure:  

Since I was not able to find the glibc-2.3.2-5 RPMs available for download, I'm making the RPMs available on my website. These RPMs are copies of the glibc RPMs that came with the RH 9 CDs I bought in the store. I do not recommend to use any of the "compat" RPMs from older Red Hat distributions since RH 9 contains major changes.  

Here is the procedure for installing glibc-2.3.2-5 temporarely on your RH 9 server:  

Download the 2.3.2-5 glibc RPMs from here on my web site.  

Make sure to check all the digests and signatures contained in the downloaded RPMs since you never know if someone made changes to these RPMs or if someone replaced them. To ensure the integrity and origin of the RPMs, run the following commands:  
 $ su - root 
 # rpm --import /usr/share/rhn/RPM-GPG-KEY 
 # rpm --checksig glibc-2.3.2-5.i686.rpm glibc-common-2.3.2-5.i386.rpm glibc-devel-2.3.2-5.i386.rpm 
 glibc-2.3.2-5.i686.rpm: (sha1) dsa sha1 md5 gpg OK 
 glibc-common-2.3.2-5.i386.rpm: (sha1) dsa sha1 md5 gpg OK 
 glibc-devel-2.3.2-5.i386.rpm: (sha1) dsa sha1 md5 gpg OK 
 # 
Downgrade glibc, glibc-common, and glibc-devel:  
 # rpm -Uvh --oldpackage glibc-2.3.2-5.i686.rpm glibc-common-2.3.2-5.i386.rpm glibc-devel-2.3.2-5.i386.rpm 
If you get the following error:  
 error: Failed dependencies: 
         glibc = 2.3.2-11.9 is needed by (installed) glibc-debug-2.3.2-11.9 
         glibc = 2.3.2-11.9 is needed by (installed) glibc-utils-2.3.2-11.9 
         glibc-devel = 2.3.2-11.9 is needed by (installed) glibc-debug-2.3.2-11.9 
         glibc-devel = 2.3.2-11.9 is needed by (installed) nptl-devel-2.3.2-11.9 

then you can temporarily remove the RPMs from your system until you upgrade the glibc RPMs after your Oracle installation:  
 # rpm -e glibc-debug glibc-utils nptl-devel 

Now try to run runInstaller again. 

After Oracle has been installed, you can upgrade glibc, glibc-common, and glibc-devel again. For example:  
 # rpm -Uvh glibc-2.3.2-11.9.i686.rpm glibc-common-2.3.2-11.9.i386.rpm glibc-devel-2.3.2-11.9.i386.rpm 

According to Red Hat, binary compatibility in Red Hat Linux is always guaranteed for binaries and shared libraries accross releases, but not for .o files nor .a files. However, compatibility is guaranteed for .o files and .a files. _within_ a realease. Since glibc-2.3.2-5 and glibc-2.3.2-11.9 are from the same release, compatibility should be guaranteed for .o files (Oracle's .o files which have been created during the Oracle installation) and .a files.  
This means that Oracle should be fine when you upgrade glibc after the Oracle installation.  

If you have any problems or issues with this solution, or if you have any comments, please let me know. You can find my email address at the bottom of this web site.  


$ dbca 
SIGSEGV   11*  segmentation violation 
        stackbase=0x453da000, stackpointer=0x453d9d5c 
Full thread dump: 
    "AWT-EventQueue-0" (TID:0x411d1e20, sys_thread_t:0x453d9e0c, 
state:R) prio=5 *current thread* 
        java.lang.Object.wait(Object.java) 
        java.awt.EventQueue.getNextEvent(EventQueue.java:126) 
... 
I got reports about dbca crashing on Red Hat 8.0 and on Red Hat 9. If this happens, try the following suggestion: 

$ su - root 
touch /etc/rac_on 
Now try to restart dbca. 

Another option is to edit $ORACLE_HOME/bin/dbca and to put the following lines under comment except the line marked in blue:  
 # if [ -f /etc/rac_on ]; then 
 # Run DBCA 
 $JRE_DIR/bin/jre -native -DORACLE_HOME=$OH ... 
 # else 
 # Run DBCA 
 # $JRE_DIR/bin/jre -DORACLE_HOME=$OH ... 
 # fi 

Now try to restart dbca.  


./runInstaller: line 58: ./runInstaller: cannot execute binary file.  
You are probably trying to run a 64-bit Oracle version on a 32-bit Linux system. Make sure you downloaded the right Oracle version for your Linux system.  

To check if runInstaller is a 32-bit binary or a 64-bit binary, run the following command:  
$ cd /mnt/cdrom 
$ file install/linux/runInstaller 
install/linux/runInstaller: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), for GNU/Linux 2.0.0, dynamically linked (uses shared libs), not stripped 

To check if your Linux system is 32-bit system or a 64-bit system, run e.g. the following command:  
$ file /sbin/init 
/sbin/init: ELF 32-bit LSB executable, Intel 80386, version 1 (SYSV), for GNU/Linux 2.2.5, dynamically linked (uses shared libs), not stripped 



The Oracle installer runInstaller hangs at:   Installing Java Runtime Environment... Link pending... Copying README...  
This problems comes up only on RH 9. You probably forgot to set the environment variable LD_ASSUME_KERNEL to 2.4.1.  

To rectify this problem, run the following command and restart runInstaller:  
oracle$ export LD_ASSUME_KERNEL=2.4.1 
For more information on this issue, see Red Hat 9.  


Can't find init file for Database "SID".  
I saw this error only with Oracle 9i R2 (9.2.0) when It tried to start the database with dbstart. 

I copied the init file for my SID "test" from /opt/oracle/admin/test/pfile to $ORACLE_HOME/dbs to get dbstart and dbshut working:  
cp /opt/oracle/admin/test/pfile/inittest.ora.642002224936 $ORACLE_HOME/dbs/inittest.ora 


"Error in setting permissions of file/directory /opt/oracle/jre/1.1.8/bin/i686/native_threads/.extract_args"  
This happens if you didn't burn your CD correctly. 
Either you burn your CD again to include dot files or you copy the .extract_args file from your downloaded image to where runInstaller complains it is missing.  


"jre was not found in /tmp/OraInstall/jre/bin/i586/green_threads/jre"  
You are probably running runInstaller on a 586 machine, or your AMD CPU gets recognized as 586 (e.g. AMD K6-III-400). You can check your machine (hardware) type by executing "uname -m". If you are not running on a 586 or on a AMD machine, try to link jre to java and see if this solves your problem.  

To rectify the problem with the 586 machine or with the AMD CPU, create a link for lib and bin from i586 to i686 and make the i686 directories read only. For example: 

ln -s /tmp/OraInstall/jre/bin/i686 /tmp/OraInstall/jre/bin/i586 
ln -s /tmp/OraInstall/jre/lib/i686 /tmp/OraInstall/jre/lib/i586 
chmod u-w /tmp/OraInstall/jre/bin/i686/tmp/OraInstall/jre/lib/i686 
Now restart runInstaller.  


../jre/bin/i386/native_threads/java: error while loading shared libraries: libstdc++-libc6.1-1.so.2: cannot open shared object file: No such file or directory  
You probably forgot to install the compat-libstdc++ RPM which is a package for "Standard C++ libraries for Red Hat Linux 6.2 backwards compatibility". To rectify this problem, install the compat-libstdc++ RPM. For example on Red Hat 9:  
rpm -ivh compat-libstdc++-7.3-2.96.118.i386.rpm 
See also Development Packages for more information.  


/opt/oracle/jre/1.1.8/bin/../lib/i686/green_threads/libzip.so: symbol errno, version GLIBC_2.0 not defined in file libc.so.6 with link time reference (libzip.so)  
Unable to initialize threads: cannot find class java/lang/Thread  
Could not create Java VM  
I experienced this problem when I was running the Database Configuration Assistant dbca on Red Hat 9 without setting the LD_ASSUME_KERNEL environment variable.  

To rectify this problem, run the following command on Red Hat 9 and restart dbca:  
oracle$ export LD_ASSUME_KERNEL=2.4.1 
For more information on this issue, see Red Hat 9.  


Other Errors  
You might want to check out the Oracle on Linux Discussion Forum.  





The information provided in this article shows how I installed Oracle on my server(s) and is distributed AS IS. Every effort has been made to provide the information as accurate as possible, but no warranty or fitness is implied. The use of this information described herein is your responsibility, and to use it in your own environments do so at your own risk.  



Comments?  webmaster_at_puschitz.com

 
 

