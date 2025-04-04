/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 03:56:03 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/02/14 03:56:03 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static bool	check_syntax(char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (argv[i])
	{
		if ((argv[i][0] != '+' && argv[i][0] != '-' && (argv[i][0] < '0' || argv[i][0] > '9')))
		{
			ft_printf("Error: Syntax error on %s.\n", argv[i]);
			return (1);
		}
		j = 1;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
			{
				ft_printf("Error: Syntax error on %s.\n", argv[i]);
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
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atol(argv[i]) != ft_atoi(argv[i]))
		{
			ft_printf("Error: Limit error on %s.\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static bool	check_duplicates(char **argv)
{
	int		i;
	int		j;
	long	number;

	i = 0;
	while (argv[i])
	{
		j = i + 1;
		number = ft_atol(argv[i]);
		while (argv[j])
		{
			if (number == ft_atol(argv[j]))
			{
				ft_printf("Error: Duplicate error on %s.\n", argv[i]);
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
