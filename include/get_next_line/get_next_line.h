/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 10:07:52 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/07 12:47:57 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

char	*get_next_line(int fd);
char	*read_next_line(int fd, char *string);
char	*ft_strchr1(const char *s, int c);
char	*ft_strjoin1(char *s1, char const *s2);
size_t	ft_strlen1(const char *s);
void	*ft_memcpy1(void *dst, const void *src, size_t n);
void	ft_rearange_buffer(char *buffer);
char	*ft_cutstr(char *nextline);
void	ft_bzero1(void *s, size_t n);

#endif