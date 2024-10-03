/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:07:11 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/16 17:07:27 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp1;
	t_list	*tmp2;

	if (!*lst)
		return ;
	tmp1 = *lst;
	while (tmp1->next)
	{
		tmp2 = tmp1->next;
		ft_lstdelone(tmp1, del);
		tmp1 = tmp2;
	}
	ft_lstdelone(tmp1, del);
	*lst = NULL;
}
