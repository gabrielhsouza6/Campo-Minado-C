//
// Created by USER on 10/12/2025.
//

#ifndef PROJETO_AE2_TELAGAME_H
#define PROJETO_AE2_TELAGAME_H

    #include <gtk/gtk.h>
    #include <stdlib.h>
    #include <time.h>
    #include <string.h>

    typedef struct {
        int tipo;           // Vazio = 0 , Bomba = 1
        int bombasPerto;    // Quantidade de bombas ao redor
        int status;          // Escondido = 0 , Revelado = 1, Flag = 2
        int x;               // Linha
        int y;               // Coluna
    }Celula;

    void alterarTela(GtkWidget *novaTela);
    GtkWidget *getTelaGame();
    GtkWidget *getTelaInicio();
    void gerarTabela();
    int verificarBombas(int x, int y);
    void deletarTabela();
    void flagCelula(GtkGestureClick* gesture_click, gint n, gdouble x, gdouble y, gpointer data);
    void clickCelula(GtkButton* gtk_button, gpointer data);
    GtkWidget *getBotaoTabela(Celula* celula);
    void atualizarBandLabel();
    void endDialog(char* result);
    void clickLabel(GtkGestureClick* gesture_click, gint n, gdouble x, gdouble y, gpointer data);
    void atualizarVitorias(int v); // zerar (v = 0) , adicionar (v = 1)
    void printTabela();

#endif //PROJETO_AE2_TELAGAME_H