/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:44:56 by pstrohal          #+#    #+#             */
/*   Updated: 2024/03/15 17:41:17 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;

	if (!lst)
		return (0);
	len = 1;
	while (!(lst->next == NULL))
	{
		len++;
		lst = lst->next;
	}
	return (len);
}
// int main(void)
// {
// 	char *arr = "ertrhg5r4t5ghrg5345gr";
// 	t_list *p = ft_lstnew(arr);

// 	printf("%d", ft_lstsize(p));
// 	return (0);
// }