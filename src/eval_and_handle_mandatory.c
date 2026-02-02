/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_mandatory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 02:15:30 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/30 02:15:30 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char_mandatory(va_list *args)
{
	int				count;
	unsigned char	c;

	count = 0;
	c = (unsigned char)va_arg(*args, int);
	count += write(1, &c, 1);
	return (count);
}

int	handle_string_mandatory(va_list *args)
{
	char	*str;
	int		len;

	str = va_arg(*args, char *);
	if (!str)
		str = "(null)";
	len = 0;
	while (str[len])
		len++;
	if (write(1, str, len) == -1)
		return (-1);
	return (len);
}

int	eval_format(const char **format, va_list *args)
{
	int	len;

	if (!ft_strchr("csdiuxXp%", (*format[1])))
	{
		len = write(1, format, 1);
		return (len);
	}
	else
	{
		if (**format == 'c')
			len = handle_char_mandatory(args);
		else if (**format == 's')
			len = handle_string_mandatory(args);
		else if (**format == 'p')
			len = handle_pointer_mandatory(args);
		else if (**format == 'd' || **format == 'i')
			len = handle_integer_mandatory(args);
		else if (**format == 'u')
			len = handle_unsigned_mandatory(args);
		else if (**format == 'x' || **format == 'X')
			len = handle_hexadecimal_mandatory(args);
		else if (**format == '%')
			len = write(1, "%", 1);
		return (len);
	}
}
