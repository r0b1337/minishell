/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:42:19 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/06 16:50:32 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	signal_handler -	printing prompt if sigint
**				happens
*/

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		print_prompt();
	}
	return ;
}

/*
**	process_sighandler - handles signals in a process
*/

void	process_sighandler(int signo)
{
	if (signo == SIGINT)
		ft_putchar('\n');
}
