# bbshk
Реализация оболочки **bash**  

сборка: `make`  
запуск: `./minishell`  

### Используемые функции:
```
printf, malloc, free, write, open, read, close, fork, wait,
waitpid, signal, kill, exit, getcwd, chdir, stat, execve, dup,
dup2, pipe, opendir, readdir, closedir, strerror, errno,
isatty, ttyname, ttyslot, ioctl, getenv,
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
```
### Реализация: 
  * special characters: `\` `;` `|` `’` `"` (without multiline) `$?` environment variables `$`   
  * have a working history (стрелка вниз и вверх)  
  * redirections: `<` `>` `<<` `>>`
  * ctrl-C
  * ctrl-D выйти из оболочки.
  * ctrl- \
  * встроенные функции:
    * echo with option -n
    * cd with only a relative or absolute path
    * pwd with no options
    * export with no options
    * unset with no options
    * env with no options or arguments
    * exit with no options
 
![terminal](https://github.com/hyoghurt/bbshk/raw/master/terminal.png)
