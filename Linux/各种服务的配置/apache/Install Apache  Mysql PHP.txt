
Installing Apache, MySQL, and PHP on Linux
Apache | Linux | MySQL | PHP | Programming

This tutorial is designed to guide you through the initial steps of setting up Apache, MySQL, and PHP on Linux. The Linux distribution being utilized for this tutorial is Fedora Core 1, however the steps should be very similar across most distributions. This tutorial makes the assumption that you have the required development tools loaded for compiling programs from source, these tools are beyond the scope of this document and will not be covered here. Also, it assumes you can use the vi text editor for basic editing tasks.



Apache, MySQL, and PHP have become one of the most utilized combinations for developing content driven websites. They are robust, flexible, provide a decent level of security, and they are available for many different platforms. That being said, lets get to building a web server.


Get the sourceballs -


The first thing you need to do is obtain the sourceballs for each package, we will be compiling each package from scratch here, and, while there are also binary packages available for some distributions, I find your end results are usually better when building each package for your machine. Make sure you get the source files.


Here are the links and the package versions available at the time this tutorial was written


Apache
URL : http://httpd.apache.org/download.cgi
Current Version - 2.0.48


MySQL
URL : http://www.mysql.com/downloads/mysql-4.0.html
Current Version - 4.0.16


PHP
URL : http://www.php.net/downloads.php
Current Version - 4.3.4


Ok, so you've got the files now what ?, well now the fun begins..


Installation -


The first thing we need to do is extract the sourceballs so we can work with the files included in them. Beginning now we will be working as root, so open a terminal window, change to the directory in which you saved your downloaded files and become root by issuing the su command, enter the root password and you should be good to go.


To extract the sourceballs type the following commands;


#tar -zxf httpd-2.0.48.tar.gz (enter)


#tar -zxf mysql-4.0.16.tar.gz (enter)


#tar -zxf php-4.3.4.tar.gz (enter)


The commands above will extract the sourceballs into their own separate directories. Now lets move on to compiling the source into usable programs. We'll start with Apache.


Compiling Apache -


Change into the directory created when you untarred the sourceball as follows;


#cd httpd-2.0.48 (enter)


Follow this command by typing;


#./configure --prefix=/usr/local/apache2 --enable-mods-shared=most (enter)


This tells Apache to install in the /usr/local/apache2 directory, and to build most of the available loadable modules. There are a ton of options with Apache, but these should work for the most part. Once the configure is done and the system returns the prompt to you, issue the following command;


#make


This will take a few minutes, once the prompt comes back again issue the following command;


#make install


Wait for a few minutes and viola !, Apache is installed with the exception of a few minor changes we still need to make. They are as follows..


Issue the following command;


#vi /usr/local/apache2/conf/httpd.conf


Check to make sure the following line is present in the file at the bottom of the LoadModule list, if it is not there add it;


LoadModule php4_module modules/libphp4.so


Find the DirectoryIndex line and edit it so it looks like the following;


DirectoryIndex index.html index.html.var index.php


Find the AddType application section and add the following line;


AddType application/x-httpd-php .php


Thats it, save the file and we are done with Apache. Now, on to MySQL !


Compiling MySQL -


Change into the MySQL source directory as follows;


#cd mysql-4.0.16 (enter)


Follow this command by typing;


#./configure --prefix=/usr/local/mysql --localstatedir=/usr/local/mysql/data --disable-maintainer-mode --with-mysqld-user=mysql --enable-large-files-without-debug (enter)


Sit back and wait for a while while configure does its thing, once the system returns the prompt to you issue the following command;


#make (enter)


Unless you have a very fast machine this will take some time, so spend time with your family, grab a beer, go for a walk, or whatever you're into. When you get back, assuming the system has returned the prompt to you issue the following command;


#make install (enter)


Cool !, MySQL is installed, there are only a couple things left to do to get it working, first we need to create a group for MySQL as follows;


#/usr/sbin/groupadd mysql (enter)


Then we create a user called mysql which belongs to the mysql group;


#/usr/sbin/useradd -g mysql mysql (enter)


Now we install the database files as follows;


#./scripts/mysql_install_db (enter)


Then we make a couple minor ownership changes;


