// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   door_bonus.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/11/01 18:41:16 by pstrohal          #+#    #+#             */
// /*   Updated: 2024/11/07 22:56:26 by pstrohal         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// # include "../cub_bonus.h"


// void	calc_doorlines(t_game *game, t_doorhelp *hlp, t_door *d)
// {
// 	int		i;
// 	double	dist;
// 	double angle;
// 	t_point	vector;
// 	t_point	screen_intersect;
// 	i = -1;
// 	while (++i <= hlp->px_len)
// 	{

// 			screen_intersect = get_point_plus_x_times_vector(hlp->sl, (double)(hlp->left + i + EPSILON), hlp->screenvector);
// 			hlp->door_intersect = intersection(hlp->pos, screen_intersect, hlp->left_d_point, hlp->right_d_point);
// 			dist = dist_between_two_points(hlp->pos, hlp->door_intersect);
// 			angle = angle_between_vectors(hlp->dirvector, vector_between_two_points(hlp->pos, hlp->door_intersect));
// 			dist *= cos(angle);
// 			hlp->lineheight = (int)round(HEIGHT / dist);
			
// 			// if (dist <= game->map.dist_buffer[hlp->left + i])
// 				draw_doorline(game, hlp, d, hlp->left + i);
// 			if (hlp->left + i == hlp->left || hlp->left + i == hlp->right)
// 			{
// 				for(int k = 0; k < HEIGHT; k++)
// 				{
// 					mlx_put_pixel(game->img, hlp->left + i, k, EA);
// 				}
// 			}
// 		// dist += distjump;
// 	}
// }

// t_point	get_door_intersect(t_doorhelp *hlp, int i)
// {
// 	t_point	tmp;
// 	t_point	vector;
// 	double	angle;
// 	double dir_angle;
// 	double magnitude;

// 	vector = hlp->left_vector;
// 	vector = normalize(vector);
// 	angle = atan2(vector.y, vector.x);
// 	// if (i == hlp->px_len)
// 	// 	printf("before: %f ", angle * 180 /PI);
// 	// magnitude = angle;
// 	// angle += (double)i * hlp->px_angle;
// 	// if (i == hlp->px_len)
// 	// 	printf("after: %f total:%f dangle:%f\n", angle * 180 / PI, (magnitude - angle) * 108 / PI, hlp->p1p2_angle * 180 / PI);
// 	// fflush(stdout);
// 	vector.x = cos(angle);
// 	vector.y = sin(angle);
// 	tmp = get_new_point(hlp->pos, vector);
// 	tmp = intersection(hlp->pos, tmp, hlp->left_d_point, hlp->right_d_point);
// 	return (tmp);
// }

// void	set_doorvectors(t_doorhelp *hlp)
// {
// 	t_point	doorvector;
// 	double	divider;
	
// 	divider = hlp->p1p2_angle / hlp->px_angle;
// 	doorvector = vector_between_two_points(hlp->left_d_point, hlp->right_d_point);
// 	hlp->doorstepvector.x = doorvector.x / divider;
// 	hlp->doorstepvector.y = doorvector.y / divider;
// }

// t_point	get_screen_intersect(t_doorhelp *hlp, int i)
// {
// 	double camx;
// 	t_point	ray_dir;

// 	camx = 2 * i / (double)WIDTH - 1;
// 	ray_dir.x = hlp->dirvector.x + hlp->scr.x * camx;
// 	ray_dir.y = hlp->dirvector.x + hlp->scr.y * camx;
// 	return(get_new_point(hlp->pos, ray_dir));
// }

// int	get_screen_x_coord(t_doorhelp *hlp, t_point intersect)
// {
// 	int	x_pixel_value;
// 	double	x_on_screen_plane;
// 	t_point	vector;

// 	vector = vector_between_two_points(hlp->sl, intersect);
// 	x_on_screen_plane = dist_between_two_points(hlp->sl, intersect);
// 	if (hlp->screenvector.x * vector.x + hlp->screenvector.y * vector.y < 0)
// 		x_on_screen_plane *= -1;
// 	x_pixel_value = (int)(x_on_screen_plane / hlp->screenstep);
// 	// printf("%f\n", x_on_screen_plane);
// 	return (x_pixel_value);
// }

// int	get_screen_coord(t_doorhelp *hlp, int i)
// {
// 	t_point	vector;
// 	double	angle;
// 	int	amount;

// 	if (i == LEFT)
// 		vector = hlp->left_vector;
// 	else
// 		vector = hlp->right_vector;
// 	angle = angle_between_vectors(hlp->slvector, vector);
// 	amount = (int)(angle / hlp->px_angle);
// 	return (amount);
// }

// void set_px_len(t_doorhelp *hlp)
// {
// 	double	half_pov;
// 	double	delta;

