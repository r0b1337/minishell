#include "minishell.h"

int	env_builtin(int ac, char **av)
{
	int i;
	char **var;
	int err;
	char **tmpenv;
	char *bin;

	i = 0;
	tmpenv = ft_tabcpy(envp);
	err = 0;
	if (ac == 1)
		return (print_env());
	else
	{
		while (av[++i])
		{
			if (ft_strchr(av[i], '='))
				env_add_var(tmpenv, av[i]);
			else if ((var = get_env_var(tmpenv, av[i])) != NULL)
			{
				err = 1;
				ft_putendl(*var);
			}
			else if ((bin = get_exec(tmpenv, av[i])) != NULL)
			{
				err = 1;
				exec_command(&av[i], tmpenv);
				break ;
			}
			else
			{
				err = 1;
				env_error(av[i]);
			}
		}
		if (err == 0)
			while (*tmpenv)
				ft_putendl(*tmpenv++);
			
	}
	free_command(tmpenv);
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

void	env_add_var(char **env, char *var)
{
	int i;
	char **tmp;

	i = 0;
	if ((tmp = get_env_var(env, get_var_name(var))) != NULL)
		*tmp = ft_strdup(var);
	else
	{
		while (env[i])
			i++;
		env[i] = ft_strdup(var);
	}
}
