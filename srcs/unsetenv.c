#include "minishell.h"

static void	unset_env(char *varname)
{
	char **tmp;
	if (!(tmp = get_env_var(envp, varname)))
		return ;
	ft_strdel(tmp);
	*tmp = ft_strdup("");
	return ;
}

int	unsetenv_builtin(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		ft_putstr_fd("unsetenv: not enough arguments\n", STDERR_FILENO);
	else
		while(av[i])
			unset_env(av[i++]);
	return (1);
}
