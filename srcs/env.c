#include "minishell.h"

int	env_builtin(char **av)
{
	int i;
	char *var;

	i = 0;
	if (!av[1])
		return (print_env());
	else
	{
		while (av[++i])
		{
			if (ft_strchr(av[i], '='))
			{
				print_env();
				ft_putendl(av[i]);
			}
			else
				if ((var = get_env_var(av[i])) != NULL)
					ft_putendl(var);
				else
					env_error(av[i]);
		}
	}
	return (1);
}

int	print_env(void)
{
	int i;

	i = 0;
	while (envp[i])
		ft_putendl(envp[i++]);
	return (1);
}

void	env_error(char *arg)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}
