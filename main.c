/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:06:02 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/19 20:59:28 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_data(t_fdf *data)
{
	if (data->height == 1 && data->widht == 1)
	{
		ft_putstr_fd ("Wrong form of map!\n", 1);
		free(data);
		exit(0);
	}
}

void	init(t_fdf *data)
{
	data->win_w = 1500;
	data->win_h = 1500;
	data->zoom = 10;
	data->ang = 0.9;
	data->mv_lr = 500;
	data->mv_updn = 500;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_w,
			data->win_h, "Wireframe model");
}

void	check_map(const char *file_name)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(file_name, O_RDONLY);
	i = ft_strlen(file_name) - 4;
	file_name += i;
	if (fd == -1)
	{
		ft_putstr_fd ("the map does not exist!\n", 1);
		exit (0);
	}
	line = get_next_line(fd);
	if (!line || (ft_strncmp(file_name, ".fdf", 4) != 0))
	{
		ft_putstr_fd ("Wrong form of map!\n", 1);
		exit (0);
	}
	free(line);
	close(fd);
}

int	main(int args, char *argv[])
{
	t_fdf	*data;

	if (args == 2)
	{
		check_map(argv[1]);
		data = (t_fdf *)malloc(sizeof(t_fdf));
		if (!data)
			return (0);
		init(data);
		check_data(data);
		read_map(argv[1], data);
		draw_map(data);
		mlx_key_hook(data->win_ptr, key_hook, data);
		mlx_hook(data->win_ptr, 17, (1L << 17), key_cross, data);
		mlx_loop(data->mlx_ptr);
	}
	else
		ft_putstr_fd ("There is a wrong count of arguments!\n", 1);
	return (0);
}
