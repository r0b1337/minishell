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

#define EXIST_ERROR 1
#define TYPE_ERROR 2

typedef void (*sig_t) (int);

char	**envp;

void	init_env(char **env);
int	print_env(char **env);
int	env_error(char *arg);
int	env_builtin(int ac, char **av);
char	*get_var_name(char *var);
char	**get_env_var(char **env, char *var);
void	replace_var(char **env, char *var);
void	set_env(char *var, char *content);
char	*get_var_content(char *var);

int	exit_builtin(int ac, char **av);
void	exit_error(int no, char *arg);

char	*get_exec(char **env, char *path);
int	exec_command(char **command, char **env);
void	free_command(char **command);

void	print_prompt(void);
int	print_error(char *command);

int	is_builtin(int ac, char **av);

int	cd_builtin(int ac, char **av);

void	signal_handler(int signo);

#endif
