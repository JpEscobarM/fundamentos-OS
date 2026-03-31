//
// Created by jmartins on 31/03/2026.
//

#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdlib.h>

/**
 * Função auxiliar para read_file, somente abre o arquivo no modo especificado, trata erro de abertura e retorna o ponteiro do arquivo
 * @param FILE_PATH caminho absoluto do arquivo
 * @param mode modo de abertura
 * @return FILE*
 */
FILE* open_file(char *FILE_PATH,char *mode);

/**
 *Abre o arquivo especificado e retorna um buffer do tipo char* com o texto completo do arquivo
 * @param FILE_PATH caminho absoluto do arquivo
 * @param mode modo de abertura
 * @return char*
 */
char* read_file( char  *FILE_PATH,char *mode);

#endif //FILE_H