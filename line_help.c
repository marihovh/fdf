/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 07:35:31 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/19 15:51:04 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	color(t_point *a, t_point *b)
{
	if ((int)(a->z == 0) && (int)(b->z == 0))
		a->color = 0xffffff;
	else if (a->z > 20)
		a->color = a->z + 0x3273a8;
	else
		a->color = 0x3273a8;
}

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	zooming(t_fdf *data, t_point *a, t_point *b)
{
	if (data->zoom > 0)
	{
		a->x *= data->zoom;
		a->y *= data->zoom;
		b->x *= data->zoom;
		b->y *= data->zoom;
	}
	else
		data->zoom = 0;
}

void	isometric(t_fdf *data, t_point *a, t_point *b)
{
	a->x = (a->x - a->y) * cos(data->ang);
	a->y = (a->x + a->y) * sin(data->ang) - a->z;
	b->x = (b->x - b->y) * cos(data->ang);
	b->y = (b->x + b->y) * sin(data->ang) - b->z;
}

void	z_is(t_fdf *data, t_point *a, t_point *b)
{
	a->z = data->z_map[(int)a->y][(int)a->x];
	b->z = data->z_map[(int)b->y][(int)b->x];
}
