/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alienpls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:00:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/28 18:02:46 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void append_node(t_ai **e, t_point pos)
{
	t_ai *new_node = NULL;
	t_ai *temp = *e;

	new_node = (t_ai *)malloc(sizeof(t_ai));

	new_node->tex = mlx_load_png("./include/textures/ALIEN.png");
	new_node->pos = pos;
	new_node->next = NULL;
	
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


void draw_sprites(t_game *game, t_ai *enemy)
{
	t_ai *e = enemy;

	t_point s;
	t_point proj;
	// double spritescrx;
	t_texture tex;

	while (e)
	{
		printf("Dist: %lf\n", e->dist);
		e = e->next;
	}

	e = enemy;

	while(e)
	{
		s.x = (e->pos.x - game->player.pos.x);
		s.y = (e->pos.y - game->player.pos.y);
		
		double invcam = 1.0 / (game->player.scr.x * game->player.dir.y - game->player.dir.x * game->player.scr.y);

		proj.x = invcam * (game->player.dir.y * s.x - game->player.dir.x * s.y);
		proj.y = invcam * ((-game->player.scr.y) * s.x + game->player.scr.x * s.y);

		int height_offset = (int)((1 - -1.0) / proj.y * HEIGHT);
		printf("offset: %d\n", height_offset);
		if (proj.y < 0)
		{
			e = e->next;
			continue;
		}
		int spritescrx = (int)((WIDTH / 2) * (1 + proj.x / proj.y));

		int sheight = abs((int)(HEIGHT / proj.y)) * 7;
		int starty = (-sheight) / 2 + HEIGHT / 2 + height_offset - game->y;
		if (starty < 0)
			starty = 0;
		int endy = sheight / 2 + HEIGHT / 2 + height_offset - game->y;
		if (endy >= HEIGHT)
			endy = HEIGHT - 1;
		
		int swidth = abs((int)(HEIGHT / proj.y)) * 7;
		int startx = (-swidth) / 2 + spritescrx;
		// if (startx < 0) 
		// 	startx = 0;
		int endx = swidth / 2 + spritescrx;
		if (endx >= WIDTH)
			endx = WIDTH - 1;
		
		printf("Y: s: %d e: %d || X: s: %d e: %d\n", starty, endy, startx, endx);
		
		int line = startx;
		if (startx < 0)
			line = 0;
		tex.step = 1.0 * e->tex->height / sheight;

		while (line < endx)
		{
			tex.tex.x = e->tex->width * ((double)(line - startx) / swidth);	
			int y = starty;
			
			while(y < endy && e->dist < game->dist_arr[line])
			{
				tex.tex.y = (double)(y - starty) * tex.step;
				tex.arr_pos = ((int)tex.tex.y * e->tex->width + (int)tex.tex.x) * 4;
				tex.tex_pos = &e->tex->pixels[tex.arr_pos];
				tex.pic_pos = (y * game->img->width + line) * 4;
				tex.img_pos = &game->img->pixels[tex.pic_pos];
				
				tex.test = *(u_int32_t *)tex.tex_pos;
				if (tex.test != 0)
					*(uint32_t *)tex.img_pos = tex.test;

				// ft_memmove(&tex.test, tex.tex_pos, 4);
				// if (tex.test > 0)
				// 	ft_memmove(tex.img_pos, &tex.test, 4);

				y++;
			}
			line++;
		}
		e = e->next;
	}
}

void enemy_dist(t_game *game, t_ai **enemy)
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
	draw_sprites(game, *enemy);

}

t_ai *load_alien(t_game *game)
{
	int count = 3;
	t_point pos;
	t_ai *e = NULL;

	pos.x = 5.5;
	pos.y = 1.5;


	printf("load enemies:\n");
	while(count)
	{
		append_node(&e, pos);
		pos.x += 2.0;
		pos.y += 0.0;
		count--;
		printf("load %d\n", count);
	}

	return (e);
}