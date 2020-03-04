/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 10:46:30 by cotis             #+#    #+#             */
/*   Updated: 2020/03/04 18:25:43 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				keys(int key, data *a)
{
	int		bpp;
	int		sl;
	int		end;

	if (key == 91)
		a->alpha += 0.2;
	if (key == 84)
		a->alpha -= 0.2;
	if (key == 88)
		a->beta += 0.2;
	if (key == 86)
		a->beta -= 0.2;
	if (key == 92)
		a->gamma += 0.2;
	if (key == 89)
		a->gamma -= 0.2;
	if (key == 69)
		a->zoom += 5;
	if (key == 78)
		a->zoom -= 5;
	if (key == 53)
		exit(0);
	if (key == 126)
		a->shift_y -= 20;
	if (key == 125)
		a->shift_y += 20;
	if (key == 123)
		a->shift_x -= 20;
	if (key == 124)
		a->shift_x += 20;
	a->img_ptr = mlx_new_image(a->mlx_ptr, 1920, 1080);
	if ((a->str = (int*)mlx_get_data_addr(a->img_ptr, &bpp, &sl, &end)) == NULL)
		errors(-2);
	draw(a);
	mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img_ptr, 0, 0);
	mlx_destroy_image(a->mlx_ptr, a->img_ptr);
	return (key);
}

int				image(data *a)
{
	int		bpp;
	int		sl;
	int		end;

	a->shift_x = 960;
	a->shift_y = 540;
	a->zoom = 10;
	a->zoom_z = 1;
	a->mlx_ptr = mlx_init();
	a->win_ptr = mlx_new_window(a->mlx_ptr, 1920, 1080, "Love");
	a->img_ptr = mlx_new_image(a->mlx_ptr, 1920, 1080);
	a->str = (int *)mlx_get_data_addr(a->img_ptr, &bpp, &sl, &end);
	draw(a);
	mlx_put_image_to_window(a->mlx_ptr, a->win_ptr, a->img_ptr, 0, 0);
	mlx_hook(a->win_ptr, 3, 0, keys, a);
	mlx_loop(a->mlx_ptr);
	return (0);
}

void		draw(data *a)
{
	int		x;
	int		y;
	
	y = 0;
	while (y < a->y_max)
	{
		x = 0;
		while (x <  a->x_max)
		{
			if (x < (a->x_max - 1))
			{
				algoritm(x, y, x + 1, y, a->str, a);
			}
			if (y < (a->y_max - 1))
			{
				algoritm(x, y, x, y + 1, a->str, a);
			}
			x++;
		}
		y++;
	}
}

void	rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

void	rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

static void			isometric(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

void				zoom(t_put *fdf, data *a)
{
	fdf->z1 = a->z_list[(int)fdf->y1][(int)fdf->x1];
	fdf->z2 = a->z_list[(int)fdf->y2][(int)fdf->x2];
	fdf->x1 *= a->zoom;
	fdf->y1 *= a->zoom;
	fdf->x2 *= a->zoom;
	fdf->y2 *= a->zoom;
}

void				color(t_put *fdf, data *a)
{
	a->color = (fdf->z1) ?  0x9C02A7: 0x7CE701;
}

void				move(t_put *fdf, data *a)
{
	fdf->x1 += a->shift_x;
	fdf->y1 += a->shift_y;
	fdf->x2 += a->shift_x;
	fdf->y2 += a->shift_y;
}

void				brazenham(t_put *fdf, data *a, int *str)
{
	fdf->deltaX = abs(fdf->x2 - fdf->x1);
	fdf->deltaY = abs(fdf->y2 - fdf->y1);
	fdf->signX = fdf->x1 < fdf->x2 ? 1 : -1;
	fdf->signY = fdf->y1 < fdf->y2 ? 1 : -1;
	fdf->error = fdf->deltaX - fdf->deltaY;
	if (((fdf->y2) < 1080) && (fdf->x2 < 1920) && ((fdf->y2) >= 0) && (fdf->x2 >= 0))
		str[fdf->x2 + fdf->y2 * 1920] = a->color;
	while ((fdf->x1 != fdf->x2 || fdf->y1 != fdf->y2) && ((fdf->y1) < 1080) 
	&& (fdf->x1 < 1920) && ((fdf->y1) >= 0) && (fdf->x1 >= 0))
	{
		str[fdf->x1 + fdf->y1 * 1920] = a->color;
		fdf->error2 = fdf->error * 2;
		if (fdf->error2 > -(fdf->deltaY))
		{
			fdf->error -= fdf->deltaY;
			fdf->x1 += fdf->signX;
		}
		if (fdf->error2 < fdf->deltaX)
		{
			fdf->error += fdf->deltaX;
			fdf->y1 += fdf->signY;
		}
	}
}

void				algoritm(int x1, int y1, int x2, int y2, int *str, data *a)
{
	t_put		fdf;
	
	fdf.x1 = x1;
	fdf.x2 = x2;
	fdf.y1 = y1;
	fdf.y2 = y2;
	zoom(&fdf, a);
	color(&fdf, a);
	isometric(&(fdf.x1), &(fdf.y1), fdf.z1);
	isometric(&(fdf.x2), &(fdf.y2), fdf.z2);
	rotate_x(&(fdf.y1), &(fdf.z1), a->alpha);
	rotate_x(&(fdf.y2), &(fdf.z2), a->alpha);
	rotate_y(&(fdf.x1), &(fdf.z1), a->beta);
	rotate_y(&(fdf.x2), &(fdf.z2), a->beta);
	rotate_z(&(fdf.x1), &(fdf.y1), a->gamma);
	rotate_z(&(fdf.x2), &(fdf.y2), a->gamma);
	move(&fdf, a);
	brazenham(&fdf, a, str);
}
