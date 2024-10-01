/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:19:41 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/01 16:49:35 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

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
	return (error(SET, FALSEIDENT), FALSEIDENT);
}

int	check_identifyer(char *line, int *map_flag)
{
	static int	idents[6];
	int			i;
	int			current;

	i = 0;
	current = -2;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		return (EMPTYLINE);
	current = comp_ident(&line[i], idents);
	if (current >= 0)
		idents[current] = 1;
	else if (current == FALSEIDENT)
	{
		if (line[i] == '1')
		{
			error(SET, NOUGHT);
			*map_flag = 1;
		}
	}
	return (current);
}

void	insert_map(t_map *map, char **str)
{
	int		arrlen;
	char	**tmp;

	arrlen = arr_len(map->str_map);
	tmp = (char **)malloc(sizeof(char *) * (arrlen + 2));
	err_check(tmp, MALLOC);
	mv_arr(map->str_map, tmp);
	if (arrlen > 0)
		free(map->str_map);
	tmp[arrlen] = *str;
	tmp[arrlen + 1] = NULL;
	map->str_map = tmp;
}

void	get_info(int fd, t_map *map)
{
	char	*next_line;
	int		map_flag;

	map_flag = 0;
	while (!error(GET, NOUGHT))
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		if (*next_line == '\n')
			continue ;
		if (next_line[ft_strlen(next_line) - 1] == '\n')
			next_line[ft_strlen(next_line) - 1] = '\0';
		if (!map_flag && check_identifyer(next_line, &map_flag) >= 0)
			insert_info(map, &next_line);
		else if (map_flag)
			insert_map(map, &next_line);
	}
	if (error(GET, NOUGHT))
	{
		printf("invalid input");
		exit(2);
	}
	validate_map(map);
}

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

void	print_input(t_map *map)
{
	for (int i = 0; i < map->map_h; i++)
	{
		for (int k = 0; k < map->map_w; k++)
		{
			if (map->map[i][k] == 1)
				write(1, "1", 1);
			else if (map->map[i][k] == 0)
				write(1, "0", 1);
			else
				write(1, "-", 1);
		}
		write(1, "\n", 1);
	}
}

int	read_input(char **argv, t_player *player, t_map *map)
{
	int i;
	int  fd;

	i = 0;
	if (!ft_strchr(argv[1], '.') || ft_strncmp(ft_strrchr(argv[1], '.'),
			".cub\0", 5))
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	get_info(fd, map);
	get_start_pos(map, player);
	close(fd);
	// print_input(player, map);
	return (0);
}
