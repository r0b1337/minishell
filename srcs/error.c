#include "minishell.h"

/*
**	print_error -	prints unknown command error
*/

int	print_error(char *command)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (-1);
}
