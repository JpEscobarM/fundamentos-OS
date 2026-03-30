#include "thread.h"


int main(void)
{

    Param_t *param_t = NULL;

    inicializa_parametros_threads(&param_t);

   exibe_parametros_threads(&param_t);

    inicializa_barreira();



    free(param_t);
    return 0;
}
