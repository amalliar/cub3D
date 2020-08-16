/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_image_to_bmp_file.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amalliar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 20:15:52 by amalliar          #+#    #+#             */
/*   Updated: 2020/08/14 17:35:46 by amalliar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

unsigned char	*create_bmp_file_header(int height, int stride)
{
	int						file_size;
	static unsigned char	file_header[FILE_HEADER_SIZE] = {0};

	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + (stride * height);
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);
	return (file_header);
}

unsigned char	*create_bmp_info_header(int height, int width)
{
	static unsigned char	info_header[INFO_HEADER_SIZE] = {0};

	info_header[0] = (unsigned char)(INFO_HEADER_SIZE);
	info_header[4] = (unsigned char)(width);
	info_header[5] = (unsigned char)(width >> 8);
	info_header[6] = (unsigned char)(width >> 16);
	info_header[7] = (unsigned char)(width >> 24);
	info_header[8] = (unsigned char)(height);
	info_header[9] = (unsigned char)(height >> 8);
	info_header[10] = (unsigned char)(height >> 16);
	info_header[11] = (unsigned char)(height >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(8 * BYTES_PER_PIXEL);
	return (info_header);
}

int				mlx_image_to_bmp_file(t_mlx_image *mi, const char *name)
{
	static unsigned char	padding[3] = {0, 0, 0};
	int						y;
	t_conv_data				cd;

	cd.width_in_bytes = mi->width * mi->bits_per_pixel / 8;
	cd.padding_size = (4 - (cd.width_in_bytes) % 4) % 4;
	cd.stride = cd.width_in_bytes + cd.padding_size;
	if ((cd.fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, \
		S_IRUSR | S_IWUSR)) == -1)
		return (-1);
	cd.file_header = create_bmp_file_header(mi->height, cd.stride);
	write(cd.fd, cd.file_header, FILE_HEADER_SIZE);
	cd.info_header = create_bmp_info_header(-mi->height, mi->width);
	write(cd.fd, cd.info_header, INFO_HEADER_SIZE);
	cd.img = (unsigned char *)mi->addr;
	y = 0;
	while (y < mi->height)
	{
		write(cd.fd, cd.img + (y * mi->line_length), mi->line_length);
		write(cd.fd, padding, cd.padding_size);
		++y;
	}
	close(cd.fd);
	return (0);
}