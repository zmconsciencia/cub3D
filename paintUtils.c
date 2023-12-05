/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paintUtils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:06:48 by jabecass          #+#    #+#             */
/*   Updated: 2023/12/05 14:02:03 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    paintFloor(int color, int x, int drawEnd)
{
    int i = drawEnd;
    if (drawEnd >= data()->window.h)
        return ;
    while (i < data()->window.h)
    {
        my_mlx_pixel_put(data()->buffer, x, i, color);
        i++;
    }
}

void    paintCeiling(int color, int x, int drawStart)
{
    int i = 0;
    if (drawStart <= 0)
        return ;
    while (i < drawStart)
    {
        my_mlx_pixel_put(data()->buffer, x, i, color);
        i++;
    }
}

void    paintToWindow(void)
{
    int y;
    int x;

    x = 0;
    y = 0;
    while (y < data()->window.h)
    {
        x = 0;
        while(x < data()->window.w)
        {
            my_mlx_pixel_put(data()->image, x, y, my_mlx_pixel_get((data())->buffer, x, y));
            x++;    
        }
        y++;
    }
}

void    clearScreen(void)
{
    int x;
    int y;

    for (y = 0; y < data()->window.h; y++) {
        for (x = 0; x < data()->window.w; x++) {
            int color = 0x000000;
            my_mlx_pixel_put(data()->buffer, x, y, color);
        }
    }
}