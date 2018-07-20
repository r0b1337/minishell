#include "minishell.h"

int	setenv_builtin(int ac, char **av)
{
	if (ac == 1)
		print_env(envp);
	if (ac == 2)
		set_env(av[1], "");
	if (ac == 3)
		set_env(av[1], av[2]);
	else if (ac > 3)
		ft_putstr_fd("setenv: Too many arguments\n", STDERR_FILENO);
	return (1);
}
