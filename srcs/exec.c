#include "minishell.h"

int	exec_command(char **command)
{
	pid_t process;

	process = fork();
	if (process == 0)
		process = execve(get_exec(command[0]), command, envp);
	wait(&process);
	if (process == -1)
		return (print_error(command[0]));
	return (0);
}
