/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alienpls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:00:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/30 16:33:24 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void append_node(t_ai **e, t_point pos, mlx_texture_t **tex)
{
	t_ai *new_node = NULL;
	t_ai *temp = *e;

	new_node = (t_ai *)malloc(sizeof(t_ai));

	new_node->tex = tex;
	new_node->pos = pos;
	new_node->next = NULL;
	new_node->hp = 100;
	
	if (!*e)
	{
		*e = new_node; 
		return;
	}
	
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	swap(t_ai **head)
{
	t_ai	*first;
	t_ai	*second;

	first = *head;
	second = (*head)->next;
	first->next = second->next;
	second->next = first;
	*head = second;
}

void sort_ai(t_ai **enemy)
{
	t_ai **temp = enemy;

	while((*temp)->next)
	{
		if ((*temp)->next->dist > (*temp)->dist)
		{
			swap(temp);
			temp = enemy;
		}
		else
			temp = &(*temp)->next;
	}
}

void draw_sprites(t_game *game, t_ai *enemy, int frame)
{
	t_ai *e = enemy;

	t_point s;
	t_point proj;
	t_texture tex;
	int i;
	i = frame / 6;
	// while (e)
	// {
	// 	printf("Dist: %lf\n", e->dist);
	// 	e = e->next;
	// }

	e = enemy;

	while(e)
	{
		// if (e->hp <= 0)
		// {
		// 	e = e->next;
		// 	continue;
		// }
		s.x = (e->pos.x - game->player.pos.x);
		s.y = (e->pos.y - game->player.pos.y);
		
		double invcam = 1.0 / ((game->player.scr.x * 10) * (game->player.dir.y * 10) - (game->player.dir.x * 10) * (game->player.scr.y * 10));

		proj.x = invcam * ((game->player.dir.y * 10) * s.x - (game->player.dir.x * 10) * s.y);
		proj.y = invcam * ((-game->player.scr.y * 10) * s.x + (game->player.scr.x * 10) * s.y);

		int height_offset = (int)((0.1 - 0) / proj.y * HEIGHT);
		// printf("offset: %d\n", height_offset);

		int spritescrx = (int)((WIDTH / 2) * (1 + proj.x / proj.y));

		int sheight = abs((int)(HEIGHT / proj.y));
		int starty = (-sheight) / 2 + HEIGHT / 2 + height_offset - game->y;
		// if (starty < 0)
		// 	starty = 0;
		int endy = sheight / 2 + HEIGHT / 2 + height_offset - game->y;
		if (endy >= HEIGHT)
			endy = HEIGHT;
		
		int swidth = abs((int)(HEIGHT / proj.y));
		int startx = (-swidth) / 2 + spritescrx;
		// if (startx < 0) 
		// 	startx = 0;
		int endx = swidth / 2 + spritescrx;
		if (endx >= WIDTH)
			endx = WIDTH;
		// if ((WIDTH/2 >= startx && WIDTH/2 <= endx) && (HEIGHT/2 >= starty && HEIGHT/2 <= endy) && game->player.attack)
		// {
		// 	e->hp -= 2;
		// 	game->player.attack = 0;
		// }
		
		// printf("Y: s: %d e: %d || X: s: %d e: %d\n", starty, endy, startx, endx);
		
		int line = startx;
		if (startx < 0)
			line = 0;
		tex.step = 1.0 * e->tex[i]->height / sheight;

		while (line < endx && proj.y > 0)
		{
			tex.tex.x = e->tex[i]->width * ((double)(line - startx) / swidth);	
			
			int y = starty;
			if (y < 0)
				y = 0;
				
			while(y < endy && proj.y < game->dist_arr[line])
			{
				tex.tex.y = (double)(y - starty) * tex.step;
				tex.arr_pos = ((int)tex.tex.y * e->tex[i]->width + (int)tex.tex.x) * 4;
				tex.tex_pos = &e->tex[i]->pixels[tex.arr_pos];
				tex.pic_pos = (y * game->img->width + line) * 4;
				tex.img_pos = &game->img->pixels[tex.pic_pos];
				
				tex.test = *(u_int32_t *)tex.tex_pos;
				tex.test = darken_colour(tex.test, proj.y * 15);
				if (tex.test != 0)
					*(uint32_t *)tex.img_pos = tex.test;

				y++;
			}
			line++;
		}
		e = e->next;
	}
}

void enemy_dist(t_game *game, t_ai **enemy, int frame)
{
	t_ai *e = *enemy;

	t_point p = game->player.pos;

	t_point len;

	while(e)
	{
		len.x = fabs(e->pos.x - p.x);
		len.y = fabs(e->pos.y - p.y);
		
		e->dist = sqrt(pow(len.x, 2.0) + pow(len.y, 2.0));
		// printf("Player: x:%lf, y:%lf\nDist: %lf\n", p.x, p.y, e->dist);
		e = e->next;
	}

	sort_ai(enemy);
	// e = enemy;
	// printf("sorted:\n");
	// // while (e)
	// // {
	// // 	printf("Dist: %lf\n", e->dist);
	// // 	e = e->next;
	// // }
	draw_sprites(game, *enemy, frame);

}

t_ai *load_alien(t_game *game)
{
	int count = 1;
	t_point pos;
	t_ai *e = NULL;

	pos.x = 12.5;
	pos.y = 1.5;

	mlx_texture_t **idle;

	idle = (mlx_texture_t **)malloc(sizeof(mlx_texture_t*) * 6);
	idle[0] = mlx_load_png("./include/textures/sprites/tile000.png");
	idle[1] = mlx_load_png("./include/textures/sprites/tile001.png");
	idle[2] = mlx_load_png("./include/textures/sprites/tile002.png");
	idle[3] = mlx_load_png("./include/textures/sprites/tile003.png");
	idle[4] = mlx_load_png("./include/textures/sprites/tile004.png");
	idle[5] = mlx_load_png("./include/textures/sprites/tile005.png");


	// printf("load enemies:\n");
	while(count)
	{
		append_node(&e, pos, idle);
		pos.x += 2.0;
		pos.y += 0.0;
		count--;
		// printf("load %d\n", count);
	}

	return (e);
}