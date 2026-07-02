/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 19:40:18 by adaza-ru          #+#    #+#             */
/*   Updated: 2025/12/22 19:40:18 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_manage_buffer(char c, int mode)
{
	static char	buffer[BUFFER_SIZE];
	static int	i = 0;
	static int	total_printed = 0;

	if (mode == FLUSH)
	{
		if (i > 0)
		{
			write(1, buffer, i);
			total_printed += i;
			i = 0;
		}
		return (total_printed);
	}
	if (mode == GET_TOTAL)
		return (total_printed);
	buffer[i] = c;
	i++;
	if (i == BUFFER_SIZE)
	{
		write(1, buffer, BUFFER_SIZE);
		total_printed += BUFFER_SIZE;
		i = 0;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;
	int		error_modifier;

	error_modifier = 1;
	len = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			eval_format(&format, &args, &error_modifier);
		}
		else
			ft_manage_buffer(*format, WRITE);
		if (*format)
			format++;
	}
	va_end(args);
	ft_manage_buffer(0, FLUSH);
	len = ft_manage_buffer(0, GET_TOTAL);
	return (len * error_modifier);
}
