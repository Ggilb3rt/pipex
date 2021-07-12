# Project pipex

```
./pipex file1 cmd1 cmd2 file2
< file1 cmd1 | cmd2 > file2
```
Examples
```
./pipex infile "ls -l" "wc -l" outfile
./pipex infile "grep a1" "wc -w" outfile
< infile grep a1 | wc -w > outfile
```

##To do :
### BASICS
- check number of arguments
- check if files can be opened (create output if doesn't exist) av[1] and av[ac - 1]
- split CMDs (from av[2] to av[ac - 2])
	- NOPE SPLIT DO IT [add NULL in the end of CMDs ==> {"cmd", "opt1", "opt2", NULL} (needed in execve())]
- add PATH to splited[0]

### THEN
- 'send' file1 content to cmd1 (cf 42/test/pipex/divide/file_to_cmd.c doesn't works)
- pipe cmd1 to cmd2 (cf 42/test/pipex/divide/cmd1_to_cmd2.c)
	==> pipe from cmd1 (read end) to cmd2 (write end)
		--> use dup2 to put STDOUT in read end of pipe
		--> use dup2 to put STDIN in write end of pipe
- 'send' cmd2 out to file2 (cf 42/test/pipex/divide/cmd_to_file.c)
	==> use dup2 to put STDOUT to file2 fd

The difficulty will be to handle proccess with fork() and waitpid()


### Comportements a check
```
bash-3.2$ < tests/in ls | > tests/out #n'imprime rien
bash-3.2$ < tests/in | ls > tests/out #imprime ls dans out
```
