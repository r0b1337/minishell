#include "minishell.h"

static void	change_cwd(char *cwd)
{
	char buf[4096];

	if (!cwd)
	{
		chdir(get_var_content("HOME"));
		getcwd(buf, 4096);
		set_env("OLDPWD", get_var_content("PWD"));
		set_env("PWD", buf);
	}
	else
	{
		chdir(cwd);
		set_env("OLDPWD", get_var_content("PWD"));
		set_env("PWD", cwd);
	}
}

static void	cd_error(int no, char *arg)
{
	if (no == EXIST_ERROR)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	else if (no == TYPE_ERROR)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": Not a directory\n", STDERR_FILENO);
	}
}

static int	is_dir(char *path)
{
	struct stat s;

	stat(path, &s);
	if (s.st_mode & S_IFDIR)
		return (1);
	return (0);
}

static char	*prev_cwd(char *path)
{
	char buf[4096];
	int i;

	i = 0;
	getcwd(buf, 4096);
	while (buf[i])
		i++;
	while (buf[i - 1] && buf[i - 1] != '/')
		buf[i -- - 1] = '\0';
	return (ft_strjoin(buf, &path[3]));
}

static char	*parse_path(char *path)
{
	char *ret;
	int	i;

	i = 0;
	if (path[0] == '.' && path[1] != '.')
		ret = ft_strjoin(get_var_content("PWD"), &path[1]);
	else if (path[0] == '~')
		ret = ft_strjoin(get_var_content("HOME"), &path[1]);
	else if (path[0] == '.' && path[1] == '.')
		ret = prev_cwd(path);
	else
		ret = ft_strdup(path);
	while (ret[i])
		i++;
	while (ret[i - 1] && ret[i - 1] == '/' && i > 1)
		ret[i-- - 1] = '\0';
	return (ret);
}

int	cd_builtin(int ac, char **av)
{
	char	*parsed;

	if (ac == 1)
		change_cwd(NULL);
	else
	{
		parsed = parse_path(av[1]);
		if (!ft_strcmp(av[1], "--"))
			change_cwd(get_var_content("OLDPWD"));
		else if (access(parsed, F_OK) == -1)
			cd_error(EXIST_ERROR, av[1]);
		else if (!is_dir(parsed))
			cd_error(TYPE_ERROR, av[1]);
		else
			change_cwd(parsed);
		ft_strdel(&parsed);
	}
	return (1);
}
