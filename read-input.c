/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read-input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 16:19:41 by pstrohal          #+#    #+#             */
/*   Updated: 2024/09/14 16:37:22 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_player get_info(int fd)
{
	char *next_line;
	t_player play;
	
	while (1)
	{
		next_line = get_next_line(fd);
		if (!next_line)
			return (NULL);
		
	}
}

int read_input(int argc, char **argv)
{
	int i;
	int  fd;
	t_player p;
	char *tmp;
	i = 0;
	if(argc != 2)
		return (-1);
	fd = open(argv[1]);
	if (fd < 0)
		return (-1);
	if (!ft_strchr(argv[1], '.')
		|| ft_strncmp(ft_strrchr(argv[1], '.'), ".cub\0", 5))
		return (-1);
	p = get_info(fd);
	close (fd);
	
}
