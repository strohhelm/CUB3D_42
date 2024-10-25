/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/25 16:37:39 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub_bonus.h"

t_point	intersection(t_point pos, t_point sl, t_point sr, t_point p)
{
	t_point	s;
	double	denominator;

	denominator = ((p.x - pos.x) * (sl.y - sr.y) - (p.y - pos.y) * (sl.x - sr.x));
	if (denominator == 0.0)
	{
		s.x = 0.0;
		s.y = 0.0;
		return(s);
	}
	else
	{
	s.x = ((sl.x - sr.x) * (p.x * pos.y - p.y * pos.x) - (p.x - pos.x)
		* (sl.x * sr.y - sl.y * sr.x))
			/ denominator;
	s.y = ((sl.y - sr.y) * (p.x * pos.y - p.y * pos.x) - (p.y - pos.y)
		* (sl.x * sr.y - sl.y * sr.x))
			/ denominator;
	}
	s.x = pos.x + s.x * (p.x - pos.x);
	s.y = pos.x + s.y * (p.y - pos.y);
	return (s);
}

t_point get_screen(t_player *player, int i)
{
	t_point s;

	if (i)
	{
	s.x = player->pos.x + player->dir.x + player->scr.x;
	s.y = player->pos.y + player->dir.y + player->scr.y;
	}
	else
	{
		s.x = player->pos.x + player->dir.x - player->scr.x;
		s.y = player->pos.y + player->dir.y - player->scr.y;
	}
	return (s);
	
}

void	draw_door(t_game *game, t_door *d)
{
	t_point	delta;
	double	dist;
	int		px_len;
	t_point	left_intersect;
	t_point	right_intersect;
	t_point sl = get_screen(&game->player, 0);
	t_point sr = get_screen(&game->player, 1);
	t_point scrvector;
	scrvector.x = sr.x - sl.x;
	scrvector.y = sr.y - sl.y;
	double screenwidth = sqrt(scrvector.x * scrvector.x + scrvector.y * scrvector.y);
	left_intersect = intersection(game->player.pos, sl, sr, d->left);
	right_intersect = intersection(game->player.pos, sl, sr, d->right);
	printf("left_intersect:x:%f  y:%f\n", left_intersect.x, left_intersect.y);
	double step = screenwidth / WIDTH;
	int xleft = 0;
	int xright = 0;
	if (left_intersect.x > 0.0 && left_intersect.y > 0.0)
	{
		scrvector.x = left_intersect.x - sl.x;
		scrvector.y = left_intersect.y - sl.y;
		xleft = (int)sqrt(scrvector.x * scrvector.x + scrvector.y * scrvector.y);
	}

	if (right_intersect.x > 0.0 && right_intersect.y > 0.0)
	{
		scrvector.x = right_intersect.x - sr.x;
		scrvector.y = right_intersect.x - sr.x;
		xright = (int)sqrt(scrvector.x * scrvector.x + scrvector.y * scrvector.y);
	}

	int i = -1;
	// printf("%d, %d\n", xleft, xright);
	while (++i < HEIGHT)
	{
		if (xleft > 0)
			mlx_put_pixel(game->img, xleft, i, 0xFF0000FF);
		if (xright > 0)
			mlx_put_pixel(game->img, xright, i, 0xFF0000FF);
	}
}

void	draw_doors(t_game *game)
{
	t_door	*i;
	t_list	*tmp;

	tmp = game->map.dstuff.doors;
	while (tmp)
	{
		i = (t_door *)tmp->content;
		draw_door(game, i);
			// fflush(stdout);
			// printf("\n");
		tmp = tmp->next;
	}
	return ;
}
