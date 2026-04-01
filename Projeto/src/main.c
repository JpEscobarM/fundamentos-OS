#include "cJSON.h"
#include "file.h"

#define FILE_1 DATA_DIR "/mqtt_senzemo_cx_bg_reduzido.json"
#define FILE_2 DATA_DIR "/senzemo_cx_bg_reduzido.json"


int main(void)
{
 char *bufferLeitura = read_file(FILE_2, "rb");

 cJSON *root = cJSON_Parse(bufferLeitura);

 int n = cJSON_GetArraySize(root);

 for(int i = 0; i < n; i++)
 {
  cJSON *item = cJSON_GetArrayItem(root, i);

  cJSON *payload = cJSON_GetObjectItem(item, "brute_data");

  printf("%s\n", payload->valuestring);
 }

 printf("Quantidade de registros: %d\n", cJSON_GetArraySize(root));


 cJSON_Delete(root);
 free(bufferLeitura);
 return 0;
}