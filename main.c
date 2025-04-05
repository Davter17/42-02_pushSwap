/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:38:30 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:38:34 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_bilist		*slot_a;
	t_bilist		*slot_b;

	slot_b = NULL;
	if (argc == 1)
		return (1);
	if (argc == 2)
		argv = ft_split(argv[1], ' ');
	else
		argv = argv + 1;
	if (check_errors(argv))
		exit(1);
	generate_slot(&slot_a, argv);
	if (!slot_sorted(slot_a))
	{
		if (slot_len(slot_a) <= 3)
			slot_a = solve_three(slot_a);
		else
			slot_a = turk_algorithm(&slot_a, &slot_b);
	}
	slot_print(slot_a);
	slot_free(&slot_a);
	return (0);
}
