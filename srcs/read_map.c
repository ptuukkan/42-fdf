/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 12:00:53 by ptuukkan          #+#    #+#             */
/*   Updated: 2019/12/19 12:00:54 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		count_numbers(char *line)
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
				ft_exiterror("Invalid characters in map", 4, 2);
		}
		else if (ft_isdigit(line[i]))
		{
			while (ft_isdigit(line[i]))
				i++;
			numbers++;
		}
		else
			ft_exiterror("Invalid characters in map", 4, 2);
	}
	return (numbers);
}

void	read_map_info(t_map *map, char *file)
{
	int		fd;
	int		lines;
	int		line_length;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exiterror("Cannot open file", 2, 2);
	lines = 0;
	while (get_next_line(fd, &line))
	{
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

int		get_next_number(char **line, int *number)
{
	int	found;

	found = 0;
	*number = ft_atoi(*line);
	while (**line != '\0' && ft_isdigit(**line) == 0)
		(*line)++;
	while (ft_isdigit(**line))
	{
		(*line)++;
		found = 1;
	}
	if (found)
		return (1);
	return (0);
}

void	read_altitude(int *arr, char *line)
{
	int		i;
	int		number;

	i = 0;
	while (get_next_number(&line, &number))
	{
		arr[i] = number;
		i++;
	}
}

void	read_map(char *file, t_fdf *fdf)
{
	int		fd;
	char	*line;
	int		i;

	read_map_info(&fdf->map, file);
	if (!(fdf->map.altitude = (int **)ft_memalloc(sizeof(int *) *\
		fdf->map.height)))
		ft_exiterror("Memory allocation error", 5, 2);
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_exiterror("Cannot open file", 2, 2);
	i = 0;
	while (get_next_line(fd, &line))
	{
		if (!(fdf->map.altitude[i] = (int *)ft_memalloc(sizeof(int) *\
			fdf->map.width)))
			ft_exiterror("Memory allocation error", 5, 2);
		read_altitude(fdf->map.altitude[i], line);
		ft_strdel(&line);
		i++;
	}
}
