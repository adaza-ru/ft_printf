/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaza-ru <adaza-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 14:35:33 by adaza-ru          #+#    #+#             */
/*   Updated: 2026/01/28 14:35:33 by adaza-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

void	putnbr_base(unsigned long long nbr, char *base)
{
	size_t			base_len;

	base_len = ft_strlen(base);
	if (nbr >= (unsigned long long)base_len)
		putnbr_base(nbr / base_len, base);
	ft_manage_buffer(base[nbr % base_len], WRITE);
}

void	ft_putstr_buffer(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_manage_buffer(str[i], WRITE);
		i++;
	}
}
