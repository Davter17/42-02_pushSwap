/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:38:05 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:49:33 by mpico-bu          ###   ########.fr      */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_error(void)
{
	write(2, "Error\n", 6);
}

static bool	check_syntax(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		if (argv[i][0] != '+' && argv[i][0] != '-'
			&& (argv[i][0] < '0' || argv[i][0] > '9'))
		{
			print_error();
			return (1);
		}
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				print_error();
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static bool	check_limits(char **argv)
{
	int			i;
	int			error;
	long long	atol_val;

	i = 0;
	while (argv[i])
	{
		error = 0;
		atol_val = ft_atol(argv[i], &error);
		if (error || atol_val != (long long)ft_atoi(argv[i]))
		{
			print_error();
			return (1);
		}
		i++;
	}
	return (0);
}

static bool	check_duplicates(char **argv)
{
	int			i;
	int			j;
	int			error;
	long long	number;

	i = 0;
	while (argv[i])
	{
		error = 0;
		number = ft_atol(argv[i], &error);
		j = i + 1;
		while (argv[j])
		{
			error = 0;
			if (number == ft_atol(argv[j], &error))
			{
				print_error();
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

bool	check_errors(char **argv)
{
	if (check_syntax(argv))
		return (1);
	if (check_limits(argv))
		return (1);
	if (check_duplicates(argv))
		return (1);
	return (0);
}
