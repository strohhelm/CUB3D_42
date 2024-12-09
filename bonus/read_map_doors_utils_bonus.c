/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_doors_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:24:09 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 15:19:45 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	init_left_door_north(t_door *dp, t_da *hlp)
{
	dp->p1.x = hlp->x + 0.5;
	dp->p1.y = hlp->y;
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y + 0.5;
	init_rest_door(dp, hlp, 0);
}

void	init_right_door_north(t_door *dp, t_da *hlp)
{
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y + 0.5;
	dp->p1.x = hlp->x + 0.5;
	dp->p1.y = hlp->y + 1.0;
	init_rest_door(dp, hlp, 1);
}

void	init_left_door_west(t_door *dp, t_da *hlp)
{
	dp->p1.x = hlp->x;
	dp->p1.y = hlp->y + 0.5;
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y + 0.5;
	init_rest_door(dp, hlp, 0);
}

void	init_right_door_west(t_door *dp, t_da *hlp)
{
	dp->p2.x = hlp->x + 0.5;
	dp->p2.y = hlp->y + 0.5;
	dp->p1.x = hlp->x + 1.0;
	dp->p1.y = hlp->y + 0.5;
	init_rest_door(dp, hlp, 1);
}
