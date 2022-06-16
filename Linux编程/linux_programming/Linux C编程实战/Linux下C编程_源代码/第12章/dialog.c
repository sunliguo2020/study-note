#include<gtk/gtk.h>

void make_dialog()
{
	GtkWidget *dialog;
	GtkWidget *label;
	GtkWidget *button;
	GtkWidget *vbox;
	GtkWidget *hbox;
	
	dialog = gtk_dialog_new();
	
	/*向对话框中加入一个文本标签*/
	vbox = GTK_DIALOG(dialog)->vbox;
	label = gtk_label_new("This is a dialog");
	gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,TRUE,30);
	
	/*向对话框中加入两个按钮*/
	hbox = GTK_DIALOG(dialog)->action_area;
	button = gtk_button_new_with_label("yes");
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,0);
	button = gtk_button_new_with_label("no");
	gtk_box_pack_start(GTK_BOX(hbox),button,FALSE,FALSE,0);
	
	gtk_widget_show_all(dialog);
}

void hello(GtkWidget *widget,gpointer *data)
{
        make_dialog();
}

int main(int argc,char **argv)
{
	GtkWidget *window;
	GtkWidget *button;
	
	gtk_init(&argc,&argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window),"destroy",
				GTK_SIGNAL_FUNC(gtk_main_quit),NULL);
	gtk_container_border_width(GTK_CONTAINER(window),20);
	
	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(GTK_OBJECT(button),"clicked",
				GTK_SIGNAL_FUNC(hello),"I am from button");
	
	gtk_container_add(GTK_CONTAINER(window),button);
	gtk_widget_show(button);
	gtk_widget_show(window);
	
	gtk_main();
	
	return 0;
}
