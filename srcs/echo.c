/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:53:48 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/05 19:53:49 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	echo_builtin -	clone of echo utility
*/

int	echo_builtin(int ac, char **av)
{
	int i;

	i = 1;
	if (ac == 1)
		ft_putchar('\n');
	else
	{
		while (av[i])
		{
			ft_putstr(av[i++]);
			ft_putchar(' ');
		}
		ft_putchar('\n');
	}
	return (1);
}
