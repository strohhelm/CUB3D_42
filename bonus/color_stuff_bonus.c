/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_stuff_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:39:20 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/14 22:11:48 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

// inverts the colour at a specific pixel location
uint32_t	invert_colour(uint8_t *col)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	var;

	var = 80;
	red = (*col) & 0xFF;
	green = (*(col + 1)) & 0xFF;
	blue = (*(col + 2)) & 0xFF;
	red = 255 - red + var;
	green = green + var;
	blue = 255 - blue;
	return (red << 24 | green << 16 | blue << 8 | 255);
}

// returns the uint32_t value of the pixel described by the 4 uint8_t
// pointed to by argument.
uint32_t	colour(uint8_t *col)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = *col;
	g = *(col + 1);
	b = *(col + 2);
	a = *(col + 3);
	return (r << 24 | g << 16 | b << 8 | a);
}

// function specific. initializes wall and floor colour with the inverted
// ceiling colour given in mapfile. floor colour will be darkened.
void	change_colour(uint32_t col, unsigned int *wall, unsigned int *floor)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;

	red = ((col) >> 24) & 0xFF;
	green = (col >> 16) & 0xFF;
	blue = (col >> 8) & 0xFF;
	red = 255 - red;
	green = 255 - green;
	blue = 255 - blue;
	*floor = (red << 24 | green << 16 | blue << 8 | 255);
	*wall = (red - 10) / 4 << 24 | (green - 10) / 4 << 16 | (blue - 10)
		/ 4 << 8 | 255;
}

// darkens the colour by a specified amount by substraction it from all colour
// values except alpha
uint32_t	darken_colour(uint32_t col, int amount)
{
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	a;

	red = (col >> 24) & 0xFF;
	green = (col >> 16) & 0xFF;
	blue = (col >> 8) & 0xFF;
	a = col & 0xFF;
	if (amount > a)
		a = 0;
	else
		a -= amount;
	if (amount > green)
		green = 0;
	else
		green -= amount;
	if (amount > blue)
		blue = 0;
	else
		blue -= amount;
	return (red << 24 | green << 16 | blue << 8 | a);
}

//returns the colour from rgbvalues with full alpha value
unsigned int	get_colour(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}
