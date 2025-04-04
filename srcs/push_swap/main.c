/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 22:38:58 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/03/17 19:07:39 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
int	main(int argc, char **argv)
{
	t_bilist		*slot_a;
	t_bilist		*slot_b;
	bool			splitted;

	slot_b = NULL;
	splitted = false;
	if (argc == 1)
		return (1);
	if (argc == 2)
	{
		argv = ft_split(argv[1], ' ');
		splitted = true;
	}
	if (splitted)
		generate_slot(&slot_a, argv);
	else
		generate_slot(&slot_a, argv + 1);
	if (slot_sorted(slot_a))
		return (free(&slot_a), 0);
	if (slot_len(slot_a) <= 3)
		sort_three(&slot_a);
	else
		sort_slots(&slot_a, &slot_b);
	free(&slot_a);
	return (0);
}
*/

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
	slot_print(slot_a);
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
