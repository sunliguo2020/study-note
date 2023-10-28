#include<gtk/gtk.h>

/*函数声明*/
GtkWidget* makeTable();
GtkWidget* makeTextEntry();
GtkWidget* makecheckButtons();
GtkWidget* makeButtonBox();

/*点击check按钮的回调函数*/
void click_button(GtkWidget *widget,gpointer *data)
{
	g_print("click %s ",(char *)data);

	if(GTK_TOGGLE_BUTTON(widget)->active)
		g_print("and state is active\n");
	else
		g_print("and state is not active\n");
}

void destroy(GtkWidget *widget,gpointer *data) 
{
	gtk_main_quit();
}

int main(int argc,char **argv)
{
	GtkWidget *window;
	GtkWidget *table;

	gtk_init(&argc,&argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	g_signal_connect(GTK_OBJECT(window),"destroy",
				GTK_SIGNAL_FUNC(destroy),NULL);
	gtk_container_border_width(GTK_CONTAINER(window),30);


	table = makeTable();
	gtk_container_add(GTK_CONTAINER(window),table);

	gtk_widget_show(window);
	
	gtk_main();
	
	return 0;
}

GtkWidget* makeTable()
{
	GtkWidget *table;
	GtkWidget *checkButtons;
	GtkWidget *textEntry;
	GtkWidget *buttonBox;

	/*创建table控件*/
	table = gtk_table_new(2,2,FALSE);
	gtk_widget_show(table);

	/*创建标签和编辑框*/
	textEntry = makeTextEntry();
	gtk_table_attach(GTK_TABLE(table),textEntry,
		         0,1,0,1,
                  	 GTK_FILL|GTK_EXPAND|GTK_SHRINK,0,
			 0,0);
	gtk_widget_show(textEntry);

	/*创建四个check按钮*/
	checkButtons = makecheckButtons();
	gtk_table_attach(GTK_TABLE(table),checkButtons,
		         1,2,0,1,
			 GTK_FILL | GTK_EXPAND,
			 GTK_FILL | GTK_EXPAND,
			 10,0);
	gtk_widget_show(checkButtons);

	/*创建两个按钮*/
	buttonBox = makeButtonBox();
	gtk_table_attach(GTK_TABLE(table),buttonBox,
	       	      	 0,2,1,2,
         	      	 GTK_EXPAND|GTK_FILL|GTK_SHRINK,0,
		         5,10);
	gtk_widget_show(buttonBox);

	return table;
}

GtkWidget* makeTextEntry()
{
	GtkWidget *vbox;
	GtkWidget *label;
	GtkWidget *text;

	vbox = gtk_vbox_new(FALSE,5);

	/*生成标签控件*/
	label = gtk_label_new("please enter your name:");
	gtk_box_pack_start(GTK_BOX(vbox),label,FALSE,FALSE,0);
	gtk_widget_show(label);

	/*生成编辑框*/
	text = gtk_entry_new_with_max_length(15);
	gtk_box_pack_start(GTK_BOX(vbox),text,FALSE,FALSE,0);
	gtk_widget_show(text);

	return vbox;
}

GtkWidget* makecheckButtons()
{
	GtkWidget *vbox;
	GtkWidget *check;	

	vbox = gtk_vbox_new(FALSE,0);

	check = gtk_check_button_new_with_label("apple");
	g_signal_connect(GTK_OBJECT(check),"clicked",
				GTK_SIGNAL_FUNC(click_button),"apple");
	gtk_box_pack_start(GTK_BOX(vbox),check,FALSE,FALSE,0);
	gtk_widget_show(check);

	check = gtk_check_button_new_with_label("banana");
    	g_signal_connect(GTK_OBJECT(check),"clicked",
				GTK_SIGNAL_FUNC(click_button),"banana");
	gtk_box_pack_start(GTK_BOX(vbox),check,FALSE,FALSE,0);
	gtk_widget_show(check);

	check = gtk_check_button_new_with_label("orange");
    	g_signal_connect(GTK_OBJECT(check),"clicked",
				GTK_SIGNAL_FUNC(click_button),"orange");
	gtk_box_pack_start(GTK_BOX(vbox),check,FALSE,FALSE,0);
	gtk_widget_show(check);

	check = gtk_check_button_new_with_label("pear");
    	g_signal_connect(GTK_OBJECT(check),"clicked",
				GTK_SIGNAL_FUNC(click_button),"pear");
	gtk_box_pack_start(GTK_BOX(vbox),check,FALSE,FALSE,0);
	gtk_widget_show(check);

	return vbox;
}

GtkWidget* makeButtonBox()
{
	GtkWidget *hbox;
	GtkWidget *button;

	hbox = gtk_hbox_new(FALSE,0);

	button = gtk_button_new_with_label("yes");
	gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,20);
	gtk_widget_show(button);

	button = gtk_button_new_with_label("no");
	gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,60);
	gtk_widget_show(button);

	return hbox;
}
