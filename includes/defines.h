#ifndef DEFINES_H
#define DEFINES_H 1

//Scenario parameters
#define SCENE_HEIGHT 30
#define SCENE_WIDTH 30

//Arrow keys
#define KEY_LEFT 100
#define KEY_UP 101
#define KEY_RIGHT 102
#define KEY_DOWN 103

//World parameters
#define WORLD_SIDE 300.0f

//Objects in game matrix
#define GAME_SPACE   0
#define GAME_WALL 1
#define GAME_PLAYER 2
#define GAME_ENEMY 3
#define GAME_TRAIL 4

//Returns of the matrixcontroller
#define STEP_OK 0
#define STEP_COLLISION_WALL 1
#define STEP_COLLISION_ENEMY 2
#define STEP_COLLISION_TRAIL 3

//Directions of elements in game
#define DIRECTION_LEFT 0
#define DIRECTION_UP 1
#define DIRECTION_RIGHT 2
#define DIRECTION_DOWN 3

//Player parameters
#define PLAYER_HEIGHT 3.0f

//Wall parameters
#define WALL_HEIGHT 10.0f

//Trail parameters
#define TRAIL_HEIGHT 4.6f

//Game modes
#define GAME_MODE_TOP 0
#define GAME_MODE_3D 1

//Camera paramenters
#define CAMERA_3RD_DISTANCE 10.0f
#define CAMERA_TOP_DISTANCE 390.0f




#endif