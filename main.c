#include <gtk/gtk.h>

static void print(GtkWidget *widget, gpointer data) {
  g_print("%s\n", (char *) data); //data is a (void *)
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkWidget *window, *box, *button;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "Window"); //GTK_WINDOW acts like a cast to GtkWindow, with some checks
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);

  box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
  gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

  gtk_window_set_child(GTK_WINDOW(window), box);

  button = gtk_button_new_with_label("Hello World");
  g_signal_connect(button, "clicked", G_CALLBACK(print), "Hello World From App");

  gtk_box_append(GTK_BOX(box), button);

  gtk_widget_show(window);
}

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  //the application id "my.app" should respect this format, with '.' to separate
  app = gtk_application_new("my.app", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK (activate), NULL); //when receive a signal the app will run activate function
  status = g_application_run(G_APPLICATION (app), argc, argv); //send a signal to app
  g_object_unref (app); //free application

  return status;
}