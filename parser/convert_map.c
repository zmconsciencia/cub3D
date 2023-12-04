/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:23:19 by svalente          #+#    #+#             */
/*   Updated: 2023/12/04 09:21:55 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void convert_matrix_char_to_int(void)
{
	int i;
	int j;

	if (data()->map.map)
	{
		j = matrix_size(data()->map.map, 'y');
		data()->map.map_int = ft_calloc(j + 1, sizeof(int *));
		j = -1;
		while (data()->map.map[++j])
		{
			i = matrix_size(data()->map.map, 'x');
			data()->map.map_int[j] = ft_calloc(i + 1, sizeof(int));
			i = -1;
			while (data()->map.map[j][++i])
				data()->map.map_int[j][i] = ft_atoi(&data()->map.map[j][i]);
			data()->map.map_int[j][i] = 0;
		}
		data()->map.map_int[j] = NULL;
	}
}
