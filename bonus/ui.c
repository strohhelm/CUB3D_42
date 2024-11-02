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