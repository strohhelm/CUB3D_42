/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:30:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/15 16:56:16 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int arr_len(char **arr)
{
	int	i,
	
	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

int	mv_arr(char **src, char **dest)
{
	int i = -1;
	if (src && dest)
	{
		while (src[++i])
			dest[i] = src[i];
		dest[i] = NULL;
	}
	return (i);
}