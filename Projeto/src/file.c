//
// Created by jmartins on 31/03/2026.
//
#include "file.h"


FILE* open_file(char *FILE_PATH,char *mode)
{
    FILE *f = fopen(FILE_PATH,mode);

    if (f == NULL)
    {
        printf("<open_file>ERRO: não foi possivel abrir o arquivo %s",FILE_PATH);
        exit(1);
    }

    return f;
}


char* read_file(char *file_path,char *mode)
{
    FILE *f = open_file(file_path, mode);

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char *buffer = malloc(size + 1);
    if (buffer == NULL) {
        printf("Erro ao alocar memoria\n");
        fclose(f);
        exit(1);
    }

    size_t bytes_lidos = fread(buffer, 1, size, f);
    buffer[bytes_lidos] = '\0';

    fclose(f);
    return buffer;
}
