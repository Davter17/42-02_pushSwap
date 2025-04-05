/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_algorithm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:40:20 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:40:24 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_bilist	*solve_three(t_bilist *slot)
{
	int	num_1;
	int	num_2;
	int	num_3;

	num_1 = slot->value;
	if (slot->next)
	{
		num_2 = slot->next->value;
		if (slot->next->next)
		{
			num_3 = slot->next->next->value;
			if (num_1 > num_2 && num_2 > num_3)
				ra(&slot);
			else if (num_1 > num_3 && num_3 > num_2)
				ra(&slot);
			else if (num_2 > num_1 && num_1 > num_3)
				rra(&slot);
			else if (num_2 > num_3 && num_3 > num_1)
				rra(&slot);
		}
		if (slot->value > slot->next->value)
			sa(&slot);
	}
	return (slot_first(slot));
}

static void	fill_b(t_bilist **slot_a, t_bilist **slot_b)
{
	t_bilist	*cheapest;

	update_nodes(*slot_a, *slot_b, 'a');
	cheapest = slot_cheapest(*slot_a);
	if (cheapest->ra && cheapest->target->ra)
	{
		while (*slot_a != cheapest && *slot_b != cheapest->target)
			rr(slot_a, slot_b);
	}
	else if (!(cheapest->ra) && !(cheapest->target->ra))
	{
		while (*slot_b != cheapest->target && *slot_a != cheapest)
			rrr(slot_a, slot_b);
	}
	update_indexs(*slot_a, *slot_b);
	slot_to_top(slot_a, cheapest, 'a');
	slot_to_top(slot_b, cheapest->target, 'b');
	pb(slot_a, slot_b);
}

static void	unfill_b(t_bilist **slot_a, t_bilist **slot_b)
{
	update_nodes(*slot_a, *slot_b, 'b');
	slot_to_top(slot_a, (*slot_b)->target, 'a');
	pa(slot_a, slot_b);
}

t_bilist	*turk_algorithm(t_bilist **slot_a, t_bilist **slot_b)
{
	int	len_a;

	len_a = slot_len(*slot_a);
	if (len_a-- > 3)
		pb(slot_a, slot_b);
	while (len_a-- > 3 && !slot_sorted(*slot_a))
		fill_b(slot_a, slot_b);
	*slot_a = solve_three(*slot_a);
	while (*slot_b)
		unfill_b(slot_a, slot_b);
	update_indexs(*slot_a, NULL);
	slot_to_top(slot_a, slot_min(*slot_a), 'a');
	return (*slot_a);
}
