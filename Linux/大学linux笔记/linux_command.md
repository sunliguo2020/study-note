last
lastb &#21015;&#20986;&#19981;&#25104;&#21151;&#30331;&#24405;&#30340;&#35760;&#24405;
ac                   (1)  - print statistics about users' connect time
users                (1)  - print the user names of users currently logged in to the current host
lastlog              (8)  - reports the most recent login of all users or of a given user
lastcomm             (1)  - print out information about previously executed commands
xwd                  (1x)  - dump an image of an X window
xwdtopnm             (1)  - convert an X11 or X10 window dump file to a PNM image
convert              (1)  - convert between image formats as well as resize an image, blur, crop, despeckle, dither, draw on, flip, join, re-sample, and much more
xmessage             (1x)  - display a message or query in a window (X-based /bin/echo)
#at 16:05
at&gt;xmessage -display :0.0 &quot;Message&quot;
at&gt;&lt;EOT&gt;
xsetroot             (1x)  - root window parameter setting utility for X
atrm [at]            (1)  - queue, examine or delete jobs for later execution
atq [at]             (1)  - queue, examine or delete jobs for later execution
arch                 (1)  - print machine architecture
indent               (1)  - changes the appearance of a C program by inserting or deleting whitespace
indent              (rpm) - A GNU program for formatting C code.
hdparm               (8)  - get/set hard disk parameters
hdparm              (rpm) - A utility for displaying and/or setting hard disk parameters.
uptime               (1)  - Tell how long the system has been running
type                 (1p)  - write a description of command type
type [builtins]      (1)  - bash built-in commands, see bash(1)
xmessage             (1x)  - display a message or query in a window (X-based /bin/echo)
xsetroot             (1x)  - root window parameter setting utility for X
symlinks             (8)  - symbolic link maintenance utility
symlinks            (rpm) - A utility which maintains a system's symbolic links.
xargs                (1)  - build and execute command lines from standard input
xargs                (1p)  - construct argument lists and invoke utility
ulimit               (1p)  - set or report file size limit
ulimit               (3)  - get and set user limits
ulimit               (3p)  - get and set process limits
ulimit [builtins]    (1)  - bash built-in commands, see bash(1)
ulimit.h [ulimit]    (0p)  - ulimit commands
ulimit [unimplemented] (2)  - unimplemented system calls
vmstat               (8)  - Report virtual memory statistics
logrotate            (8)  - rotates, compresses, and mails system logs
logrotate           (rpm) - Rotates, compresses, removes and mails system log files.
stat                 (1)  - display file or file system status
stat                 (2)  - get file status
stat                 (3p)  - get file status
&#35760;&#24405;&#20250;&#35805;&#21629;&#20196;  script               (1)  - make typescript of terminal session
&#32456;&#31471;&#35774;&#32622;&#21629;&#20196; stty
stty -a 
display              (1)  - displays an image or image sequence on any X server
import               (1)  - saves any visible window on an X server and outputs it as an image file. You can capture a single window, the entire screen, or any rectangular portion of the screen
tune2fs              (8)  - adjust tunable filesystem parameters on ext2/ext3 filesystems
losetup              (8)  - set up and control loop devices
 dircolors - color setup for ls
apropos word    &#26174;&#31034;&#21644;word&#30456;&#20851;&#30340;&#21629;&#20196;
time command     &#35745;&#31639;&#21629;&#20196;&#36816;&#34892;&#30340;&#26102;&#38388;
nice info &#36816;&#34892;&#19968;&#20010;&#20302;&#20248;&#20808;&#32423;&#30340;&#21629;&#20196;
alias hd='od -Ax -tx1z -v'
alias realpath='readlink -f'
&#30446;&#24405;&#25805;&#20316;
cd - &#22238;&#21040;&#21069;&#19968;&#20010;&#30446;&#24405;
cd  &#22238;&#21040;&#29992;&#25143;&#30446;&#24405;
(cd dir &amp;&amp;command) &#36827;&#20837;&#30446;&#24405;dir&#65292;&#25191;&#34892;&#21629;&#20196;command&#28982;&#21518;&#22238;&#21040;&#24403;&#21069;&#30446;&#24405;
pushd .   &#23558;&#24403;&#21069;&#30446;&#24405;&#21387;&#20837;&#26632;&#65292;&#20197;&#21518;&#21487;&#20197;&#20351;&#29992;popd&#22238;&#21040;&#27492;&#30446;&#24405;

&#24402;&#26723;
 tar c dir/ |bzip 2 &gt;dir.tar.gz   &#23558;&#30446;&#24405;dir/&#21387;&#32553;&#25171;&#21253;
 bzip2 -dc dir.tar.bz2|tar x
 tar c dir/|gzip |gpg -c|ssh user@remote 'dd of=dir.tar.gz.dgp'
 &#23558;&#30446;&#24405;&#21387;&#32553;&#25171;&#21253;&#25918;&#22312;&#36828;&#31243;&#26426;&#22120;&#19978;

recode
  recode -l  &#26174;&#31034;&#25152;&#26377;&#26377;&#25928;&#30340;&#23383;&#31526;&#38598;&#21450;&#21035;&#21517;
  recode ..HTML -&lt;file.txt&gt; file.html


pstree
