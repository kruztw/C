#include <gtk/gtk.h>


static void print_output(GtkWidget *self, gpointer entry)
{
    const gchar *buf = gtk_entry_get_text(GTK_ENTRY(entry));
    g_print("You enter: %s\n", buf);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *nameEntry;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkEntry");

    nameEntry = gtk_entry_new();
    button = gtk_button_new_with_label("Send");
    g_signal_connect(button, "clicked", G_CALLBACK(print_output), nameEntry);

    grid = gtk_grid_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Name"), 0, 1, 1, 1);   
    gtk_grid_attach(GTK_GRID(grid), nameEntry, 1, 1, 2, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);

    gtk_container_add(GTK_CONTAINER(window), grid);


    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
