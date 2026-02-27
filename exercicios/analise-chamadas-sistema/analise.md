*Análise de chamadas de sistema*

Analise os códigos ola_mundo.c e ola_mundo.py a seguir.
 Avalie qual dos códigos fará mais chamadas de sistema. 
 Em seguida compile-os (quando necessário for) e execute-os.
 Após isso, através do comando strace, avalie as chamadas de sistema identificadas e
 avalie qual dos programas de fato executa mais chamadas de sistema.
 Explique o(s) motivo(s) que levaram a tal resultado.
 
**Analsie ola_mundo.c**

A execução de um codigo é realizada pelas seguintes etapas:

1 - Inicialização do processo.
2 - Carregamento das bibliotecas.
3️ - Preparação do ambiente de execução.
4️ - Execução do programa (main).
5️ - Saída no terminal.
6️ - Finalização / interação terminal.

strace ./ola_mundo:

execve("./ola_mundo", ["./ola_mundo"], 0x7ffcae6cb330 /* 47 vars */) = 0 -> carrega o executável "./ola_mundo"
na memória em conjunto com as variáveis de ambiente, após isso executa o programa, o " = 0" é o valor de retorno
da syscall, CHAMADA DE SISTEMA.

brk(NULL) = 0x6105d8072000 -> brk(NULL) consulta o valor atual do program break, ou seja, o endereço do topo atual do heap
"0x6105d8072000", a região que será utilizada para alocação dinâmica de memória durante a execução do
programa, CHAMADA DE SISTEMA.
 
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7ac452b9e000 ->
mmap é uma chamada de sistema que solicita ao kernel a reserva de uma região de memória virtual, CHAMADA DE SISTEMA.

As chamadas de sistema que ocorrem a seguir são durante a inicialização
do processo, são executadas pelo dynamic loader e a biblioteca padrão C (glibc), antes da execução do main() do programa:
 
access("/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory) -> CHAMADA DE SISTEMA
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3 -> CHAMADA DE SISTEMA
fstat(3, {st_mode=S_IFREG|0644, st_size=41587, ...}) = 0 -> CHAMADA DE SISTEMA
mmap(NULL, 41587, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7ac452b93000 -> CHAMADA DE SISTEMA
close(3)   -> CHAMADA DE SISTEMA
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3 -> CHAMADA DE SISTEMA
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832 -> CHAMADA DE SISTEMA
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784 -> CHAMADA DE SISTEMA
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0 -> CHAMADA DE SISTEMA
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784 -> CHAMADA DE SISTEMA
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7ac452800000 -> CHAMADA DE SISTEMA

mmap(0x7ac452828000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7ac452828000 -> CHAMADA DE SISTEMA
mmap(0x7ac4529b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x7ac4529b0000 -> CHAMADA DE SISTEMA
mmap(0x7ac4529ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x7ac4529ff000 -> CHAMADA DE SISTEMA
mmap(0x7ac452a05000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7ac452a05000 -> CHAMADA DE SISTEMA
close(3)    = 0 -> CHAMADA DE SISTEMA
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7ac452b90000 -> CHAMADA DE SISTEMA




arch_prctl(ARCH_SET_FS, 0x7ac452b90740) = 0 -> CHAMADA DE SISTEMA
set_tid_address(0x7ac452b90a10)         = 1547 -> CHAMADA DE SISTEMA
set_robust_list(0x7ac452b90a20, 24)     = 0 -> CHAMADA DE SISTEMA
rseq(0x7ac452b91060, 0x20, 0, 0x53053053) = 0 -> CHAMADA DE SISTEMA
mprotect(0x7ac4529ff000, 16384, PROT_READ) = 0 -> CHAMADA DE SISTEMA
mprotect(0x6105d56de000, 4096, PROT_READ) = 0 -> CHAMADA DE SISTEMA
mprotect(0x7ac452bdc000, 8192, PROT_READ) = 0 -> CHAMADA DE SISTEMA
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0 -> CHAMADA DE SISTEMA
munmap(0x7ac452b93000, 41587)           = 0 -> CHAMADA DE SISTEMA
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0 -> CHAMADA DE SISTEMA
getrandom("\x97\xcc\xf7\x53\xda\xf6\x04\x32", 8, GRND_NONBLOCK) = 8 -> CHAMADA DE SISTEMA
brk(NULL)                               = 0x6105d8072000 -> CHAMADA DE SISTEMA
brk(0x6105d8093000)                     = 0x6105d8093000 -> CHAMADA DE SISTEMA
write(1, "Ola turma!\n", 11Ola turma! )            = 11 -> CHAMADA DE SISTEMA
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0 -> CHAMADA DE SISTEMA
read(0, ^Cstrace: Process 1547 detached
