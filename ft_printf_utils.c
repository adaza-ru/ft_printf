/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:38:51 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/25 19:38:51 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (2048);
	else
		return (0);
}

void	init_print_struct(t_print *print_struct)
{
	print_struct->dash = 0;
	print_struct->zero = 0;
	print_struct->dot = 0;
	print_struct->hash = 0;
	print_struct->space = 0;
	print_struct->plus = 0;
	print_struct->width = 0;
	print_struct->precision = -1;
	print_struct->identifier = '\0';
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	x;

	x = (unsigned char)c;
	i = 0;
	if (*s == '\0' && c != 0)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == x)
			return ((char *)&s[i]);
		i++;
	}
	if (x == '\0')
		return ((char *)&s[i]);
	return (NULL);
}