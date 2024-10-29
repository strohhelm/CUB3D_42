/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/29 13:37:37 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub_bonus.h"

t_point	intersection(t_point a, t_point b, t_point c, t_point d)
{
	t_point	s;
	double t;
	double u;
	double	denominator;

	s.x = 0.0;
	s.y = 0.0;
	denominator = ((a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x));
	if (!denominator)
		return(s);
	else
	{
		t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / denominator;
		u = - (((a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x)) / denominator);
	}
	if (t >= 0 && u >= 0 && u <= 1)
	{
		s.x = a.x + t * (b.x - a.x);
		s.y = a.y + t * (b.y - a.y);
	}
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

double	dist_betwen_two_points(t_point a, t_point b)
{
	double	dist;
	t_point	vector;
	
	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	dist = sqrt(vector.x * vector.x + vector.y * vector.y);
	return (dist);
}

t_point	vector_between_two_points(t_point a, t_point b)
{
	t_point vector;

	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	return (vector);
}

t_point	get_new_point(t_point p, t_point vector)
{
	t_point result;

	result.x = p.x + vector.x;
	result.y = p.y + vector.y;
	return (result);
}

int	get_screen_x_coord(t_point sl, t_point intersect, double step)
{
	int	x_pixel_value;
	double	x_on_screen_plane;

	x_on_screen_plane = dist_betwen_two_points(sl, intersect);
	x_pixel_value = x_on_screen_plane / step;
	return (x_pixel_value);
}


void	draw_doorline(t_game *game, t_doorhelp *hlp, t_door *d, int x)
{
	int		i;
	int		end;
	int		start;
	double	doorx;
	double	doory;
	double doorstep;
	t_point	tex_pos;
	uint8_t *texpos;
	uint8_t *img_pos;
	uint32_t	colour;
	double	tex_step;
	i = 0;
	start = -hlp->lineheight / 2 +  HEIGHT / 2 - game->y;
	end = hlp->lineheight / 2 + HEIGHT / 2;
	tex_step = 1.0 * d->texture->height / hlp->lineheight;
	doorstep = hlp->doorwidth / d->texture->width;
	doorx = dist_betwen_two_points(d->left, hlp->door_intersect);
	tex_pos.x = doorx * (double)d->texture->width / doorstep;
	// printf("%d\n", hlp->lineheight);
	while (i <= hlp->lineheight)
	{
		if (start + i >= 0 && start + i <= HEIGHT)
		{
			tex_pos.y = i * tex_step;
			uint32_t tex_index = ((int)(tex_pos.y d->texture->width) + (int)tex_pos.x )* 4;
			texpos = &d->texture->pixels[tex_index];
			// ft_memcpy(&colour, texpos, 4);
			img_pos = &game->img->pixels[(int)(((start + i) * game->img->width * 4.0) + x * 4.0)];
			ft_memcpy(img_pos, texpos, 4);
			
			// mlx_put_pixel(game->img, x, start + i, colour);
			// mlx_put_pixel(game->img, x, start + i, SO);
		}
		i++;
	}
}

// ray->lineheight = HEIGHT / ray->walldist;
	// ray->start = -ray->lineheight / 2 + HEIGHT / 2;
	// ray->end = ray->lineheight / 2 + HEIGHT / 2;
void	calc_doorlines(t_game *game, t_doorhelp *hlp, t_door *d)
{
	int		i;
	double	dist;
	t_point	screen_intersect;
	
	i = -1;
	
	screen_intersect.x = hlp->sl.x;
	screen_intersect.y = hlp->sl.y;
	while (++i <= hlp->px_len)
	{
		if (hlp->left + i >= 0 && hlp->left + i <= WIDTH)
		{
			screen_intersect.x = hlp->left_intersect.x + i * (hlp->screenvector.x * hlp->step);
			screen_intersect.y = hlp->left_intersect.y + i * (hlp->screenvector.y * hlp->step);
			
			hlp->door_intersect = intersection(game->player.pos, d->left, d->right, screen_intersect);
			
			dist = dist_betwen_two_points(hlp->door_intersect, game->player.pos);
			hlp->lineheight = HEIGHT / dist;
			if (i == 0 )
				printf("left:  dist: %f, mapdist: %f, lineheight: %d\n", dist, game->map.dist_buffer[hlp->left + i], hlp->lineheight);
			if (i == hlp->px_len)
				printf("right: dist: %f, mapdist: %f, lineheight: %d\n", dist, game->map.dist_buffer[hlp->left + i], hlp->lineheight);
			
				// printf("px: %f py:%f,dix:%f, diy:%f\n", game->player.pos.x, game->player.pos.y, hlp->door_intersect.x, hlp->door_intersect.y);
			if (dist < game->map.dist_buffer[hlp->left + i])
				draw_doorline(game, hlp, d, hlp->left + i);
		}
	}
}
//sl = screen left, sr = screen right, si = screen intersection
void	draw_door(t_game *game, t_door *d)
{
	t_doorhelp	hlp;
	
	hlp.sl = get_screen(&game->player, 0);
	hlp.sr = get_screen(&game->player, 1);
	hlp.doorwidth = dist_betwen_two_points(d->left, d->right);
	hlp.screenwidth = dist_betwen_two_points(hlp.sl, hlp.sr);
	hlp.screenvector = vector_between_two_points(hlp.sl, hlp.sr);
	hlp.step = hlp.screenwidth / (double)WIDTH;
	hlp.left_intersect = intersection(game->player.pos, hlp.sl, hlp.sr, d->left);
	hlp.right_intersect = intersection(game->player.pos, hlp.sl, hlp.sr, d->right);
	if (hlp.left_intersect.x != 0.0 && hlp.left_intersect.y != 0.0)
		hlp.left = get_screen_x_coord(hlp.sl, hlp.left_intersect, hlp.step);
	if (hlp.right_intersect.x != 0.0 && hlp.right_intersect.y != 0.0)
		hlp.right = get_screen_x_coord(hlp.sl, hlp.right_intersect, hlp.step);
	hlp.px_len = (int)fabs((double)(hlp.right - hlp.left));
	calc_doorlines(game, &hlp, d);
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
