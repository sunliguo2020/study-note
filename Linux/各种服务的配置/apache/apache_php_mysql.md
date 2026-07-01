Step 1:
  Get the sourceballs:
    Apache URL: http://httpd.apache.org
    MySQL  URL: http://www.mysql.com
    PHP    URL: http://www.php.net
Setp 2:
    Installation:
      a)
        To extract the sourceballs 
           tar zxvf *.tar.gz
      b)Compiling Apache 
         #./configure --prefix=/usr/local/apache2 
         #make &&make install
         #/usr/local/apache2/bin/apachectl start
         #cp /usr/local/apache2/bin/apachectl /etc/init.d/httpd
      c)Compiling MySQL
          #./configure --prefix=/usr/local/mysql --localstatedir=/usr/local/mysql/data --with-charset=utf8 --with-mysqld-user=mysql --enable-large-files --without-debug
          #make &&make install
          Add a login user and group for 'mysqld' to run as:
              #groupadd mysql
              #useradd -g mysql -d /usr/local/mysql/data mysql
          #cp support-files/my-medium.cnf /etc/my.cnf
           Create the MySQL grant tables:安装mysql基数据库
              #cd /usr/local/mysql
              #./bin/mysql_install_db --user=mysql 
          
          #chown -R root .
          #chown -R mysql data 
          #chgrp -R mysql .
         
               #./bin/mysqladmin -u root password [newpassword]
            #cp support-files/mysql.server /etc/init.d/mysql
            #chkconfig --add mysqld
            #chkconfig --level 35 mysqld on
        d)Compiling PHP
           #./configure --with-apxs2=/usr/local/apache2/bin/apxs --with-mysl=/usr/localmysql --prefix=/usr/local/php
           #make&&make install
           #cp php.ini-dist /usr/local/lib/php.ini
  Step 4: Test
          #cd /usr/local/apache2/htdocs
          #echo "<?php phpinfo();?>">test.php
  
