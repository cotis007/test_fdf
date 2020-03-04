/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:34:59 by cotis             #+#    #+#             */
/*   Updated: 2020/03/04 18:21:56 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	errors(int c)
{
	if (c == -1)
	{
		write(1, "Error of reading file\n", 21);
		exit(0);
	}
	if (c == -2)
	{
		write(1, "Fails to set up the connection\n", 50);
		exit(0);
	}
}

int		x_count(char *line)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (line[0] != ' ')
		k++;
	while (line[i])
	{
		if (line[i] == ' ' && line[i + 1] == '\0')
			k--;
		if (line[i] == ' ' && line[i + 1] != ' ')
			k++;
		i++;
	}
	validation(line);
	return (k);
}

void	y_count(char *fl_name, data *a)
{
	int		fd;
	char	*line;

	if ((fd = open(fl_name, O_RDONLY)) < 0)
		errors(-1);
	while (get_next_line(fd, &line))
	{
		a->y_max++;
		free(line);
	}
	close(fd);
}

void	map_read(char *fl_name, data *a)
{
	int		fd;
	char	*line;
	char	**str;

	y_count(fl_name, a);
	a->z_list = (int **)malloc(sizeof(int *) * a->y_max);
	if ((fd = open(fl_name, O_RDONLY)) < 0)
		errors(-1);
	while (get_next_line(fd, &line))
	{
		if (a->x_max == 0)
			a->x_max = x_count(line);
		else if (a->x_max != x_count(line))
			errors(-1);
		a->z_list[a->j] = (int *)malloc(sizeof(int) * a->x_max);
		str = ft_strsplit(line, ' ');
		a->i = 0;
		while (a->i < a->x_max)
		{
			a->z_list[a->j][a->i] = ft_atoi(str[a->i]);
			a->i++;
		}
		
		a->j++;
		free(line);
	}
}

int		main(int argc, char **argv)
{
	data	a;

	if (argc != 2)
		errors(-1);
	map_read(argv[1], &a);
	image(&a);
	return (0);
}
