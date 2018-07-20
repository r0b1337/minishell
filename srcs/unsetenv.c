#include "minishell.h"

static void	unset_env(char *var)
{
	int i;
	int j;
	int size;
	char **new;
	int pos;

	i = 0;
	j = 0;
	size = ft_strlen_tab(envp) - 1;
	pos = get_env_var(envp, var);
	if ((new = (char **)malloc(sizeof(char *) * size + 1)) == NULL)
		return ;
	while (envp[j])
	{
		if (ft_strcmp(envp[j], envp[pos]) != 0)
			new[i++] = ft_strdup(envp[j]);
		j++;
	}
	new[i] = NULL;
	free_command(envp);
	envp = new;
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
