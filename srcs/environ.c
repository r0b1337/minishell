#include "minishell.h"

void	init_env(char **env)
{
	int i;

	i = 0;
	while(env[i])
		i++;
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	envp[i] = NULL;
	i = -1;
	while (env[++i])
		envp[i] = ft_strdup(env[i]);
	return ;
}

int	get_env_var(char **env, char *var)
{
	int i;

	i = 0;
	while (env[i] && ft_strcmp(get_var_name(env[i]), var) != 0)
		i++;
	if(env[i])
		return (i);
	else
		return (-1);
}

char	*get_var_name(char *var)
{
	char *ret;

	if (!var || !*var)
		return (NULL);	
	if (var[0] == '=')
		return (var);
	ft_strucpy(&ret, var, '=');
	return (ret);
}
