#include <iostream>
#include <queue>

using namespace std;

//OPT e FIFO

FILE * openFile(FILE *arq);
void closeFile(FILE *arq);
int getSequencia(FILE *arq, char *sequencia);
int getTamMemoria(FILE *arq);
void realizaFifo(char *sequencia, int tamanho_sequencia, int tamMemoria);
void realizaOpt(char *sequencia, int tamanho_sequencia, int tamMemoria);
void escreveSaida(char *matriz_memoria);

int main() {
    char sequencia[100];
    int tamanho_sequencia;
    FILE *arq = NULL;
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
        realizaOpt(sequencia, tamanho_sequencia, tamMemoria);
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

void realizaFifo(char *sequencia, int tamanho_sequencia, int tam_memoria){
    char numero_requisitado;
    char memoria[tam_memoria];
    char matriz_memoria[tam_memoria][tamanho_sequencia];
    //Inicializa matriz
    int i;
    int j;
    for(i = 0; i < tam_memoria; i++){
        memoria[i] = ' ';
        for(j = 0; j < tamanho_sequencia; j++){
            matriz_memoria[i][j] = ' ';
        }
    }
    bool hit;
    double acertos = 0;
    queue<char> fila_chegada;
    char mais_antigo;
    bool memoria_cheia;

    for(i = 0; i < tamanho_sequencia; i++){
        numero_requisitado = sequencia[i];
        hit = false;
        if(i==0){
            mais_antigo = sequencia[0];
            matriz_memoria[0][0] = numero_requisitado;
            memoria[i] = numero_requisitado;
            fila_chegada.push(numero_requisitado);
        }else{
            for(j = 0; j < tam_memoria; j++){
                if(numero_requisitado == memoria[j]){
                   hit =true;
                   acertos++;
                }
            }
            if(hit == true){
                for(j = 0; j < tam_memoria; j++){
                    matriz_memoria[j][i] = '_';
                }
            }else{
                memoria_cheia = true;
                fila_chegada.push(numero_requisitado);
                for(j = 0; j < tam_memoria; j++){
                    if(memoria[j] == ' '){
                        memoria_cheia = false;
                        memoria[j] = numero_requisitado;
                        break;
                    }
                }
                if(memoria_cheia){
                    mais_antigo = fila_chegada.front();
                    for(j = 0; j < tam_memoria; j++){
                        if(memoria[j] == mais_antigo){
                            memoria[j] = numero_requisitado;
                            break;
                        }
                    }
                }
                for(j = 0; j < tam_memoria; j++){
                    matriz_memoria[j][i] = memoria[j];
                }
            }
        }
    }

    for(i = 0; i < tam_memoria; i++){
        cout << endl;
        for(j = 0; j < tamanho_sequencia; j++){
           cout <<  matriz_memoria[i][j];
        }
    }
    double erros = tamanho_sequencia - acertos;
    cout << endl <<  "ACERTOS: " << acertos<< endl;
    cout <<  "ERROS: " << erros << endl;
    cout <<  "TOTAL REQUISICOES: " << tamanho_sequencia<< endl;
    cout <<  "TAXA DE ERRO: " << (erros/tamanho_sequencia)<< endl;

}

void realizaOpt(char *sequencia, int tamanho_sequencia, int tam_memoria){
    char numero_requisitado;
    char memoria[tam_memoria];
    char matriz_memoria[tam_memoria][tamanho_sequencia];
    //Inicializa matriz
    int i;
    int j;
    for(i = 0; i < tam_memoria; i++){
        memoria[i] = ' ';
        for(j = 0; j < tamanho_sequencia; j++){
            matriz_memoria[i][j] = ' ';
        }
    }

    bool hit;
    double acertos = 0;
    char maior_tempo;
    bool memoria_cheia;

    for(i = 0; i < tamanho_sequencia; i++){
        numero_requisitado = sequencia[i];
        hit = false;
        if(i==0){
            matriz_memoria[0][0] = numero_requisitado;
            memoria[i] = numero_requisitado;
        }else{
            for(j = 0; j < tam_memoria; j++){
                if(numero_requisitado == memoria[j]){
                   hit =true;
                   acertos++;
                }
            }
            if(hit == true){
                for(j = 0; j < tam_memoria; j++){
                    matriz_memoria[j][i] = '_';
                }
            }else{
                memoria_cheia = true;
                for(j = 0; j < tam_memoria; j++){
                    if(memoria[j] == ' '){
                        memoria_cheia = false;
                        memoria[j] = numero_requisitado;
                        break;
                    }
                }
                if(memoria_cheia){
                    int relacao_tempo = 0;
                    for(j = 0; j < tam_memoria; j++){
                        bool nunca_usado = true;
                        for(int k = i+1; k < tamanho_sequencia; k++){
                            if(memoria[j] == sequencia[k]){
                                nunca_usado = false;
                                if(k > relacao_tempo){
                                    relacao_tempo = k;
                                    maior_tempo = sequencia[k];
                                }
                                break;
                            }
                        }
                        if(nunca_usado){
                            maior_tempo = memoria[j];
                            break;
                        }
                    }
                    for(j = 0; j < tam_memoria; j++){
                        if(memoria[j] == maior_tempo){
                            memoria[j] = sequencia[i];
                            break;
                        }
                    }
                }
                for(j = 0; j < tam_memoria; j++){
                    matriz_memoria[j][i] = memoria[j];
                }
            }
        }
    }

    for(i = 0; i < tam_memoria; i++){
        cout << endl;
        for(j = 0; j < tamanho_sequencia; j++){
           cout <<  matriz_memoria[i][j];
        }
    }

    double erros = tamanho_sequencia - acertos;
    cout << endl <<  "ACERTOS: " << acertos<< endl;
    cout <<  "ERROS: " << erros << endl;
    cout <<  "TOTAL REQUISICOES: " << tamanho_sequencia<< endl;
    cout <<  "TAXA DE ERRO: " << (erros/tamanho_sequencia)<< endl;
}





