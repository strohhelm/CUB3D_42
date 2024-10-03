/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:46:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/15 16:15:59 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*t_list1;

	t_list1 = (t_list *)malloc(sizeof(*t_list1));
	if (!t_list1)
		return (NULL);
	t_list1->content = content;
	t_list1->next = NULL;
	return (t_list1);
}

// int	main(void)
// {
// 	t_list	*t_list2;

// 	t_list2 = ft_lstnew("HALLO WAS GEHT AB?");
// 	printf("%s", (*t_list2).next);
// }
