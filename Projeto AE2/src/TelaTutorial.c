//
// Created by USER on 05/12/2025.
//
#include "TelaTutorial.h"

GtkWidget *tutorialBox;
GtkWidget *label1_1;
GtkWidget *label1_2;
GtkWidget *inst1;
GtkWidget *ilust1;
GtkWidget *label2_1;
GtkWidget *label2_2;
GtkWidget *inst2;
GtkWidget *ilust2;
GtkWidget *label3_1;
GtkWidget *label3_2;
GtkWidget *inst3;
GtkWidget *ilust3;
GtkWidget *label4_1;
GtkWidget *label4_2;
GtkWidget *inst4;
GtkWidget *ilust4;
GtkWidget *tutorialWindow;

GtkWidget *getTelaTutorial() {
    tutorialBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    label1_1 = gtk_label_new(NULL);
    label1_2 = gtk_label_new(NULL);
    inst1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ilust1 = gtk_flow_box_new();
    label2_1 = gtk_label_new(NULL);
    label2_2 = gtk_label_new(NULL);
    inst2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ilust2 = gtk_flow_box_new();
    label3_1 = gtk_label_new(NULL);
    label3_2 = gtk_label_new(NULL);
    inst3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ilust3 = gtk_flow_box_new();
    label4_1 = gtk_label_new(NULL);
    label4_2 = gtk_label_new(NULL);
    inst4 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    ilust4 = gtk_flow_box_new();

    gtk_label_set_markup(GTK_LABEL(label1_1), "<b><span size='15000'>Clique com o botão esquerdo do mouse</span></b>");
    gtk_label_set_markup(GTK_LABEL(label1_2), "<b><span size='15000'>para revelar o quadrado.</span></b>");
    gtk_label_set_markup(GTK_LABEL(label2_1), "<b><span size='15000'>Clique com o botão direito do mouse</span></b>");
    gtk_label_set_markup(GTK_LABEL(label2_2), "<b><span size='15000'>para colocar uma bandeira no quadrado.</span></b>");
    gtk_label_set_markup(GTK_LABEL(label3_1), "<b><span size='15000'>Sempre haverá um quadrado com um 'S' no começo do jogo</span></b>");
    gtk_label_set_markup(GTK_LABEL(label3_2), "<b><span size='15000'>para simbolizar um ponto seguro para começar.</span></b>");
    gtk_label_set_markup(GTK_LABEL(label4_1), "<b><span size='15000'>Clique no contador de bandeiras</span></b>");
    gtk_label_set_markup(GTK_LABEL(label4_2), "<b><span size='15000'>para voltar a tela de início a qualquer momento.</span></b>");

    gtk_flow_box_append(GTK_FLOW_BOX(ilust1), gtk_picture_new_for_filename("imgs\\quadradoVazio.png"));
    gtk_flow_box_append(GTK_FLOW_BOX(ilust1), gtk_picture_new_for_filename("imgs\\quadradoNum.png"));
    gtk_flow_box_append(GTK_FLOW_BOX(ilust1), gtk_picture_new_for_filename("imgs\\quadradoBomba.png"));
    gtk_flow_box_append(GTK_FLOW_BOX(ilust2), gtk_picture_new_for_filename("imgs\\quadradoBandeira.png"));
    gtk_flow_box_append(GTK_FLOW_BOX(ilust3), gtk_picture_new_for_filename("imgs\\quadradoS.png"));
    gtk_flow_box_append(GTK_FLOW_BOX(ilust4), gtk_picture_new_for_filename("imgs\\labelBandeira.png"));

    gtk_widget_set_halign(label1_1, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(label1_2, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(label2_1, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(label2_2, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(label3_1, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(label3_2, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(label4_1, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(label4_2, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(ilust1, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(ilust2, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(ilust3, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(ilust4, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX(inst1), label1_1);
    gtk_box_append(GTK_BOX(inst1), label1_2);
    gtk_box_append(GTK_BOX(inst2), label2_1);
    gtk_box_append(GTK_BOX(inst2), label2_2);
    gtk_box_append(GTK_BOX(inst3), label3_1);
    gtk_box_append(GTK_BOX(inst3), label3_2);
    gtk_box_append(GTK_BOX(inst4), label4_1);
    gtk_box_append(GTK_BOX(inst4), label4_2);

    gtk_widget_set_size_request(inst1, 500, 65);
    gtk_widget_set_size_request(inst2, 500, 65);
    gtk_widget_set_size_request(inst3, 500, 65);
    gtk_widget_set_size_request(inst4, 500, 65);
    gtk_widget_set_size_request(ilust1, 500, 65);
    gtk_widget_set_size_request(ilust2, 500, 65);
    gtk_widget_set_size_request(ilust3, 500, 65);
    gtk_widget_set_size_request(ilust4, 500, 65);

    gtk_box_append(GTK_BOX(tutorialBox), inst1);
    gtk_box_append(GTK_BOX(tutorialBox), ilust1);
    gtk_box_append(GTK_BOX(tutorialBox), inst2);
    gtk_box_append(GTK_BOX(tutorialBox), ilust2);
    gtk_box_append(GTK_BOX(tutorialBox), inst3);
    gtk_box_append(GTK_BOX(tutorialBox), ilust3);
    gtk_box_append(GTK_BOX(tutorialBox), inst4);
    gtk_box_append(GTK_BOX(tutorialBox), ilust4);

    return tutorialBox;
}

void mostrarJanelaTutorial() {
    tutorialWindow = gtk_window_new();
    gtk_window_set_title (GTK_WINDOW (tutorialWindow), "Tutorial");
    gtk_window_set_default_size (GTK_WINDOW (tutorialWindow), 550, 600);
    gtk_window_set_child(GTK_WINDOW(tutorialWindow), getTelaTutorial());
    gtk_window_present (GTK_WINDOW (tutorialWindow));
}