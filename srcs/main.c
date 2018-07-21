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
		signal(SIGINT, signal_handler);
		if (get_next_line(STDIN_FILENO, &line) > 0 && !ft_strequ(line, ""))
		{
			command = ft_strsplit(line, ' ');
			if (is_builtin(ft_strlen_tab(command), command) >= 0)
				free_command(command);
			else
			{
				exec_command(command, envp);
				free_command(command);
			}
		}
		ft_strdel(&line);
	}
	(void)ac;
	(void)av;
	return (0);
}

char	*get_exec(char **env, char *path)
{
	char **tmp;
	struct stat s;
	int i;
	int size;
	char *newpath;

	i = 0;
	if (stat(path, &s) == 0 && (s.st_mode & S_IFREG))
		return (path);
	if ((tmp = ft_strsplit(envp[get_env_var(env, "PATH")], '=')) == NULL)
		return (NULL);
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

int	is_builtin(int ac, char **av)
{
	if(ft_strequ(av[0], "echo"))
		return (echo_builtin(ac, av));
	if(ft_strequ(av[0], "cd"))
		return (cd_builtin(ac, av));
	if(ft_strequ(av[0], "setenv"))
		return (setenv_builtin(ac, av));
	if(ft_strequ(av[0], "unsetenv"))
		return (unsetenv_builtin(ac, av));
	if(ft_strequ(av[0], "env"))
		return (env_builtin(ac, av));
	if(ft_strequ(av[0], "exit"))
		return (exit_builtin(ac, av));
	return (-1);
}

void	free_command(char **command)
{
	while(*command)
		ft_strdel(command++);
}
