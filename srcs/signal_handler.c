#include "minishell.h"

/*
**	signal_handler -	printing prompt if SIGINT
**				happens
*/

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		print_prompt();
	}
	return ;
}
