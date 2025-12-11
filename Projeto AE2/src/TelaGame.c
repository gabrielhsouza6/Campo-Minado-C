//
// Created by USER on 28/11/2025.
//
#include "TelaGame.h"

GtkGesture *labelGesture;
GtkWidget *gameBox;
Celula **tabela;
GtkWidget *tabelaBox;
GtkWidget *bandeiraLabel;
int old_v;
int l;
int c;
GtkGesture ***gesture;
int bandeiras;
int bombas;
int gameStatus;   // em progresso = 0 , finalizado = 1
int q;

GtkWidget *getTelaGame() {
    gameBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    srand(time(0));

    l=0;
    c=0;
    bandeiras = 0;
    gameStatus = 0;
    q = 0;

    tabelaBox = gtk_grid_new();
    bandeiraLabel = gtk_label_new(NULL);
    gtk_label_set_markup(GTK_LABEL(bandeiraLabel), "<b><span size='30000'>Bandeiras: 0</span></b>");

    labelGesture = gtk_gesture_click_new();
    g_signal_connect(labelGesture, "pressed", G_CALLBACK(clickLabel), NULL);
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(labelGesture), 1);
    gtk_widget_add_controller(bandeiraLabel, GTK_EVENT_CONTROLLER(labelGesture));

    gerarTabela();

    printTabela();

    gesture = (GtkGesture***)malloc(15*sizeof(GtkGesture**));
    for (int i=0; i<15; i++) {
        gesture[i] = (GtkGesture**) malloc(15*sizeof(GtkGesture*));
    }

    for (int i=0; i<15; i++) {
        for (int j=0; j<15; j++) {
            gesture[i][j] = gtk_gesture_click_new();
        }
    }


    for (int i=0; i<15; i++){
        for (int j=0; j<15; j++){
            gtk_grid_attach(GTK_GRID(tabelaBox), getBotaoTabela(&tabela[i][j]), j, i, 1, 1);
        }
    }

    gtk_widget_set_halign(tabelaBox, GTK_ALIGN_CENTER);
    gtk_box_append(GTK_BOX(gameBox), tabelaBox);
    gtk_box_append(GTK_BOX(gameBox), bandeiraLabel);

    return gameBox;
}

void gerarTabela() {

    //Reservando Memória para a tabela
    tabela = (Celula**)malloc(15*sizeof(Celula*));
    for (int i = 0; i < 15; i++) {
        tabela[i] = (Celula*)malloc(15*sizeof(Celula));
    }

    //Setando espacos vazios e com bombas
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 15; j++) {
            int randNum = rand() % 10; // NOLINT(cert-msc30-c, cert-msc50-cpp)
            if (randNum > 6) {  // 30% de chance de ser bomba
                tabela[i][j].tipo = 1;
                bombas++;
            }else {
                tabela[i][j].tipo = 0;
            }
        }
    }

    //Setando numeros dos espacos vazios
    for (int i = 0; i<15; i++) {
        for (int j = 0; j < 15; j++) {
            tabela[i][j].bombasPerto = verificarBombas(i, j);
            tabela[i][j].status = 0;
            tabela[i][j].x = i;
            tabela[i][j].y = j;
        }
    }
}

int verificarBombas(int x, int y){
    int bombasProximas = 0;
    for (int i=x-1; i<=x+1; i++){
        for (int j=y-1; j<=y+1; j++){
            if (i<0 || i>14 || j<0 || j>14){
                continue;
            }
            if (tabela[i][j].tipo == 1){
                bombasProximas++;
            }
        }
    }
    return bombasProximas;
}

void deletarTabela() {
    free(tabela);
    free(gesture);
}

void flagCelula(GtkGestureClick* gesture_click, gint n, gdouble x, gdouble y, gpointer data){
    Celula *but_data = (Celula*)data;
    GtkButton *button = GTK_BUTTON(gtk_event_controller_get_widget(GTK_EVENT_CONTROLLER(gesture_click)));
    if (but_data->status == 0) {
        but_data->status = 2;
        gtk_button_set_child(button, gtk_image_new_from_file("imgs\\flag icon-semfundo.png"));
        bandeiras++;
    }else if (but_data->status == 2){
        but_data->status = 0;
        gtk_button_set_child(button, NULL);
        bandeiras--;
    }
    if (but_data->status != 1 && gameStatus == 0) {
        atualizarBandLabel();
        int escondido = 0;
        int bombasSalvas = 0;
        for (int i=0; i<15; i++) {
            for (int j=0; j<15; j++) {
                if (tabela[i][j].status == 0 || tabela[i][j].status == 2) {
                    escondido++;
                }
                if (tabela[i][j].status == 2 && tabela[i][j].tipo == 1) {
                    bombasSalvas++;
                }
            }
        }
        if (escondido == bombas && bombasSalvas == bombas) {
            endDialog("win");
            atualizarVitorias(1);
        }
    }
}

