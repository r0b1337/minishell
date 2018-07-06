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
	int status;
	pid_t child;
	int i;

	line = NULL;
	i = -1;
	status = 0;
	init_env(env);
	while(1)
	{
		ft_putcolor(GREEN, "(r0b) $> ");
		if (get_next_line(STDIN_FILENO, &line) > 0 && !ft_strequ(line, "\n"))
		{
			command = ft_strsplit(line, ' ');
			ft_strdel(&line);
			child = fork();
			if (child == 0)
				child = execve(get_exec(command[0]), command, envp);
			wait(&child);
			if (child == -1)
			{
				ft_putstr("-minishell: ");
				ft_putstr(command[0]);
				ft_putstr(": command not found\n");
			}
			while (command[++i])
				ft_strdel(&command[i]);
			i = -1;
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

void	print_env(void)
{
	int i;

	i = 0;
	while (envp[i])
		ft_putendl(envp[i++]);
}

char	*get_env_var(char *var)
{
	int i;

	i = 0;
	while (ft_strcmp(get_var_name(envp[i]), var) != 0)
		i++;
	return (envp[i]);
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
