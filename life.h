/**
 * @file life.h
 * @brief Header files for Conway's Game of Life and sdl
 * @author Josiah Cury
 * @date 4/29/2019
 */
#ifndef LIFE_H_
#define LIFE_H_

unsigned char **init_matrix(int rows, int cols);
void hedge_life(unsigned char **A, unsigned char **B, int rows, int cols);
void free_matrix(unsigned char **A, int rows);
void torus_life(unsigned char **A, unsigned char **B, int rows, int cols);
void klein_life(unsigned char **A, unsigned char **B, int rows, int cols);

#endif