# chown -R root:mysql /usr/local/mysql (enter)


# chown -R mysql:mysql /usr/local/mysql/data (enter)


Last but not least, we use vi to add a line the ld.so.conf file as follows;


#vi /etc/ld.so.conf


And we add the following line;


/usr/local/mysql/lib/mysql


Thats it, MySQL is installed, you can run it by issuing the following command;


#/usr/local/mysql/bin/mysqld_safe --user=mysql &


And as long as we're here we might as well set a root password for MySQL as follows;


#/usr/local/mysql/bin/mysqladmin -u root password new_password


Where new_password is the password you want to use.


Ok, so far so good, on to PHP !


Compiling PHP -


Change into the PHP source directory as follows;


#cd php-4.3.4 (enter)


Follow this command by typing;


#./configure --prefix=/usr/local/php --with-apxs2=/usr/local/apache2/bin/apxs --with-mysql=/usr/local/mysql (enter)


Once the prompt comes back to you issue the following command;


#make (enter)


Hang out for awhile, and then yep, you guessed it, once you have the prompt back;


#make install (enter)


Once the install finishes and you have the prompt back issue the following command;


#cp php.ini-recommended /usr/local/php/lib/php.ini (enter)


Then edit that file;


#vi /usr/local/php/lib/php.ini (enter)


And change the following;


Find the doc_root section and enter the correct path for the directory which serves your web content, such as;


doc_root= "/usr/local/apache2/htdocs/"


(this is default for apache2)


Then find the file_uploads section and change it to reflect the following;


file_uploads=Off


(for security reasons)


Thats if for PHP, now lets see if it all works..


Testing -


Assuming your MySQL process is still running from earlier, lets start Apache by issuing the following command;


#/usr/local/apache2/bin/apachectl start (enter)


This starts the Apache web server, now change into the following directory;


#cd /usr/local/apache2/htdocs (enter)


And using vi create a file called test.php;


#vi test.php


Add the following line to the file;


<?php phpinfo(); ?>


Save the file, then fire up your browser and point it to localhost/test.php. You should see a listing of all kinds of cool info about Apache, PHP, etc. If you do then your set !, if you don't, then take a look at your logs for Apache and MySql, and remember Google is your friend. But hopefully you do, and now you have a fully functioning setup.


Ok, one last step and we'll be done, you have everything running now, but you had to start Apache and MySql manually, that's something you don't want to have to remember to do everytime you reboot your machine, so lets fix it.


Starting Apache and MySQL Automatically -


Lets start with MySQL, as root make your working directory that of the MySQL source directory you worked with earlier, something similar to;


#cd /home/xxxx/mysql-4.0.16 <enter>


Then, copy the file mysql.server to your /etc/init.d directory as follows;


#cp support-files/mysql.server /etc/init.d/mysql


Ok, lets create some links in the startup folders for run levels 3 and 5.


#cd /etc/rc3.d <enter>


#ln -s ../init.d/mysql S85mysql <enter>


#ln -s ../init.d/mysql K85mysql <enter>


#cd /etc/rc5.d <enter>


#ln -s ../init.d/mysql S85mysql <enter>


#ln -s ../init.d/mysql K85mysql <enter>


#cd ../init.d <enter>

#chmod 755 mysql <enter>


Thats it for MySQL, it should start automatically now when you reboot your machine. Now lets do the same for Apache, still as root make your working directory that of the Apache binaries as follows;


#cd /usr/local/apache2/bin <enter>


Then, copy the file called apachectl as follows;


#cp apachectl /etc/init.d/httpd <enter>


Now, for some more links;


#cd /etc/rc3.d <enter>


#ln -s ../init.d/httpd S85httpd <enter>


#ln -s ../init.d/httpd K85httpd <enter>


#cd /etc/rc5.d <enter>


#ln -s ../init.d/httpd S85httpd <enter>


#ln -s ../init.d/httpd K85httpd <enter>


And thats it for Apache !, it should start automatically along with MySQL the next time you boot your machine.


That brings us to the end of this tutorial, hopefully you found it helpful, and Good Luck !

--http://www.hostlibrary.com/installing_apache_mysql_php_on_linux
