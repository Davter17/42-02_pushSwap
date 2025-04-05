/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 17:14:34 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/02/14 03:56:11 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

static void	move_a_to_b(t_bilist **a, t_bilist **b)
{
	t_bilist	*cheapest_node;

	cheapest_node = slot_cheapest(*a);
	if (cheapest_node->ra && cheapest_node->target->ra)
	{
		while (*b != cheapest_node->target && *a != cheapest_node)
			rr(a, b);
	}
	else if (!(cheapest_node->ra) && !(cheapest_node->target->ra))
	{
		while (*b != cheapest_node->target && *a != cheapest_node)
			rrr(a, b);
	}
	update_indexs(*a, *b);
	prep_for_push(a, cheapest_node, 'a');
	prep_for_push(b, cheapest_node->target, 'b');
	pb(a, b);
}

static void	move_b_to_a(t_bilist **a, t_bilist **b)
{
	prep_for_push(a, (*b)->target, 'a');
	pa(a, b);
}

static void	min_on_top(t_bilist **a)
{
	while ((*a)->value != slot_min(*a)->value)
	{
		if (slot_min(*a)->ra)
			ra(a);
		else
			rra(a);
	}
}

t_bilist	*turk_algorithm(t_bilist **slot_a, t_bilist **slot_b)
{
	int	len_a;

	pb(slot_a, slot_b);
	len_a = slot_len(*slot_a);
	if (len_a > 3 && !slot_sorted(*slot_a))
		pb(slot_a, slot_b);
	len_a--;
	while (len_a > 3 && !slot_sorted(*slot_a))
	{
		update_nodes(*slot_a, *slot_b, 'a');
		move_a_to_b(slot_a, slot_b);
		len_a--;
	}
	*slot_a = solve_three(*slot_a);
	while (*slot_b)
	{
		update_nodes(*slot_a, *slot_b, 'b');
		move_b_to_a(slot_a, slot_b);
	}
	update_indexs(*slot_a, *slot_b);
	min_on_top(slot_a);
	return (*slot_a);
}
