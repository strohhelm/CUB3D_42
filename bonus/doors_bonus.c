/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/02 17:29:48 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub_bonus.h"

void get_screen(t_player *player, t_doorhelp *hlp)
{
	hlp->sl.x = player->pos.x - player->scr.x + player->dir.x;
	hlp->sl.y = player->pos.y - player->scr.y + player->dir.y;
	hlp->sr.x = player->pos.x + player->scr.x + player->dir.x;
	hlp->sr.y = player->pos.y + player->scr.y + player->dir.y;
	hlp->pos.x = player->pos.x;
	hlp->pos.y = player->pos.y;
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
	start = -hlp->lineheight / 2 + HEIGHT / 2 - game->y;
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
			dist = orth_distance(hlp->sl, hlp->sr, hlp->door_intersect);
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

void	set_doorvectors(t_doorhelp *hlp)
{
	t_point	doorvector;
	double	divider;
	
	divider = hlp->p1p2_angle / hlp->px_angle;
	doorvector = vector_between_two_points(hlp->left_d_point, hlp->right_d_point);
	hlp->doorstepvector.x = doorvector.x / divider;
	hlp->doorstepvector.y = doorvector.y / divider;
	hlp->door_start = get_point_plus_x_times_vector(hlp->left_d_point, hlp->left, hlp->doorstepvector);
}

int	left_or_right(t_game *game, t_doorhelp *hlp, t_point p)
{
	t_point	screenvector;
	t_point	p_orth_vector;
	double	dot_product;
	double	mag_scr;
	double	mag_orth;
	t_point	p_intersect;
	t_point	p_scr;
	t_point	p_dir;
	t_point	dir_point;

	screenvector = game->player.scr;
	p_scr = vector_between_two_points(p, get_new_point(p, screenvector));
	p_dir = get_new_point(p, p_scr);
	dir_point = get_new_point(hlp->pos, hlp->dirvector);
	p_intersect = intersection(p, p_dir, hlp->pos, dir_point);
	printf("%f | %f\n", p_intersect.x, p_intersect.y);
	p_orth_vector = vector_between_two_points(p, p_intersect);
	dot_product = dot_prod(screenvector, p_orth_vector);
	mag_scr = magn(screenvector);
	mag_orth = magn(p_orth_vector);
	if (dot_product == mag_scr * mag_orth)
		return (RIGHT);
	else if (dot_product == -1 * mag_scr * mag_orth)
		return (LEFT);
	else
		return (OOPS);
}

void set_px_len(t_doorhelp *hlp)
{
	if (hlp->left_angle <= hlp->pov_angle / 2)
	{
			hlp->left = (int)((hlp->pov_angle / 2 - hlp->left_angle) / hlp->px_angle);
		if (hlp->left == RIGHT)
			hlp->left += WIDTH / 2;
	}
	else
	{
			hlp->left = 0;
		if (hlp->left_dir == RIGHT)
			hlp->left = WIDTH;
	}
	if (hlp->right_angle <= hlp->pov_angle / 2)
	{
		hlp->right = (int)((hlp->right_angle - hlp->pov_angle / 2) / hlp->px_angle);
		if (hlp->right_dir == RIGHT)
			hlp->right += WIDTH / 2;
	}
	else
	{
		hlp->right = WIDTH;
		if (hlp->right_dir == LEFT)
			hlp->right = 0;
	}
	hlp->px_len = hlp->right - hlp->left;
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
	hlp->screenstep = hlp->screenwidth / (double)WIDTH;
	hlp->stepvector.x = hlp->screenvector.x * hlp->screenstep;
	hlp->stepvector.y = hlp->screenvector.y * hlp->screenstep;
	hlp->dirvector = game->player.dir;
	hlp->p1vector = vector_between_two_points(game->player.pos, d->p1);
	hlp->p2vector = vector_between_two_points(game->player.pos, d->p2);
	hlp->slvector = vector_between_two_points(game->player.pos, d->hlp.sl);
	hlp->srvector = vector_between_two_points(game->player.pos, d->hlp.sr);
	hlp->p1_angle = angle_between_vectors(hlp->dirvector, hlp->p1vector) * 180.0 / PI;
	hlp->p2_angle = angle_between_vectors(hlp->dirvector, hlp->p2vector) * 180.0 / PI;
	hlp->pov_angle = angle_between_vectors(hlp->slvector, hlp->srvector) * 180.0 / PI;
	hlp->p1p2_angle = angle_between_vectors(hlp->p1vector, hlp->p2vector) * 180.0 / PI;
	hlp->px_angle = hlp->pov_angle / (double)WIDTH;
	set_left_right_vectors(game, hlp, d);
	set_px_len(hlp);
	set_doorvectors(hlp);
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
