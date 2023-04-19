/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:05:09 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/19 15:47:31 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"   

void	move(t_fdf *data, t_point *a, t_point *b)
{
	a->x += data->mv_lr;
	a->y += data->mv_updn;
	b->x += data->mv_lr;
	b->y += data->mv_updn;
}

void	draw_line(t_fdf *data, t_point a, t_point b)
{
	float	dx;
	float	dy;
	int		maxi;

	z_is(data, &a, &b);
	zooming(data, &a, &b);
	isometric(data, &a, &b);
	move(data, &a, &b);
	dx = b.x - a.x;
	dy = b.y - a.y;
	maxi = max(fabsf(dx), fabsf(dy));
	dx /= maxi;
	dy /= maxi;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		color(&a, &b);
		my_mlx_pixel_put(data, a.x, a.y, a.color);
		a.x += dx;
		a.y += dy;
	}
}

void	draw(t_fdf *data, t_point *a, t_point *b, t_img img)
{
	a->y = -1;
	while (++a->y < data->height)
	{
		a->x = -1;
		while (++a->x < data->widht)
		{
			if (a->x < data->widht - 1)
			{
				b->x = a->x + 1;
				b->y = a->y;
				draw_line(data, *a, *b);
			}
			if (a->y < data->height - 1)
			{
				b->x = a->x;
				b->y = a->y + 1;
				draw_line(data, *a, *b);
			}
		}
	}
}

void	draw_map(t_fdf *data)
{
	t_point	*a;
	t_point	*b;

	data->img.img = mlx_new_image(data->mlx_ptr, data->win_w, data->win_h);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	a = malloc(sizeof(t_point));
	b = malloc(sizeof(t_point));
	draw(data, a, b, data->img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	free(a);
	free(b);
}
