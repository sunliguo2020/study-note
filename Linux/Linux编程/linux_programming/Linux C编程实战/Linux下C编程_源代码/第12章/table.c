#include<gtk/gtk.h>

int main(int argc,char **argv)
{
	GtkWidget *window;
	GtkWidget *clist;
	
	gtk_init(&argc,&argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window),"destroy",
				GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
	gtk_container_border_width(GTK_CONTAINER(window),20);
	
	char *titles[] = {
		"name","age","major"
	};
	
	char *rows1[] = {
		"John","20","computer"
	};
	
	char *rows2[] = {
		"Bill","24","maths"
	};
	
	char *rows3[] = {
		"Martin","22","English"
	};
	
	clist = gtk_clist_new_with_titles(3,titles);
    	gtk_clist_set_column_width(GTK_CLIST(clist),0,50);
    	gtk_clist_set_column_width(GTK_CLIST(clist),1,50);
    	gtk_clist_set_column_width(GTK_CLIST(clist),2,150);
	gtk_container_add(GTK_CONTAINER(window),clist);
	gtk_clist_append(GTK_CLIST(clist),rows1);
	gtk_clist_append(GTK_CLIST(clist),rows2);
	gtk_clist_append(GTK_CLIST(clist),rows3);
	
	/*获取表格中第0行第2列格子的数据，并在命令行上打印出来*/
	char *text = (char *)g_malloc(32);
	gtk_clist_get_text(GTK_CLIST(clist),0,2,&text);
	g_print("%s\n",text);
	
    	gtk_clist_sort(GTK_CLIST(clist));
	
	gtk_widget_show(clist);
	gtk_widget_show(window);
	
	gtk_main();
	
	return 0;
}
