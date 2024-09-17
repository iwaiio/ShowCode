#include <gtk/gtk.h>

#include "head.h"
#include "version.h"

static void on_activate(GtkApplication *app, gpointer user_data) {
    // Создаём новое окно
    GtkWidget *window = gtk_application_window_new(app);
    
    // Устанавливаем заголовок окна
    gtk_window_set_title(GTK_WINDOW(window), "TEST WINDOW");
    
    // Задаём размеры окна
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    
    // Показываем окно
    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    printf("Version: %s\n", PROJECT_VERSION);

    // Создаём новое GTK-приложение
    GtkApplication *app = gtk_application_new("com.example.GtkApp", G_APPLICATION_FLAGS_NONE);
    
    // Подключаем сигнал активации к функции on_activate
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    
    // Запускаем приложение
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    
    // Удаляем приложение после завершения
    g_object_unref(app);
    
    return status;
}