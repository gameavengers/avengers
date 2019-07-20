#pragma once


//Tên ứng dụng
#define WINDOW_CLASS_NAME L"Avengers"
#define MAIN_WINDOW_TITLE L"Captain America and The Avengers"
//Màu background, kích cỡ màn hình
#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 235

//Framerate tối đa
#define MAX_FRAME_RATE 90

//
enum Stage {
	STAGE_1,
	STAGE_2,
	STAGE_BOSS_1,
	STAGE_BOSS_2
};
enum ObjectType
{
	DEFAULT,
	BRICK,
	BRICK_NOCOLLISION_BOTTOM,
	ON_BUTTON,
	RIVER,
	SWING
};
//TiledMap
//
// MAP
#define BACKGROUND_1 L"Resources\\TiledMap\\Map-Charleston.png"
#define BACKGROUND_2 L"Resources\\TiledMap\\Map-Pittsburgh.png"
#define BACKGROUND_BOSS_1 L"Resources\\TiledMap\\Map-Boss1.png"
#define BACKGROUND_BOSS_2 L"Resources\\TiledMap\\Map-Boss2.png"
// TILE
#define TILES_MATRIX_STAGE_1 L"Resources\\TiledMap\\Map-Charleston-Matrix.txt"
#define TILES_MATRIX_STAGE_2 L"Resources\\TiledMap\\Map-Pittsburgh-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS_1 L"Resources\\TiledMap\\Map-Boss1-Matrix.txt"
#define TILES_MATRIX_STAGE_BOSS_2 L"Resources\\TiledMap\\Map-Boss2-Matrix.txt"

#define TILES_MATRIX_DELIMITER ","
#define TILES_WIDTH_PER_TILE	16
#define TILES_HEIGHT_PER_TILE	16
#define TILES_TRANSCOLOR D3DCOLOR_XRGB(255, 0, 255)

#define GRID_SIZE 64
#define GRID_MAX_X 48
#define GRID_MAX_Y 5

//Giá trị tốc độ đi, tốc độ nhảy, trọng lực
#define CAPTAIN_WALK_SPEED		0.125f
#define CAPTAIN_JUMP_SPEED_Y	0.3f
#define CAPTAIN_GRAVITY			0.04f
#define CAPTAIN_JUMP_MAX		70

#define CAPTAIN_TEXTURE_LOCATION L"Resources\\Captain\\Captain.png"
#define CAPTAIN_TEXTURE_TRANS_COLOR D3DCOLOR_XRGB(255, 0, 255)
#define CAPTAIN_SPRITE_WIDTH 25
#define CAPTAIN_SPRITE_HEIGHT 45