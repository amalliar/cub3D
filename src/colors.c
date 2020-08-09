/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 18:07:59 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/08 16:33:36 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colors.h"

int		create_color(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

int		get_alpha(int color)
{
	return ((color & (0xFF << 24)) >> 24);
}

int		get_red(int color)
{
	return ((color & (0xFF << 16)) >> 16);
}

int		get_green(int color)
{
	return ((color & (0xFF << 8)) >> 8);
}

int		get_blue(int color)
{
	return (color & 0xFF);
}

int		add_shade(double distance, int color)
{
	int 	a;
	int 	r;
	int 	g;
	int 	b;

	a = get_alpha(color);
	r = get_red(color);
	g = get_green(color);
	b = get_blue(color);
	r -= r * distance;
	g -= g * distance;
	b -= b * distance;
	return (create_color(a, r, g, b));
}

int		get_opposite(int color)
{
	int		a;

	a = get_alpha(color);
	return ((~color & 0x00FFFFFF) | a);
}
