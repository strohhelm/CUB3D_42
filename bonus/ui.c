#include "../cub_bonus.h"

void health_bar(t_game *game)
{
    mlx_image_t *hp;
    hp = mlx_new_image(game->mlx, WIDTH, HEIGHT);

    int start = WIDTH/2 - 250;
    int end = WIDTH/2 + 250;
    int height = 15;
    int starty = HEIGHT - HEIGHT/10;

    int y = starty;

    while (y <= starty + height)
    {
        int x = start;
        while(x <= end)
        {
            mlx_put_pixel(hp, x, y, 0xFF0000FF);
            x++;
        }
        y++;
    }




    mlx_image_to_window(game->mlx, hp, 0, 0);
}