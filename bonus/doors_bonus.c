/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:21:53 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/05 21:10:57 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../cub_bonus.h"

void get_screen(t_player *player, t_doorhelp *hlp)
{
	hlp->sl.x = player->pos.x - player->scr.x + player->dir.x;
	hlp->sl.y = player->pos.y - player->scr.y + player->dir.y;
	hlp->sr.x = player->pos.x + player->scr.x + player->dir.x;
	hlp->sr.y = player->pos.y + player->scr.y + player->dir.y;
	hlp->pos = player->pos;
	hlp->scr = player->scr;
	
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
	doorx = dist_between_two_points(hlp->left_d_point, hlp->door_intersect);
	
	tex_pos.x = (double)d->texture->width / (hlp->doorwidth / doorx);
	tex_pos.y = 0;
	while (i <= hlp->lineheight)
	{
		if (start + i >= 0 && start + i <= HEIGHT)
		{
			uint32_t tex_index = (((int)round(tex_pos.y) * d->texture->width) + (int)round(tex_pos.x) ) * 4;
			texpos = &d->texture->pixels[tex_index];
			img_pos = &game->img->pixels[(((start + i) * game->img->width) + x) * 4];
			ft_memcpy(img_pos, texpos, 4);
		}
		tex_pos.y += tex_step;
		i++;
	}
}

t_point	get_door_intersect(t_doorhelp *hlp, int i)
{
	t_point	tmp;
	t_point	vector;
	double	angle;
	double dir_angle;
	double magnitude;

	vector = hlp->left_vector;
	vector = normalize(vector);
	angle = atan2(vector.y, vector.x);
	// if (i == hlp->px_len)
	// 	printf("before: %f ", angle * 180 /PI);
	// magnitude = angle;
	// angle += (double)i * hlp->px_angle;
	// if (i == hlp->px_len)
	// 	printf("after: %f total:%f dangle:%f\n", angle * 180 / PI, (magnitude - angle) * 108 / PI, hlp->p1p2_angle * 180 / PI);
	// fflush(stdout);
	vector.x = cos(angle);
	vector.y = sin(angle);
	tmp = get_new_point(hlp->pos, vector);
	tmp = intersection(hlp->pos, tmp, hlp->left_d_point, hlp->right_d_point);
	return (tmp);
}

t_point	get_screen_intersect(t_doorhelp *hlp, int i)
{
	double camx;
	t_point	ray_dir;

	camx = 2 * i / (double)WIDTH - 1;
	ray_dir.x = hlp->dirvector.x + hlp->scr.x * camx;
	ray_dir.y = hlp->dirvector.x + hlp->scr.y * camx;
	return(get_new_point(hlp->pos, ray_dir));
}

