#include "game.h"

int	handle_keypress(int keycode)
{
	if (keycode == ESC)
	{
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void drawLineVertical(t_mlx *mlx, int x, int height)
{
	int y;

	y = 0;
	while (y <= height)
	{
		my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x, y, RED);
		y++;
	}
}

void drawLineHorizontal(t_mlx *mlx, int y, int width)
{
	int x;

	x = 0;
	while (x <= width)
	{
		my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x, y, RED);
		x++;
	}
}

void mlx_ini(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "14x14 Grid");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr= mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_length, &mlx->endian);
}

void my_mlx_pixel_put(char *addr, int line_length, int bpp, int x, int y, int color)
{
	char *dst;

	if (x < -2 || y < 0 || x >= WIDTH || y >= HEIGHT) 
		return;
	dst = addr + (y * line_length + x * (bpp / 8));
	*(unsigned int*)dst = color;
}

void draw_squar(t_mlx *mlx, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	while (i < TILE)
	{
		j = 0;	
		while (j < TILE)
		{
			my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x * TILE + i, y * TILE + j, color);
			j++;
		}
		i++; 
	}
}

void draw_map(t_cub *game, t_mlx *mlx)
{
	int x;
	int y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == '1')
				draw_squar(mlx, x, y, RED);
			x++;
		}
		y++;
	}
}


void draw_player(t_mlx *mlx, t_player *player)
{
	int raduis;
	int i; 
	int j;

	raduis = 10;
	i = -raduis;
	while (i <= raduis)
	{
		j = -raduis;
		while (j <= raduis)
		{
			if (i*i + j*j <= raduis*raduis)
				my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp,
						(int)player->x + i, (int)player->y + j, BLU);
			j++;
		}
		i++;
	}
}

void draw_grids(t_mlx *mlx)
{
	int gridSize = TILE * 14;
	int row;
	int col = 0;

	while (col <= 14)
	{
		row = 0;
		while (row <= 14)
		{
			drawLineHorizontal(mlx, row * TILE, gridSize);
			row++;
		}
		drawLineVertical(mlx, col * TILE, gridSize);
		col++;
	}
}

void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1)
    {
        my_mlx_pixel_put(mlx->addr, mlx->line_length, mlx->bpp, x0, y0, color);
        if (x0 == x1 && y0 == y1)
		break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x0 += sx;}
        if (e2 <  dx) { err += dx; y0 += sy; }
    }
}

int render(t_cub *game)
{
	ft_bzero(game->mlx->addr, (size_t)game->mlx->line_length * HEIGHT);

	draw_grids(game->mlx);
	draw_player(game->mlx, game->player);
	draw_map(game, game->mlx);
	cast_all_rays(game);
//	draw_fov(game);
	printf("%sangle :%f%s, \n", COLORE, game->player->angle, RESET);
	printf("cos of angle :%f, \n", cos(game->player->angle));

	mlx_put_image_to_window(game->mlx->mlx, game->mlx->win, game->mlx->img, 0, 0);
	return 0;
}

int handle_keypres(int keycode, t_player *player)
{
	if (keycode == UP)
	{
		player->y += player->dir_y * player->speed;
		player->x += player->dir_x * player->speed;
	}
	if (keycode == DOWN)
	{
		player->y -= player->dir_y * player->speed;
		player->x -= player->dir_x * player->speed;
	}
	if (keycode == LEFT)
	{
		player->angle -= 0.1;
		player->dir_x = cos(player->angle);
		player->dir_y = sin(player->angle);
	}
	if (keycode == RIGHT)
	{
		player->angle += 0.1;
		player->dir_x = cos(player->angle);
		player->dir_y = sin(player->angle);
	}
	return (0);
}

void cast_all_rays(t_cub *game)
{
    double ray_angle;
    int i;

    i = 0;
    while (i < NUM_RAYS)
    {
        ray_angle = game->player->angle - (FOV / 2) + i * (FOV / NUM_RAYS);
        cast_single_ray(game, ray_angle);  // call our one-ray function
        i++;
    }
}

void cast_single_ray(t_cub *game, double angle)
{
    double ray_x = game->player->x;
    double ray_y = game->player->y;
    double step_x = cos(angle);
    double step_y = sin(angle);

    while (1)
    {
        ray_x += step_x;
        ray_y += step_y;

        if (game->map[(int)ray_y / TILE][(int)ray_x / TILE] == '1')
            break;
	
	draw_line(game->mlx, game->player->x, game->player->y, (int)ray_x, (int)ray_y, GRE);
    }
}

/*
void cast_single_ray(t_cub *game, double ray_angle)
{
    double ray_x = game->player->x;
    double ray_y = game->player->y;
    double step = 1.0; // how far the ray moves each time
    int map_x, map_y;

    while (1)
    {
        // move forward in direction of the ray
        ray_x += cos(ray_angle) * step;
        ray_y += sin(ray_angle) * step;

        // convert pixel position to map square
        map_x = (int)(ray_x / TILE);
        map_y = (int)(ray_y / TILE);

        // check if we hit a wall
        if (game->map[map_y][map_x] == '1')
        {
            draw_line(game->mlx, game->player->x, game->player->y,
                      (int)ray_x, (int)ray_y, GRE);
            break;
        }
    }
}
*/

void draw_fov(t_cub *game)
{
	int end_x;
	int end_y;
	int i;
	double ray_engle;

	i = 0;
	while (i < NUM_RAYS)
	{
		ray_engle = game->player->angle - (FOV / 2) + i * (FOV / NUM_RAYS);
		end_x = (int)(game->player->x + cos(ray_engle) * RAY_LENGTH);	
		end_y = (int)(game->player->y + sin(ray_engle) * RAY_LENGTH);	
		draw_line(game->mlx, game->player->x, game->player->y, end_x, end_y, GRE);
		i++;
	}
}
int main()
{
	t_mlx mlx;
	t_cub cub;
	t_player player;

	char *map[] = {
	"11111111111111",
	"10000000000001",
	"10000000000001",
	"10100000000001",
	"10000000000001",
	"10100000000001",
	"101100P0000001",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"10000000000001",
	"11111111111111",
	NULL,
	};

	mlx_ini(&mlx);
	cub.map = map;
	player.x = 80;
	player.y = 80;
	player.speed = 10;
	player.angle = 0;
	player.dir_x = cos(player.angle);
	player.dir_y = sin(player.angle);
	cub.player = &player;
	cub.mlx = &mlx;
	draw_grids(&mlx);
	draw_map(&cub, &mlx);
	
	mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
	mlx_hook(mlx.win, 2, 1L<<0, handle_keypres, cub.player);
	mlx_loop_hook(mlx.mlx, render, &cub);
	mlx_key_hook(mlx.win, handle_keypress, NULL); mlx_loop(mlx.mlx);
}

