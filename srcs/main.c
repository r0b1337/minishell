/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 03:24:43 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/05 03:25:10 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	char *line;
	char **command;

	line = NULL;
	init_env(env);
	while(1)
	{
		print_prompt();
		if (get_next_line(STDIN_FILENO, &line) > 0 && !ft_strequ(line, ""))
		{
			command = ft_strsplit(line, ' ');
			ft_strdel(&line);
			if (is_builtin(command[0], command))
				continue ;
			exec_command(command);
			free_command(command);
			free(command);
			command = NULL;
			continue ;
		}
		else
			ft_strdel(&line);
	}
	(void)ac;
	(void)av;
	return (0);
}

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

char	*get_env_var(char *var)
{
	int i;

	i = 0;
	while (envp[i] && ft_strcmp(get_var_name(envp[i]), var) != 0)
		i++;
	if(envp[i])
		return (envp[i]);
	else
		return (NULL);
}

char	*get_var_name(char *var)
{
	char *ret;

	ft_strucpy(&ret, var, '=');
	return (ret);
}

char	*get_exec(char *path)
{
	char **tmp;
	struct stat s;
	int i;
	int size;
	char *newpath;
	
	i = 0;
	tmp = ft_strsplit(get_env_var("PATH"), '=');
	tmp = ft_strsplit(tmp[1], ':');
	while (tmp[i])
		i++;
	size = i;
	i = 0;
	while (tmp[i] && (stat((newpath = ft_strjoin(ft_strjoin(tmp[i], "/"), path)), &s) == -1 
		|| !(s.st_mode & S_IFREG)))
		i++;
	if (i == size)
		return (NULL);
	return (newpath);
}

void	print_prompt(void)
{
	ft_putcolor(GREEN, "$> ");
}

int	is_builtin(char *bin, char **av)
{
	if(ft_strequ(bin, "echo"))
		return (1);
	if(ft_strequ(bin, "cd"))
		return (1);
	if(ft_strequ(bin, "setenv"))
		return (1);
	if(ft_strequ(bin, "unsetenv"))
		return (1);
	if(ft_strequ(bin, "env"))
		return (env_builtin(av));
	if(ft_strequ(bin, "exit"))
		return (exit_builtin(av));
	return (0);
}

void	free_command(char **command)
{
	while(*command)
		ft_strdel(command++);
	command = NULL;
}
