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

static void	rotate_both(t_bilist **a, t_bilist **b, t_bilist *cheapest_node)
{
	while (*b != cheapest_node->target_node && *a != cheapest_node)
		rr(a, b);
	update_indexs(*a, *b);
}

static void	rev_rotate_both(t_bilist **a, t_bilist **b, t_bilist *cheapest_node)
{
	while (*b != cheapest_node->target_node && *a != cheapest_node)
		rrr(a, b);
	update_indexs(*a, *b);
}

static void	move_a_to_b(t_bilist **a, t_bilist **b)
{
	t_bilist	*cheapest_node;

	cheapest_node = slot_cheapest(*a);
	if (cheapest_node->above_median && cheapest_node->target_node->above_median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median) && !(cheapest_node->target_node->above_median))
		rev_rotate_both(a, b, cheapest_node);
	prep_for_push(a, cheapest_node, 'a');
	prep_for_push(b, cheapest_node->target_node, 'b');
	pb(a, b);
}

static void	move_b_to_a(t_bilist **a, t_bilist **b)
{
	prep_for_push(a, (*b)->target_node, 'a');
	pa(a, b);
}

static void	min_on_top(t_bilist **a)
{
	while ((*a)->value != slot_min(*a)->value)
	{
		if (slot_min(*a)->above_median)
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
		init_nodes_a(*slot_a, *slot_b);
		move_a_to_b(slot_a, slot_b);
		len_a--;
	}
	*slot_a = solve_three(*slot_a);
	while (*slot_b)
	{
		init_nodes_b(*slot_a, *slot_b);
		move_b_to_a(slot_a, slot_b);
	}
	update_indexs(*slot_a, *slot_b);
	min_on_top(slot_a);
	return (*slot_a);
}
