#include <gtk/gtk.h>

static void print_hello (GtkWidget *widget, gpointer   data)
{
  g_print ("print on terminal\n");
}

static void my_start_app (GtkApplication *app, gpointer user_data)
{
  GtkWidget *window;
  GtkWidget *button;
  GtkWidget *button_box;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

  button_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
  gtk_container_add (GTK_CONTAINER (window), button_box);


  // 為 button 設置兩個 "clicked" event (依序執行)
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_widget_destroy), window);
  gtk_container_add (GTK_CONTAINER (button_box), button);


  gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("kruztw.tw", G_APPLICATION_FLAGS_NONE);

  // 為 app 設置 "activate" event (啟動時會執行 my_start_app) 
  g_signal_connect (app, "activate", G_CALLBACK (my_start_app), NULL);

  // 運行 app
  status = g_application_run (G_APPLICATION (app), argc, argv);

  g_object_unref (app);

  return status;
}
