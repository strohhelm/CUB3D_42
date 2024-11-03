/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alienpls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:00:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/03 14:40:44 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void append_node(t_ai **e, t_point pos, mlx_texture_t **idle, mlx_texture_t **dying)
{
	t_ai *new_node = NULL;
	t_ai *temp = *e;

	new_node = (t_ai *)malloc(sizeof(t_ai));

	new_node->tex[0] = idle;
	new_node->tex[1] = dying;
	new_node->pos = pos;
	new_node->next = NULL;
	new_node->hp = 100;
	new_node->state = ALIVE;
	new_node->i = 0;
	new_node->hit = 0;
	
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
	static int i;

	e = enemy;
	int k = 1;
	while(e)
	{
		// if (e->state == DEAD)
		// {
		// 	e = e->next;
		// 	continue;
		// }
		if (e->state == ALIVE)
			e->i = frame / 6;
		else if (frame % 6 == 0 && e->i < 7 && k)
		{
			e->i += 1;
		}
		
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
		
		
		if ((WIDTH/2 >= startx && WIDTH/2 <= endx) && (HEIGHT/2 >= starty && HEIGHT/2 <= endy) && game->player.attack)
		{
			e->hp -= 100;
			e->hit = 1;
			if (e->hp <= 0)
			{
				e->state = DYING;
				e->i = 0;
			}
			game->player.attack = 0;
		}
		
		// printf("Y: s: %d e: %d || X: s: %d e: %d\n", starty, endy, startx, endx);
		
		int line = startx;
		if (startx < 0)
			line = 0;
		tex.step = 1.0 * e->tex[e->state][e->i]->height / sheight;

		while (line < endx && proj.y > 0)
		{
			tex.tex.x = e->tex[e->state][e->i]->width * ((double)(line - startx) / swidth);	
			
			int y = starty;
			if (y < 0)
				y = 0;
				
			while(y < endy && proj.y < game->dist_arr[line])
			{
				tex.tex.y = (double)(y - starty) * tex.step;
				tex.arr_pos = ((int)tex.tex.y * e->tex[e->state][e->i]->width + (int)tex.tex.x) * 4;
				tex.tex_pos = &e->tex[e->state][e->i]->pixels[tex.arr_pos];
				tex.pic_pos = (y * game->img->width + line) * 4;
				tex.img_pos = &game->img->pixels[tex.pic_pos];
				
				tex.test = *(u_int32_t *)tex.tex_pos;
				tex.test = darken_colour(tex.test, proj.y * 15);
				if (tex.test != 0)
				{
					if (e->hit)
						*(uint32_t *)tex.img_pos = 0xFF0000FF;
					else
						*(uint32_t *)tex.img_pos = tex.test;
				}

				y++;
			}
			line++;
		}
		// if (e->i == 7)
		// 	e->state = DEAD;
		// if (game->player.attack)	
			game->player.attack = 0;
		e->hit = 0;
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
		if (e->dist <= 0.5 && game->player.hp > 0)
		{
			game->player.hp -= 5;
			health_bar(game);
			if (game->player.hp <= 0)
			{
				mlx_texture_t *end = mlx_load_png("./include/textures/GAME_OVER.png");
				mlx_image_t *go = mlx_texture_to_image(game->mlx, end);
				blank(game);
				mlx_image_to_window(game->mlx, go, 180, 100);
				game->over = 1;
				// sleep(2);
				// free_game_end(game);
			}
		}
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

	pos.x = 8.5;
	pos.y = 1.5;

	mlx_texture_t **idle;

	idle = (mlx_texture_t **)malloc(sizeof(mlx_texture_t*) * 6);
	idle[0] = mlx_load_png("./include/textures/sprites/idle/tile000.png");
	idle[1] = mlx_load_png("./include/textures/sprites/idle/tile001.png");
	idle[2] = mlx_load_png("./include/textures/sprites/idle/tile002.png");
	idle[3] = mlx_load_png("./include/textures/sprites/idle/tile003.png");
	idle[4] = mlx_load_png("./include/textures/sprites/idle/tile004.png");
	idle[5] = mlx_load_png("./include/textures/sprites/idle/tile005.png");

	mlx_texture_t **dying;

	dying = (mlx_texture_t **)malloc(sizeof(mlx_texture_t*) * 8);
	dying[0] = mlx_load_png("./include/textures/sprites/dying/dying1.png");
	dying[1] = mlx_load_png("./include/textures/sprites/dying/dying2.png");
	dying[2] = mlx_load_png("./include/textures/sprites/dying/dying3.png");
	dying[3] = mlx_load_png("./include/textures/sprites/dying/dying4.png");
	dying[4] = mlx_load_png("./include/textures/sprites/dying/dying5.png");
	dying[5] = mlx_load_png("./include/textures/sprites/dying/dying6.png");
	dying[6] = mlx_load_png("./include/textures/sprites/dying/dying7.png");
	dying[7] = mlx_load_png("./include/textures/sprites/dying/dying8.png");


	// printf("load enemies:\n");
	while(count)
	{
		append_node(&e, pos, idle, dying);
		pos.x += 2.0;
		pos.y += 0.0;
		count--;
		// printf("load %d\n", count);
	}

	return (e);
}