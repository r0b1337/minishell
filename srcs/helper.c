/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 16:20:06 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/06 16:23:14 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	env_help - help function needed to pass 25line
**				norm rule
*/

char	**env_help(char **av, char **tmpenv)
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
