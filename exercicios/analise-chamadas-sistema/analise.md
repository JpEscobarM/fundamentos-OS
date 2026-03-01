# Análise de chamadas de sistema

Analise os códigos ola_mundo.c e ola_mundo.py a seguir.
 Avalie qual dos códigos fará mais chamadas de sistema. 
 Em seguida compile-os (quando necessário for) e execute-os.
 Após isso, através do comando strace, avalie as chamadas de sistema identificadas e avalie qual dos programas de fato executa mais chamadas de sistema.
 Explique o(s) motivo(s) que levaram a tal resultado.
 
## Analsie ola_mundo.c

A execução de um codigo é realizada pelas seguintes etapas:

1 - Inicialização do processo.
2 - Carregamento das bibliotecas.
3️ - Preparação do ambiente de execução.
4️ - Execução do programa (main).
5️ - Saída no terminal.
6️ - Finalização / interação terminal.

strace ./ola_mundo:

carrega o executável "./ola_mundo"
na memória em conjunto com as variáveis de ambiente, após isso executa o programa, o " = 0" é o valor de retorno
da syscall.

```
execve("./ola_mundo", ["./ola_mundo"], 0x7ffcae6cb330 /* 47 vars */) = 0
```

consulta o valor atual do program break, ou seja, o endereço do topo atual do heap
"0x6105d8072000", a região que será utilizada para alocação dinâmica de memória durante a execução do
programa.
```
brk(NULL) = 0x6105d8072000
```

mmap é uma chamada de sistema que solicita ao kernel a reserva de uma região de memória virtual. 
```
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7ac452b9e000 
```

As chamadas de sistema que ocorrem a seguir são durante a inicialização
do processo, são executadas pelo dynamic loader e a biblioteca padrão C (glibc), antes da execução do main() do programa:
 ```
access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=41587, ...}) = 0
mmap(NULL, 41587, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7ac452b93000
close(3)  
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7ac452800000
mmap(0x7ac452828000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7ac452828000
mmap(0x7ac4529b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x7ac4529b0000
mmap(0x7ac4529ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x7ac4529ff000
mmap(0x7ac452a05000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7ac452a05000
close(3)    = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7ac452b90000
```


Esse trecho mostra a preparação final do ambiente de execução pelo sistema e pela biblioteca padrão C, incluindo configuração de threads, memória e segurança. Após essa inicialização, ocorre a chamada efetiva do programa, representada pela syscall write, responsável pela saída exibida no terminal.

```
arch_prctl(ARCH_SET_FS, 0x7ac452b90740) = 0
Registra no kernel o enderço onde o kernel irá escrever o TID (Thread Identifier) e também usar para sinalizar quando ocorrer o término da thread.
set_tid_address(0x7ac452b90a10)         = 1547
set_robust_list(0x7ac452b90a20, 24)     = 0
registra rseq, a otimização do Linux para operações rápidas por CPU, glibc utiliza normalmente para melhorar desempenho em rotinas internas.
rseq(0x7ac452b91060, 0x20, 0, 0x53053053) = 0
mprotect(0x7ac4529ff000, 16384, PROT_READ) = 0
mprotect(0x6105d56de000, 4096, PROT_READ) = 0
mprotect(0x7ac452bdc000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7ac452b93000, 41587)           = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
getrandom("\x97\xcc\xf7\x53\xda\xf6\x04\x32", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x6105d8072000
brk(0x6105d8093000)                     = 0x6105d8093000
write(1, "Ola turma!\n", 11Ola turma! )            = 11
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
strace: Process 1547 detached
```
Nem toda execução do programa corresponde a chamadas de sistema. As syscalls representam apenas as interações entre o programa e o kernel, como acesso a arquivos, gerenciamento de memória e saída no terminal. A maior parte da execução ocorre em espaço de usuário, dentro das bibliotecas e do próprio programa, sem necessidade de chamadas de sistema. O strace exibe apenas esses momentos de interação com o kernel, o que dá a impressão de que toda a execução consiste em syscalls.

a única chamada de sistema diretamente necessária para a lógica do programa é o write().

### chamadas de sistema ola_mundo.c: 1