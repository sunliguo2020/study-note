#include<gtk/gtk.h>
	
/*����ص�����hello�������ťʱ��ϵͳ�Զ�����*/
void hello(GtkWidget *widget,gpointer *data)
{
	g_print("button clicked and data = %s\n",(char *)data);
}
	
/*����ص�����destroy���رմ���ʱ��ϵͳ�Զ�����*/
void destroy(GtkWidget *widget,gpointer *data) 
{
	gtk_main_quit();
}
	
int main(int argc,char **argv)
{
	/*����ָ��ؼ���ָ��*/
	GtkWidget *window;
	GtkWidget *button;
	
	/*��ʼ��ͼ����ʾ����*/
	gtk_init(&argc,&argv);
	
	/*�������ڣ������õ��رմ���ʱ��Ҫִ�еĻص�����*/
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
			g_signal_connect(GTK_OBJECT(window),"destroy",
	GTK_SIGNAL_FUNC(destroy),NULL);
       	/*���ô��ڵ�����*/
	gtk_container_border_width(GTK_CONTAINER(window),20);
		
	/*������ť�������õ������ťʱ��Ҫִ�еĻص�����*/
	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(GTK_OBJECT(button),"clicked",
	GTK_SIGNAL_FUNC(hello),"I am from button");
	
	/*����ť���뵽������*/
	gtk_container_add(GTK_CONTAINER(window),button);
	/*��ʾ��ť�ʹ���*/
	gtk_widget_show(button);
	gtk_widget_show(window);
		
	/*������Ϣ����ѭ��*/
	gtk_main();
		
	return 0;
}
