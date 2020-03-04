/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <cotis@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 07:05:56 by cotis             #+#    #+#             */
/*   Updated: 2020/03/04 18:14:02 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	*mystrtok(char *str, const char *delim)
{
	static char		*next;

	if (str)
	{
		next = str;
		while (*next && ft_strchr(delim, *next))
			*next++ = '\0';
	}
	if (!*next)
		return (NULL);
	str = next;
	while (*next && !ft_strchr(delim, *next))
		++next;
	while (*next && ft_strchr(delim, *next))
		*next++ = '\0';
	return (str);
}

void	validation(char *line)
{
	char		*pch;
	char		*l;

	l = (char *)malloc(sizeof(char) * ft_strlen(line));
	l = ft_strcpy(l, line);
	pch = mystrtok(l, " ");
	while (pch != NULL)
	{
		check_input(pch);
		pch = mystrtok(NULL, " ");
	}
	free(l);
}

void		RGBcheck(char *input)
{
	int			i;

	i = 0;
	while (input[i])
	{
		if (input[i] == ',' && input[i + 1] != '0' && input[i + 2] != 'x')
			errors(-1);
		i++;
	}
}

int		check_input(char *input)
{
	size_t		i;

	i = 0;
	if (input[0] == '-' && input[i + 1] == 0)
		errors(-1);
	if (input[0] == '-')
		i = 1;
	if ((input[i] == '0' || input[i] == '-')
	&& input[i + 1] >= '0' && input[i + 1] <= '9')
		errors(-1);
	while (i < ft_strlen(input))
	{
		if (input[i] == ',')
		{
			RGBcheck(input);
			break ;
		}
		if (input[i] >= '0' && input[i] <= '9')
			i++;
		else
			errors(-1);
	}
	return (2);
}
