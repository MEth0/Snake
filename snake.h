/*
** snake.h for snake in /home/morgan/Documents/openGL
**
** Made by Morgan SIMON
** Login   <morgan.simon@epitech.eu>
**
** Started on  Thu Jun  8 17:28:06 2017 Morgan SIMON
** Last update Thu Jun  8 19:10:00 2017 Morgan SIMON
*/

#ifndef SNAKE_H
#define SNAKE_H

#define SIZE		20
#define WIDTH		1280
#define HEIGHT		720
#define MAX_SNAKE_SIZE	(WIDTH * HEIGHT)
#define START_X		200
#define START_Y		200
#define START_LEN	5
#define START_DIR	RIGHT
#define SPEED		10 /* Step per sec */

#define DIED() { died = true;			\
    printf("DIED - SCORE = %d\n", score); }

typedef struct
{
  int   posx;
  int   posy;
} t_snake;

typedef enum
  {
    RIGHT = 0,
    DOWN,
    LEFT,
    UP,
  } t_dir;

#endif
