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

int	handle_format(t_print *tab, va_list *args)
{
	int	len;

	len = 0;
	if (tab->identifier == 'c')
		len = handle_char(tab, args);
	else if (tab->identifier == 's')
		len = handle_string(tab, args);
	else if (tab->identifier == 'p')
		len = handle_pointer(tab, args);
	else if (tab->identifier == 'd' || tab->identifier == 'i')
		len = handle_integer(tab, args);
	else if (tab->identifier == 'u')
		len = handle_unsigned(tab, args);
	else if (tab->identifier == 'x' || tab->identifier == 'X')
		len = handle_hexadecimal(tab, args);
	else if (tab->identifier == '%')
		len = handle_percent(tab);
	return (len);
}

int	eval_format(const char **format, va_list *args)
{
	t_print	tab;
	int		len;

	init_print_struct(&tab);
	parse_format(format, &tab);
	if (tab.identifier == '\0' || !ft_strchr("cspdiuxX%", tab.identifier))
	{
		while (**format != '%')
			(*format)--;
		len = write(1, "%", 1);
	}
	else
		len = handle_format(&tab, args);
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
			len += eval_format(&format, &args);
		else
			len += write(1, format, 1);
		if (*format)
			format++;
	}
	va_end(args);
	return (len);
}

/*
#include <stdio.h>

int main(void)
{
	printf("ft_printf	|	printf original\n");

    ft_printf("Hello World!	|	");
	printf("Hellow World!\n");


		return (0);
}
*/