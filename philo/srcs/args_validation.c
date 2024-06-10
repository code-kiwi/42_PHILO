/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhotting <mhotting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:08:07 by mhotting          #+#    #+#             */
/*   Updated: 2024/06/10 15:40:52 by mhotting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#include "philo.h"

/**
 * @brief Checks if the given string, converted to a number is <= INT_MAX
 * @param str The string to parse
 * @return true if str is valid, else returns false
*/
static bool	is_int_overflow(char *str)
{
	size_t	i;
	long	nb;

	i = 0;
	if (str[i] == '\0')
		return (false);
	while (str[i] == '0')
		i++;
	if (ft_strlen(str) > 10)
		return (false);
	nb = ft_atoul(str);
	if (nb == 0 || nb > INT_MAX)
		return (false);
	return (true);
}

/**
 * @brief Checks if the given string is a valid string number
 * 
 * A valid string number is:
 * 	- a str starting with one or multiple spaces
 * 	- after spaces, a '+' sign is accepted
 * 	- then only digits are considered as valid
 * 	- the number represented is an integer >= 0 and <= INT_MAX
 * @param str The string to validate
 * @return true if the string is valid number, else returns false
*/
static bool	is_a_valid_number(char *str)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (false);
	j = i;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (is_int_overflow(str + j));
}

/**
 * @brief Checks the program arguments validity
 * @param argc The number of arguments
 * @param argv The arguments
 * @return true if the given args are valid, else returns false
*/
bool	validate_args(int argc, char **argv)
{
	size_t	i;
	size_t	argc_conv;

	if (argv == NULL || argc < 5 || argc > 6)
		return (false);
	i = 1;
	argc_conv = (size_t) argc;
	while (i < argc_conv)
	{
		if (!is_a_valid_number(argv[i]))
			return (false);
		i++;
	}
	return (true);
}
