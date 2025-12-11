#include "main.h"

GtkWidget *mainBox;
GtkWidget *mainWindow;

void alterarTela(GtkWidget *novaTela) {
    gtk_window_set_child(GTK_WINDOW(mainWindow), novaTela);
}

static void activate (GtkApplication *app, gpointer user_data) {

    mainWindow = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (mainWindow), "Campo Minado");
    gtk_window_set_default_size (GTK_WINDOW (mainWindow), 550, 600);

    alterarTela(getTelaInicio());
    gtk_window_present (GTK_WINDOW (mainWindow));
}

int main (int argc, char **argv){
    GtkApplication *app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    int status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}