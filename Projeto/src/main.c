#include "cJSON.h"
#include "file.h"

#define FILE_1 DATA_DIR "/mqtt_senzemo_cx_bg_reduzido.json"
#define FILE_2 DATA_DIR "/senzemo_cx_bg_reduzido.json"


int main(void)
{
 char *bufferLeitura = read_file(FILE_2, "rb");

 cJSON *root = cJSON_Parse(bufferLeitura);

 if (root == NULL) {
  const char *erro = cJSON_GetErrorPtr();
  printf("ERRO DE PARSE: %s\n", erro ? erro : "desconhecido");
  free(bufferLeitura);
  return 1;
 }

 printf("Parse OK\n");
 printf("Quantidade de registros: %d\n", cJSON_GetArraySize(root));

 cJSON_Delete(root);
 free(bufferLeitura);
 return 0;
}