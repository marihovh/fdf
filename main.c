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

// int	key_hook(int keycode, t_fdf *data, t_img img)
// {
// 	if (keycode == 53)
// 	{
// 		ft_putstr_fd ("The session is over!\n", 1);
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		free(data);
// 		exit(0);
// 		return (0);
// 	}
// 	key_if(keycode, data);
// 	mlx_clear_window(data->mlx_ptr, data->win_ptr);
// 	draw_map(data, img);
// 	return (0);
// }


int key_hook(int keycode, t_fdf *data, t_img img)
{
	if (keycode == 53)
	{
		ft_putstr_fd ("The session is over!\n", 1);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		free(data);
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

int	main(int args, char *argv[])
{
	t_fdf	*data;

	if (args == 2)
	{
		if (open(argv[1], O_RDONLY) == -1)
		{
			printf("the map does not exist!\n");
			return (0);
		}
		data = (t_fdf *)malloc(sizeof(t_fdf));
		data->win_w = 1000;
		data->win_h = 1000;
		data->zoom = 5;
		data->ang = 0.9;
		data->mv_lr = 500;
		data->mv_updn = 500;
		data->mlx_ptr = mlx_init();
		data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_w, data->win_h, argv[1]);
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
