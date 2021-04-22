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

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_RELEASE		3
#define X_EVENT_KEY_EXIT		17

#define KEY_ESC		53
# define KEY_Q		12
# define KEY_W		13
# define KEY_E		14
# define KEY_R		15
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2

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

void load_texture(t_game *game);
void load_image(t_game *game, int *texture, char *path, t_img *img);
void verLine(t_game *game, int x, int y1, int y2, int color);
int main_loop(t_game * game);
int key_press(int keycode, t_game *game);

int 	main(int argc, char **argv){
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
	if (!(game.texture = (int**)malloc(sizeof(int*) * 8)))
		return -1;
	for (int i = 0; i < 8; i++){
		if (!(game.texture[i] = (int *)malloc(sizeof(int)*(texHeight * texWidth))))
			return -1;
	}
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < texHeight * texWidth; j++)
			game.texture[i][j] = 0;
	}

	load_texture(&game);

	game.img.img = mlx_new_image(game.mlx, screenWidth, screenHeight);
	game.img.data = (int*)mlx_get_data_addr(game.img.img, &game.img.bpp, &game.img.size_l, &game.img.endian);
	

	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_put_image_to_window(game.mlx, game.win, game.buf, 0, 0);
	mlx_loop(game.mlx);
}

int		main_loop(t_game *game){
	for (int y = 0; y < screenHeight; y++){
		float rayDirX0 = game->dirX - game->planeX;
		float rayDirY0 = game->dirY - game->planeY;
		float rayDirX1 = game->dirX + game->planeX;
		float rayDirY1 = game->dirX + game->planeY;

		int p = y - screenHeight / 2;

		float posZ = 0.5 * screenHeight;
		float rowDistance = posZ / p;

		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / screenWidth;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / screenWidth;

		float floorX = game->posX + rowDistance * rayDirX0;
		float floorY = game->posY + rowDistance * rayDirY0;

		for (int x = 0; x < screenWidth; x++){
			int cellX = (int)floorX;
			int cellY = (int)floorY;

			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			int floorTexture = 3;
			int ceilingTexture = 6;

			int color;

			color = game->texture[floorTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711;

			game->buf[y][x] = color;

			color = game->texture[ceilingTexture][texWidth * ty + tx];
			color = (color >> 1) & 8355711;

			game->buf[screenHeight - y - 1][x] = color;
		}
	}
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

		int texNum = worldMap[mapX][mapY] - 1;

		double wallX;
		if (side == 0)
			wallX = game->posY + perpWallDist * rayDirY;
		else
			wallX = game->posY + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		double step = 1.0 * texHeight / lineHeight;
		double texPos = (drawStart - screenHeight / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++){
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			int color = game->texture[texNum][texWidth * texY + texX];
			if (side == 1)
				color = (color >> 1) & 8355711;
			game->buf[y][x] = color;
		}
        double floorXWall, floorYWall;

        if (side == 0 && rayDirX > 0){
            floorXWall = mapX;
            floorYWall = mapY + wallX;
        } else if (side == 0 && rayDirX < 0){
            floorXWall = mapX + 1.0;
            floorYWall = mapY + wallX;
        } else if (side == 1 && rayDirY > 0){
            floorXWall = mapX + wallX;
            floorYWall = mapY;
        } else {
            floorXWall = mapX + wallX;
            floorYWall = mapY + 1.0;
        }

        double distWall, distPlayer, currentDist;

        distWall = perpWallDist;
        distPlayer = 0.0;

        if (drawEnd < 0)
            drawEnd = screenHeight;
        for (int y = drawEnd + 1; y < screenHeight; y++){
            currentDist = screenHeight / (2.0 * y -screenHeight);

            double weight = (currentDist - distPlayer) / (distWall - distPlayer);
            double currentFloorX = weight * floorXWall + (1.0 - weight) * game->posX;
            double currentFloorY = weight * floorYWall + (1.0 - weight) * game->posY;

            int floorTexX, floorTexY;
            floorTexX = (int)(currentFloorX * texWidth) % texWidth;
            floorTexY = (int)(currentFloorY * texHeight) % texHeight;

            int checkerBoardPattern = ((int)(currentFloorX) + (int)(currentFloorY)) % 2;
            int floorTexture;
            if (checkerBoardPattern == 0) floorTexture = 3;
            else floorTexture = 4;

            game->buf[y][x] = (game->texture[floorTexture][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
            game->buf[screenHeight - y][x] = game->texture[6][texWidth * floorTexY + floorTexX];
        }
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

int		key_press(int keycode, t_game *game){
	if (keycode == KEY_W){
		if (!worldMap[(int)(game->posX + game->dirX * game->moveSpeed)][(int)(game->posY)])
			game->posX += game->dirX * game->moveSpeed;
		if (!worldMap[(int)(game->posX)][(int)(game->posY + game->dirY * game->moveSpeed)])
			game->posY += game->dirY * game->moveSpeed;
	}
    if (keycode == KEY_S){
        if (!worldMap[(int)(game->posX - game->dirX * game->moveSpeed)][(int)(game->posY - game->dirY * game->moveSpeed)]){
            game->posX -= game->dirX * game->moveSpeed;
            game->posY -= game->dirY * game->moveSpeed;
        }
    }
    if (keycode == KEY_D){
        double oldDirX = game->dirX;
		game->dirX = game->dirX * cos(-game->rotSpeed) - game->dirY * sin(-game->rotSpeed);
		game->dirY = oldDirX * sin(-game->rotSpeed) + game->dirY * cos(-game->rotSpeed);
		double oldPlaneX = game->planeX;
		game->planeX = game->planeX * cos(-game->rotSpeed) - game->planeY * sin(-game->rotSpeed);
		game->planeY = oldPlaneX * sin(-game->rotSpeed) + game->planeY * cos(-game->rotSpeed);
    }

	if (keycode == KEY_A){
        double oldDirX = game->dirX;
        game->dirX = game->dirX * cos(game->rotSpeed) - game->dirY * sin(game->rotSpeed);
        game->dirY = oldDirX * sin(game->rotSpeed) + game->dirY * cos(game->rotSpeed);
        double oldPlaneX = game->planeX;
        game->planeX = game->planeX * cos(game->rotSpeed) - game->planeY * sin(game->rotSpeed);
        game->planeY = oldPlaneX * sin(game->rotSpeed) + game->planeY * cos(game->rotSpeed);
	}
	return (0);
}


void	load_image(t_game *game, int *texture, char *path, t_img *img)
{
    img->img = mlx_xpm_file_to_image(game->mlx, path, &img->img_width, &img->img_height);
    img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
    for (int y = 0;y < img->img_height; y++)
        for (int x = 0;x < img->img_width; x++)
            texture[img->img_width * y + x] = img->data[img->img_width * y + x];
    mlx_destroy_image(game->mlx, img->img);
}

void	load_texture(t_game *game)
{
	t_img img;

	load_image(game, game->texture[0], "textures/eagle.png", &img);
	load_image(game, game->texture[1], "textures/redbrick.png", &img);
	load_image(game, game->texture[2], "textures/purplestone.png", &img);
    load_image(game, game->texture[3], "textures/greystone.png", &img);
    load_image(game, game->texture[4], "textures/bluestone.png", &img);
    load_image(game, game->texture[5], "textures/mossy.png", &img);
    load_image(game, game->texture[6], "textures/wood.png", &img);
    load_image(game, game->texture[7], "textures/colorstone.png", &img);
}
