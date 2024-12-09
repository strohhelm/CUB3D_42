/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:19:41 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/27 15:16:37 by pstrohal         ###   ########.fr       */
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

int	check_str(char **next_line, int *map_flag)
{
	int	i;

	i = 0;
	if (!*next_line)
		return (0);
	if (**next_line == '\n' || **next_line == '\0')
	{
		free(*next_line);
		if (*map_flag)
			*map_flag = 2;
		return (-1);
	}
	else if (*map_flag)
	{
		while (next_line[0][i] == ' ' || next_line[0][i] == '\t')
			i++;
		if (next_line[0][i] == '\n' || next_line[0][i] == '\0')
		{
			free(*next_line);
			return (-1);
		}
	}
	return (1);
}

void	get_info(int fd, t_map *map)
{
	char	*next_line;
	int		map_flag;
	int		status;

	map_flag = 0;
	while (error(GET, NOUGHT) >= 0)
	{
		next_line = get_next_line(fd);
		status = check_str(&next_line, &map_flag);
		if (!status)
			break ;
		else if (status < 0)
			continue ;
		if (next_line[ft_strlen(next_line) - 1] == '\n')
			next_line[ft_strlen(next_line) - 1] = '\0';
		if (!map_flag && check_identifyer(next_line, &map_flag) >= 0)
			insert_info(map, &next_line);
		else if (map_flag == 1)
			insert_map(map, &next_line);
		else if (map_flag == 2)
			error_print("What is this map here? you are tying to be funny?");
	}
	check_error(error(GET, NOUGHT));
	validate_map(map);
	return ;
}

void	read_input(char **argv, t_player *player, t_map *map)
{
	int	fd;

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
