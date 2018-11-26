#include <iostream>
#include <map>
#include <vector>

#include "dataStruct.hpp"
using namespace std;

int main(int argc, char* argv[]){
	searchMachine machine(argc, argv);

	cout << "Escreva a palavra pela qual deseja buscar nos " << argc-1<< " arquivos fornecidos: " << endl;
	string palavra;
	
	while( cin >> palavra) {
		if(palavra == "STOP") break;
		removesCharAndToLower(palavra);
		
		set<string> filesEncontradas = machine.fazConsulta(palavra);
		set<string>::iterator it;

		if(filesEncontradas.size() > 0){
			for(it = filesEncontradas.begin();it != filesEncontradas.end();it++){
				cout << *it << endl;
			}
		}
		else {
			cout << "A palavra nao foi encontrada em nenhum arquivo!" << endl;
		}
		cout << "Para parar a execucao, digite 'STOP' " << endl << endl;
	}

	return 0;
}
