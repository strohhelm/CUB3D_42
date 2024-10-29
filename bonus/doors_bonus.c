/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/29 20:41:40 by pstrohal         ###   ########.fr       */
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
		u = -(((a.x - b.x) * (a.y - c.y) - (a.y - b.y) * (a.x - c.x)) / denominator);
	}
	if (t > 0)
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
		s.x = player->pos.x + player->scr.x + player->dir.x;
		s.y = player->pos.y + player->scr.y + player->dir.y;
	}
	else
	{
		s.x = player->pos.x + player->dir.x - player->scr.x;
		s.y = player->pos.y + player->dir.y - player->scr.y;
	}
	return (s);
	
}

t_point	vector_between_two_points(t_point a, t_point b)
{
	t_point vector;

	vector.x = b.x - a.x;
	vector.y = b.y - a.y;
	return (vector);
}

double	dist_between_two_points(t_point a, t_point b)
{
	double	dist;
	t_point	vector;
	
	vector = vector_between_two_points(a, b);
	dist = sqrt(vector.x * vector.x + vector.y * vector.y);
	return (dist);
}


t_point	get_new_point(t_point p, t_point vector)
{
	t_point result;

	result.x = p.x + vector.x;
	result.y = p.y + vector.y;
	return (result);
}

int	get_screen_x_coord(t_doorhelp *hlp, t_point intersect)
{
	int	x_pixel_value;
	double	x_on_screen_plane;

	x_on_screen_plane = dist_between_two_points(hlp->sl, intersect);
	x_pixel_value = x_on_screen_plane / hlp->screenstep;
	return (x_pixel_value);
}


void	draw_doorline(t_game *game, t_doorhelp *hlp, t_door *d, int x)
{
	int		i;
	int		end;
	int		start;
	double	doorx;
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
	doorstep = hlp->doorwidth / (double)d->texture->width;
	
	doorx = dist_between_two_points(d->p1, hlp->door_intersect);
	
	tex_pos.x = doorx / doorstep;
	
	while (i <= hlp->lineheight)
	{
		if (start + i >= 0 && start + i <= HEIGHT)
		{
			tex_pos.y = i * tex_step;
			uint32_t tex_index = ((int)(tex_pos.y * d->texture->width) + (int)tex_pos.x ) * 4;
			texpos = &d->texture->pixels[tex_index];
			// ft_memcpy(&colour, texpos, 4);
			img_pos = &game->img->pixels[(int)(((start + i) * game->img->width * 4.0) + x * 4.0)];
			ft_memcpy(img_pos, texpos, 4);
			
			// mlx_put_pixel(game->img, x, start + i, colour);/
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
	screen_intersect.x = hlp->p1_intersect.x;
	screen_intersect.y = hlp->p1_intersect.y;
	while (++i <= hlp->px_len)
	{
		if (hlp->left + i >= 0 && hlp->left + i <= WIDTH)
		{
		
			hlp->door_intersect = intersection(game->player.pos, screen_intersect, d->p1, d->p2);

			dist = dist_between_two_points(game->player.pos, hlp->door_intersect);
			hlp->lineheight = (int)((double) HEIGHT / dist);
			
			if (i == 0 )
				printf("left:  dist: %f, mapdist: %f, lineheight: %d\n", dist, game->map.dist_buffer[hlp->left + i], hlp->lineheight);
			if (i == hlp->px_len)
				printf("right: dist: %f, mapdist: %f, lineheight: %d\n", dist, game->map.dist_buffer[hlp->left + i], hlp->lineheight);
			
				// printf("px: %f py:%f,dix:%f, diy:%f\n", game->player.pos.x, game->player.pos.y, hlp->door_intersect.x, hlp->door_intersect.y);
			if (dist < game->map.dist_buffer[hlp->left + i])
				draw_doorline(game, hlp, d, hlp->left + i);
		}
		screen_intersect.x += hlp->stepvector.x;
		screen_intersect.y += hlp->stepvector.y;
	}
}

void	handle_colinearity(t_game *game, t_doorhelp *hlp, t_point p, t_point q)
{
	t_point vector;
	vector = vector_between_two_points(game->player.pos, p);
	if ((vector.x * hlp->screenvector.x + vector.y * hlp->screenvector.y) > 0)
		{
			hlp->right = WIDTH;
			hlp->left = get_screen_x_coord(hlp, q);
			hlp->p2_intersect = hlp->sr;
		}
	else
	{
		hlp->left = 0;
		hlp->right = get_screen_x_coord(hlp, hlp->p2_intersect);
		hlp->p1_intersect = hlp->sl;
	}
	return ;
}

void	handle_left_right_situation(t_game *game, t_door *d)
{
	t_point	vector_pos_p1;
	t_point	vector_pos_p2;
	u_int32_t		tmp;

	vector_pos_p1 = vector_between_two_points(game->player.pos, d->p1);
	vector_pos_p2 = vector_between_two_points(game->player.pos, d->p2);
	
	d->hlp.left = get_screen_x_coord(&d->hlp, d->hlp.p1_intersect);
	d->hlp.right = get_screen_x_coord(&d->hlp, d->hlp.p2_intersect);
	
	if (d->hlp.left > d->hlp.right)
	{
		tmp = d->hlp.left;
		d->hlp.left = d->hlp.right;
		d->hlp.right = tmp;
	}
}
void	handle_outside_screen_intersections(t_game *game, t_doorhelp *hlp, t_door *d)
{

	if (!hlp->p2_intersect.x && !hlp->p2_intersect.y && !hlp->p1_intersect.x && !hlp->p1_intersect.y)
	{
		hlp->px_len = 0;
		return ;
	}
	else if (!hlp->p1_intersect.x && !hlp->p1_intersect.y)
		handle_colinearity(game, hlp, d->p1, d->p2);
	else if (!hlp->p2_intersect.x && !hlp->p2_intersect.y)
		handle_colinearity(game, hlp, d->p2, d->p1);
	else
	handle_left_right_situation(game, d);
	hlp->px_len = hlp->right - hlp->left;
	return ;
}

//sl = screen left, sr = screen right, si = screen intersection
void	draw_door(t_game *game, t_door *d)
{
	t_doorhelp	*hlp;

	hlp = &d->hlp;
	hlp->sl = get_screen(&game->player, 0);
	hlp->sr = get_screen(&game->player, 1);
	
	hlp->doorwidth = dist_between_two_points(d->p1, d->p2);
	hlp->screenwidth = dist_between_two_points(hlp->sl, hlp->sr);
	hlp->screenvector = vector_between_two_points(hlp->sl, hlp->sr);
	hlp->screenstep = hlp->screenwidth / (double)WIDTH;
	hlp->stepvector.x = hlp->screenvector.x * hlp->screenstep;
	hlp->stepvector.y = hlp->screenvector.y * hlp->screenstep;
	hlp->p1_intersect = intersection(game->player.pos, d->p1, hlp->sl, hlp->sr);
	hlp->p2_intersect = intersection(game->player.pos, d->p2, hlp->sl, hlp->sr);
	handle_outside_screen_intersections(game, hlp, d);
	if (hlp->px_len)
		calc_doorlines(game, &d->hlp, d);
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
