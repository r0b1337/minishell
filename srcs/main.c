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
		if (get_next_line(STDIN_FILENO, &line) != -1 && !ft_strequ(line, ""))
		{
			command = ft_strsplit(line, ' ');
			if (is_builtin(ft_strlen_tab(command), command) >= 0)
			{
				ft_strdel(&line);
				free_command(command);
				continue ;
			}
			else
				exec_command(command, envp);
			free_command(command);
		}
		ft_strdel(&line);
	}
	(void)ac;
	(void)av;
	return (0);
}

static char	*path_to_bin(char *path, char *bin)
{
	char *ret;
	char *tmp;

	tmp = ft_strjoin(path, "/");
	ret = ft_strjoin(tmp, bin);
	ft_strdel(&tmp);
	return (ret);
}

char	*get_exec(char **env, char *path)
{
	char **tmp;
	char **tmp2;
	struct stat s;
	int i;
	int size;
	char *newpath;

	i = 0;
	if (stat(path, &s) == 0 && (s.st_mode & S_IFREG))
		return (path);
	if ((tmp2 = ft_strsplit(env[get_env_var(env, "PATH")], '=')) == NULL)
		return (NULL);
	if ((tmp = ft_strsplit(tmp2[1], ':')) == NULL)
	{
		free_command(tmp2);
		return (NULL);
	}
	while (tmp[i])
		i++;
	size = i;
	i = 0;
	while (tmp[i] && ((stat((newpath = path_to_bin(tmp[i], path)), &s)) == -1
				|| !(s.st_mode & S_IFREG)))
	{
		i++;
		ft_strdel(&newpath);
	}
	free_command(tmp);
	free_command(tmp2);
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
	int i;

	i = 0;
	while(command[i])
		ft_strdel(&command[i++]);
	free(command);
	command = NULL;
}
