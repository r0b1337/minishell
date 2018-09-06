/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:53:58 by rdurst            #+#    #+#             */
/*   Updated: 2018/09/06 17:01:44 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	print_error -	prints unknown command error
*/

int	print_error(char *command)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (-1);
}
