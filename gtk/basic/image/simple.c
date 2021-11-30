#include <gtk/gtk.h>

static void print_hello (GtkWidget *widget, gpointer   data)
{
    g_print ("Hello World\n");
}

static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button;
    GtkWidget *image;
    
    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_container_set_border_width (GTK_CONTAINER (window), 10);
    
    grid = gtk_grid_new ();
    gtk_container_add(GTK_CONTAINER (window), grid);

    image = gtk_image_new_from_file("a.jpg");
    gtk_grid_attach(GTK_GRID(grid), image, 0, 1, 2, 2);

    button = gtk_button_new_with_label("Quit");

    // horizental expand gtk_widget_set_expand(widget, bool) , 放大就會看到效果
    gtk_widget_set_hexpand(button, 1);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 3, 2, 1);

    gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
