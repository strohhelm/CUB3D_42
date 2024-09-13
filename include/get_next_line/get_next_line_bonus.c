/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:07:56 by pstrohal          #+#    #+#             */
/*   Updated: 2024/05/22 16:32:36 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_next_line(int fd, char **buffer)
{
	ssize_t	btsread;
	char	*nextbuild;
	char	tmp[BUFFER_SIZE + 1];

	btsread = 0;
	nextbuild = (char *)malloc(BUFFER_SIZE + 1);
	if (!nextbuild)
		return (free(*buffer), NULL);
	if (!*buffer)
		nextbuild[0] = '\0';
	else
		ft_memcpy(nextbuild, *buffer, ft_strlen(*buffer) + 1);
	while (!ft_strchr(nextbuild, '\n'))
	{
		btsread = read(fd, tmp, BUFFER_SIZE);
		if (btsread == 0)
			return (free(*buffer), nextbuild);
		else
			tmp[btsread] = '\0';
		nextbuild = ft_strjoin1(nextbuild, tmp);
		if (!nextbuild)
			return (free(*buffer), NULL);
	}
	return (free(*buffer), nextbuild);
}

char	*ft_cutstr(char **buffer)
{
	int		i;
	char	*cutstring;

	cutstring = ft_strchr(*buffer, '\n');
	if (!cutstring)
	{
		i = ft_strlen(*buffer);
		i--;
	}
	else
		i = cutstring - (*buffer);
	cutstring = (char *)malloc((i + 2) * sizeof(char));
	if (!cutstring)
	{
		free(*buffer);
		return (*buffer = NULL, NULL);
	}
	ft_memcpy(cutstring, *buffer, i + 1);
	cutstring[i + 1] = '\0';
	return (cutstring);
}

void	ft_rearange_buffer(char *buffer)
{
	int	i;

	i = 0;
	if (buffer)
	{
		while (buffer[i] != '\n')
		{
			if (buffer[i++] == '\0')
			{
				buffer[0] = '\0';
				return ;
			}
		}
		ft_memcpy(buffer, &buffer[i + 1], ft_strlen(buffer) - i);
	}
	return ;
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*nextline;

	if ((fd < 0 || fd > OPEN_MAX) || (read(fd, buffer[fd], 0) < 0))
	{
		if (buffer[fd])
			buffer[fd][0] = '\0';
		return (NULL);
	}
	buffer[fd] = read_next_line(fd, &buffer[fd]);
	if (buffer[fd] == NULL)
		return (NULL);
	if (*buffer[fd] == '\0')
	{
		free(buffer[fd]);
		return (buffer[fd] = NULL, NULL);
	}
	nextline = ft_cutstr(&buffer[fd]);
	ft_rearange_buffer(buffer[fd]);
	return (nextline);
}

// int	main(void)
// {
// 	int		i;
// 	int		x;
// 	int		fd[4];
// 	char	*str;

// 	i = 1;
// 	x = 0;
// 	fd[0] = open("empty", O_RDONLY);
// 	// fd[1] = open("42_with_nl", O_RDONLY);
// 	// fd[2] = open("alternate_line_nl_no_nl", O_RDONLY);
// 	// fd[3] = open("43_with_nl", O_RDONLY);
// 	while (i-- >= 0)
// 	{
// 		// printf("test %d$\n", (x + 1));
// 		str = get_next_line(fd[x]);
// 		printf("%s$\n", str);
// 		// if (x == 3)
// 		// {
// 		// 	x = 0;
// 		// 	printf("------------------------------------------------\n");
// 		// }
// 		// else
// 		// 	x++;
// 	}
// 	close (fd[0]);
// 	// close (fd[1]);
// 	// close (fd[2]);
// 	// close (fd[3]);
// 	free(str);
// }
