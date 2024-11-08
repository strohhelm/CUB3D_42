/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:09:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/11/08 13:35:29 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void health_bar(t_game *game)
{
    int start = WIDTH/2 - 250;
    int end = WIDTH/2 + 250;
    int hp = start + game->player.hp * 5;
    int height = 15;
    int starty = HEIGHT - HEIGHT/15;

    int y = starty;
    
    while (y <= starty + height)
    {
        int x = start;
        while(x <= end)
        {
            if (x < hp)
                mlx_put_pixel(game->hp, x, y, 0xFF0000FF);
            else
                mlx_put_pixel(game->hp, x, y, 0x00000000);
            x++;
        }
        y++;
    }
}

void load_gun(t_game *game)
{
    mlx_texture_t **gun;
    mlx_image_t *gun_img;
	gun = (mlx_texture_t **)malloc(sizeof(mlx_texture_t*) * 4);
    gun[0] = mlx_load_png("include/textures/gunsprites/1.png");
    gun[1] = mlx_load_png("include/textures/gunsprites/2.png");
    gun[2] = mlx_load_png("include/textures/gunsprites/3.png");
    gun[3] = mlx_load_png("include/textures/gunsprites/4.png");
    gun_img = mlx_texture_to_image(game->mlx, gun[0]);

    game->player.gun = gun;
    game->player.gun_img = gun_img;
    mlx_image_to_window(game->mlx, gun_img, WIDTH - 600, HEIGHT - 500);
}

void gun_anim(t_game *game, int frame)
{
    static int i = 0;
    if (game->player.attack)
        game->player.attack = 2;
    else if(!game->player.attack)
        return;
    if (frame % 4 == 0 && i < 3)
        i++;
    // printf("Gun ani %d\n", i);
    mlx_delete_image(game->mlx, game->player.gun_img);
    game->player.gun_img = mlx_texture_to_image(game->mlx, game->player.gun[i]);
    mlx_image_to_window(game->mlx, game->player.gun_img, WIDTH - 600, HEIGHT - 500);

    if (i >= 3)
    {
        mlx_delete_image(game->mlx, game->player.gun_img);
        game->player.gun_img = mlx_texture_to_image(game->mlx, game->player.gun[0]);
        mlx_image_to_window(game->mlx, game->player.gun_img, WIDTH - 600, HEIGHT - 500);
        i = 0;
    	game->player.attack = 0;
    }
}
