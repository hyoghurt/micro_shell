# micro_shell
Implementation shell **bash**  
The objective of this project is to create a simple shell and learn a lot about processes and file descriptors.

Compile minishell: `make`    
Run: `./minishell`  

### Functions used:
```
printf, malloc, free, write, open, read, close, fork, wait,
waitpid, signal, kill, exit, getcwd, chdir, stat, execve, dup,
dup2, pipe, opendir, readdir, closedir, strerror, errno,
isatty, ttyname, ttyslot, ioctl, getenv,
tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
```
### Implementation: 
  * special characters: `\` `;` `|` `’` `"` (without multiline) `$?` environment variables `$`   
  * redirections: `<` `>` `<<` `>>`
  * have a working history (up and down key)  
  * ctrl-C
  * ctrl-D
  * ctrl- \
  * built-in functions:
    * echo with option -n
    * cd with only a relative or absolute path
    * pwd with no options
    * export with no options
    * unset with no options
    * env with no options or arguments
    * exit with no options
 
![terminal](https://github.com/hyoghurt/bbshk/raw/master/terminal.png)
