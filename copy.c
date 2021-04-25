#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mlx/mlx.h"

#define texWidth 64
#define texHeight 64
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

#define X_EVENT_KEY_PRESS       2
#define X_EVENT_KEY_RELEASE     3
#define X_EVENT_KEY_EXIT        17

#define KEY_ESC        53
# define KEY_Q        12
# define KEY_W        13
# define KEY_E        14
# define KEY_R        15
# define KEY_A        0
# define KEY_S        1
# define KEY_D        2

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
    void     *img;
    int        *data;

    int        img_width;
    int        img_height;
    int        size_l;
    int        bpp;
    int        endian;
}t_img;

typedef struct s_game {
    void    *mlx;
    void    *win;
    t_img    img;
    int        buf[screenHeight][screenWidth];
    int        **texture;

    double    posX;
    double    posY;
    double    dirX;
    double    dirY;
    double    planeX;
    double    planeY;

    double    moveSpeed;
    double    rotSpeed;
}t_game;

int main(int argc, char *argv[]) {
	t_game game;
	game.posX = 22.0;
	game.posY = 11.5;
	game.dirX = -1.0;
	game.dirY = 0.0;
	game.planeX = 0;
	game.planeY = 0.66;
	game.moveSpeed = 0.05;

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, screenWidth, screenHeight, "test");

	for (int i = 0; i < screenHeight; i++){
		for (int j = 0; j <screenWidth; j++)
			game.buf[i][j] = 0;
	}

	if (!(game.texture = (int**)malloc(sizeof(int*) * 8)))
		return -1;
	
	for (int i = 0; i < 8; i++){
		if (!(game.texture[i] = (int*)malloc(sizeof(int)*(texHeight * texWidth))))
			return -1;
	}

	for (int i = 0; i< 8; i++){
		for (int j = 0; j < texHeight * texWidth; j++)
			game.texture[i][j] = 0;
	}

	load_texture(&game);

	game.img.img = mlx_new_image(game.mlx, screenWidth, screenHeight);
	game.img.data = (int *)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);

	mlx_hook(game.win, X_EVENT_KEY_PRESS, &key_press, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}

int		main_loop(t_game *game){
	for (int x = 0; x < screenWidth; x++) {
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
	}
}
