#include "minishell.h"

int	env_builtin(int ac, char **av)
{
	int i;
	int pos;
	int err;
	char *tmp;
	char **tmpenv;

	i = 0;
	err = 0;
	if (ac == 1)
		return (print_env(envp));
	else
	{
	tmpenv = ft_tabcpy(envp);
		while (av[++i])
		{
			if (ft_strchr(av[i], '='))
				replace_var(tmpenv, av[i]);
			else if ((pos = get_env_var(tmpenv, av[i])) != -1)
				ft_putendl(tmpenv[pos]);
			else if ((tmp = get_exec(tmpenv, av[i])) != NULL)
			{
				err = exec_command(&av[i], tmpenv);
				ft_strdel(&tmp);
				break ;
			}
			else
				err = env_error(av[i]);
			if (pos != -1 && !ft_strchr(av[i], '='))
				err = 1;
		}
		if (err == 0)
			print_env(tmpenv);
	free_command(tmpenv);
	}
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
	return ;
}

char	*get_var_content(char *var)
{
	int  pos;
	char **tmp;
	char *ret;

	if ((pos = get_env_var(envp, var)) == -1)
		return (NULL);
	tmp = ft_strsplit(envp[pos], '=');
	ret = ft_strdup(tmp[1]);
	free_command(tmp);
	return (ret);
}

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

char	**add_var(char **env, char *var)
{
	int i;
	int size;
	char **new;

	i = 0;
	size = ft_strlen_tab(env) + 1;
	if ((new = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return (NULL);
	while (i < size - 1)
	{
		new[i] = ft_strdup(env[i]);
		i++;
	}
	new[i] = ft_strdup(var);
	new[i + 1] = NULL;
	free_command(env);
	return (new);
}
