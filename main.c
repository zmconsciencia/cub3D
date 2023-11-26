/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabecass <jabecass@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 11:12:54 by jabecass          #+#    #+#             */
/*   Updated: 2023/11/26 16:58:59 by jabecass         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*data(void)
{
	static t_data	data;

	return (&data);
}

void draw_line(int x0, int y0, int x1, int y1);

int bigX = 8, bigY = 8, mSize = 64;

int FixAng(int a){ if(a>359){ a-=360;} if(a<0){ a+=360;} return a;}
float degToRad(int a) { return a*PI/180.0;}

float dist(float ax, float ay, float bx, float by, float ang) {return (sqrt((bx-ax) *  (bx-ax) + (by-ay) *  (by-ay)));}

void mlx_draw_line(int x0, int y0, int x1, int y1, int thickness, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        for (int i = 0; i < thickness; i++)
        {
            my_mlx_pixel_put(data()->image, x0, y0 + i, color);
        }

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void drawRays2D(void)
{
    int r, mx, my, dof;
    float rx, ry, ra, xo, yo, finalDist;

    // ra = data()->pda;
    ra = data()->pda - DR*30;

    if (ra < 0) {ra += 2*PI;}
    if (ra > 2*PI) {ra -= 2*PI;}
    for (r = 0; r < 60; r++) {
        printf("%d", r);
        dof = 0;
        float aTan = -1/tan(ra);
        float distH = 100000;
        float hx = data()->px;
        float hy = data()->py;
        //Horizontal lines
        if (ra > PI) {
            ry = (((int)data()->py>>6)<<6)-0.001;
            rx = (data()->py - ry) * aTan+data()->px;
            yo=-64;
            xo=-yo*aTan;
        }
        if (ra < PI) {
            ry = (((int)data()->py>>6)<<6)+64;
            rx = (data()->py - ry) * aTan+data()->px;
            yo=64;
            xo=-yo*aTan;
        }
        while(dof < 8) {
            mx=(int) (rx)>>6;
            my=(int) (ry)>>6;
            if (mx >= 0 && mx < bigX && my >= 0 && my < bigY && data()->map[my][mx] == 1) {
                hx = rx;
                hy = ry;
                distH = dist(data()->px, data()->py, hx, hy, ra);
                dof = 8;
            }
            else {rx+=xo; ry+=yo; dof += 1;}
        }

        //Vertical Lines
        dof = 0;
        float nTan = -tan(ra);
        float distV = 100000;
        float vx = data()->px;
        float vy = data()->py;
        if (ra > PI2 && ra<PI3) {
            rx = (((int)data()->px>>6)<<6)-0.001;
            ry = (data()->px - rx) * nTan+data()->py;
            xo=-64;
            yo=-xo*nTan;
        }
        if (ra < PI2 || ra >PI3) {
            rx = (((int)data()->px>>6)<<6)+64;
            ry = (data()->px - rx) * nTan+data()->py;
            xo=64;
            yo=-xo*nTan;
        }
        if (ra == 0 || ra == PI) {rx=data()->px; ry=data()->py; dof = 8;}
        while(dof < 8) {
            mx=(int) (rx)>>6;
            my=(int) (ry)>>6;
            if (mx >= 0 && mx < bigX && my >= 0 && my < bigY && data()->map[my][mx] == 1) {
                vx = rx;
                vy = ry;
                distV = dist(data()->px, data()->py, vx, vy, ra);
                dof = 8;
            }
            else {rx+=xo; ry+=yo; dof += 1;}
        }
        if (distV<distH) {rx = vx; ry = vy; finalDist = distH;}
        if (distV>distH) {rx = hx; ry = hy; finalDist = distV;}
        draw_line(data()->px, data()->py, rx, ry);
        //----3DCast
        int ca = FixAng(data()->pda - ra);
        finalDist = distH * cos(degToRad(ca));
        if (r == 30) {printf("%f", finalDist);}
        int lineH = (mSize * 320) / finalDist;
        if (lineH > 320)
            lineH = 320;
        int lineOff = 160 - (lineH >> 1);
        int color = 0xFF0000;
        for (int i = 0; i < lineH; i++)
        {
            for (int w = 530; w < 538; w++) {
                my_mlx_pixel_put(data()->image, r * 8 + w, lineOff + i, color);
                my_mlx_pixel_put(data()->image, r * 8 + w, lineOff + lineH, color);
            }
        }
        ra +=DR; if (ra < 0) {ra +=2*PI;} if (ra>2*PI) {ra -=2*PI;} 
    }
}

void draw_line(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(data()->image, x0, y0, 0x038c93);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void drawplayer(void) {
    int size = 20;
    int px = data()->px;
    int py = data()->py;
    float vertex1_x = px + size * cos(data()->pda);
    float vertex1_y = py + size * sin(data()->pda);

    float angle1 = data()->pda - (5 * PI / 6);
    float angle2 = data()->pda + (5 * PI / 6);
    float vertex2_x = px + size * cos(angle1);
    float vertex2_y = py + size * sin(angle1);
    float vertex3_x = px + size * cos(angle2);
    float vertex3_y = py + size * sin(angle2);

    draw_line(vertex1_x, vertex1_y, vertex2_x, vertex2_y);
    draw_line(vertex2_x, vertex2_y, vertex3_x, vertex3_y);
    draw_line(vertex3_x, vertex3_y, vertex1_x, vertex1_y);
    drawRays2D();
}

void buttons(int kp) {
    if ((kp == XK_d || kp == XK_Right))
	{
        data()->pda += 0.1;
        if (data()->pda > 2*PI) {data()->pda -= 2*PI;}
        data()->pdx = cos(data()->pda) * 5; data()->pdy = sin(data()->pda) * 5;
	}
	else if ((kp == XK_s || kp == XK_Down))
	{
		data()->px -= data()->pdx;
		data()->py -= data()->pdy;
	}
	else if ((kp == XK_a || kp == XK_Left))
	{
		data()->pda -= 0.1;
        if (data()->pda < 0) {data()->pda += 2*PI;} data()->pdx = cos(data()->pda) * 5; data()->pdy = sin(data()->pda) * 5;
    }
	else if ((kp == XK_w || kp == XK_Up))
	{
        data()->px += data()->pdx;
		data()->py += data()->pdy;
	}
    else if ((kp == XK_Escape))
        exit_game();
}

void paintCanva() {
    paintFloor();
    drawplayer();
	mlx_put_image_to_window(data()->window.mlx_ptr, data()->window.win_ptr ,data()->image.img, 0, 0);
}

int move(int kp) {
    buttons(kp);
    paintCanva();
    return (0);
}

int	game_loop(void *a)
{
	(void) a;
	return (0);
}

int main(void) {
    data()->px = 100;
    data()->py = 100;
    data()->map = NULL;
    data()->pdx = cos(data()->pda) * 5; data()->pdy = sin(data()->pda) * 5;
    allocateMap();
    data()->window = new_program(1024, 510, "cub3D");
    if (!data()->window.win_ptr || !data()->window.mlx_ptr)
        exit(1);
    data()->image = new_img(1024, 510);
    paintCanva();
    mlx_hook(data()->window.win_ptr, 2, 1L << 0, move, data());
    mlx_hook(data()->window.win_ptr, 17, 0, exit_game, data());
    mlx_loop_hook(data()->window.mlx_ptr, game_loop, data());
	mlx_loop(data()->window.mlx_ptr);
}