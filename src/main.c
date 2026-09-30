/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:38:30 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:50:36 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_bilist		*slot_a;
	t_bilist		*slot_b;
	char			**split_argv;
	int				i;

	slot_b = NULL;
	split_argv = NULL;
	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		split_argv = ft_split(argv[1], ' ');
		argv = split_argv;
	}
	else
		argv = argv + 1;
	if (check_errors(argv))
	{
		if (split_argv)
		{
			i = 0;
			while (split_argv[i])
				free(split_argv[i++]);
			free(split_argv);
		}
		exit(1);
	}
	generate_slot(&slot_a, argv);
	if (!slot_sorted(slot_a))
		slot_a = turk_algorithm(&slot_a, &slot_b);
	slot_free(&slot_a);
	if (split_argv)
	{
		i = 0;
		while (split_argv[i])
			free(split_argv[i++]);
		free(split_argv);
	}
	return (0);
}
