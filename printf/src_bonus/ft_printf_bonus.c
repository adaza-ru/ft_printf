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

#include "ft_printf_bonus.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	if (!format)
		return (0);
	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			len += eval_format(&format, &args);
		}
		else
			len += write(1, format, 1);
		if (*format)
			format++;
	}
	va_end(args);
	return (len);
}
