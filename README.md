# minishell

## 지옥의 미니셸 오픈!

### 쓸 수 있는 함수

malloc, free, write, open, read, close, fork, wait,
waitpid, wait3, wait4, signal, kill, exit, getcwd,
chdir, stat, lstat, fstat, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, errno

### 구현해야 하는 것

- echo with option ’-n’
- cd with only a relative or absolute path
- pwd without any options
- export without any options
- unset without any options
- env without any options and any arguments
- exit without any options
- ; in the command should separate commands like in bash
- ’ and " should work like in bash except for multiline commands
- Redirections < > “>>” should work like in bash except for file descriptor aggregation
- Pipes | should work like in bash
- Environment variables ($ followed by characters) should work like in bash
- $? should work like in bash
- ctrl-C, ctrl-D and ctrl-\ should have the same result as in bash