/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/04 14:25:31 by pstrohal         ###   ########.fr       */
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

void set_px_len(t_doorhelp *hlp)
{
	double	half_pov;

	half_pov = hlp->pov_angle / 2.0;
	if (hlp->left_angle <= hlp->pov_angle / 2.0)
	{
		if (hlp->left_dir == LEFT)
			hlp->left = (int)((hlp->pov_angle / 2.0 - hlp->left_angle) / hlp->px_angle + EPSILON);
		else
			hlp->left = (int)((hlp->pov_angle / 2.0 + hlp->left_angle) / hlp->px_angle + EPSILON);
	}
	else
	{
		hlp->left = 0;
		if (hlp->left_dir == RIGHT)
			hlp->left = WIDTH;
	}
	if (hlp->right_angle < hlp->pov_angle / 2.0)
	{
		if (hlp->right_dir == LEFT)
			hlp->right = (int)((hlp->pov_angle / 2.0 - hlp->right_angle) / hlp->px_angle + EPSILON);
		else
			hlp->right = (int)((hlp->pov_angle / 2.0 + hlp->right_angle) / hlp->px_angle + EPSILON);
	}
	else
	{
		hlp->right = WIDTH;
		if (hlp->right_dir == LEFT)
			hlp->right = 0;
	}
	hlp->px_len = hlp->right - hlp->left;
	printf("left_angle: %f, right_angle: %f\n", hlp->left_angle, hlp->right_angle);
	printf("left: %d, right %d\n", hlp->left, hlp->right);
	printf("\n");
	fflush(stdout);

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
	hlp->p1_angle = angle_between_vectors(hlp->dirvector, hlp->p1vector);
	hlp->p2_angle = angle_between_vectors(hlp->dirvector, hlp->p2vector);
	hlp->pov_angle = angle_between_vectors(hlp->slvector, hlp->srvector);
	hlp->p1p2_angle = angle_between_vectors(hlp->p1vector, hlp->p2vector);
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
