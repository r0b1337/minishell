/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdurst <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/05 03:17:58 by rdurst            #+#    #+#             */
/*   Updated: 2018/07/05 03:24:37 by rdurst           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "libft.h"
#include "get_next_line.h"

char	**envp;

void	init_env(char **env);
void	print_env(void);
char	*get_env_var(char *var);
char	*get_var_name(char *var);
char	*get_exec(char *path);

#endif
