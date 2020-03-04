#ifndef FDF_H
#define FDF_H

#define NULL 0
# include "mlx.h"
# include "libft.h"
#include <stdio.h>
#include <string.h>
# include <math.h>
# define INT 1
# define FLOAT 2
# define N -1


typedef struct      s_put
{
    int  z1;                                                                    
    int  z2;
    int deltaX;
    int x1;
    int x2;
    int y1;
    int y2;
    int deltaY;
	int signX; 
	int signY;
	int error;
    int error2 ;
    
}                   t_put;

typedef struct      s_data
{
    double      alpha;
    double      beta;
    double      gamma;
    int         zoom_z;
    void        *mlx_ptr;
    void        *win_ptr;
    void        *img_ptr; 
    int         **z_list;
    int         x_max;
    int         y_max;
    int         *str;
    float       zoom;
    int         color;
    int         shift_x;
    int         shift_y;
    int         i;
    int         j;
}                   data;

void            draw(data *a);
void	        validation(char *line);
int             check_input(char *input);
char            *mystrtok(char *str, const char *delim);
void            errors(int c);
int             image(data *a);
void            algoritm(int x1, int y1, int x2, int y2, int *str, data *a) ;
#endif
