/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:14:46 by svalente          #+#    #+#             */
/*   Updated: 2024/01/10 16:54:00 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file_access(char *file)
{
	if (access(file, R_OK) == -1)
		return (0);
	return (1);
}

int files_access()
{
	if (!check_file_access(data()->map.textures.north.path) || 
		!check_file_access(data()->map.textures.south.path) ||
		!check_file_access(data()->map.textures.west.path) ||
		!check_file_access(data()->map.textures.east.path))
		return (0);
	return (1);
}
