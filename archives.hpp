#ifndef ARCHIVES_H
#define ARCHIVES_H

#include <iostream>
using namespace std;

//Classe de excessao referente a abertura, leitura ou encerramento de arquivos
class archivesException : public exception {
  public:
    virtual const char* what() const throw(){
      return "Erro na abertura do(s) arquivo(s), cheque-o(s) e tente novamente!";
    }
};

class handleArchives{
  public:
    ifstream openArchives(char* file);
};

#endif
