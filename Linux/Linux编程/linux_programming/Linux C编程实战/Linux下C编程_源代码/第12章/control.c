#include<gtk/gtk.h>
	
int main(int argc,char **argv)
{
	GtkWidget *window;
	GtkWidget *vbox;
	GtkObject *adjustment;
	GtkWidget *bar;
	GtkWidget *spinbutton;
	GList	  *glist;
	GtkWidget *combo;
	
	gtk_init(&argc,&argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window),"destroy",
				GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
	gtk_container_border_width(GTK_CONTAINER(window),40);
	
	vbox = gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	
	/*创建进度条*/
	adjustment = gtk_adjustment_new(70.0,0.0,100.0,1.0,0.0,0.0);
	bar = gtk_progress_bar_new_with_adjustment(GTK_ADJUSTMENT(adjustment));
	gtk_progress_bar_set_bar_style(GTK_PROGRESS_BAR(bar),
						GTK_PROGRESS_CONTINUOUS);
	gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(bar),
						GTK_PROGRESS_LEFT_TO_RIGHT);
	gtk_box_pack_start(GTK_BOX(vbox),bar,TRUE,TRUE,15);
	gtk_widget_show(bar);
	
	/*微调按钮*/
    	adjustment = gtk_adjustment_new(80.0,0.0,100.0,1.0,0.0,0.0);
    	spinbutton = gtk_spin_button_new(GTK_ADJUSTMENT(adjustment),1.0,1);
   	gtk_box_pack_start(GTK_BOX(vbox),spinbutton,TRUE,TRUE,15);
   	gtk_widget_show(spinbutton);
	
	/*创建组合框*/
	glist = NULL;
	glist = g_list_append(glist,"apple");
	glist = g_list_append(glist,"banana");
	glist = g_list_append(glist,"orange");
	glist = g_list_append(glist,"pear");
	combo = gtk_combo_new();
	gtk_combo_set_popdown_strings(GTK_COMBO(combo),glist);
	gtk_box_pack_start(GTK_BOX(vbox),combo,TRUE,TRUE,15);
	gtk_widget_show(combo);
	
	gtk_widget_show(vbox);
	gtk_widget_show(window);
	
	gtk_main();
	
	return 0;
}