// 	half_pov = hlp->pov_angle / 2.0;
// 	hlp->left_intersect = intersection(hlp->pos, hlp->left_d_point, hlp->sl, hlp->sr);
// 	hlp->right_intersect = intersection(hlp->pos, hlp->right_d_point, hlp->sl, hlp->sr);
// 	hlp->dist_left = dist_between_two_points(hlp->pos, hlp->left_d_point);
// 	hlp->dist_right = dist_between_two_points(hlp->pos, hlp->right_d_point);
// 	if (hlp->left_angle < half_pov)
// 	{
// 		// hlp->left = get_screen_coord(hlp, LEFT);
// 		hlp->left = get_screen_x_coord(hlp, hlp->left_intersect);
// 		hlp->door_start = hlp->left_d_point;
// 	}
// 	else
// 	{
// 		hlp->left = 0;
// 		if (hlp->left_dir == RIGHT)
// 			hlp->left = WIDTH;
// 		delta = (hlp->left_angle - half_pov) / hlp->px_angle;
// 		hlp->door_start = get_point_plus_x_times_vector(hlp->left_d_point, delta, hlp->doorstepvector);
// 	}
// 	if (hlp->right_angle < half_pov)
// 		hlp->right = get_screen_x_coord(hlp, hlp->right_intersect);
// 	else
// 	{
// 		hlp->right = WIDTH;
// 		if (hlp->right_dir == LEFT)
// 			hlp->right = 0;
// 	}
// 	hlp->px_len = hlp->right - hlp->left;
// 	if (hlp->left_angle > NINETY && hlp->right_angle > NINETY)
// 		hlp->px_len = 0;
// }
// void	draw_door(t_game *game, t_door *d)
// {
// 	t_doorhelp	*hlp;
	
// 	hlp = &d->hlp;
// 	get_screen(&game->player, hlp);
// 	hlp->doorwidth = dist_between_two_points(d->p1, d->p2);
// 	hlp->screenwidth = dist_between_two_points(hlp->sl, hlp->sr);
// 	hlp->screenvector = vector_between_two_points(hlp->sl, hlp->sr);
// 	hlp->screenstep = hlp->screenwidth / (double)WIDTH;
// 	hlp->stepvector.x = hlp->screenvector.x / (double)WIDTH;
// 	hlp->stepvector.y = hlp->screenvector.y / (double)WIDTH;
// 	hlp->dirvector = game->player.dir;
// 	hlp->p1vector = vector_between_two_points(game->player.pos, d->p1);
// 	hlp->p2vector = vector_between_two_points(game->player.pos, d->p2);
// 	hlp->slvector = vector_between_two_points(game->player.pos, hlp->sl);
// 	hlp->srvector = vector_between_two_points(game->player.pos, hlp->sr);
// 	hlp->p1_angle = angle_between_vectors(hlp->dirvector, hlp->p1vector);
// 	hlp->p2_angle = angle_between_vectors(hlp->dirvector, hlp->p2vector);
// 	hlp->pov_angle = angle_between_vectors(hlp->slvector, hlp->srvector);
// 	hlp->p1p2_angle = angle_between_vectors(hlp->p1vector, hlp->p2vector);
// 	hlp->px_angle = hlp->pov_angle / (double)WIDTH;
// 	set_left_right_vectors(game, hlp, d);
// 	set_px_len(hlp);
// 	set_doorvectors(hlp);

// 	int i = -1;
// 	t_point screenx;
// 	double	dist;
// 	double angle;
// 	while (++i < WIDTH)
// 	{
// 		screenx = get_point_plus_x_times_vector(hlp->sl, (double)i, hlp->stepvector);
// 		hlp->door_intersect = intersection(hlp->pos, screenx, d->p1, d->p2);
// 		if (hlp->door_intersect.x && hlp->door_intersect.y)
// 		{
// 			dist = dist_between_two_points(hlp->pos, hlp->door_intersect);
// 			angle = angle_between_vectors(hlp->dirvector, vector_between_two_points(hlp->pos, screenx));
// 			dist *= cos(angle);
// 			hlp->lineheight = (int)((double)HEIGHT / dist);
// 			if (dist <= game->map.dist_buffer[i])
// 				draw_doorline(game, hlp, d, i);
// 		}
// 	}
// }

// // distance from line through a and b to point c;
// double orth_distance(t_point a, t_point b, t_point c)
// {
// 	double result;
// 	double	denominator;
// 	double numerator;
	
// 	denominator = sqrt(pow(b.y - a.y, 2) + pow(b.x - a.x, 2));
// 	numerator = (b.y - a.y) * c.x - (b.x - a.x) * c.y + (b.x * a.y - b.y * a.x);
// 	result = fabs(numerator) / denominator;
// 	return (result);
// }

// double magn(t_point a)
// {
// 	return (sqrt(a.x * a.x + a.y * a.y));
// }

