/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 17:08:49 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 17:12:19 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// speed = how much rotation per call of function,
//	l_r = left or right rotation; left -> l_r = 1, right -> l_r = -1;
void	rotate_dir_plane(t_point *dir, t_point *plane, double speed, double l_r)
{
	double	tmp_x;

	speed *= l_r;
	tmp_x = dir->x;
	dir->x = dir->x * cos(speed) - dir->y * sin(speed);
	dir->y = tmp_x * sin(speed) + dir->y * cos(speed);
	tmp_x = plane->x;
	plane->x = plane->x * cos(speed) - plane->y * sin(speed);
	plane->y = tmp_x * sin(speed) + plane->y * cos(speed);
}

void	update_pos(t_game *game, t_point new_pos)
{
	if (!intersection_with_door(game, game->player.pos, new_pos))
	{
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
}

void	set_new_pos(t_game *game, t_point *new_pos, char key, int mod)
{
	if (key == 'w')
	{
		new_pos->x = game->player.pos.x + game->player.dir.x * mod;
		new_pos->y = game->player.pos.y + game->player.dir.y * mod;
		collision(*new_pos, game);
	}
	else if (key == 's')
	{
		new_pos->x = game->player.pos.x - game->player.dir.x * mod;
		new_pos->y = game->player.pos.y - game->player.dir.y * mod;
		collision(*new_pos, game);
	}
	else if (key == 'a')
	{
		new_pos->x = game->player.pos.x + game->player.dir.y * mod;
		new_pos->y = game->player.pos.y - game->player.dir.x * mod;
		collision(*new_pos, game);
	}
	else if (key == 'd')
	{
		new_pos->x = game->player.pos.x - game->player.dir.y * mod;
		new_pos->y = game->player.pos.y + game->player.dir.x * mod;
		collision(*new_pos, game);
	}
}
