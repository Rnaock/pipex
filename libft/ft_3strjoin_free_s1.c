/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_3strjoin_free_s1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 17:33:28 by manuel            #+#    #+#             */
/*   Updated: 2022/08/07 17:33:42 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_3strjoin_free_s1(char *s1, char *s2, char *s3)
{
	void	*new_s;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	new_s = (char *)ft_calloc((len1 + len2 + len3 + 1), sizeof(char));
	if (new_s == NULL)
		return (NULL);
	ft_memmove(new_s, s1, ft_strlen(s1));
	ft_memmove(new_s + len1, s2, ft_strlen(s2));
	ft_memmove(new_s + len1 + len2, s3, ft_strlen(s3));
	((char *)new_s)[len1 + len2 + len3] = '\0';
	free(s1);
	return ((char *)new_s);
}
