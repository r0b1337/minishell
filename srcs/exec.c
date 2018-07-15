#include "minishell.h"

int	exec_command(char **command)
{
	pid_t process;
	char	*bin;

	if ((bin = get_exec(command[0])) == NULL)
		return (print_error(command[0]));
	process = fork();
	if (process == 0)
		process = execve(bin, command, envp);
	wait(&process);
	return (0);
}