void clickCelula(GtkButton* gtk_button, gpointer data){
    Celula *but_data = (Celula*)data;

    if (but_data->status == 0) {

        char *string1 = (char*)malloc(50*sizeof(char));
        strcpy(string1, "<b><span size='15000'>0</span></b>");

        for (int i=(but_data->x)-2; i<=(but_data->x)+2; i++) {
            for (int j=(but_data->y)-2; j<=(but_data->y)+2; j++) {

                if (i<0 || i>14 || j<0 || j>14) {
                    continue;
                }

                GtkButton* button = GTK_BUTTON(gtk_grid_get_child_at(GTK_GRID(tabelaBox), j, i));

                if (tabela[i][j].status == 0) {
                    if (tabela[i][j].tipo == 1 && but_data->x == i && but_data->y == j && gameStatus == 0) {

                        gtk_button_set_child(button, gtk_image_new_from_file("imgs\\campoMinadoIcone.png"));
                        tabela[i][j].status = 1;
                        endDialog("lose");
                        atualizarVitorias(0);

                    }else if (tabela[i][j].tipo != 1){

                        char cBombasPerto = (char)(tabela[i][j].bombasPerto+48);
                        string1[22] = cBombasPerto;
                        GtkWidget* label = gtk_label_new (NULL);
                        gtk_label_set_markup(GTK_LABEL(label), string1);
                        gtk_button_set_child(button, label);
                        tabela[i][j].status = 1;
                    }
                }
            }
        }
        free(string1);
    }
}

GtkWidget *getBotaoTabela(Celula* celula) {
    GtkWidget *mainButton = gtk_button_new();
    Celula *button_data = g_new(Celula, 1);
    button_data = celula;

    gtk_widget_set_size_request(mainButton, 20, 20);
    g_signal_connect(mainButton, "clicked", G_CALLBACK(clickCelula), button_data);
    g_signal_connect(gesture[l][c], "pressed", G_CALLBACK(flagCelula), button_data);
    gtk_gesture_single_set_button(GTK_GESTURE_SINGLE(gesture[l][c]), 3);
    gtk_widget_add_controller(mainButton, GTK_EVENT_CONTROLLER(gesture[l][c]));
    if ( celula->tipo == 0 && q == 0 ) {
        GtkWidget *tempLabel = gtk_label_new (NULL);
        gtk_label_set_markup(GTK_LABEL(tempLabel), "<b><span size='15000'>S</span></b>");
        gtk_button_set_child(GTK_BUTTON(mainButton), tempLabel);
        q++;
    }

    if (c<14) {
        c++;
    }else {
        l++;
        c=0;
    }

    return mainButton;
}

void atualizarBandLabel(){
    char *tempString = (char*)malloc(50*sizeof(char));
    sprintf(tempString, "<b><span size='30000'>Bandeiras: %d</span></b>", bandeiras);
    gtk_label_set_markup(GTK_LABEL(bandeiraLabel), tempString);
}

void endDialog(char* result) {
    if (strcmp(result, "win") == 0) {
        gtk_label_set_markup(GTK_LABEL(bandeiraLabel), "<b><span size='30000'>Você Ganhou! :)</span></b>");
    }else if (strcmp(result, "lose") == 0) {
        gtk_label_set_markup(GTK_LABEL(bandeiraLabel), "<b><span size='30000'>Você Perdeu! :(</span></b>");
    }
    gameStatus = 1;
}

void clickLabel(GtkGestureClick* gesture_click, gint n, gdouble x, gdouble y, gpointer data) {
    alterarTela(getTelaInicio());
    deletarTabela();
}

void atualizarVitorias(int v /* zerar = 0 , adicionar = 1 */) {
    FILE *arq;
    if ((arq = fopen("data\\vitorias.bin", "rb")) == NULL) {
        printf("Erro ao encontrar arquivo de dados\n");
    }
    fread(&old_v, sizeof(int), 1, arq);
    fclose(arq);
    if ((arq = fopen("data\\vitorias.bin", "wb")) == NULL) {
        printf("Erro ao encontrar arquivo de dados\n");
    }
    if (v == 0) {
        old_v = 0;
    }else if (v == 1) {
        old_v++;
    }
    fwrite(&old_v, sizeof(int), 1, arq);
    fclose(arq);
}

void printTabela() {
    for (int i=0; i<15; i++) {
        for (int j=0; j<15; j++) {
            if (tabela[i][j].tipo == 1) {
                printf("X ");
            } else {
                printf("%d ", tabela[i][j].bombasPerto);
            }
        }
        printf("\n");
    }
}