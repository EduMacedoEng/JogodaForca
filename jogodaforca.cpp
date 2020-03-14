#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;
string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;

bool letra_existe(char chute, string palavra_secreta) {
    for (int i = 0; i < palavra_secreta.size(); i++) {
        if (chute == palavra_secreta[i]) {
            return true;
        }
        /*else { // Esse else mata o for e compara somente com a primeira letra da palavra secreta.
            return false;
        }*/
    }
    /*
    for (char letra : palavra_secreta){
        if (chute == letra){
            return true;
        }
    } 
    return false;
    */
    return false;
}

bool nao_acertou() {
    for (char letra : palavra_secreta) {
        if (!chutou[letra]) {
            return true;
        }
    }
    return false;
}

bool nao_enforcou() {
    return chutes_errados.size() < 5;
}

void imprime_cabecalho() {
    cout << "*********************" << endl;
    cout << "*** Jogo da Forca ***" << endl;
    cout << "*********************" << endl;
    cout << endl;
}

vector<string> ler_arquivo() {
    ifstream arquivo;
    arquivo.open("C:/Users/eduardo.macedo/.vscode/Desktop/C_C++_-_Alura/jogodaforca/jogodaforca/palavras.txt");
    if (arquivo.is_open()) {
        int qtd_palavras;
        arquivo >> qtd_palavras;
        vector<string> palavras_do_arquivo;

        //cout << "O arquivo possui: " << qtd_palavras << " palavras." << endl;

        for (int i = 1; i <= qtd_palavras; i++) {
            string palavra_lida;
            arquivo >> palavra_lida;
            palavras_do_arquivo.push_back(palavra_lida);
            //cout << "Na linha: " << i << " | " << palavra_lida << endl;
        }
        arquivo.close(); // Boa prática. Sempre fechar o arquivo quando abrir.
        return palavras_do_arquivo;
    }
    else {
        cout << "Nao foi possivel acessar o banco de palavras.";
        exit(0); // Comando que usamos para parar o arquivo no momento da condicional.
    }
}

void salvar_arquivo(vector<string> nova_lista) {
    ofstream arquivo;
    arquivo.open("C:/Users/eduardo.macedo/.vscode/Desktop/C_C++_-_Alura/jogodaforca/jogodaforca/palavras.txt");

    if (arquivo.is_open()) {
        arquivo << nova_lista.size() << endl; // Aqui eu escrevo no arquivo a quantidade de palavras.

        for (string palavra : nova_lista) {
            arquivo << palavra << endl;
        }

        cout << "A palavra foi salva com sucesso !" << endl;
        arquivo.close();
    }
    else {
        cout << "Nao foi possivel acessar o banco de palavras" << endl;
        exit(0);
    }
}

void adicionar_palavra() {
    string nova_palavra;
    cout << "Digite a palavra que voce deseja adicionar: ";
    cin >> nova_palavra;

    vector<string> lista_palavras = ler_arquivo();
    lista_palavras.push_back(nova_palavra);

    salvar_arquivo(lista_palavras);
}

void imprime_rodape() {
    int cond_nova_palavra;
    cout << "Fim de jogo !" << endl;
    cout << "A palavra secreta era: " << palavra_secreta << endl;
    if (nao_acertou()) {
        cout << "Tente novamente !" << endl;
    }
    else {
        cout << "Parabens, voce acertou a palavra secreta.";
        cout << "Voce deseja adicionar uma nova palavra ao banco de palavras ?" << endl;
        cout << "1 - Sim" << endl;
        cout << "2 - Nao" << endl;
        cout << "Opcao: ";cin >> cond_nova_palavra;
        if (cond_nova_palavra = 1) {
            adicionar_palavra();
        }
    }
}

void imprime_erros() {
    cout << "\nChutes errados: ";
    for (char letra : chutes_errados) {
        cout << letra << " ";
    }
    cout << endl;
}

void imprime_palavra() {
    for (char letra : palavra_secreta) {
        if (chutou[letra]) {
            cout << letra << " ";
        }
        else {
            cout << "_ ";
        }
    }
    cout << endl;
}

void chuta() {
    cout << "Seu chute: ";
    char chute;
    cin >> chute;

    chutou[chute] = chute;

    if (letra_existe(chute, palavra_secreta)) {
        cout << "\nVoce acertou ! Seu chute esta na palavra." << endl;
    }
    else {
        cout << "\nVoce errou! Seu chute nao esta na palavra." << endl;
        chutes_errados.push_back(chute);
    }
    cout << endl;
}



void sorteia_palavras() {
    vector<string> palavras = ler_arquivo();
    
    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size();

    palavra_secreta = palavras[indice_sorteado];
}

int main() {
    imprime_cabecalho();

    ler_arquivo();
    sorteia_palavras();

    while (nao_acertou() && nao_enforcou()) {
        imprime_erros();   
        imprime_palavra();
        chuta();
    }
    imprime_rodape();
}   