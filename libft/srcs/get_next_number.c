/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptuukkan <ptuukkan@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:06:03 by ptuukkan          #+#    #+#             */
/*   Updated: 2020/01/29 14:06:04 by ptuukkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_next_number(char **line, int *number)
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
