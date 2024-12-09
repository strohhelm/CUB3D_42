/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:09:10 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/13 16:41:36 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	error(int e_action, int e_error)
{
	static int	error_status = 0;

	if (e_action == GET)
		return (error_status);
	else if (e_action == SET)
		error_status = e_error;
	return (NOUGHT);
}

// malloc protection wrapper
void	err_check(void *p, char *msg)
{
	if (!p)
	{
		error_print(msg);
	}
	else
		return ;
}

// fatal error exit wrapper.
void	error_print(char *msg)
{
	printf("Error\n%s\n", msg);
	exit(1);
}

// error check for map parser specifically.
void	check_error(int e)
{
	if (e == DOUBLEIDENT)
		error_print("Woah hey there! There is a twice set identifier!");
	else if (e == FALSEIDENT)
		error_print("Woah hey there! Thats not a valid identifier!");
	else if (e == NOINFO)
		error_print("Woah hey there! There is nothing!");
	else if (e != ALLIDENT)
		error_print("Woah hey there! There are identifiers missing!");
	return ;
}
