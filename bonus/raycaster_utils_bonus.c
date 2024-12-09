/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 16:48:47 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 16:58:58 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	render_calc(t_game *game, t_rays *ray)
{
	if (ray->side == 0)
		ray->walldist = (ray->sdistx - ray->deldistx) / 10;
	else
		ray->walldist = (ray->sdisty - ray->deldisty) / 10;
	ray->wallhit.x = game->player.pos.x + ray->walldist * 10 * ray->ray_dir_x;
	ray->wallhit.y = game->player.pos.y + ray->walldist * 10 * ray->ray_dir_y;
	ray->minimap_hit.x = ray->walldist * 10 * ray->ray_dir_x;
	ray->minimap_hit.y = ray->walldist * 10 * ray->ray_dir_y;
	ray->hitp.x = (game->player.pos.x + ray->walldist * 10 * ray->ray_dir_x);
	ray->hitp.y = (game->player.pos.y + ray->walldist * 10 * ray->ray_dir_y);
	ray->lineheight = HEIGHT / ray->walldist;
	ray->start = -ray->lineheight / 2 + HEIGHT / 2;
	ray->end = ray->lineheight / 2 + HEIGHT / 2;
	ray->dir = get_direction(game->player.pos, ray->hitp, ray->side);
}
