#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx/mlx.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef struct s_img {
	void 	*img;
	int		*data;

	int		img_width;
	int		img_height;
	int		size_l;
	int		bpp;
	int		endian;
}t_img;

typedef struct s_game {
	void	*mlx;
	void	*win;
	t_img	img;
	int		buf[screenHeight][screenWidth];
	int		**texture;

	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;

	double	moveSpeed;
	double	rotSpeed;
}t_game;

void verLine(t_game *game, int x, int y1, int y2, int color);
int main_loop(t_game * game);

int 	main(void){
	t_game game;
	game.posX = 22.0;
	game.posY = 11.5;
	game.dirX = -1.0;
	game.dirY = 0.0;
	game.planeX = 0.0;
	game.planeY = 0.66;
	game.moveSpeed = 0.05;
	game.rotSpeed = 0.05;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, screenWidth, screenHeight, "test");
	for (int i = 0; i < screenHeight; i++){
		for (int j = 0; j < screenWidth; j++){
			game.buf[i][j] = 0;
		}
	}
	main_loop(&game);
	mlx_loop(game.mlx);
}

int		main_loop(t_game *game){
	for (int x = 0; x < screenWidth; x++){
		double cameraX = 2 * x / (double)screenWidth - 1;
		double rayDirX = game->dirX + game->planeX * cameraX;
		double rayDirY = game->dirY + game->planeY * cameraX;

		int mapX = (int)game->posX;
		int mapY = (int)game->posY;

		double sideDistX, sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0){
			stepX = -1;
			sideDistX = (game->posX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - game->posX) * deltaDistX;
		}
		if (rayDirY < 0){
			stepY = -1;
			sideDistY = (game->posY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - game->posY) * deltaDistY;
		}
		while (hit == 0){
			if (sideDistX < sideDistY){
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (worldMap[mapX][mapY] > 0){
				hit = 1;
			}
		}
		if (side == 0)
			perpWallDist = (mapX - game->posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - game->posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(screenHeight / perpWallDist);

		int drawStart = -lineHeight / 2 + screenHeight / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + screenHeight / 2;
		if (drawEnd >= screenHeight)
			drawEnd = screenHeight - 1;

		int color;
		if (worldMap[mapX][mapY] == 1)
			color = 0xff0000;
		else if (worldMap[mapX][mapY] == 2)
			color = 0x00ff00;
		else if (worldMap[mapX][mapY] == 3)
			color = 0x0000ff;
		else if (worldMap[mapX][mapY] == 4)
			color = 0xffffff;
		else
			color = 0xffff00;
		if (side == 1)
			color /= 2;
		verLine(game, x, drawStart, drawEnd, color);
	}
	return (0);
}

void	verLine(t_game *game, int x, int y1, int y2, int color){
	int y;
	y = y1;
	while (y <= y2){
		mlx_pixel_put(game->mlx, game->win, x, y, color);
		y++;
	}
}
