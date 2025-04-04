/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:17:51 by mpico-bu          #+#    #+#             */
/*   Updated: 2025/03/17 21:29:47 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/push_swap.h"

void	update_indexs(t_bilist *slot_a, t_bilist *slot_b)
{
	int			i;
	int			j;
	int			median;
	t_bilist	*slots[2];
	t_bilist	*current;

	slots[0] = slot_a;
	slots[1] = slot_b;
	i = 0;
	while (i < 2)
	{
		median = slot_len(slots[i]) / 2;
		current = slots[i];
		j = 0;
		while (current)
		{
			current->index = j;
			current->above_median = (j <= median);
			current = current->next;
			j++;
		}
		i++;
	}
}

static t_bilist	*find_best_match(t_bilist *slot_out, t_bilist *slot_in, bool a_b)
{
	t_bilist	*best_node;
	long		best_match;

	best_node = NULL;
	if (a_b)
		best_match = LONG_MIN;
	else
		best_match = LONG_MAX;
	while (slot_in)
	{
		if ((a_b && slot_in->value < slot_out->value && slot_in->value > best_match) ||
			(!a_b && slot_in->value > slot_out->value && slot_in->value < best_match))
		{
			best_match = slot_in->value;
			best_node = slot_in;
		}
		slot_in = slot_in->next;
	}
	return (best_node);
}

static void	update_targets(t_bilist *slot_out, t_bilist *slot_in, bool a_b)
{
	t_bilist	*target;

	while (slot_out)
	{
		target = find_best_match(slot_out, slot_in, a_b);
		if (target)
			slot_out->target_node = target;
		else
		{
			if (a_b)
				slot_out->target_node = slot_max(slot_in);
			else
				slot_out->target_node = slot_min(slot_in);
		}
		slot_out = slot_out->next;
	}
}

static void	update_cost(t_bilist *slot_a, t_bilist *slot_b)
{
	int	len_a;
	int	len_b;

	len_a = slot_len(slot_a);
	len_b = slot_len(slot_b);
	while (slot_a)
	{
		slot_a->push_cost = slot_a->index;
		if (!(slot_a->above_median))
			slot_a->push_cost = len_a - (slot_a->index);
		if (slot_a->target_node->above_median)
			slot_a->push_cost += slot_a->target_node->index;
		else
			slot_a->push_cost += len_b - (slot_a->target_node->index);
		slot_a = slot_a->next;
	}
}

static void	update_cheapest(t_bilist *slot)
{
	t_bilist	*cheapest_node;

	cheapest_node = slot;
	while (slot)
	{
		if (slot->push_cost < cheapest_node->push_cost)
			cheapest_node = slot;
		slot = slot->next;
	}
	cheapest_node->cheapest = true;
}

void	init_nodes_a(t_bilist *a, t_bilist *b)
{
	update_indexs(a, b);
	update_targets(a, b, 1);
	update_cost(a, b);
	update_cheapest(a);
}

void	init_nodes_b(t_bilist *a, t_bilist *b)
{
	update_indexs(a, b);
	update_targets(b, a, 0);
}
