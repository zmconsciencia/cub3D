/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 16:09:18 by svalente          #+#    #+#             */
/*   Updated: 2023/11/30 11:10:51 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_free(char *str)
{
	if (str)
		err_msg(str);
	if (data()->map.file)
		free_matrix(data()->map.file);
	if (data()->map.textures.north)
		free(data()->map.textures.north);
	if (data()->map.textures.south)
		free(data()->map.textures.south);
	if (data()->map.textures.west)
		free(data()->map.textures.west);
	if (data()->map.textures.east)
		free(data()->map.textures.east);
	if (data()->map.map)
		free_matrix(data()->map.map);
	exit (0);
}