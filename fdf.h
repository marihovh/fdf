/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 03:49:50 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/08 08:20:31 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "macos/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "/Users/marihovh/Desktop/42-fdf/libft/libft.h"
# include "/Users/marihovh/Desktop/42-fdf/fdf.h"
# include <stdio.h>

typedef struct s_fdf	t_fdf;
typedef struct s_point	t_point;
typedef struct s_img	t_img;

struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct	s_fdf
{
	int		height;
	int		widht;
	int		**z_map;
	int		zoom;
	int		mv_lr;
	int		mv_updn;
	float	ang;
	int 	win_w;
	int		win_h;
	t_img	img;
	void	*mlx_ptr;
	void	*win_ptr;
};

struct s_point
{
	float			x;
	float			y;
	float			z;
	unsigned int	color;
};

int		max(int a, int b);
void	draw_map(t_fdf *data);
char	*get_next_line(int fd);
int		get_widht(char *file_name);
int		get_height(char *file_name);
void	color(t_point *a, t_point *b);
int		ft_word_cnt(char const *s, char c);
int		ft_gradient(t_point *a, t_point *b);
void	read_map(char *file_name, t_fdf *data);
void	z_is(t_fdf *data, t_point *a, t_point *b);
void	zooming(t_fdf *data, t_point *a, t_point *b);
void	draw_line(t_fdf *data, t_point a, t_point b);
void	isometric(t_fdf *data, t_point *a, t_point *b);
void	my_mlx_pixel_put(t_fdf *data, int x, int y, int color);

#endif