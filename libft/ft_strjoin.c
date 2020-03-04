/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cotis <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 19:20:16 by cotis             #+#    #+#             */
/*   Updated: 2019/11/23 08:51:31 by cotis            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	ft_strcpy(str, (char*)s1);
	ft_strcat(str, (char*)s2);
	return (str);
}
