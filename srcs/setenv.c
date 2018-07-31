#include "minishell.h"

/*
**	set_env -	like add_var() but with format
**			setenv FOO BAR
*/

void	set_env(char *var, char *content)
{
	char *tmp;
	char *tmp2;
	int  i;
	int  pos;

	i = 0;
	tmp2 = ft_strjoin(var, "=");
	tmp = ft_strjoin(tmp2, content);
	if ((pos = get_env_var(envp, var)) == -1)
		envp = add_var(envp, tmp);
	else
	{
		ft_strdel(&envp[pos]);
		envp[pos] = ft_strdup(tmp);
	}
	ft_strdel(&tmp);
	ft_strdel(&tmp2);
}

/*
**	replace_var -	replace an existing var's content
**			or creating a new var with content
*/

char	**replace_var(char **env, char *var)
{
	int i;
	int pos;
	char **tmp;

	i = 0;
	tmp = ft_strsplit(var, '=');
	if ((pos = get_env_var(env, tmp[0])) != -1)
	{
		ft_strdel(&env[pos]);
		env[pos] = ft_strdup(var);
	}
	else
		env = add_var(env, var);
	free_command(tmp);
	return (env);
}

/*
**	setenv_builtin -	clone of setenv utility
*/

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
