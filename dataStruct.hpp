#include <bits/stdc++.h>
using namespace std;
bool isInvalidCharacter(char c);

//Classe para a busca. Utiliza a estrutura "map", recomendada para a execucao do trabalho.
class searchMachine {
	private:
		map<string, set<string> > indiceInvertido;
	public:
		set<string> fazConsulta(string palavra);
		searchMachine(int numberFiles, char* files[]);
		
};
