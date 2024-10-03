/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:19:41 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/03 19:55:16 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	insert_map(t_map *map, char **str)
{
	int		arrlen;
	char	**tmp;

	arrlen = arr_len(map->str_map);
	tmp = (char **)malloc(sizeof(char *) * (arrlen + 2));
	if (!tmp)
		error_print("Shit went down in malloc, get a working pc mate!");
	mv_arr(map->str_map, tmp);
	if (arrlen > 0)
		free(map->str_map);
	tmp[arrlen] = *str;
	tmp[arrlen + 1] = NULL;
	map->str_map = tmp;
	return ;
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
		if (*next_line == '\n' && !map_flag)
		{
			free(next_line);
			continue ;
		}
		if (next_line[ft_strlen(next_line) - 1] == '\n')
			next_line[ft_strlen(next_line) - 1] = '\0';
		if (!map_flag && check_identifyer(next_line, &map_flag) >= 0)
			insert_info(map, &next_line);
		else if (map_flag)
			insert_map(map, &next_line);
	}
	check_error(error(GET, NOUGHT));
	validate_map(map);
	return ;
}

void	read_input(char **argv, t_player *player, t_map *map)
{
	int	i;
	int	fd;

	i = 0;
	if (!ft_strchr(argv[1], '.') || ft_strncmp(ft_strrchr(argv[1], '.'),
			".cub\0", 5))
		error_print("Woah hey there! Thats not a '.cub' file!");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_print("Woah hey there! Thats not a valid file!");
	get_info(fd, map);
	get_start_pos(map, player);
	close(fd);
	return ;
}
