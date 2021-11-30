#include <gtk/gtk.h>

void clicked_callback(GtkButton *button, GtkWindow *window) {
    GtkWidget *dialog = gtk_dialog_new_with_buttons("TITLE", window, GTK_DIALOG_DESTROY_WITH_PARENT, "BTN1", GTK_RESPONSE_OK, "BTN2", GTK_RESPONSE_REJECT, NULL);

    GtkWidget *label = gtk_label_new(NULL);

    gtk_label_set_markup(GTK_LABEL(label),  "<b>良葛格學習筆記</b>\nhttp://caterpillar.onlyfun.net");

    g_signal_connect(G_OBJECT(dialog), "response", G_CALLBACK(gtk_widget_destroy), NULL);
    gtk_widget_show_all(dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button;

    gtk_init(&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GtkDialog");

    button = gtk_button_new_with_label("LEVEL1");
    gtk_container_add(GTK_CONTAINER(window), button);
    g_signal_connect(GTK_WINDOW(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(GTK_BUTTON(button), "clicked", G_CALLBACK(clicked_callback), window);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
