# Project pipex

To do :

### BASICS
- check number of arguments
- check if files can be opened (create output if doesn't exist) av[1] and av[ac - 1]
- split CMDs (from av[2] to av[ac - 2])
	- add NULL in the end of CMDs ==> {"cmd", "opt1", "opt2", NULL} (needed in execve())

### THEN
- 'send' file1 content to cmd1 (cf 42/test/pipex/divide/file_to_cmd.c doesn't works)
- pipe cmd1 to cmd2 (cf 42/test/pipex/divide/cmd1_to_cmd2.c)
	==> pipe from cmd1 (read end) to cmd2 (write end)
		--> use dup2 to put STDOUT in read end of pipe
		--> use dup2 to put STDIN in write end of pipe
- 'send' cmd2 out to file2 (cf 42/test/pipex/divide/cmd_to_file.c)
	==> use dup2 to put STDOUT to file2 fd

The difficulty will be to handle proccess with fork() and waitpid()