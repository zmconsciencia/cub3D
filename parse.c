/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svalente <svalente@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 15:59:50 by jabecass          #+#    #+#             */
/*   Updated: 2023/11/29 16:05:27 by svalente         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int mapX = 8, mapY = 8, mapS = 64;
// int initial_map[8][8] = {
//     {1,1,1,1,1,1,1,1},
//     {1,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,1},
//     {1,0,0,1,1,0,0,1},
//     {1,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,1},
//     {1,0,0,0,0,0,0,1},
//     {1,1,1,1,1,1,1,1},
//     };

// void allocateMap() {
//     data()->map = (int **)malloc(mapY * sizeof(int *));
//     for (int i = 0; i < mapY; i++) {
//         data()->map[i] = (int *)malloc(mapX * sizeof(int));
//     }
//     for (int i = 0; i < mapY; i++) {
//         for (int j = 0; j < mapX; j++) {
//             data()->map[i][j] = initial_map[i][j];
//         }
//     }
// }

// void paintFloor()
// {
//     int x;
//     int y;
//     int size = mapS - 2;

//     for (y = 0; y < mapY * mapS; y++) {
//         for (x = 0; x < mapX * mapS; x++) {
//             my_mlx_pixel_put(data()->image, x, y, 0x00333333);
//         }
//     }
//     for (y = 0; y < mapY; y++) {
//         for (x = 0; x < mapX; x++) {
//             int color = (data()->map[y][x] == 1) ? 0xFFFFFF : 0x000000;
//             for (int i = 0; i < size; i++) {
//                 for (int j = 0; j < size; j++) {
//                     my_mlx_pixel_put(data()->image, x * mapS + i, y * mapS + j, color);
//                 }
//             }
//         }
//     }
// }