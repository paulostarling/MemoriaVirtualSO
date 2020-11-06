#include <iostream>

using namespace std;

FILE * openFile(FILE *arq);
void closeFile(FILE *arq);
char * getTamMemoria(FILE *arq);

int main() {
    char sequencia[100];
    FILE *arq = NULL;
    arq = openFile(arq);
    char *tamMemoria;

    if (arq == NULL) {
        printf("ERRO! O arquivo não foi aberto!\n");
        return 0;
    }
    printf("Arquivo encontrado e aberto\n");

    fgets(sequencia, 100, arq);
    cout << "Sequencia: " << sequencia << endl;

    //Verificar como salvar o tamanho em uma variavel int
    tamMemoria = getTamMemoria(arq);

    closeFile(arq);
    return 0;
}

FILE * openFile(FILE *arq) {
    arq = fopen("entrada.txt", "rt");
    return arq;
}

void closeFile(FILE *arq) {
    fclose(arq);
}

char * getTamMemoria(FILE *arq) {
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
    cout << "Tamanho da Memoria: "<< tamanho << endl;
    return tamanho;
}






