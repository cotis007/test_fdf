/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 09:13:27 by cotis             #+#    #+#             */
/*   Updated: 2020/02/17 05:22:48 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		buf_work(char **str, char **line)
{
	char			*mass;
	char			*eol;

	if ((eol = ft_strchr(*str, '\n')))
	{
		*line = ft_strsub(*str, 0, eol - *str);
		mass = ft_strsub(*str, eol - *str + 1, BUFF_SIZE);
		ft_strdel(str);
		*str = mass;
		if (*str[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str[MAX_FD];
	char			buf[BUFF_SIZE + 1];
	char			*mass;
	int				ret;

	if (fd < 0 || line == NULL || fd > MAX_FD)
		return (-1);
	if (str[fd] != NULL && ft_strchr(str[fd], '\n'))
		return (buf_work(&str[fd], line));
	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		mass = str[fd];
		str[fd] = !str[fd] ? ft_strdup(buf) : ft_strjoin(str[fd], buf);
		ft_strdel(&mass);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret < 0)
		return (-1);
	if (!str[fd])
		return (0);
	else
		return (buf_work(&str[fd], line));
}
