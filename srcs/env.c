#include "minishell.h"

int	env_builtin(int ac, char **av)
{
	int i;
	char **var;
	int err;
	char **tmpenv;

	i = 0;
	tmpenv = ft_tabcpy(envp);
	err = 0;
	if (ac == 1)
		return (print_env(tmpenv));
	else
	{
		while (av[++i])
		{
			if (ft_strchr(av[i], '='))
				replace_var(tmpenv, av[i]);
			else if ((var = &tmpenv[get_env_var(tmpenv, av[i])]) != NULL)
				ft_putendl(*var);
			else if (get_exec(tmpenv, av[i]) != NULL)
			{
				err = exec_command(&av[i], tmpenv);
				break ;
			}
			else
				err = env_error(av[i]);
		}
		if (err == 0)
			while (*tmpenv)
				ft_putendl(*tmpenv++);

	}
	free_command(tmpenv);
	return (1);
}

int	print_env(char **env)
{
	int i;

	i = -1;
	while (env[++i])
		if(ft_strcmp(env[i], "") != 0)
			ft_putendl(env[i]);
	return (1);
}

int	env_error(char *arg)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	return (1);
}

void	replace_var(char **env, char *var)
{
	int i;
	char **tmp;

	i = 0;
	if ((tmp = &env[get_env_var(env, get_var_name(var))]) != NULL)
		*tmp = ft_strdup(var);
	else
	{
		while (env[i])
			i++;
		env[i] = ft_strdup(var);
	}
}

char	*get_var_content(char *var)
{
	char **tmpvar;
	char **tmp;

	if (!(tmpvar = &envp[get_env_var(envp, var)]))
		return (NULL);
	tmp = ft_strsplit(*tmpvar, '=');
	return (tmp[1]);
}

void	set_env(char *var, char *content)
{
	char *tmp;
	int  i;
	int  pos;

	i = 0;
	tmp = ft_strjoin(ft_strjoin(var, "="), content);
	if ((pos = get_env_var(envp, var)) == -1)
		add_var(tmp);
	else
	{
		ft_strdel(&envp[pos]);
		envp[pos] = ft_strdup(tmp);
	}
	ft_strdel(&tmp);
}

void	add_var(char *var)
{
	int i;
	int size;
	char **new;

	i = 0;
	size = ft_strlen_tab(envp) + 1;
	if ((new = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return ;
	while (i < size - 1)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	new[i + 1] = NULL;
	free_command(envp);
	envp = new;
}
