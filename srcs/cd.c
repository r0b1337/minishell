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

int	cd_builtin(int ac, char **av)
{
	if (ac == 1)
		change_cwd(NULL);
	else if (!ft_strcmp(av[1], "--"))
		change_cwd(get_var_content("OLDPWD"));
	else if (access(av[1], F_OK) == -1)
		cd_error(EXIST_ERROR, av[1]);
	else if (!is_dir(av[1]))
		cd_error(TYPE_ERROR, av[1]);
	else
		change_cwd(av[1]);
	return (1);
}
