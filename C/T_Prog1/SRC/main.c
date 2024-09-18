#include <gtk/gtk.h>
#include <glib.h>
#include "head.h"
#include "version.h"

#define fName "ScoreLog"
#define AppName "MathApp"
#define AppID "com.iwai.MathApp"

uint16_t scr;
uint8_t num1;
uint8_t num2;
long answ;
uint8_t result;
char task[16];
char strScore[16];

uint8_t file_overwrite(char *fileName, char *fileText){
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        return 1;
    }else{
        fprintf(file, fileText);
    }
    fclose(file);
}

uint8_t file_read(char *fileName, char *buffer, uint16_t *score){
    FILE *file = fopen(fileName, "r");
    printf("1\n");
    if (file == NULL) {
        fclose(file);
        printf("2\n");
        file_overwrite(fileName, "Score: 0");
        printf("3\n");
        update_score_num_from_str("Score: 0", score);
        printf("4\n");
        update_score_str_from_num(buffer, score);
        printf("5\n");
        fclose(file);
        printf("6\n");

        return 1;
    }else{
        fgets(buffer, 100, file);
        printf("\ntext - %s\n", buffer);
        update_score_num_from_str(buffer, score);
        printf("\ntext - %s\n", buffer);
        printf("score - %u\n\n", scr);
        fclose(file);

        return 0;
    }
}

uint8_t generate_nums(uint8_t *number1, uint8_t *number2, long *answer, char *buffer){
    char buff[8];
    int nBuff;
    *number1 = rand() % 100;
    *number2 = rand() % 100;

    snprintf(buff, sizeof(buff), "%d", *number1);
    strncpy(buffer, buff, 8);

    nBuff = rand() % 4;
    switch (nBuff){
    case 0:
        *answer = *number1 + *number2;
        strncat(buffer, " + ", 4);
        break;
    case 1:
        *answer = *number1 - *number2;
        strncat(buffer, " - ", 4);
        break;
    case 2:
        *answer = *number1 * *number2;
        strncat(buffer, " * ", 4);
        break;
    case 3:
        if(*number2 == 0){
            *number2 = 1;
        }
        
        *answer = *number1 % *number2;
        strncat(buffer, " % ", 4);
        break;
    
    default:
        return 1;
    }

    snprintf(buff, sizeof(buff), "%d", *number2);
    strncat(buffer, buff, sizeof(buffer) - strlen(buffer) - 1);

    return 0;
}

uint8_t update_score_str_from_num(char *buffer, uint16_t *num){
    char buff[8];
    strcpy(buffer, "Score: ");
    snprintf(buff, sizeof(buff), "%d", *num);
    strcat(buffer, buff);
    printf("num:%u\n", *num);
    printf("buff:%s\n", buff);
    printf("преобразование из числа в строку: %s\n", buffer);

    return 0;
}

uint8_t update_score_num_from_str(char *buffer, uint16_t *num){
    long buff;
    buff = strtol(buffer, NULL, 10);
    *num = ((uint16_t)buff);
    printf("buffer:%s\n", buffer);
    printf("buff:%ld\n", buff);
    printf("преобразование из строки в число: %u\n", *num);

    return 0;
}

static void on_button_clicked_generate(GtkLabel *label){
    generate_nums(&num1, &num2, &answ, task);
    
    gtk_label_set_text(label, task);

    return;
}

static void on_button_clicked_update_gui(GtkWidget *widget, gpointer data){
    GtkWidget **fields = (GtkWidget **)data;

    update_score_str_from_num(strScore, &scr);
    file_overwrite(fName, strScore);

    gtk_label_set_text(GTK_LABEL(fields[0]), strScore);
    gtk_label_set_text(GTK_LABEL(fields[1]), task);
    gtk_editable_set_text(GTK_EDITABLE(fields[2]), "");

    return;
}

static void on_button_clicked_exit(GtkWidget *widget, gpointer data){
    g_print("bye\n");


    gtk_window_destroy(data);

    return;
}

static void on_button_clicked_answer(GtkWidget *widget, gpointer data){
    GtkWidget *entry = (GtkWidget *)data;
    const gchar *text = gtk_editable_get_text(GTK_EDITABLE(entry));

    if(answ == strtol(text, NULL, 10)){
        ++scr;
        result = 1;
        generate_nums(&num1, &num2, &answ, task);
        //j,yjdbnm bynthatqc
        g_print("true\n");
    }else{
        result = 0;
        g_print("false\n");
    }

    return;
}

static void on_activate(GtkApplication *app, gpointer user_data){
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *score;
    GtkWidget *text;
    GtkWidget *entry;
    GtkWidget *buttonOk;
    GtkWidget *buttonExit;
    GtkWidget *buttonGenerate;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), AppName);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);

    grid = gtk_grid_new();
    gtk_widget_set_halign (grid, GTK_ALIGN_CENTER);
    gtk_widget_set_valign (grid, GTK_ALIGN_CENTER);
    gtk_window_set_child(GTK_WINDOW (window), grid);

    score = gtk_label_new(strScore);
    text = gtk_label_new(task);
    entry = gtk_entry_new();

    GtkWidget *fields[3] = {score, text, entry};

    buttonOk = gtk_button_new_with_label("Ok");
    g_signal_connect(buttonOk, "clicked", G_CALLBACK(on_button_clicked_answer), entry);
    g_signal_connect_swapped(buttonOk, "clicked", G_CALLBACK(on_button_clicked_generate), text);
    g_signal_connect(buttonOk, "clicked", G_CALLBACK(on_button_clicked_update_gui), fields);
    
    buttonExit = gtk_button_new_with_label("Exit");
    g_signal_connect(buttonExit, "clicked", G_CALLBACK(on_button_clicked_exit), window);

    buttonGenerate = gtk_button_new_with_label("Generate!");
    g_signal_connect_swapped(buttonGenerate, "clicked", G_CALLBACK(on_button_clicked_generate), text);

    gtk_grid_attach (GTK_GRID (grid), score, 0, 0, 4, 2);
    gtk_grid_attach (GTK_GRID (grid), text, 0, 5, 4, 2);
    gtk_grid_attach (GTK_GRID (grid), entry, 0, 10, 4, 2);
    gtk_grid_attach (GTK_GRID (grid), buttonOk, 0, 15, 2, 1);
    gtk_grid_attach (GTK_GRID (grid), buttonExit, 2, 15, 2, 1);
    gtk_grid_attach (GTK_GRID (grid), buttonGenerate, 0, 18, 4, 1);
    
    gtk_window_present(GTK_WINDOW(window));

    return;
}

int main(int argc, char **argv){
    result = 2;

    srand(time(NULL));

    file_read(fName, strScore, &scr);
    generate_nums(&num1, &num2, &answ, task);

    GtkApplication *app;
    int status;

    app = gtk_application_new(AppID, G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    
    g_object_unref(app);
    
    return status;
}