#include<gtk/gtk.h>

int main(int argc,char **argv)
{
	GtkWidget *window;
	GtkWidget *menu;
	GtkWidget *menubar;
	GtkWidget *rootmenu;
	GtkWidget *menuitem;
	
	gtk_init(&argc,&argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Menu Demo");
	g_signal_connect(GTK_OBJECT(window),"destroy",
		             GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
	gtk_container_border_width(GTK_CONTAINER(window),20);
	
	/*����һ���²˵���Ȼ�󴴽�3���˵��������3���˵�����뵽�˵���*/
	menu = gtk_menu_new();
		
	menuitem = gtk_menu_item_new_with_label("New");
	gtk_menu_append(GTK_MENU(menu),menuitem);
	gtk_widget_show(menuitem);
	
	menuitem = gtk_menu_item_new_with_label("Open");
	gtk_menu_append(GTK_MENU(menu),menuitem);
	gtk_widget_show(menuitem);
	
	menuitem = gtk_menu_item_new_with_label("Close");
	gtk_menu_append(GTK_MENU(menu),menuitem);
	gtk_widget_show(menuitem);
	
	/*����һ�����˵�*/
	rootmenu = gtk_menu_item_new_with_label("File");
	gtk_widget_show(rootmenu);
	
	/*���˵����뵽���˵���*/
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu);
	/*�����˵���*/
	menubar = gtk_menu_bar_new();
	/*�����˵������뵽�˵�����*/
	gtk_menu_bar_append(GTK_MENU_BAR(menubar),rootmenu);
	
	/*ʹ��ͬ���ķ����������ڶ���˵�*/
	menu = gtk_menu_new();	
	menuitem = gtk_menu_item_new_with_label("Cut");
	gtk_menu_append(GTK_MENU(menu),menuitem);
	gtk_widget_show(menuitem);
	
	menuitem = gtk_menu_item_new_with_label("Paste");
	gtk_menu_append(GTK_MENU(menu),menuitem);
	gtk_widget_show(menuitem);
	
	rootmenu = gtk_menu_item_new_with_label("Edit");
	gtk_widget_show(rootmenu);
	
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(rootmenu),menu);
	gtk_menu_bar_append(GTK_MENU_BAR(menubar),rootmenu);
	
	/*���˵������뵽�����У�����ʾ�˵����ʹ���*/
	gtk_container_add(GTK_CONTAINER(window),menubar);
	gtk_widget_show(menubar);
	gtk_widget_show(window);
	
	gtk_main();
	
	return 0;
}
