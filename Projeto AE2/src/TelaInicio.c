//
// Created by USER on 28/11/2025.
//
#include "TelaInicio.h"

GtkWidget *inicioBox;
GtkWidget *fotoTitulo;
GtkWidget *label1Titulo;
GtkWidget *label2Titulo;
GtkWidget *tituloBox;
GtkWidget *buttonBox;
GtkWidget *startButton;
GtkWidget *tutorialButton;
GtkWidget *recordeLabel;
GtkWidget *startLabel;
GtkWidget *tutorialLabel;
FILE *arq;
int v;

GtkWidget *getTelaInicio() {
    inicioBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    v = 0;

    if ((arq = fopen("data\\vitorias.bin", "rb")) == NULL) {
        printf("Não há arquivo de vitorias\n");
        arq = fopen("data\\vitorias.bin", "wb");
        if (fwrite(&v, sizeof(int), 1, arq) == 0) {
            printf("Erro ao escrever no arquivo\n");
        }
        fclose(arq);
    }else {
        fread(&v, sizeof(int), 1, arq);
        fclose(arq);
    }

    tituloBox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);

    //Picture ilustração do início
    fotoTitulo = gtk_picture_new_for_filename("imgs\\campoMinadoIcone.png");
    gtk_widget_set_valign(fotoTitulo, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(fotoTitulo, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(inicioBox), fotoTitulo);

    //Label primeira linha do titulo
    label1Titulo = gtk_label_new (NULL);
    gtk_label_set_markup(GTK_LABEL(label1Titulo), "<b><span size='40000'>Campo</span></b>");
    gtk_box_append (GTK_BOX (tituloBox), label1Titulo);

    //Label segunda linha do titulo
    label2Titulo = gtk_label_new (NULL);
    gtk_label_set_markup(GTK_LABEL(label2Titulo), "<b><span size='40000'>Minado</span></b>");
    gtk_box_append (GTK_BOX (tituloBox), label2Titulo);

    //Box Botões
    buttonBox = gtk_flow_box_new();
    gtk_widget_set_size_request(buttonBox, 200, 250);
    gtk_flow_box_set_row_spacing(GTK_FLOW_BOX(buttonBox), 50);
    gtk_widget_set_valign(buttonBox, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(buttonBox, GTK_ALIGN_CENTER);
    gtk_widget_set_hexpand(buttonBox, FALSE);
    gtk_widget_set_vexpand(buttonBox, FALSE);

    //Botão Jogar
    startButton = gtk_button_new();
    gtk_widget_set_size_request(startButton, 130, 50);
    startLabel = gtk_label_new ("<b><span size='18000'>Jogar</span></b>");
    gtk_label_set_use_markup(GTK_LABEL(startLabel), TRUE);
    gtk_button_set_child(GTK_BUTTON(startButton), startLabel);
    gtk_flow_box_append(GTK_FLOW_BOX(buttonBox), startButton);
    g_signal_connect(startButton, "clicked", G_CALLBACK(startGame), NULL);

    //Botão Tutorial
    tutorialButton = gtk_button_new();
    gtk_widget_set_size_request(tutorialButton, 130, 50);
    tutorialLabel = gtk_label_new ("<b><span size='18000'>Tutorial</span></b>");
    gtk_label_set_use_markup(GTK_LABEL(tutorialLabel), TRUE);
    gtk_button_set_child(GTK_BUTTON(tutorialButton), tutorialLabel);
    gtk_flow_box_append(GTK_FLOW_BOX(buttonBox), tutorialButton);
    g_signal_connect(tutorialButton, "clicked", G_CALLBACK(showTutorial), NULL);

    //Label Recorde
    recordeLabel = gtk_label_new (NULL);
    char *tempString = (char*)malloc(50*sizeof(char));
    sprintf(tempString, "<span size='20000'>Vitórias Seguidas: %d</span>", v);
    gtk_label_set_markup(GTK_LABEL(recordeLabel), tempString);
    free(tempString);
    gtk_widget_set_size_request(recordeLabel, 400, 100);

    //Add componentes ao inicioBox
    gtk_box_append(GTK_BOX(inicioBox), tituloBox);
    gtk_box_append(GTK_BOX(inicioBox), buttonBox);
    gtk_box_append(GTK_BOX(inicioBox), recordeLabel);

    return inicioBox;
}

void startGame() {
    alterarTela(getTelaGame());
}

void showTutorial() {
    mostrarJanelaTutorial();
}