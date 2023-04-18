/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:06:02 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/08 07:30:38 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_if(int keycode, t_fdf *data)
{
	if (keycode == 123 || keycode == 0)
		data->mv_lr -= 10;
	if (keycode == 124 || keycode == 2)
		data->mv_lr += 10;
	if (keycode == 126 || keycode == 13)
		data->mv_updn -= 10;
	if (keycode == 125 || keycode == 1)
		data->mv_updn += 10;
	if (keycode == 69)
		data->zoom += 1;
	if (keycode == 78)
		data->zoom -= 1;
	if (keycode == 91)
		data->ang += 0.1;
	if (keycode == 84)
		data->ang -= 0.1;
}

int key_hook(int keycode, t_fdf *data, t_img img)
{
	if (keycode == 53)
	{
		ft_putstr_fd ("The session is over!\n", 1);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		int i = -1;
		while (++i < data->height)
			free(data->z_map[i]);
		free(data);
		 system("leaks fdf");
		exit(0);
		return (0);
	}
	key_if(keycode, data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw_map(data);
	return (0);
}

int key_cross(t_fdf *data, int keycode, t_img img)
{
	ft_putstr_fd ("The session is over!\n", 1);
	(void)keycode;
	exit(0);
}

void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color)
{
	char	*dst;

	if (x > 0 && y > 0 && data->win_w > x && data->win_h > y)
	{
		dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));
		*(unsigned int*)dst = color;
	}
}

void check_data(t_fdf *data)
{
	if (data->height == 1 && data->widht == 1)
	{
		ft_putstr_fd ("Wrong form of map!\n", 1);
		free(data);
		exit(0);
	}
}

void init(t_fdf *data)
{
	data->win_w = 1500;
	data->win_h = 1500;
	data->zoom = 10;
	data->ang = 0.9;
	data->mv_lr = 500;
	data->mv_updn = 500;
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_w, data->win_h, "Wireframe model");
}

void check_map(const char *file_name)
{
	int fd;
	int i;

	i = 0;
	fd = open(file_name, O_RDONLY);
	i = ft_strlen(file_name) - 4;
	file_name += i;
	if (fd == -1)
	{
		ft_putstr_fd ("the map does not exist!\n", 1);
		exit (0);
	}
	if (ft_strncmp(file_name, ".fdf", 4) != 0)
	{
		ft_putstr_fd ("Wrong form of map!\n", 1);
		exit (0);
	}
	if (!get_next_line(fd))
	{
		ft_putstr_fd ("Wrong form of map!\n", 1);
		exit (0);
	}
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