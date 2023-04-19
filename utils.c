/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 15:38:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/19 15:46:54 by marihovh         ###   ########.fr       */
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

int	key_hook(int keycode, t_fdf *data, t_img img)
{
	int	i;

	i = 0;
	if (keycode == 53)
	{
		ft_putstr_fd ("The session is over!\n", 1);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		while (i < data->height)
			free(data->z_map[i++]);
		free(data);
		exit(0);
		return (0);
	}
	key_if(keycode, data);
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	draw_map(data);
	return (0);
}

int	key_cross(t_fdf *data, int keycode, t_img img)
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
		dst = data->img.addr + (y * data->img.line_length + x
				* (data->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}
