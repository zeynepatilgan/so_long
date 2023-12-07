/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:43:50 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/02 14:43:53 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	x;
	size_t	y;
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	x = ft_strlen(s1);
	y = ft_strlen(s2) + 1;
	str = (char *)malloc(x + y);
	if (!str)
		return (0);
	ft_strlcpy(str, s1, x + 1);
	ft_strlcpy(str + x, s2, y);
	return (str);
}
