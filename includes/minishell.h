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

typedef void (*sig_t) (int);

char	**envp;

void	init_env(char **env);
int	print_env(char **env);
int	env_error(char *arg);
int	env_builtin(int ac, char **av);
void	env_add_var(char **env, char *var);
int	exit_builtin(int ac, char **av);
void	exit_error(int no, char *arg);
char	**get_env_var(char **env, char *var);
char	*get_var_name(char *var);
char	*get_exec(char **env, char *path);
void	print_prompt(void);
int	print_error(char *command);
int	exec_command(char **command, char **env);
int	is_builtin(int ac, char **av);
void	free_command(char **command);
void	signal_handler(int signo);

#endif
