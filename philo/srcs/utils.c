/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:35:03 by mhotting          #+#    #+#             */
/*   Updated: 2024/05/23 11:27:31 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "philo.h"

/**
 * @brief Converts the given string into an unsigned long number
 * @param nb_ptr the string to convert
 * @return the resulting number as an unsigned long
*/
unsigned long	ft_atoul(const char *nb_ptr)
{
	unsigned long	res;

	if (nb_ptr == NULL)
		return (0);
	res = 0;
	while (ft_isspace(*nb_ptr))
		nb_ptr++;
	if (*nb_ptr == '+')
		nb_ptr++;
	while (ft_isdigit(*nb_ptr))
	{
		res = res * 10 + ((unsigned long)(*nb_ptr - '0'));
		nb_ptr++;
	}
	return (res);
}

/**
 * @brief Checks a character is a digit
 * @param c the character to check
 * @return true is c is a digit, else false
*/
int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * @brief Checks a character is a space (as defined in the real isspace() func)
 * @param c the character to check
 * @return true is c is a space, else false
*/
int	ft_isspace(int c)
{
	return (
		c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v'
	);
}

/**
 * @brief Returns the length of the given string
 * @param s the string whose length is to be returned
 * @return the length of s
*/
size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count] != '\0')
		count++;
	return (count);
}

/**
 * @brief Prints a formatted error message
 * @param str the error message to print
 * 
*/
void	print_error(char *str)
{
	printf(ANSI_COL_RED "Philo error: " ANSI_RESET "%s\n", str);
}
