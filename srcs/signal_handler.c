/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:42:19 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/05 19:42:20 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	signal_handler -	printing prompt if SIGINT
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
