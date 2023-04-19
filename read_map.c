/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:06:16 by marihovh          #+#    #+#             */
/*   Updated: 2023/04/19 21:00:08 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *file_name)
{
	int		height;
	int		fd;
	char	*str;

	fd = open(file_name, O_RDONLY);
	height = 0;
	str = get_next_line(fd);
	if (!str)
		return (0);
	while (str)
	{
		height++;
		free(str);
		str = get_next_line(fd);
	}
	close (fd);
	return (height);
}

int	get_widht(char *file_name)
{
	int		widht;
	int		fd;
	char	*line;

	widht = 0;
	fd = open(file_name, O_RDONLY);
	line = get_next_line(fd);
	widht = ft_word_cnt(line, ' ');
	free(line);
	close(fd);
	return (widht);
}

void	fill(char *line, int *z_map)
{
	char	**splited;
	int		i;

	i = -1;
	splited = ft_split(line, ' ');
	while (splited[++i])
	{
		z_map[i] = ft_atoi(splited[i]);
		free(splited[i]);
	}
	free(splited);
}

void	read_map(char *file_name, t_fdf *data)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(file_name, O_RDONLY);
	i = -1;
	data->height = get_height(file_name);
	data->widht = get_widht(file_name);
	data->z_map = (int **)malloc(sizeof(int *) * (data->height));
	while (++i < data->height)
		data->z_map[i] = (int *)malloc(sizeof(int *) * (data->widht));
	i = -1;
	while (++i < data->height)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		fill(line, data->z_map[i]);
		free(line);
	}
	close(fd);
}
