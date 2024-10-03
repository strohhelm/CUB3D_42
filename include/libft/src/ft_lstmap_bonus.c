/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 21:17:40 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/15 22:52:30 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*newlist;
	void	*tmp;

	newlist = NULL;
	if (!lst)
		return (NULL);
	while (lst)
	{
		tmp = f(lst->content);
		node = ft_lstnew(tmp);
		if (node == NULL)
		{
			del(tmp);
			ft_lstclear(&newlist, del);
		}
		else
			ft_lstadd_back(&newlist, node);
		lst = lst->next;
	}
	return (newlist);
}
