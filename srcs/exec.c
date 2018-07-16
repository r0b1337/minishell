#include "minishell.h"

int	exec_command(char **command, char **env)
{
	pid_t process;
	char	*bin;

	if ((bin = get_exec(env, command[0])) == NULL)
		return (print_error(command[0]));
	process = fork();
	if (process == 0)
		process = execve(bin, command, env);
	wait(&process);
	return (1);
}
