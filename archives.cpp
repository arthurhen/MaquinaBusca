#include <iostream>
#include <fstream>
#include "archives.hpp"
using namespace std;

	//Abre o arquivo
  ifstream handleArchives::openArchives(char* file) {
  ifstream archive;
  archive.open(file);
  
    //Nos casos em que nao eh possivel abrir o arquivo, utiliza a excessao para resolve-la.
  if(!archive.is_open()){
    throw archivesException();  
  }

  return archive;
}
