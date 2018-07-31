#include "minishell.h"

/*
**	echo_builtin -	clone of echo utility
*/

int	echo_builtin(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		ft_putchar('\n');
	else
	{
		while(av[i])
		{	
			ft_putstr(av[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	return (1);
}
