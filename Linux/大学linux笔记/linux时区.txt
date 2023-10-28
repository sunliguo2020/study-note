

[root@localhost ~]# ls -l /etc/localtime 
lrwxrwxrwx. 1 root root 33 Dec  8 08:00 /etc/localtime -> /usr/share/zoneinfo/Asia/Shanghai

appliance@zabbix:~$ tzselect 
Please identify a location so that time zone rules can be set correctly.
Please select a continent, ocean, "coord", or "TZ".
 1) Africa
 2) Americas
 3) Antarctica
 4) Asia
 5) Atlantic Ocean
 6) Australia
 7) Europe
 8) Indian Ocean
 9) Pacific Ocean
10) coord - I want to use geographical coordinates.
11) TZ - I want to specify the time zone using the Posix TZ format.
#? 4
Please select a country whose clocks agree with yours.
 1) Afghanistan           18) Israel                35) Palestine
 2) Armenia               19) Japan                 36) Philippines
 3) Azerbaijan            20) Jordan                37) Qatar
 4) Bahrain               21) Kazakhstan            38) Russia
 5) Bangladesh            22) Korea (North)         39) Saudi Arabia
 6) Bhutan                23) Korea (South)         40) Singapore
 7) Brunei                24) Kuwait                41) Sri Lanka
 8) Cambodia              25) Kyrgyzstan            42) Syria
 9) China                 26) Laos                  43) Taiwan
10) Cyprus                27) Lebanon               44) Tajikistan
11) East Timor            28) Macau                 45) Thailand
12) Georgia               29) Malaysia              46) Turkmenistan
13) Hong Kong             30) Mongolia              47) United Arab Emirates
14) India                 31) Myanmar (Burma)       48) Uzbekistan
15) Indonesia             32) Nepal                 49) Vietnam
16) Iran                  33) Oman                  50) Yemen
17) Iraq                  34) Pakistan
#? 9
Please select one of the following time zone regions.
1) Beijing Time
2) Xinjiang Time
#? 1

The following information has been given:

        China
        Beijing Time

Therefore TZ='Asia/Shanghai' will be used.
Local time is now:      Thu Dec  7 08:52:38 CST 2017.
Universal Time is now:  Thu Dec  7 00:52:38 UTC 2017.
Is the above information OK?
1) Yes
2) No
#? 1

You can make this change permanent for yourself by appending the line
        TZ='Asia/Shanghai'; export TZ
to the file '.profile' in your home directory; then log out and log in again.

Here is that TZ value again, this time on standard output so that you
can use the /usr/bin/tzselect command in shell scripts:
Asia/Shanghai
appliance@zabbix:~$ TZ='Asia/Shanghai'; export TZ
appliance@zabbix:~$ date -R
Thu, 07 Dec 2017 08:48:44 +0800
appliance@zabbix:~$ echo $TZ
Asia/Shanghai
appliance@zabbix:~$ ls  -a
.  ..  .bash_logout  .bashrc  .profile  .sudo_as_admin_successful
appliance@zabbix:~$ vi .profile 
appliance@zabbix:~$ clear
appliance@zabbix:~$ ls
appliance@zabbix:~$ ls -l /etc/localtime 
lrwxrwxrwx 1 root root 27 Dec  6 15:07 /etc/localtime -> /usr/share/zoneinfo/Etc/UTC
appliance@zabbix:~$ sudo mv /etc/localtime /etc/localtime.bak 
appliance@zabbix:~$ sudo ln -s  /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
appliance@zabbix:~$ ls -l /etc/localtime
lrwxrwxrwx 1 root root 33 Dec  7 08:51 /etc/localtime -> /usr/share/zoneinfo/Asia/Shanghai
appliance@zabbix:~$ date
Thu Dec  7 08:51:22 CST 2017
appliance@zabbix:~$ 