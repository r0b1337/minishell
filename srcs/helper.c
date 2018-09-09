/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 16:20:06 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/09 02:00:49 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	env_help - help function needed to pass 25line
**				norm rule
*/

char			**env_help(char **av, char **tmpenv)
{
	char	*tmp;
	int		err;
	int		i;

	i = -1;
	err = 0;
	while (av[++i])
	{
		if (ft_strchr(av[i], '='))
			tmpenv = replace_var(tmpenv, av[i]);
		else if ((tmp = get_exec(tmpenv, av[i])) != NULL)
		{
			err = exec_command(&av[i], tmpenv);
			ft_strdel(&tmp);
			break ;
		}
		else
			err = env_error(av[i]);
		if (!ft_strchr(av[i], '='))
			err = 1;
	}
	if (err == 0)
		print_env(tmpenv);
	return (tmpenv);
}

/*
**	count_args - counts how many args we have
**		without spaces and '\t'
*/

static int		count_args(char *s)
{
	int words;
	int i;

	i = 0;
	words = 0;
	while (s[i])
	{
		if ((s[i] != ' ' && s[i] != '\t')
				&& ((s[i - 1] == ' ' || s[i - 1] == '\t') || i == 0))
			words++;
		i++;
	}
	return (words);
}

/*
**	arg_len - return the size until next ' ' or '\t' for malloc
*/

static int		arg_len(char *s)
{
	int len;

	len = 0;
	while (*s && (*s != ' ' && *s != '\t'))
	{
		len++;
		s++;
	}
	return (len);
}

/*
**	parse_command - our command parser, format
**		get_next_line() output to argv
*/

char			**parse_command(char *s)
{
	int		tab_size;
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	tab_size = count_args(s);
	if ((tab = (char **)malloc(sizeof(char *) * tab_size + 1)) == NULL)
		return (NULL);
	while (tab_size--)
	{
		while ((*s == ' ' || *s == '\t') && *s)
			s++;
		if ((tab[i++] = ft_strsub(s, 0, arg_len(s))) == NULL)
			return (NULL);
		s += arg_len(s);
	}
	tab[i] = NULL;
	return (tab);
}