void	calc_doorlines(t_game *game, t_doorhelp *hlp, t_door *d)
{
	int		i;
	double	dist;
	double angle;
	t_point	vector;
	t_point	screen_intersect;
	i = -1;
	while (++i <= hlp->px_len)
	{

			screen_intersect = get_point_plus_x_times_vector(hlp->sl, (double)(hlp->left + i + EPSILON), hlp->screenvector);
			hlp->door_intersect = intersection(hlp->pos, screen_intersect, hlp->left_d_point, hlp->right_d_point);
			dist = dist_between_two_points(hlp->pos, hlp->door_intersect);
			angle = angle_between_vectors(hlp->dirvector, vector_between_two_points(hlp->pos, hlp->door_intersect));
			dist *= cos(angle);
			hlp->lineheight = (int)round(HEIGHT / dist);
			
			// if (dist <= game->map.dist_buffer[hlp->left + i])
				draw_doorline(game, hlp, d, hlp->left + i);
			if (hlp->left + i == hlp->left || hlp->left + i == hlp->right)
			{
				for(int k = 0; k < HEIGHT; k++)
				{
					mlx_put_pixel(game->img, hlp->left + i, k, EA);
				}
			}
		// dist += distjump;
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
	// printf("%f\n", x_on_screen_plane);
	return (x_pixel_value);
}
int	get_screen_coord(t_doorhelp *hlp, int i)
{
	t_point	vector;
	double	angle;
	int	amount;

	if (i == LEFT)
		vector = hlp->left_vector;
	else
		vector = hlp->right_vector;
	angle = angle_between_vectors(hlp->slvector, vector);
	amount = (int)(angle / hlp->px_angle);
	return (amount);
}

void set_px_len(t_doorhelp *hlp)
{
	double	half_pov;
	double	delta;

	half_pov = hlp->pov_angle / 2.0;
	hlp->left_intersect = intersection(hlp->pos, hlp->left_d_point, hlp->sl, hlp->sr);
	hlp->right_intersect = intersection(hlp->pos, hlp->right_d_point, hlp->sl, hlp->sr);
	hlp->dist_left = dist_between_two_points(hlp->pos, hlp->left_d_point);
	hlp->dist_right = dist_between_two_points(hlp->pos, hlp->right_d_point);
	if (hlp->left_angle < half_pov)
	{
		// hlp->left = get_screen_coord(hlp, LEFT);
		hlp->left = get_screen_x_coord(hlp, hlp->left_intersect);
		hlp->door_start = hlp->left_d_point;
	}
	else
	{
		// hlp->left = 0;
		// if (hlp->left_dir == RIGHT)
			// hlp->left = WIDTH;
		// delta = (hlp->left_angle - half_pov) / hlp->px_angle;
		// hlp->door_start = get_point_plus_x_times_vector(hlp->left_d_point, delta, hlp->doorstepvector);
	}
	if (hlp->right_angle < half_pov)
		hlp->right = get_screen_x_coord(hlp, hlp->right_intersect);
	// else
	// {
	// 	hlp->right = WIDTH;
	// 	if (hlp->right_dir == LEFT)
	// 		hlp->right = 0;
	// }
	hlp->px_len = hlp->right - hlp->left;
	if (hlp->left_angle > NINETY && hlp->right_angle > NINETY)
		hlp->px_len = 0;
}
	// printf("left_angle: %f, right_angle: %f\n", hlp->left_angle, hlp->right_angle);
	// printf("left: %d, right %d\n", hlp->left, hlp->right);
	// fflush(stdout);


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
	hlp->stepvector.x = hlp->screenvector.x / (double)WIDTH;
	hlp->stepvector.y = hlp->screenvector.y / (double)WIDTH;
	hlp->dirvector = game->player.dir;
	hlp->p1vector = vector_between_two_points(game->player.pos, d->p1);
	hlp->p2vector = vector_between_two_points(game->player.pos, d->p2);
	hlp->slvector = vector_between_two_points(game->player.pos, hlp->sl);
	hlp->srvector = vector_between_two_points(game->player.pos, hlp->sr);
	hlp->p1_angle = angle_between_vectors(hlp->dirvector, hlp->p1vector);
	hlp->p2_angle = angle_between_vectors(hlp->dirvector, hlp->p2vector);
	hlp->pov_angle = angle_between_vectors(hlp->slvector, hlp->srvector);
	hlp->p1p2_angle = angle_between_vectors(hlp->p1vector, hlp->p2vector);
	hlp->px_angle = hlp->pov_angle / (double)WIDTH;
	set_left_right_vectors(game, hlp, d);
	set_px_len(hlp);
	set_doorvectors(hlp);

	int i = -1;
	t_point screenx;
	double	dist;
	double angle;
	while (++i < WIDTH)
	{
		screenx = get_point_plus_x_times_vector(hlp->sl, (double)i, hlp->stepvector);
		hlp->door_intersect = intersection(hlp->pos, screenx, hlp->left_d_point, hlp->right_d_point);
		if (hlp->door_intersect.x && hlp->door_intersect.y)
		{
			dist = dist_between_two_points(hlp->pos, hlp->door_intersect);
			angle = angle_between_vectors(hlp->dirvector, vector_between_two_points(hlp->pos, screenx));
			dist *= cos(angle);
			hlp->lineheight = (int)((double)HEIGHT / dist);
			if (dist <= game->map.dist_buffer[i])
				draw_doorline(game, hlp, d, i);
		}
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

		tmp = tmp->next;
	}
	return ;
}
