/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:15:08 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 20:54:57 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	get_start_pos(t_map *map, t_player *player)
{
	int	dir_x;
	int	dir_y;

	dir_x = 0;
	dir_y = 0;
	player->pos.x = (double)map->start[0];
	player->pos.y = (double)map->start[1];
	if (map->start[2] == 78)
		dir_y = -1;
	else if (map->start[2] == 83)
		dir_y = 1;
	else if (map->start[2] == 69)
		dir_x = 1;
	else if (map->start[2] == 87)
		dir_x = -1;
	player->dir.x = dir_x;
	player->dir.y = dir_y;
}

int	comp_ident(char *str, int *idents)
{
	char	*arr[7];
	int		i;
	int		len;

	i = -1;
	len = 2;
	arr[0] = "NO";
	arr[1] = "SO";
	arr[2] = "EA";
	arr[3] = "WE";
	arr[4] = "C";
	arr[5] = "F";
	arr[6] = NULL;
	while (++i < 6)
	{
		if (!ft_strncmp(str, arr[i], len))
		{
			if (!idents[i])
				return (i);
			return (error(SET, DOUBLEIDENT), DOUBLEIDENT);
		}
		if (i == 3)
			len = 1;
	}
	return (FALSEIDENT);
}

int	check_identifyer(char *line, int *map_flag)
{
	static int	idents[6];
	int			i;
	int			current;

	i = 0;
	current = -2;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (!line[i])
		return (EMPTYLINE);
	current = comp_ident(&line[i], idents);
	if (current >= 0)
	{
		idents[current] = 1;
		error(SET, error(GET, NOUGHT) + 1);
	}
	else if (current == FALSEIDENT)
	{
		if (line[i] == '1')
			*map_flag = 1;
		else
			error(SET, FALSEIDENT);
	}
	return (current);
}
