#include "/usr/include/gtk-1.2/gtk/gtk.h"
//#/usr/include/gtk-2.0/gtk/gtk.h/usr/include/pygtk-2.0/pygtk/pygtk.h
/* 一般可以在 /usr/include/gtk-2.0 下找到上边的头文件
* 上边的头文件的作用是包含进行GTK编程所有可能用到的头
* 文件，包括glib.h等
*/
int   main(int argc, char *argv[])
   {
         GtkWidget *window;
         // GtkWidget 是绝大部分可视组件的的基类
         gtk_init(&argc, &argv);
          //对程序传入的命令行参数进行标准化处理
        window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
           //创建窗口(200x200大小)
       gtk_window_set_title(GTK_WINDOW(window), "Hello,Dubuntu!");
           //设置窗口标题
          gtk_widget_show(window);
									           //显示窗口
           gtk_main();
          //Gtk程序主循环
									           return 0;
 } 
