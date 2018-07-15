#include "libft.h"

void	ft_putstr_tab(char **tab)
{
	while (*tab)
		ft_putendl(*tab++);
}
