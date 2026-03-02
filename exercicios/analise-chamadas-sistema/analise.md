# Análise de chamadas de sistema

Analise os códigos ola_mundo.c e ola_mundo.py a seguir.
 Avalie qual dos códigos fará mais chamadas de sistema. 
 Em seguida compile-os (quando necessário for) e execute-os.
 Após isso, através do comando strace, avalie as chamadas de sistema identificadas e avalie qual dos programas de fato executa mais chamadas de sistema.
 Explique o(s) motivo(s) que levaram a tal resultado.
 
## Análise antes da execução: 

 Em tese o programa em python deve executar mais chamadas de sistema do que um programa em C, mesmo os dois programas sendo extremamente simples, a resposta pra isso é porque o em C o código vira um executável nativo em binário que chama a libc e executa o main() praticamente de forma direta. Em python o script não é executado diretamente, o que executamos é um interpretador python que inicializa o runtime, configura o ambiente, carrega módulos e após isso abre e lê o arquivo .py do código, essas operações acabam por requisitar muito do kernel e assim geram mais syscalls.


## strace ./ola_mundo:

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


## strace python3 ola_mundo.py: 

```
execve("/usr/bin/python3", ["python3", "ola_mundo.py"], 0x7fff9a89b458 /* 49 vars */) = 0
brk(NULL)                               = 0x1ae23000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x73becad39000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=89071, ...}) = 0
mmap(NULL, 89071, PROT_READ, MAP_PRIVATE, 3, 0) = 0x73becad23000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=952616, ...}) = 0
mmap(NULL, 950296, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x73becac3a000
mmap(0x73becac4a000, 520192, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x10000) = 0x73becac4a000
mmap(0x73becacc9000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x8f000) = 0x73becacc9000
mmap(0x73becad21000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xe7000) = 0x73becad21000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libz.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=113000, ...}) = 0
mmap(NULL, 110744, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x73becac1e000
mmap(0x73becac20000, 73728, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x2000) = 0x73becac20000
mmap(0x73becac32000, 24576, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x14000) = 0x73becac32000
mmap(0x73becac38000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1a000) = 0x73becac38000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libexpat.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=174336, ...}) = 0
mmap(NULL, 176256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x73becabf2000
mmap(0x73becabf6000, 118784, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x4000) = 0x73becabf6000
mmap(0x73becac13000, 32768, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x21000) = 0x73becac13000
mmap(0x73becac1b000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x73becac1b000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\220\243\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
fstat(3, {st_mode=S_IFREG|0755, st_size=2125328, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2170256, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x73beca800000
mmap(0x73beca828000, 1605632, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x73beca828000
mmap(0x73beca9b0000, 323584, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1b0000) = 0x73beca9b0000
mmap(0x73beca9ff000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1fe000) = 0x73beca9ff000
mmap(0x73becaa05000, 52624, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x73becaa05000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x73becabf0000
arch_prctl(ARCH_SET_FS, 0x73becabf1080) = 0
set_tid_address(0x73becabf1350)         = 13748
set_robust_list(0x73becabf1360, 24)     = 0
rseq(0x73becabf19a0, 0x20, 0, 0x53053053) = 0
mprotect(0x73beca9ff000, 16384, PROT_READ) = 0
mprotect(0x73becac1b000, 8192, PROT_READ) = 0
mprotect(0x73becac38000, 4096, PROT_READ) = 0
mprotect(0x73becad21000, 4096, PROT_READ) = 0
mprotect(0xa27000, 4096, PROT_READ)     = 0
mprotect(0x73becad79000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x73becad23000, 89071)           = 0
getrandom("\x31\xc3\x8e\x4d\x17\x99\xed\x4b", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x1ae23000
brk(0x1ae44000)                         = 0x1ae44000
openat(AT_FDCWD, "/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=5727920, ...}) = 0
mmap(NULL, 5727920, PROT_READ, MAP_PRIVATE, 3, 0) = 0x73beca200000
close(3)                                = 0
openat(AT_FDCWD, "/usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=27028, ...}) = 0
mmap(NULL, 27028, PROT_READ, MAP_SHARED, 3, 0) = 0x73becad32000
close(3)                                = 0
futex(0x73becaa0472c, FUTEX_WAKE_PRIVATE, 2147483647) = 0
getcwd("/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema", 4096) = 66
getrandom("\x62\x61\x62\x11\xff\x8b\xeb\xf5\x63\xb7\x51\x68\x95\x7f\xbc\xb2\x71\x05\xdd\x52\xdf\xaf\xe9\x43", 24, GRND_NONBLOCK) = 24
gettid()                                = 13748
mmap(NULL, 1048576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x73becaaf0000
mmap(NULL, 266240, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x73becaaaf000
mmap(NULL, 135168, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x73becaa8e000
brk(0x1ae65000)                         = 0x1ae65000
mmap(NULL, 16384, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x73becad2e000
brk(0x1ae86000)                         = 0x1ae86000
newfstatat(AT_FDCWD, "/usr/lib/jvm/java-21-openjdk-amd64/bin/python3", 0x7ffff343e070, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/local/sbin/python3", 0x7ffff343e070, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/local/bin/python3", 0x7ffff343e070, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/sbin/python3", 0x7ffff343e070, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/bin/python3", {st_mode=S_IFREG|0755, st_size=8020928, ...}, 0) = 0
openat(AT_FDCWD, "/usr/pyvenv.cfg", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/bin/pyvenv.cfg", O_RDONLY) = -1 ENOENT (No such file or directory)
readlink("/usr/bin/python3", "python3.12", 4096) = 10
readlink("/usr/bin/python3.12", 0x7ffff3439090, 4096) = -1 EINVAL (Invalid argument)
openat(AT_FDCWD, "/usr/bin/python3._pth", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/bin/python3.12._pth", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/usr/bin/pybuilddir.txt", O_RDONLY) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/bin/Modules/Setup.local", 0x7ffff343e070, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/bin/lib/python312.zip", 0x7ffff343de30, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python312.zip", 0x7ffff343de90, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/bin/lib/python3.12/os.py", 0x7ffff343de90, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/bin/lib/python3.12/os.pyc", 0x7ffff343de90, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python3.12/os.py", {st_mode=S_IFREG|0644, st_size=39786, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/bin/lib/python3.12/lib-dynload", 0x7ffff343de90, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python3.12/lib-dynload", {st_mode=S_IFDIR|0755, st_size=16384, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/lib-dynload", {st_mode=S_IFDIR|0755, st_size=16384, ...}, 0) = 0
brk(0x1aea7000)                         = 0x1aea7000
openat(AT_FDCWD, "/etc/localtime", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=1444, ...}) = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=1444, ...}) = 0
read(3, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 4096) = 1444
lseek(3, -910, SEEK_CUR)                = 534
read(3, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0"..., 4096) = 910
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python312.zip", 0x7ffff343d8c0, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python312.zip", 0x7ffff343dc40, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python3.12", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3.12", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=20480, ...}) = 0
getdents64(3, 0x1ae885a0 /* 202 entries */, 32768) = 6752
getdents64(3, 0x1ae885a0 /* 0 entries */, 32768) = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/__init__.cpython-312-x86_64-linux-gnu.so", 0x7ffff343dc40, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/__init__.abi3.so", 0x7ffff343dc40, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/__init__.so", 0x7ffff343dc40, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/__init__.py", {st_mode=S_IFREG|0644, st_size=5884, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/__init__.py", {st_mode=S_IFREG|0644, st_size=5884, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3.12/encodings/__pycache__/__init__.cpython-312.pyc", O_RDONLY|O_CLOEXEC) = 3
fcntl(3, F_GETFD)                       = 0x1 (flags FD_CLOEXEC)
fstat(3, {st_mode=S_IFREG|0644, st_size=5790, ...}) = 0
ioctl(3, TCGETS, 0x7ffff343d880)        = -1 ENOTTY (Inappropriate ioctl for device)
lseek(3, 0, SEEK_CUR)                   = 0
lseek(3, 0, SEEK_CUR)                   = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=5790, ...}) = 0
read(3, "\313\r\r\n\0\0\0\0F\217ri\374\26\0\0\343\0\0\0\0\0\0\0\0\0\0\0\0\6\0\0"..., 5791) = 5790
read(3, "", 1)                          = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3.12/encodings", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=20480, ...}) = 0
getdents64(3, 0x1ae91d60 /* 125 entries */, 32768) = 4224
getdents64(3, 0x1ae91d60 /* 0 entries */, 32768) = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/aliases.py", {st_mode=S_IFREG|0644, st_size=15677, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/aliases.py", {st_mode=S_IFREG|0644, st_size=15677, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3.12/encodings/__pycache__/aliases.cpython-312.pyc", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=12408, ...}) = 0
ioctl(3, TCGETS, 0x7ffff343ce00)        = -1 ENOTTY (Inappropriate ioctl for device)
lseek(3, 0, SEEK_CUR)                   = 0
lseek(3, 0, SEEK_CUR)                   = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=12408, ...}) = 0
read(3, "\313\r\r\n\0\0\0\0F\217ri==\0\0\343\0\0\0\0\0\0\0\0\0\0\0\0\5\0\0"..., 12409) = 12408
read(3, "", 1)                          = 0
close(3)                                = 0
brk(0x1aec8000)                         = 0x1aec8000
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/utf_8.py", {st_mode=S_IFREG|0644, st_size=1005, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/encodings/utf_8.py", {st_mode=S_IFREG|0644, st_size=1005, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3.12/encodings/__pycache__/utf_8.cpython-312.pyc", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=2147, ...}) = 0
ioctl(3, TCGETS, 0x7ffff343d910)        = -1 ENOTTY (Inappropriate ioctl for device)
lseek(3, 0, SEEK_CUR)                   = 0
lseek(3, 0, SEEK_CUR)                   = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=2147, ...}) = 0
read(3, "\313\r\r\n\0\0\0\0F\217ri\355\3\0\0\343\0\0\0\0\0\0\0\0\0\0\0\0\5\0\0"..., 2148) = 2147
read(3, "", 1)                          = 0
close(3)                                = 0
rt_sigaction(SIGPIPE, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK, sa_restorer=0x73beca845330}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGXFSZ, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK, sa_restorer=0x73beca845330}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGHUP, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGINT, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGQUIT, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGILL, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGTRAP, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGABRT, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGBUS, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGFPE, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGKILL, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGUSR1, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGSEGV, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGUSR2, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGPIPE, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK, sa_restorer=0x73beca845330}, 8) = 0
rt_sigaction(SIGALRM, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGTERM, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGSTKFLT, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGCHLD, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGCONT, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGSTOP, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGTSTP, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGTTIN, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGTTOU, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGURG, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGXCPU, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGXFSZ, NULL, {sa_handler=SIG_IGN, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK, sa_restorer=0x73beca845330}, 8) = 0
rt_sigaction(SIGVTALRM, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGPROF, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGWINCH, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGIO, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGPWR, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGSYS, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_2, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_3, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_4, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_5, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_6, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_7, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_8, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_9, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_10, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_11, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_12, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_13, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_14, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_15, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_16, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_17, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_18, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_19, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_20, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_21, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_22, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_23, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_24, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_25, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_26, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_27, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_28, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_29, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_30, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_31, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGRT_32, NULL, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
rt_sigaction(SIGINT, {sa_handler=0x6e7140, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK, sa_restorer=0x73beca845330}, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=0}, 8) = 0
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
fcntl(0, F_GETFD)                       = 0
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
ioctl(0, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
lseek(0, 0, SEEK_CUR)                   = -1 ESPIPE (Illegal seek)
ioctl(0, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
fcntl(1, F_GETFD)                       = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
ioctl(1, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
lseek(1, 0, SEEK_CUR)                   = -1 ESPIPE (Illegal seek)
ioctl(1, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
fcntl(2, F_GETFD)                       = 0
fstat(2, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
ioctl(2, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
lseek(2, 0, SEEK_CUR)                   = -1 ESPIPE (Illegal seek)
ioctl(2, TCGETS, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
mmap(NULL, 1048576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x73beca100000
newfstatat(AT_FDCWD, "/usr/bin/pyvenv.cfg", 0x7ffff343d880, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/pyvenv.cfg", 0x7ffff343d8e0, 0) = -1 ENOENT (No such file or directory)
geteuid()                               = 1000
getuid()                                = 1000
getegid()                               = 1000
getgid()                                = 1000
newfstatat(AT_FDCWD, "/home/jp/.local/lib/python3.12/site-packages", 0x7ffff343dab0, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/local/lib/python3.12/dist-packages", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
openat(AT_FDCWD, "/usr/local/lib/python3.12/dist-packages", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
getdents64(3, 0x1aeb5570 /* 2 entries */, 32768) = 48
getdents64(3, 0x1aeb5570 /* 0 entries */, 32768) = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3/dist-packages", {st_mode=S_IFDIR|0755, st_size=12288, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3/dist-packages", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=12288, ...}) = 0
getdents64(3, 0x1aeb5570 /* 199 entries */, 32768) = 8152
getdents64(3, 0x1aeb5570 /* 0 entries */, 32768) = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/dist-packages", 0x7ffff343db10, 0) = -1 ENOENT (No such file or directory)
newfstatat(AT_FDCWD, "/usr/lib/python3.12", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/sitecustomize.py", {st_mode=S_IFREG|0644, st_size=155, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/sitecustomize.py", {st_mode=S_IFREG|0644, st_size=155, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3.12/__pycache__/sitecustomize.cpython-312.pyc", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=300, ...}) = 0
ioctl(3, TCGETS, 0x7ffff343d3f0)        = -1 ENOTTY (Inappropriate ioctl for device)
lseek(3, 0, SEEK_CUR)                   = 0
lseek(3, 0, SEEK_CUR)                   = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=300, ...}) = 0
read(3, "\313\r\r\n\0\0\0\0\273$\26f\233\0\0\0\343\0\0\0\0\0\0\0\0\0\0\0\0\4\0\0"..., 301) = 300
read(3, "", 1)                          = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/lib-dynload", {st_mode=S_IFDIR|0755, st_size=16384, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/lib-dynload", {st_mode=S_IFDIR|0755, st_size=16384, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/lib-dynload", {st_mode=S_IFDIR|0755, st_size=16384, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3.12/lib-dynload", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=16384, ...}) = 0
getdents64(3, 0x1aeb5570 /* 49 entries */, 32768) = 3104
getdents64(3, 0x1aeb5570 /* 0 entries */, 32768) = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/local/lib/python3.12/dist-packages", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/local/lib/python3.12/dist-packages", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/local/lib/python3.12/dist-packages", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
openat(AT_FDCWD, "/usr/local/lib/python3.12/dist-packages", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
getdents64(3, 0x1aeb5d80 /* 2 entries */, 32768) = 48
getdents64(3, 0x1aeb5d80 /* 0 entries */, 32768) = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3/dist-packages", {st_mode=S_IFDIR|0755, st_size=12288, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3/dist-packages", {st_mode=S_IFDIR|0755, st_size=12288, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3/dist-packages", {st_mode=S_IFDIR|0755, st_size=12288, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3/dist-packages", O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_DIRECTORY) = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=12288, ...}) = 0
getdents64(3, 0x1aeb5d80 /* 199 entries */, 32768) = 8152
getdents64(3, 0x1aeb5d80 /* 0 entries */, 32768) = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/usr/lib/python3/dist-packages/apport_python_hook.py", {st_mode=S_IFREG|0644, st_size=8695, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3/dist-packages/apport_python_hook.py", {st_mode=S_IFREG|0644, st_size=8695, ...}, 0) = 0
openat(AT_FDCWD, "/usr/lib/python3/dist-packages/__pycache__/apport_python_hook.cpython-312.pyc", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=8876, ...}) = 0
ioctl(3, TCGETS, 0x7ffff343cd80)        = -1 ENOTTY (Inappropriate ioctl for device)
lseek(3, 0, SEEK_CUR)                   = 0
lseek(3, 0, SEEK_CUR)                   = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=8876, ...}) = 0
read(3, "\313\r\r\n\0\0\0\0\247\22!f\367!\0\0\343\0\0\0\0\0\0\0\0\0\0\0\0\2\0\0"..., 8877) = 8876
read(3, "", 1)                          = 0
close(3)                                = 0
getcwd("/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema", 1024) = 66
newfstatat(AT_FDCWD, "/usr/lib/python3.12", {st_mode=S_IFDIR|0755, st_size=20480, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3.12/lib-dynload", {st_mode=S_IFDIR|0755, st_size=16384, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/local/lib/python3.12/dist-packages", {st_mode=S_IFDIR|0755, st_size=4096, ...}, 0) = 0
newfstatat(AT_FDCWD, "/usr/lib/python3/dist-packages", {st_mode=S_IFDIR|0755, st_size=12288, ...}, 0) = 0
newfstatat(AT_FDCWD, "/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema/ola_mundo.py", {st_mode=S_IFREG|0664, st_size=19, ...}, 0) = 0
openat(AT_FDCWD, "/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema/ola_mundo.py", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0664, st_size=19, ...}) = 0
ioctl(3, TCGETS, 0x7ffff343df50)        = -1 ENOTTY (Inappropriate ioctl for device)
lseek(3, 0, SEEK_CUR)                   = 0
lseek(3, 0, SEEK_CUR)                   = 0
lseek(3, -22, SEEK_END)                 = -1 EINVAL (Invalid argument)
lseek(3, 0, SEEK_SET)                   = 0
close(3)                                = 0
newfstatat(AT_FDCWD, "/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema/ola_mundo.py", {st_mode=S_IFREG|0664, st_size=19, ...}, 0) = 0
readlink("ola_mundo.py", 0x7ffff342d6f0, 4096) = -1 EINVAL (Invalid argument)
getcwd("/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema", 1024) = 66
readlink("/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema/ola_mundo.py", 0x7ffff342d290, 1023) = -1 EINVAL (Invalid argument)
openat(AT_FDCWD, "/home/jp/repos/fundamentos-OS/exercicios/analise-chamadas-sistema/ola_mundo.py", O_RDONLY) = 3
ioctl(3, FIOCLEX)                       = 0
fstat(3, {st_mode=S_IFREG|0664, st_size=19, ...}) = 0
ioctl(3, TCGETS, 0x7ffff343e680)        = -1 ENOTTY (Inappropriate ioctl for device)
lseek(3, 0, SEEK_CUR)                   = 0
fstat(3, {st_mode=S_IFREG|0664, st_size=19, ...}) = 0
read(3, "print(\"Ol\303\241 mundo\")", 4096) = 19
lseek(3, 0, SEEK_SET)                   = 0
read(3, "print(\"Ol\303\241 mundo\")", 4096) = 19
read(3, "", 4096)                       = 0
close(3)                                = 0
write(1, "Ol\303\241 mundo\n", 11Olá mundo
)      = 11
rt_sigaction(SIGINT, {sa_handler=SIG_DFL, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK, sa_restorer=0x73beca845330}, {sa_handler=0x6e7140, sa_mask=[], sa_flags=SA_RESTORER|SA_ONSTACK, sa_restorer=0x73beca845330}, 8) = 0
munmap(0x73becad2e000, 16384)           = 0
exit_group(0)                           = ?

```

O resultado observado com strace nos mostra que o binário em C tem um conjunto menor de syscalls pois, carrega a libc, escreve no stdout e encerra o programa, já no strace do arquivo em python, temos o mesmo bloco inicial, porém aparecem muitas syscalls adicionais por conta do interpretador e de como o ecossistema do python funciona, mesmo sendo simples ele ainda tem mais dependencias do que um arquivo em C.