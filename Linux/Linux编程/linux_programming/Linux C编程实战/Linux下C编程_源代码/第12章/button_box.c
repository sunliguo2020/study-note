#include<gtk/gtk.h>

/*按下某个按钮后，在命令行上打印出按钮名和新的状态*/
void click_button(GtkWidget *widget,gpointer *data)
{
	g_print("%s ",(char *)data);

	if(GTK_TOGGLE_BUTTON(widget)->active)
		g_print("state is active\n");
	else
		g_print("state is not active\n");
}

void destroy(GtkWidget *widget,gpointer *data) 
{
	gtk_main_quit();
}

int main(int argc,char **argv)
{
	GtkWidget 	*window;
	GtkWidget 	*box;
	GSList    	*group;
    	GtkWidget 	*check,*radio;
	
	gtk_init(&argc,&argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window),"destroy",
				GTK_SIGNAL_FUNC(destroy),NULL);
	gtk_container_border_width(GTK_CONTAINER(window),50);

	/*生成一个垂直box容器，并将该容器加入到主窗口中*/
	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	
	/*以下生成两个check按钮，将它们加入到box容器中，并显示出来*/
	check = gtk_check_button_new_with_label("coffee");
	g_signal_connect(GTK_OBJECT(check),"clicked",
				GTK_SIGNAL_FUNC(click_button),"check button1");
	gtk_box_pack_start(GTK_BOX(box),check,TRUE,TRUE,0);
    	gtk_widget_show(check);
	
	check = gtk_check_button_new_with_label("tea");
    	g_signal_connect(GTK_OBJECT(check),"clicked",
				GTK_SIGNAL_FUNC(click_button),"check button2");
    	gtk_box_pack_start(GTK_BOX(box),check,TRUE,TRUE,0);
    	gtk_widget_show(check);
	
	/*以下生成三个radio按钮，将它们加入到box容器中，并显示出来*/
	/* 
	  注意：生成第一个radio按钮时group参数为NULL，而后每次在该
	  组中创建一个radio按钮都要使用gtk_radio_button_group 函数获取
	  新的group值
	*/
	radio = gtk_radio_button_new_with_label(NULL,"Apple");
	g_signal_connect(GTK_OBJECT(radio),"clicked",
	GTK_SIGNAL_FUNC(click_button),"Apple");
    	gtk_box_pack_start(GTK_BOX(box),radio,TRUE,TRUE,0);
	gtk_widget_show(radio);
	
	group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
    	radio = gtk_radio_button_new_with_label(group,"Banana");
   	g_signal_connect(GTK_OBJECT(radio),"clicked",
	GTK_SIGNAL_FUNC(click_button),"Banana");
    	gtk_box_pack_start(GTK_BOX(box),radio,TRUE,TRUE,0);
	gtk_widget_show(radio);
	
	group = gtk_radio_button_group(GTK_RADIO_BUTTON(radio));
    	radio = gtk_radio_button_new_with_label(group,"Orange");
   	g_signal_connect(GTK_OBJECT(radio),"clicked",
	GTK_SIGNAL_FUNC(click_button),"Orange");
	/*将第三个radio按钮设置为选中状态*/
   	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio),TRUE);
    	gtk_box_pack_start(GTK_BOX(box),radio,TRUE,TRUE,0);
	gtk_widget_show(radio);
	
	gtk_widget_show(box);
	gtk_widget_show(window);
	
	gtk_main();
	return 0;
}
