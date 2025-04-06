/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:40:32 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:42:55 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
			current->ra = (j <= median);
			current = current->next;
			j++;
		}
		i++;
	}
}

static void	update_targets(t_bilist *slot_out, t_bilist *slot_in, bool a_b)
{
	t_bilist	*match;

	while (slot_out)
	{
		match = slot_target(slot_out, slot_in, a_b);
		if (match)
			slot_out->target = match;
		else
		{
			if (a_b)
				slot_out->target = slot_max(slot_in);
			else
				slot_out->target = slot_min(slot_in);
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
		slot_a->cost = slot_a->index;
		if (!(slot_a->ra))
			slot_a->cost = len_a - (slot_a->index);
		if (slot_a->target->ra)
			slot_a->cost += slot_a->target->index;
		else
			slot_a->cost += len_b - (slot_a->target->index);
		slot_a = slot_a->next;
	}
}

static void	update_cheapest(t_bilist *slot)
{
	t_bilist	*cheapest_node;

	cheapest_node = slot;
	while (slot)
	{
		if (slot->cost < cheapest_node->cost)
			cheapest_node = slot;
		slot = slot->next;
	}
	cheapest_node->cheapest = true;
}

void	update_nodes(t_bilist *a, t_bilist *b, char slot)
{
	update_indexs(a, b);
	if (slot == 'b')
		update_targets(b, a, 0);
	else
	{
		update_targets(a, b, 1);
		update_cost(a, b);
		update_cheapest(a);
	}
}
