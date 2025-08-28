/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hfakou <hfakou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:01:45 by hfakou            #+#    #+#             */
/*   Updated: 2024/11/13 03:56:11 by hfakou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	size_t	i;
	size_t	word;
	size_t	count;

	i = 0;
	word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (word == 0)
			{
				word = 1;
				count++;
			}
		}
		else
			word = 0;
		i++;
	}
	return (count);
}

static int	ft_wordlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_wordcopy(char *dest, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static void	ft_free(char **str, int i)
{
	while (i > 0)
		free(str[--i]);
	free(str);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	size_t	len;
	int		i;
	char	**str;

	if (!s)
		return (NULL);
	i = 0;
	size = count_words(s, c);
	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);
	while (i < size)
	{
		while (*s == c)
			s++;
		len = ft_wordlen(s, c);
		str[i] = malloc(sizeof(char) * (len + 1));
		if (!str[i])
			return (ft_free(str, i), NULL);
		ft_wordcopy(str[i++], s, len);
		s += len;
	}
	str[i] = NULL;
	return (str);
}
