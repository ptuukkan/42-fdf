/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	check_hex(char **line, int *i)
{
	int	n;

	n = 0;
	if ((*line)[*i] == ' ' || (*line)[*i] == '\0')
		return (0);
	if (ft_strncmp(*line + *i, ",0x", 3) == 0 ||
		ft_strncmp(*line + *i, ",0X", 3) == 0)
	{
		*i += 3;
		while (ft_ishex((*line)[*i]))
		{
			*i += 1;
			n++;
		}
		if (((*line)[*i] == '\0' || (*line)[*i] == ' ') && n > 0 && n <= 6)
			return (1);
		*line = *line + n + 4;
		*i = *i - n - 4;
		return (0);
	}
	else
		return (0);
}

static int	count_numbers(char *line)
{
	int	numbers;
	int	i;

	numbers = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			i++;
		else if (line[i] == '-')
		{
			if (!ft_isdigit(line[++i]))
				ft_exiterror("Invalid characters in file", 4, 2);
		}
		else if (ft_isdigit(line[i]))
		{
			while (ft_isdigit(line[i]))
				i++;
			check_hex(&line, &i);
			numbers++;
		}
		else
			ft_exiterror("Invalid characters in map", 4, 2);
	}
	return (numbers);
}

static void	read_map_info(t_map *map, char *file)
{
	int		fd;
	int		lines;
	int		line_length;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exiterror("Cannot open file", 2, 2);
	lines = 0;
	line_length = 0;
	while (get_next_line(fd, &line))
	{
		if (line == NULL)
			ft_exiterror("Cannot read file", 2, 2);
		if (lines == 0)
			line_length = count_numbers(line);
		else if (count_numbers(line) != line_length)
			ft_exiterror("Invalid line length", 3, 2);
		lines++;
		ft_strdel(&line);
	}
	map->width = line_length;
	map->height = lines;
	close(fd);
}

static void	read_vertices(t_fdf *fdf, t_vec4 *vertices, char *line, int y)
{
	int			i;
	int			n;
	intmax_t	number;

	i = 0;
	while (get_next_number(&line, &number))
	{
		vertices[i].x = (double)i;
		vertices[i].y = (double)y;
		vertices[i].z = (double)number;
		vertices[i].w = 1.0;
		if (number > fdf->map.peak)
			fdf->map.peak = number;
		if (number < fdf->map.bottom)
			fdf->map.bottom = number;
		n = 0;
		vertices[i].color.set = 0;
		if (check_hex(&line, &n))
			vertices[i].color = read_color(&line);
		i++;
	}
}

void		read_file(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		i;

	fdf->map.peak = INT64_MIN;
	fdf->map.bottom = INT64_MAX;
	read_map_info(&fdf->map, file);
	if (!(fdf->map.vertices = (t_vec4 **)ft_memalloc(sizeof(t_vec4 *) *\
		fdf->map.height)))
		ft_exiterror("Memory allocation error", 5, 2);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exiterror("Cannot open file", 2, 2);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(fdf->map.vertices[i] = (t_vec4 *)ft_memalloc(sizeof(t_vec4) *\
			fdf->map.width)))
			ft_exiterror("Memory allocation error", 5, 2);
		read_vertices(fdf, fdf->map.vertices[i], line, i);
		ft_strdel(&line);
		i++;
	}
}
