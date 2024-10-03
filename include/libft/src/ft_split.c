/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 18:23:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/05/17 17:53:35 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_to_next_c(char const *s, char c)
{
	int		i;
	int		ic;
	char	*nextc;

	ic = (int)c;
	i = 0;
	nextc = ft_strchr(s, ic);
	if (nextc == NULL)
	{
		while (s[i])
			i++;
		return (i);
	}
	if (s[i] == *nextc)
		i++;
	while (s[i] != *nextc)
		i++;
	return (i);
}

static int	find_nb_of_strings_in_s(const char *s, char c)
{
	int	i;
	int	sc;

	i = 0;
	sc = 0;
	while (s[sc])
	{
		while (s[sc] == c)
			sc++;
		if (s[sc])
			i++;
		while (s[sc] != c && s[sc])
			sc++;
	}
	return (i);
}

static void	ft_free(char **arr)
{
	int	aindex;

	aindex = 0;
	while (arr[aindex])
		free(arr[aindex++]);
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		sindex;
	int		aindex;
	int		count_to_next_c;
	char	**arr;
	int		nb_of_c;

	sindex = 0;
	aindex = 0;
	nb_of_c = find_nb_of_strings_in_s((char *)s, c);
	arr = (char **)malloc((nb_of_c + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	while (nb_of_c > aindex)
	{
		while (s[sindex] == c && s[sindex])
			sindex++;
		count_to_next_c = ft_count_to_next_c(&s[sindex], c);
		arr[aindex] = (char *)ft_calloc(count_to_next_c + 1, 1);
		if (arr[aindex] == NULL)
			return (ft_free(arr), NULL);
		ft_memcpy(arr[aindex++], &s[sindex], count_to_next_c);
		sindex += (count_to_next_c + 1);
	}
	arr[aindex] = NULL;
	return (arr);
}
