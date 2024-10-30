/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/10/30 16:57:48 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub_bonus.h"

t_point	intersection(t_point a, t_point b, t_point c, t_point d)
{
	t_point	s;
	double t;
	double	denominator;

	s.x = 0.0;
	s.y = 0.0;
	denominator = ((a.x - b.x) * (c.y - d.y) - (a.y - b.y) * (c.x - d.x));
	if (!denominator)
		return(s);
	else
	{
		t = ((a.x - c.x) * (c.y - d.y) - (a.y - c.y) * (c.x - d.x)) / denominator;
	}
	if (t > 0)
	{
		s.x = a.x + t * (b.x - a.x);
		s.y = a.y + t * (b.y - a.y);
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

t_point	get_point_plus_x_times_vector(t_point p, double x, t_point v)
{
	p.x = p.x + x * v.x;
	p.y = p.y + x * v.y;
	return(p);
}

void get_screen(t_player *player, t_doorhelp *hlp)
{
	hlp->sl.x = player->pos.x - player->scr.x;
	hlp->sl.y = player->pos.y - player->scr.y;
	hlp->sr.x = player->pos.x + player->scr.x;
	hlp->sr.y = player->pos.y + player->scr.y;
	hlp->pos.x = player->pos.x - player->dir.x;
	hlp->pos.y = player->pos.y - player->dir.y;
}
int	get_screen_x_coord(t_doorhelp *hlp, t_point intersect)
{
	int	x_pixel_value;
	double	x_on_screen_plane;
	t_point	vector;

	vector = vector_between_two_points(hlp->sl, intersect);
	x_on_screen_plane = dist_between_two_points(hlp->sl, intersect);
	if (hlp->screenvector.x * vector.x + hlp->screenvector.y * vector.y < 0)
		x_on_screen_plane *= -1;
	x_pixel_value = (int)(x_on_screen_plane / hlp->screenstep);
	printf("%f\n", x_on_screen_plane);
	return (x_pixel_value);
}


void	draw_doorline(t_game *game, t_doorhelp *hlp, t_door *d, int x)
{
	int		i;
	int		end;
	int		start;
	double	doorx;
	t_point	tex_pos;
	uint8_t *texpos;
	uint8_t *img_pos;
	double	tex_step;
	
	i = 0;
	start = -hlp->lineheight / 2 +  HEIGHT / 2 - game->y;
	end = hlp->lineheight / 2 + HEIGHT / 2;
	tex_step = 1.0 * d->texture->height / hlp->lineheight;
	doorx = dist_between_two_points(d->p1, hlp->door_intersect);
	tex_pos.x = (double)d->texture->width / (hlp->doorwidth / doorx);
	tex_pos.y = 0;
	while (i <= hlp->lineheight)
	{
		if (start + i >= 0 && start + i <= HEIGHT)
		{
			uint32_t tex_index = (((int)(tex_pos.y + EPSILON) * d->texture->width) + (int)(tex_pos.x + EPSILON) ) * 4;
			texpos = &d->texture->pixels[tex_index];
			img_pos = &game->img->pixels[(((start + i) * game->img->width) + x) * 4];
			ft_memcpy(img_pos, texpos, 4);
		}
		tex_pos.y += tex_step;
		i++;
	}
}
// distance from line through a and b to point c;
double normalize_distance(t_point a, t_point b, t_point c)
{
	double result;
	double	denominator;

	denominator = sqrt((b.y - a.y) * (b.y - a.y) + (b.x - a.x) * (b.x - a.x));
	result = fabs((b.y - a.y) * c.x - (b.x - a.x) * c.y + b.x * a.y - b.y * a.x) 
			/ denominator;
	return (result);
}


void	calc_doorlines(t_game *game, t_doorhelp *hlp, t_door *d)
{
	int		i;
	double	dist;


	i = -1;
	while (++i <= hlp->px_len)
	{
		if (hlp->left + i >= 0 && hlp->left + i <= WIDTH)
		{
			hlp->door_intersect = get_point_plus_x_times_vector(hlp->door_start, i, hlp->doorstepvector);
			dist = normalize_distance(hlp->sl, hlp->sr, hlp->door_intersect);
			hlp->lineheight = (int)((double)HEIGHT / dist);
			
			if (dist <= game->map.dist_buffer[hlp->left + i])
				draw_doorline(game, hlp, d, hlp->left + i);
			if (i == 0 || i == hlp->px_len)
			{
				for(int k = 0; k < HEIGHT; k++)
				{
					mlx_put_pixel(game->img, hlp->left + i, k, SO);
				}
			}
		}
		hlp->door_intersect = get_new_point(hlp->door_intersect, hlp->doorstepvector);
	}
}


void	set_doorvectors(t_doorhelp *hlp, t_point a, t_point b)
{
	t_point	doorvector;

	doorvector = vector_between_two_points(a, b);
	hlp->doorstepvector.x = doorvector.x / (double)hlp->px_len;
	hlp->doorstepvector.y = doorvector.y / (double)hlp->px_len;
	hlp->door_start = a;
}

void	handle_left_right_situation(t_door *d)
{
	u_int32_t		tmp;
	t_point			t;
	
	d->hlp.left = get_screen_x_coord(&d->hlp, d->hlp.p1_intersect);
	d->hlp.right = get_screen_x_coord(&d->hlp, d->hlp.p2_intersect);
	if (d->hlp.left > d->hlp.right)
	{
		tmp = d->hlp.left;
		t = d->hlp.p1_intersect;
		d->hlp.left = d->hlp.right;
		d->hlp.p1_intersect = d->hlp.p2_intersect;
		d->hlp.right = tmp;
		d->hlp.p2_intersect = t;
		d->hlp.door_intersect = d->p1;
		set_doorvectors(&d->hlp, d->p2, d->p1);
	}
	else
		set_doorvectors(&d->hlp, d->p1, d->p2);
}
void	handle_outside_screen_intersections(t_game *game, t_doorhelp *hlp, t_door *d)
{
	handle_left_right_situation(d);
	printf("left:%d, right:%d\n", hlp->left, hlp->right);
	if ((hlp->left < 0 && hlp->right < 0) || (hlp->left > WIDTH && hlp->right > WIDTH)
		|| (hlp->left < 0 && hlp->right > WIDTH))
		hlp->px_len = 0;
	else
		hlp->px_len = hlp->right - hlp->left;
	return ;
}

//sl = screen left, sr = screen right, si = screen intersection
void	draw_door(t_game *game, t_door *d)
{
	t_doorhelp	*hlp;

	hlp = &d->hlp;
	get_screen(&game->player, hlp);
	hlp->doorwidth = dist_between_two_points(d->p1, d->p2);
	hlp->screenwidth = dist_between_two_points(hlp->sl, hlp->sr);
	hlp->screenvector = vector_between_two_points(hlp->sl, hlp->sr);
	hlp->screenstep = hlp->screenwidth / WIDTH;
	hlp->stepvector.x = hlp->screenvector.x * hlp->screenstep;
	hlp->stepvector.y = hlp->screenvector.y * hlp->screenstep;
	hlp->p1_intersect = intersection(hlp->pos, d->p1, hlp->sl, hlp->sr);
	hlp->p2_intersect = intersection(hlp->pos, d->p2, hlp->sl, hlp->sr);
	handle_outside_screen_intersections(game, hlp, d);
	if (hlp->px_len > 0)
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
		// printf("p1.x:%f p1.y:%f, p2.x:%f, p2.y:%f\n", i->p1.x, i->p1.y, i->p2.x, i->p2.y);
		draw_door(game, i);
			// fflush(stdout);
			// printf("\n");
		tmp = tmp->next;
	}
	return ;
}
