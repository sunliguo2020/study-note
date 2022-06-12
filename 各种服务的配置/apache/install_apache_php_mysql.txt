Installing Apache, MySQL, and PHP on Linux


Installation -


#cd httpd-2.0.48 (enter)
Follow this command by typing;
#./configure --prefix=/usr/local/apache2 --enable-mods-shared=most (enter)

This tells Apache to install in the /usr/local/apache2 directory, and to build most of the available loadable modules. There are a ton of options with Apache, but these should work for the most part. Once the configure is done and the system returns the prompt to you, issue the following command;
#make
#make install

#vi /usr/local/apache2/conf/httpd.conf

Check to make sure the following line is present in the file at the bottom of the LoadModule list, if it is not there add it;

LoadModule php4_module modules/libphp4.so

Find the DirectoryIndex line and edit it so it looks like the following;

DirectoryIndex index.html index.html.var index.php

Find the AddType application section and add the following line;

AddType application/x-httpd-php .php

Compiling MySQL -

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
 ./configure --prefix=/usr/local/php --with-apxs2=/usr/local/apache2/bin/apxs
 --with-mysql=/usr/local/mysql --with-gd=/usr --enable-gd-native-ttf
 --with-jpeg-dir=/usr/lib --with-zlib-dir=/lib --with-ttf=/usr
 --with-png-dir=/usr/lib --with-freetype-dir=/usr/include/freetype2

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
