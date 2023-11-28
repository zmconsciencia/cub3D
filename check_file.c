/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:27:18 by svalente          #+#    #+#             */
/*   Updated: 2023/11/28 11:29:13 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	err_msg(char *str)
{
	int i = -1;
	
	while (str[++i])
		write(2, &str[i], 1);
}

int	check_lines(char *av)
{
	
}

int	parser(int ac, char **av)
{
	if (ac != 2)
		return (err_msg("Wrong number of arguments\n"));
	check_lines(av[1]);
}