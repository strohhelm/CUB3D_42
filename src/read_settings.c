/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:19:14 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/24 20:29:21 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	set_colour(int type, t_map *map, char *str)
{
	char **col;
	int colour;
	int rgb[3];
	int len;
	char *tmp;
	col = ft_split(str,',');
	len = arr_len(col);
	while (--len >= 0)
	{
		tmp = ft_strtrim(col[len], " \t");
		free(col[len]);
		col[len] = tmp;
	}
	if (arr_len(col) != 3 || ft_strlen(col[0]) > 3 || ft_strlen(col[1]) > 3
		|| ft_strlen(col[2]) > 3)
		exit(6);
	rgb[0] = ft_atoi(col[0]);
	rgb[1] = ft_atoi(col[1]);
	rgb[2] = ft_atoi(col[2]);
	if (!(rgb[0] >= 0 && rgb[0] <= 255) || !(rgb[1] >= 0 && rgb[1] <= 255)
		|| !(rgb[2] >= 0 && rgb[2] <= 255))
		exit (7);
	colour = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	if (type == CEILING)
		map->ceiling = colour;
	else
		map->floor = colour;
	return ;
}

void	set_info(int type, t_map *map, char **str, int i)
{
	char *rem_str;

	rem_str = ft_substr(*str, i, ft_strlen(&(*str)[i]));
	rem_str = ft_strtrim(rem_str, " \t");
	if (type < CEILING && *rem_str && rem_str[0] == '.' && rem_str[1] == '/')
	{
		map->textures[type] = mlx_load_png(rem_str);
		if (!map->textures[type])
			exit(5);
	}
	else if (type == CEILING || type == FLOOR)
		set_colour(type, map, rem_str);
	free(rem_str);
	// free(*str);
}

void	insert_info(t_map *map, char **str)
{
	int	i;

	i = 0;
	while (*str && *str[i] && (*str[i] == ' ' || *str[i] == '\t'))
		i++;
	if (!ft_strncmp(&(*str[i]), "NO", 2))
		set_info(NORTH, map, str, i + 2);
	else if (!ft_strncmp(&(*str[i]), "SO", 2))
		set_info(SOUTH, map, str, i + 2);
	else if (!ft_strncmp(&(*str[i]), "EA", 2))
		set_info(EAST, map, str, i + 2);
	else if (!ft_strncmp(&(*str[i]), "WE", 2))
		set_info(WEST, map, str, i + 2);
	else if(*str[i] =='F')
		set_info(FLOOR, map, str, i + 1);
	else if (*str[i] == 'C')
		set_info(SOUTH, map, str, i + 1);
	else
	{
		char d = *str[i];
		printf("invalid input!\n");
		exit(13);
	}
	return ;
}
