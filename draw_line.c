/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:05:09 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/08 08:13:01 by marihovh         ###   ########.fr       */
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

void	draw_line(t_fdf *data, t_point a, t_point b, t_img img)
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
		my_mlx_pixel_put(&img, a.x, a.y, a.color);
		a.x += dx;
		a.y += dy;
	}
}

void	draw(t_fdf *data, t_point *a, t_point *b, t_img img)
{
	a->x = -1;
	while (++a->x < data->widht)
	{
		if (a->x < data->widht - 1)
		{
			b->x = a->x + 1;
			b->y = a->y;
			draw_line(data, *a, *b, img);
		}
		if (a->y < data->height - 1)
		{
			b->x = a->x;
			b->y = a->y + 1;
			draw_line(data, *a, *b, img);
		}
	}
}

void	draw_map(t_fdf *data, t_img img)
{
	t_point	*a;
	t_point	*b;

	a = malloc(sizeof(t_point));
	b = malloc(sizeof(t_point));
	a->y = -1;
	while (++a->y < data->height)
		draw(data, a, b, img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img.img, 0, 0);
	free(a);
	free(b);
}