判断文件类型
 优先采用magic方式，其次采用文件扩展名方式
2：文件类型的表示
   MIME ：层次型的方式
      JPEG：image/jpeg
      文本文件：text/plain
      XML文件：text/xml
3：文件类型的数据信息
   /usr/share/mime /usr/local/share/mime $HOME
   aliase: 文件类型的别名。例如：application/pdf application/x-pdf
   mgic:各种文件的内部标示，用于从文件内容来判断文件类型。如：BMP图片文件以BM开头。
  globs:扩展名与文件类型的对应关系。如.cpp 文件是text/x-c++src类型的
  packages目录：用于安装新文件类型用。
  其他子目录及其下的文件：更详细的描述各种文件类型。
4:图标文件与数据文件的关联
   /usr/share/icons/主题/大小/mimetypes目录下。
5:应用程序和数据文件的关联
  通过.desktop文件来实现的。
     /usr/share/applications下.
   例：
   [Desktop Entry]
   Name=Web Browser
   Comment=Browse the web
   Exec=htmlview %u
   Icon=redhat-web-browser.png
   Terminal=0
   Type=Application
   NoDisplay=true
   Encoding=UTF-8
   Categories=Application;Network;X-Red-Hat-Base;X-Red-Hat-Base-Only;
