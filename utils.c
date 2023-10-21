#include "cub3d.h"

void	ft_error(char *err)
{
	ft_putstr_fd(RED"Error\n"RST, 2);
	ft_putstr_fd(err, 2);
	exit(-1);
}

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_putstr_fd(array[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}