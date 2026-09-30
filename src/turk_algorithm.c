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
	int	n1;
	int	n2;
	int	n3;

	n1 = slot->value;
	if (slot->next)
	{
		n2 = slot->next->value;
		if (slot->next->next)
		{
			n3 = slot->next->next->value;
			if (n1 > n2 && n2 > n3)
				ra(&slot);
			else if (n1 > n3 && n3 > n2)
				ra(&slot);
			else if (n2 > n1 && n1 > n3)
				rra(&slot);
			else if (n2 > n3 && n3 > n1)
				rra(&slot);
		}
		if (slot->value > slot->next->value)
			sa(&slot);
	}
	return (slot_first(slot));
}

static void	move_to_top(t_bilist **a, t_bilist **b, t_bilist *cheap)
{
	if (cheap->ra && cheap->target->ra)
	{
		while (*a != cheap && *b != cheap->target)
			rr(a, b);
	}
	else if (!cheap->ra && !cheap->target->ra)
	{
		while (*a != cheap && *b != cheap->target)
			rrr(a, b);
	}
}

static void	fill_b(t_bilist **slot_a, t_bilist **slot_b)
{
	t_bilist	*cheapest;

	update_nodes(*slot_a, *slot_b, 'a');
	cheapest = slot_cheapest(*slot_a);
	move_to_top(slot_a, slot_b, cheapest);
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
