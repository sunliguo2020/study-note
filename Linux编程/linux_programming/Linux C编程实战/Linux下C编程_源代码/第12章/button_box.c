#include<gtk/gtk.h>

/*����ĳ����ť�����������ϴ�ӡ����ť�����µ�״̬*/
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

	/*����һ����ֱbox�������������������뵽��������*/
	box = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	
	/*������������check��ť�������Ǽ��뵽box�����У�����ʾ����*/
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
	
	/*������������radio��ť�������Ǽ��뵽box�����У�����ʾ����*/
	/* 
	  ע�⣺���ɵ�һ��radio��ťʱgroup����ΪNULL������ÿ���ڸ�
	  ���д���һ��radio��ť��Ҫʹ��gtk_radio_button_group ������ȡ
	  �µ�groupֵ
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
	/*��������radio��ť����Ϊѡ��״̬*/
   	gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(radio),TRUE);
    	gtk_box_pack_start(GTK_BOX(box),radio,TRUE,TRUE,0);
	gtk_widget_show(radio);
	
	gtk_widget_show(box);
	gtk_widget_show(window);
	
	gtk_main();
	return 0;
}
