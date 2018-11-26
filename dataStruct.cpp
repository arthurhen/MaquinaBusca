#include <bits/stdc++.h>
#include "dataStruct.hpp"
#include "archives.hpp"
using namespace std;

/* Funcao auxiliar usada dentro da "remove_if"(da biblioteca algorithm). Essa funcao (isInvalidCharacter)
 retorna true caso o caractere c seja invalido e false caso contrario.*/
bool isInvalidCharacter(char c) {
	return (
		//nao eh letra (minuscula ou maiuscula)
		(c < 65 || (c > 90 && c < 97) || c > 122)
		&&
		//nao eh numero
		(c < 48 || c > 57)
	);
}

// Funcao para separar as palavras
int shouldSeparateWord(string word){
  return word.find_last_of(".");
}

// Funcao para a conversão de arquivo-texto, retirando os caracteres invalidos
string removesCharAndToLower(string word){
  word.erase(
    remove_if(word.begin(), word.end(), isInvalidCharacter),
    word.end()
  );

  //transforma a string em lowerCase
  for(unsigned int j=0;j<word.size();j++){
    word[j] = tolower(word[j]);
  }
  
  return word;
}

//Toda a leitura do arquivo e insercao eh feita no construtor da classe, que recebe os argumentos da linha de comando, contendo os arquivos, como parametros
searchMachine::searchMachine(int numberFiles, char** files) {
	int i=0;
  handleArchives handler;

	for(i=1;i<numberFiles;i++){
    ifstream archive;
		string aux;
    
    try {
      archive = handler.openArchives(files[i]);
    }
    catch(exception &e) {
      cout << e.what() << endl;
      exit(0);
    }

		while(!archive.eof()){
			archive >> aux;

			string convertingCString(files[i]);
			string convertingFileString(aux);

			//remove characteres invalidos
			/*
				Logica: o metodo remove_if retorna um iterador para a primeira posicao apos o ultimo elemento nao removido (ou seja, um apontador para a primeira
				posicao que foi removida), e o metodo erase recebe dois parametros: o primeiro eh o inicio da remocao eh o ultimo o final dela. Portanto, o erase
				ira receber o retorno do remove_if (primeira posicao removida) e o fim daquela string (pois ao remover, o remove_if deixa as posicoes da string
				vazias, e o erase as apaga).
				Ex:
				string inicial: Arth.----ur
				retorno do remove_if: Arthur?????
				apos o erase: Arthur

			*/

      int lastDot = shouldSeparateWord(convertingFileString);
     /*
      * Funcao do while: achar palavras do tipo: bodies.--Such, ou seja, palavras juntas que,
      * na verdade, sao duas palavras. Esse while continua infinitamente ate que nao ache nenhum
      * ponto final com algo apos dele na palavra original. Enquanto achar, remove e adiciona como
      * uma palavra separada.
      */
      while(lastDot != -1) {
        string newWord = convertingFileString.substr(lastDot);

        /*
         * Remove os characteres indesejados da palavra apos o ponto e armazena seu tamanho inicial, isso
         * eh necessario para que, no fim desse while, a string "convertingFileString" seja
         * consertada (tenha a string "newWord", que ja foi tratada e eh uma substring da primeira,
         * removida)
         */
        int initialWordSize = newWord.size();
        newWord = removesCharAndToLower(newWord);
        
        // checa se o tamanho da palavra eh zero, se for ela era composta apenas de characteres indesejados
        if(newWord.size() == 0) break;
        
        // a insere no map sem character especial e em lower case
        this->indiceInvertido[convertingFileString].insert(newWord);

        // apaga da string antiga a palavra achada acima e tenta achar outro ponto final
        convertingFileString.erase(lastDot, initialWordSize);
        lastDot = shouldSeparateWord(convertingFileString);
      }

      convertingFileString = removesCharAndToLower(convertingFileString);
			// a insere no map sem character especial e em lower case
			this->indiceInvertido[convertingFileString].insert(convertingCString);
		}
	}
}

/* Faz a consulta da palavra com o metodo find, se ela acha a palavra pedida a funcao fazConsulta
retorna o set contendo os arquivos relacionados com aquela palavra */
set<string> searchMachine::fazConsulta(string palavra) {
	map<string, set<string> >::iterator it;

	it = indiceInvertido.find(palavra);
	if(it != indiceInvertido.end()) {
		return it->second;
	}
	else {
		set<string> bla;
		return bla;
	}
}
