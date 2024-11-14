/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_settings_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:19:14 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 22:13:22 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	fill_col_arr(char ***col, char *str)
{
	int		len;
	char	*tmp;

	*col = ft_split(str, ',');
	if (!*col)
		error_print("Shit went down in ft_split, get a working pc mate!");
	len = arr_len(*col);
	while (--len >= 0)
	{
		tmp = ft_strtrim((*col)[len], " \t");
		if (!tmp)
			error_print("Shit went down in ft_strtrim, get a working pc mate!");
		free((*col)[len]);
		(*col)[len] = tmp;
	}
	return ;
}

void	set_colour(int type, t_map *map, char *str)
{
	char			**col;
	unsigned int	colour;
	int				rgb[3];

	fill_col_arr(&col, str);
	if (arr_len(col) != 3 || ft_strlen(col[0]) == 0 || ft_strlen(col[1]) == 0
		|| ft_strlen(col[2]) == 0 || ft_strlen(col[0]) > 3
		|| ft_strlen(col[1]) > 3 || ft_strlen(col[2]) > 3)
		error_print("Aha what do you want me to do? imagine colours?");
	rgb[0] = ft_atoi(col[0]);
	rgb[1] = ft_atoi(col[1]);
	rgb[2] = ft_atoi(col[2]);
	if (!(rgb[0] >= 0 && rgb[0] <= 255) || !(rgb[1] >= 0 && rgb[1] <= 255)
		|| !(rgb[2] >= 0 && rgb[2] <= 255))
		error_print("Aha what do you want me to do? range: 0-255!");
	colour = get_colour(rgb[0], rgb[1], rgb[2]);
	if (type == CEILING)
		map->ceiling = colour;
	else
		map->floor = colour;
	free_string_array(col);
	return ;
}

void	validate_texture(char *rem_str)
{
	int	fd;

	if (!ft_strchr(rem_str, '.') || ft_strncmp(ft_strrchr(rem_str, '.'),
			".png\0", 5) || (ft_strchr(rem_str, '.')
			!= ft_strrchr(rem_str, '.')))
		error_print("Woah hey there! Thats not a '.png' file!");
	fd = open(rem_str, O_RDONLY);
	if (fd < 0)
		error_print("Woah hey there! not a readable texture path");
	close(fd);
}

void	set_info(int type, t_map *map, char **str, int i)
{
	char	*rem_str;
	char	*tmp;

	tmp = ft_substr(*str, i, ft_strlen(&(*str)[i]));
	if (!tmp)
		error_print("Shit went down in ft_substr, get a working pc mate!");
	rem_str = ft_strtrim(tmp, " \t");
	if (!rem_str)
		error_print("Shit went down in ft_strtrim, get a working pc mate!");
	if (type < CEILING)
	{
		validate_texture(rem_str);
		map->textures[type] = mlx_load_png(rem_str);
		if (!map->textures[type])
			error_print("Well wtf did you try here? \
			Get an actual texture buddy!");
	}
	else if (type == CEILING || type == FLOOR)
		set_colour(type, map, rem_str);
	free(rem_str);
	free(tmp);
}

void	insert_info(t_map *map, char **str)
{
	int	i;

	i = 0;
	while (*str && (*str)[i] && ((*str)[i] == ' ' || (*str)[i] == '\t'))
		i++;
	if (!ft_strncmp(&((*str)[i]), "NO", 2))
		set_info(NORTH, map, str, i + 2);
	else if (!ft_strncmp(&((*str)[i]), "SO", 2))
		set_info(SOUTH, map, str, i + 2);
	else if (!ft_strncmp(&((*str)[i]), "EA", 2))
		set_info(EAST, map, str, i + 2);
	else if (!ft_strncmp(&((*str)[i]), "WE", 2))
		set_info(WEST, map, str, i + 2);
	else if ((*str)[i] == 'F')
		set_info(FLOOR, map, str, i + 1);
	else if ((*str)[i] == 'C')
		set_info(CEILING, map, str, i + 1);
	else
		error_print("OOPS! We encountered a wrong identifier!");
	free(*str);
	return ;
}
