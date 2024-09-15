/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:19:41 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/15 17:16:16 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	comp_ident(char *str, int **idents)
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
			if (!*idents[i])
				return (i);
			return (error(SET, DOUBLEIDENT), DOUBLEIDENT);
		}
		if (i == 3)
			len = 1;
	}
	return (error(SET, FALSEIDENT), FALSEIDENT);
}

int	check_identifyer(char **line, int *map_flag)
{
	static int idents[6];
	int i;
	int current;

	i = 0;
	current = -2;
	while (line[i] && *line[i] == ' ')
		i++;
	if (line[i] && !*line[i])
		return (EMPTYLINE);
	current = comp_ident(&line[i], &idents);
	if (current >= 0)
		idents[current] = 1;
	else if (current == FALSEIDENT)
	{
		if (*line[i] == '1')
			*map_flag = 1;
	}
	return (current); 
}

void	insert_map(t_map *map, char **str, int *map_flag)
{
	static char **arr;
	static int	arrlen;
	char **tmp;
	int strlen;
	int	i;
	
	tmp = (char **)malloc(sizeof(char *) * arrlen + 2);
	err_check(tmp, MALLOC);
	mv_arr(arr, tmp);
	if (arrlen > 0)
		free(arr);
	tmp[arrlen] = *str;
	tmp[arrlen + 1] = NULL;
	arr = tmp;
	arrlen++;
}

void	get_info(int fd, t_player *player, t_map *map)
{
	char *next_line;
	int map_flag;

	map_flag = 0;
	while (!error(GET, NOUGHT))
	{
		next_line = get_next_line(fd);
		if (!next_line)
			break ;
		if (!*next_line)
			continue ;
		else if (!map_flag && check_identifyer(&next_line, &map_flag) >= 0)
			insert_info(map, player, &next_line);
		else if (map_flag)
			insert_map(map, &next_line, &map_flag);
	}
	if (error(GET, NOUGHT))
		
	validate_map(map);
}

void	read_input(int argc, char **argv, t_player *player, t_map *map)
{
	int i;
	int  fd;
	char *tmp;
	i = 0;
	if(argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	if (!ft_strchr(argv[1], '.')
		|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub\0", 5))
		return (-1);
	get_info(fd, player, map);
	close (fd);
	return ;
}