// void	set_p1_left_p2_right(t_doorhelp *hlp, t_door *d)
// {
// 	// printf("left: p1, right p2\n");
// 		hlp->left_vector = hlp->p1vector;
// 		hlp->left_d_point = d->p1;
// 		hlp->right_vector = hlp->p2vector;
// 		hlp->right_d_point = d->p2;
// 		hlp->left_angle = hlp->p1_angle;
// 		hlp->right_angle = hlp->p2_angle;
// 		hlp->left_dir = hlp->p1_dir;
// 		hlp->right_dir = hlp->p2_dir;
// }
// void	set_p2_left_p1_right(t_doorhelp *hlp, t_door *d)
// {
// 		// printf("left: p2, right p1\n");
// 		hlp->left_vector = hlp->p2vector;
// 		hlp->left_d_point = d->p2;
// 		hlp->right_vector = hlp->p1vector;
// 		hlp->right_d_point = d->p1;
// 		hlp->left_angle = hlp->p2_angle;
// 		hlp->right_angle = hlp->p1_angle;
// 		hlp->left_dir = hlp->p2_dir;
// 		hlp->right_dir = hlp->p1_dir;
// }

// void	set_left_right_vectors(t_game *game, t_doorhelp *hlp, t_door *d)
// {
// 	hlp->p1_dir = left_or_right(game, hlp, d->p1);
// 	hlp->p2_dir = left_or_right(game, hlp, d->p2);
// 	// if (hlp->p1_dir == LEFT)
// 	// 	printf("p1: LEFT ");
// 	// else if (hlp->p1_dir == RIGHT)
// 	// 	printf("p1: RIGHT ");
// 	// if (hlp->p2_dir == LEFT)
// 	// 	printf("p2: LEFT ");
// 	// else if (hlp->p2_dir == RIGHT)
// 	// 	printf("p2: RIGHT ");
// 	// printf("\n");
	
// 	hlp->p1_dist = orth_distance(hlp->pos,
// 			get_new_point(hlp->pos, hlp->dirvector), d->p1);
// 	hlp->p2_dist = orth_distance(hlp->pos,
// 			get_new_point(hlp->pos, hlp->dirvector), d->p2);
// 	if (hlp->p1_dir == LEFT && hlp->p2_dir == RIGHT)
// 		set_p1_left_p2_right(hlp, d);
// 	else if (hlp->p1_dir == RIGHT && hlp->p2_dir == LEFT)
// 		set_p2_left_p1_right(hlp, d);
// 	else if (hlp->p1_dir == RIGHT && hlp->p2_dir == RIGHT)
// 	{
// 		if (hlp->p1_dist <= hlp->p2_dist)
// 			set_p1_left_p2_right(hlp, d);
// 		else
// 			set_p2_left_p1_right(hlp, d);
// 	}
// 	else
// 	{
// 		if (hlp->p1_dist >= hlp->p2_dist)
// 			set_p1_left_p2_right(hlp, d);
// 		else
// 			set_p2_left_p1_right(hlp, d);
// 	}
// }
// t_point	get_new_point(t_point p, t_point vector)
// {
// 	t_point result;

// 	result.x = p.x + vector.x;
// 	result.y = p.y + vector.y;
// 	return (result);
// }
// t_point	normalize(t_point p)
// {
// 	double	m;

// 	m = magn(p);
// 	p.x /= m;
// 	p.y /= m;
// 	return (p);
// }

// typedef struct s_doorhelp
// {
// 	int		px_len;
// 	t_point	left_intersect;
// 	t_point	right_intersect;
// 	t_point	door_intersect;
// 	t_point	door_start;
// 	t_point	doorstepvector;
// 	t_point	sl;
// 	t_point	sr;
// 	t_point	dirvector;
// 	t_point	p1vector;
// 	t_point	p2vector;
// 	t_point	slvector;
// 	t_point	srvector;
// 	t_point	left_vector;
// 	t_point	right_vector;
// 	t_point	left_d_point;
// 	t_point	right_d_point;
// 	double	left_angle;
// 	double	right_angle;
// 	double	p1_angle;
// 	double	p2_angle;
// 	double	pov_angle;
// 	double	p1p2_angle;
// 	t_point	screenvector;
// 	double	screenwidth;
// 	t_point	stepvector;
// 	double	screenstep;
// 	double	doorwidth;
// 	double	doorstep;
// 	double	px_angle;
// 	int		left;
// 	int		right;
// 	int		lineheight;
// 	int		left_dir;
// 	int		right_dir;
// 	int		p1_dir;
// 	int		p2_dir;
// 	double	p1_dist;
// 	double	p2_dist;
// 	double dist_left;
// 	double dist_right;
// 	t_point	pos;
// 	t_point	scr;
// }	t_doorhelp;