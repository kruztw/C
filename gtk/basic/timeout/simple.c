#include <gtk/gtk.h>

gboolean timeout_callback()
{
   g_print("timeout\n"); 
}

int main(int argc, char *argv[]) {
    GtkWidget *window;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "哈囉！GTK+！");
    g_timeout_add(1000, timeout_callback, NULL);
    gtk_widget_show(window);
    gtk_main();

    return 0;
}
