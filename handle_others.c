/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_others.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:27:57 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/28 13:27:57 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_percent(t_print *tab)
{
	int	count;

	count = 0;
	if (!tab->dash)
		count += fill(tab->width - 1, ' ');
	count += write(1, "%", 1);
	if (tab->dash)
		count += fill(tab->width - 1, ' ');
	return (count);
}

int	handle_char(t_print *tab, va_list *args)
{
	int				count;
	unsigned char	c;

	count = 0;
	c = (unsigned char)va_arg(*args, int);
	if (!tab->dash)
		count += fill(tab->width - 1, ' ');
	count += write(1, &c, 1);
	if (tab->dash)
		count += fill(tab->width - 1, ' ');
	return (count);
}

int	handle_string(t_print *tab, va_list *args)
{
	int		count;
	char	*str;
	int		len;

	count = 0;
	str = va_arg(*args, char *);
	if (!str)
		str = "(null)";
	len = (int)ft_strlen(str);
	if (tab->dot && tab->precision < len)
		len = tab->precision;
	if (!tab->dash)
		count += fill(tab->width - len, ' ');
	count += write(1, str, len);
	if (tab->dash)
		count += fill(tab->width - len, ' ');
	return (count);
}
