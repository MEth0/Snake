/*
** main.c for gltest in /home/morgan/Documents/openGL
**
** Made by Morgan SIMON
** Login   <morgan.simon@epitech.eu>
**
** Started on  Wed Jun  7 04:11:46 2017 Morgan SIMON
** Last update Thu Jun  8 18:36:24 2017 Morgan SIMON
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>
#include "snake.h"

char dir = START_DIR;
t_snake snake[MAX_SNAKE_SIZE];
int len = START_LEN;
bool died = false;
int score = 0;

static void error_callback(int error, const char* description)
{
  (void)error;
  fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  (void)scancode, (void)mods;
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
      if (died == true)
	{
	  len = START_LEN;
	  dir = START_DIR;
	  snake[0].posx = START_X - (START_X % SIZE);
	  snake[0].posy = START_Y - (START_Y % SIZE);
	  score = 0;
	  died = false;
	}
    }
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    if (dir != UP) dir = DOWN;
  if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    if (dir != DOWN) dir = UP;
  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    if (dir != RIGHT) dir = LEFT;
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    if (dir != LEFT) dir = RIGHT;
}

static void draw_rect(int x, int y, int width, int height)
{
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}

static void move(char *eaten, int *foodx, int *foody)
{
  int i;

  if (snake[0].posx == *foodx && snake[0].posy == *foody)
    {
      score += 5;
      *eaten = 1;
      len +=1;
    }
  for (i = len - 1; i > 0; i--)
    {
      snake[i].posx = snake[i-1].posx;
      snake[i].posy = snake[i-1].posy;
    }
  switch (dir)
    {
    case RIGHT:
      snake[0].posx += SIZE;
      break;
    case DOWN:
      snake[0].posy += SIZE;
      break;
    case LEFT:
      snake[0].posx -= SIZE;
      break;
    case UP:
      snake[0].posy -= SIZE;
      break;
    }
  for (i = 1; i < len; i++)
    {
      if (snake[0].posx == snake[i].posx && snake[0].posy == snake[i].posy)
	DIED();
    }
  if ((snake[0].posx >= WIDTH || snake[0].posy >= HEIGHT) || (snake[0].posx < 0 || snake[0].posy < 0))
    DIED();
}

int		main(void)
{
  GLFWwindow	*window;

  glfwSetErrorCallback(error_callback);
  if (!glfwInit())
    return EXIT_FAILURE;
  if (!(window = glfwCreateWindow(WIDTH, HEIGHT, "Snek !", NULL, NULL)))
    {
      glfwTerminate();
      return EXIT_FAILURE;
    }
  glfwSetKeyCallback(window, key_callback);
  glfwMakeContextCurrent(window);

  double time = glfwGetTime();
  // no Vsync
  glfwSwapInterval(0);
  // 2D
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, WIDTH, HEIGHT, 0, 0, 1);
  glDisable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(0.1, 0.1, 0.1, 0);

  snake[0].posx = START_X - (START_X % SIZE);
  snake[0].posy = START_Y - (START_Y % SIZE);
  char eaten = 1;
  int x = 0, y = 0, i = 0, tx, ty;
  while (!glfwWindowShouldClose(window))
    {
      glClear(GL_COLOR_BUFFER_BIT);
      // Move
      if (glfwGetTime() - time >= 1.0/SPEED && died == false)
	{
	  time = glfwGetTime();
	  move(&eaten, &x, &y);
	}
      // New food
      if (eaten == 1)
	{
	  tx = rand() % WIDTH;
	  ty = rand() % HEIGHT;
	  x = tx - (tx % SIZE);
	  y = ty - (ty % SIZE);
	  eaten = 0;
	}
      // Draw
      glColor3f(1, 0, 0);
      draw_rect(x, y, SIZE, SIZE);
      double color = 1;
      double s = 0.1;
      i = 0;
      while (i < len)
	{
	  color -= s;
	  if (color <= 0.0)
	    {
	      s = -0.1;
	      color = 0.1;
	    }
	  if (color > 1.0)
	    {
	      s = 0.1;
	      color = 1.0;
	    }
	  glColor3f(0.5, color, 1);
	  draw_rect(snake[i].posx,snake[i].posy,SIZE,SIZE);
	  i++;
	}
      glfwSwapBuffers(window);
      glfwPollEvents();
    }
  glfwDestroyWindow(window);
  glfwTerminate();
  return EXIT_SUCCESS;
}
