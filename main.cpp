#include <iostream>

using namespace std;

//OPT e FIFO

FILE * openFile(FILE *arq);
void closeFile(FILE *arq);
int getSequencia(FILE *arq, char *sequencia);
int getTamMemoria(FILE *arq);
void realizaFifo(char *sequencia, int tamanho_sequencia, int tamMemoria);

int main() {
    char sequencia[100];
    int tamanho_sequencia;
    FILE *arq = NULL;
    FILE *arq_saida = NULL;
    int tamMemoria;

    arq = openFile(arq);
    if (arq == NULL) {
        printf("ERRO! O arquivo não foi aberto!\n");
        return 0;
    }
    printf("Arquivo encontrado e aberto\n");

    tamanho_sequencia = getSequencia(arq, sequencia);
    cout << "Sequencia: " << sequencia << endl;
    tamMemoria = getTamMemoria(arq);
    cout << "Tamanho memoria: " << tamMemoria << endl;
    closeFile(arq);

    cout << endl << "Qual operacao voce deseja fazer?" << endl;
    cout << "Digite 1 para FIFO." << endl;
    cout << "Digite 2 para OPT." << endl;

    int opcao;
    cin >>opcao;

    if(opcao == 1){
        cout << sequencia<< endl;
        realizaFifo(sequencia, tamanho_sequencia, tamMemoria);
    }else if(opcao == 2){
        cout << "Realiza OPT" << endl;
    }else{
        cout << "Op invalida" << endl;
        return 0;
    }


    return 0;
}

FILE * openFile(FILE *arq) {
    arq = fopen("entrada.txt", "rt");
    return arq;
}

void closeFile(FILE *arq) {
    fclose(arq);
}

int getTamMemoria(FILE *arq) {
    int i;
    char Linha[100];
    char *tamanho;
    i = 2;
    while (!feof(arq)) {
        fgets(Linha, 100, arq);
        if(i==3) {
            tamanho = Linha;
        }
        i++;
    }
    return atoi(tamanho);
}

int getSequencia(FILE *arq, char *sequencia_formatada) {
    char sequencia_arquivo[100];
    fgets(sequencia_arquivo, 100, arq);
    int j=0;
    for (int i = 0; i < 100; i++){
        if(sequencia_arquivo[i] != ',' && sequencia_arquivo[i] != ' '){
            sequencia_formatada[j] = sequencia_arquivo[i];
            if(sequencia_arquivo[i] == '\n'){
                return j;
            }
            j++;
        }
    }
    return j;
}

void realizaFifo(char *sequencia, int tamanho_sequencia, int tamMemoria){
    int matriz_evolucao[tamMemoria][tamanho_sequencia];
    for(int i = 0; i < tamMemoria; i++){
        for(int j = 0; j < tamanho_sequencia; j++){
            matriz_evolucao[i][j] = NULL;
        }
    }

    //Finalziar regra do FIFO
    int numero_requisitado;
    for(int k = 0; k < tamanho_sequencia; k++){
        numero_requisitado = sequencia[k] - '0';

    }


}





