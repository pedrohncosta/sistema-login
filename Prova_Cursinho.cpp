#include <iostream>
#include <unistd.h>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct mensagem
{
    string texto;
    bool lido;
    string usuario;
};

struct pessoa
{
    string usuario;
    string senha;
    string nome;
    string idade;
    vector<mensagem> mensagens;
};
struct nota
{
    string materia;
    string tipo;
    float nota;
};
struct professor
{
    pessoa dados;
    string turma;
    string materia;
};
struct estudante
{
    pessoa dados;
    string turma;
    vector<nota> notas;
};

void split(string linha, char a, string S[])
{
    int pos = 0, fim, i = 0;
    do
    {
        fim = linha.find(a, pos);
        if (fim == -1)
            S[i] = linha.substr(pos);
        else
            S[i++] = linha.substr(pos, fim - pos);
        pos = fim + 1;
    } while (fim != -1);
}

void salvaRegistros(vector<professor> R, vector<estudante> T)
{
    ofstream arquivo;
    arquivo.open("index.txt", ios::app);
    for (int i = 0; i < R.size(); i++)
    {
        arquivo << R[i].dados.usuario << "," << R[i].dados.senha << ",1,0" << endl;
    }
    arquivo.close();

    ofstream arquiv;
    arquiv.open("index.txt", ios::app);
    for (int i = 0; i < T.size(); i++)
    {
        arquiv << T[i].dados.usuario << "," << T[i].dados.senha << ",2,0" << endl;
    }
    arquiv.close();
}

void registro(vector<professor> &P, vector<estudante> &T)
{
    int menu;
    professor Z;
    estudante Q;
    cout << "1 -Educador\n2 -aluno\n";
    cin >> menu;
    if (menu == 1)
    {
        cout << "Usuario desejado: ";
        cin >> Z.dados.usuario;
        cout << "Senha desejada: ";
        cin >> Z.dados.senha;
        P.push_back(Z);
    }
    else if (menu == 2)
    {
        cout << "Usuario desejado: ";
        cin >> Q.dados.usuario;
        cout << "Senha desejada: ";
        cin >> Q.dados.senha;
        T.push_back(Q);
    }
    else
    {
        cout << "Opcao invalida!" << endl;
    }
}

bool autenticarUsr(string usr, string senha)
{
    bool autenticado = false;
    string linha;
    ifstream arquivo;
    arquivo.open("index.txt");
    if (arquivo.is_open())
    {
        while (getline(arquivo, linha))
        {
            string S[4];
            split(linha, ',', S);
            if (usr == S[0])
            {
                if (senha == S[1])
                    autenticado = true;
            }
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro na localização da base de dados. [Não foi possível abrir índice]";
        getchar();
    }
    return autenticado;
}

string loginMenu()
{
    string usr, senha;
    bool nAutenticado = true;
    while (nAutenticado)
    {
        string senha;
        char c_senha;
        system("cls");
        cout << "\t\t\t\tSISTEMA INTEGRAR" << endl
             << endl;
        cout << "Usuario: ";
        cin >> usr;
        fflush(stdin);
        cout << "Senha: ";
        do
        {
            c_senha = getch();
            if (c_senha != 13)
            {
                senha += c_senha;
                cout << "*";
            }
        } while (c_senha != 13);
        cout << endl;
        nAutenticado = !autenticarUsr(usr, senha);
        if (nAutenticado)
        {
            cout << "Erro de autenticação. Usuário ou senha incorretos." << endl;
            sleep(2);
        }
    }
    return usr;
}

void retirarUsr(string retirar)
{
    vector<pessoa> P;
    vector <int> auxiliar;
    string linha;
    int separa;
    pessoa T;

    ifstream arquivo;
    arquivo.open("index.txt");
    if (arquivo.is_open())
    {
        while (getline(arquivo, linha))
        {

            string S[4];
            split(linha, ',', S);
            T.usuario = S[0];
            T.senha = S[1];
            auxiliar.push_back(stoi(S[2]));
            P.push_back(T);
        }
        arquivo.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    for (int i = 0; i < P.size(); i++)
    {
        if (retirar == P[i].usuario)
        {
            vector<pessoa>::iterator it;
            it = P.begin();
            P.erase(it + i);
            cout << "Usuario retirado com sucesso" << endl << endl;
            break;
        }
    }
    
    ofstream arq;
    arq.open("index.txt", ios::trunc);
    for (int i = 0; i < P.size(); i++)
    {
        arq << P[i].usuario << "," << P[i].senha <<","<<auxiliar[i] <<",0" << endl;
    }
    arquivo.close();

}

void menuAdm()
{
    vector<professor> P;
    vector<estudante> A;
    int menu, sair = 0;
    string retirar;
    cout << "Menu Administrador" << endl
         << endl;
    while (sair == 0)
    {
        cout << "1 - Fazer Cadastro\n2 - Retirar Usuario\n3 - Sair\n";
        cin >> menu;
        switch (menu)
        {
        case 1:
            registro(P, A);
            salvaRegistros(P, A);
            break;
        case 2:
            cout << "Digite o nome do usuario que deseja retirar: ";
            cin >> retirar; //Retirar Usuario
            retirarUsr(retirar);
            break;
        case 3:
            sair = 1;
            break;
        }
    }
}

void menuEducador()
{
    cout << "Menu educador";
    // sistema do primeiro login
    //mandar mensagem
    //colocar notas

    getchar();
}

void menuEstudante()
{
    cout << "Menu estudante";
    //sistema do primeiro login
    //mandar/ver mensagem
    //ver notas
    getchar();
}

void guarda(string usr)
{
    int tipoUsr;
    ifstream arquivo;
    string linha;
    arquivo.open("index.txt");
    if (arquivo.is_open())
    {
        while (getline(arquivo, linha))
        {
            string S[4];
            split(linha, ',', S);
            if (usr == S[0])
                tipoUsr = stoi(S[2]);
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro na localização da base de dados. [Não foi possível abrir índice]";
        getchar();
    }
    switch (tipoUsr)
    {
    case -1:
        menuAdm();
        break;
    case 1:
        menuEducador();
        break;
    case 2:
        menuEstudante();
        break;
    default:
        cout << "Tipo de usuário não identificado. [Cadastro corrompido]";
        getch();
        break;
    }
}

int main()
{
    string usrAutenticado;
    usrAutenticado = loginMenu();
    guarda(usrAutenticado);
}