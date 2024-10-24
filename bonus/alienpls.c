/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alienpls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:00:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/24 17:04:45 by timschmi         ###   ########.fr       */
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
	t_texture *tex = NULL;

	double invcam = 1.0 / (game->player.scr.x * game->player.dir.y - game->player.dir.x * game->player.scr.y);
	while(e)
	{
		s.x = (e->pos.x - game->player.pos.x);
		s.y = (e->pos.y - game->player.pos.y);

		proj.x = invcam * (game->player.dir.y * s.x - game->player.dir.x * s.y);
		proj.y = invcam * ((-game->player.scr.y) * s.x + game->player.scr.x * s.y);

		int spritescrx = (int)((WIDTH / 2) * (1 + proj.x / proj.y));

		int sheight = abs((int)(HEIGHT / proj.y));
		int starty = (-sheight) / 2 + HEIGHT / 2;
		if (starty < 0)
			starty = 0;
		int endy = sheight / 2 + HEIGHT / 2;
		if (endy >= HEIGHT)
			endy = HEIGHT - 1;
		
		int swidth = abs((int)(HEIGHT / proj.y));
		int startx = (-swidth) / 2 + spritescrx;
		if (startx < 0) 
			startx = 0;
		int endx = swidth / 2 + spritescrx;
		if (endx >= WIDTH)
			endx = WIDTH - 1;
		
		
		int line = startx;

		printf("Y: s: %d e: %d || X: s: %d e: %d\n", starty, endy, startx, endx);
		while (line < endx)
		{
			tex->step = 1.0 * e->tex->height / sheight;

			tex->tex.x = e->tex->width * (line / 10);
			
			int y = starty;

			while(y < endy)
			{
				tex->tex.y = y * tex->step;
				tex->arr_pos = ((int)tex->tex.y * e->tex->width + (int)tex->tex.x) * 4;
				tex->tex_pos = &e->tex->pixels[tex->arr_pos];
				tex->pic_pos = ((starty + y) * game->img->width + line) * 4;
				tex->img_pos = &game->img->pixels[tex->pic_pos];
				
				ft_memmove(&tex->test, tex->tex_pos, 4);
				// tex->test = darken_colour(tex->test, ray->walldist * 40);
				if (tex->test > 0)
					ft_memmove(tex->img_pos, &tex->test, 4);
				
				y++;
			}
			line++;
		}
		e = e->next;
	}
}

void enemy_dist(t_game *game, t_ai *enemy)
{
	t_ai *e = enemy;

	t_point p = game->player.pos;

	t_point len;

	printf("dist\n");

	while(e)
	{
		len.x = fabs(e->pos.x - p.x);
		len.y = fabs(e->pos.y - p.y);
		
		e->dist = sqrt(pow(len.x, 2.0) + pow(len.y, 2.0));
		printf("Player: x:%lf, y:%lf\nDist: %lf\n", p.x, p.y, e->dist);
		e = e->next;
	}
	printf("sort\n");

	sort_ai(&enemy);
	// e = enemy;
	// while (e)
	// {
	// 	printf("Dist: %lf\n", e->dist);
	// 	e = e->next;
	// }
	draw_sprites(game, enemy);

}

t_ai *load_alien(t_game *game)
{
	int count = 3;
	t_point pos;
	t_ai *e = NULL;

	pos.x = 2.5;
	pos.y = 1.5;

	while(count)
	{
		append_node(&e, pos);
		pos.x += 2.0;
		pos.y += 2.0;
		count--;
		printf("loaded\n");
	}

	return (e);
}