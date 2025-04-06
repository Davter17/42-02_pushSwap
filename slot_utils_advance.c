/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_utils_advance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:39:42 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:50:06 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bilist	*slot_min(t_bilist *slot)
{
	t_bilist	*min_node;

	min_node = slot;
	while (slot)
	{
		if (slot->value < min_node->value)
			min_node = slot;
		slot = slot->next;
	}
	return (min_node);
}

t_bilist	*slot_max(t_bilist *slot)
{
	t_bilist	*max_node;

	max_node = slot;
	while (slot)
	{
		if (slot->value > max_node->value)
			max_node = slot;
		slot = slot->next;
	}
	return (max_node);
}

void	slot_free(t_bilist **slot)
{
	t_bilist	*temp;
	t_bilist	*current;

	current = *slot;
	while (current)
	{
		temp = current->next;
		current->value = 0;
		free(current);
		current = temp;
	}
	*slot = NULL;
}

void	slot_to_top(t_bilist **slot, t_bilist *node_to_top, char slot_name)
{
	while ((*slot)->value != node_to_top->value)
	{
		if (slot_name == 'a')
		{
			if (node_to_top->ra)
				ra(slot);
			else
				rra(slot);
		}
		else
		{
			if (node_to_top->ra)
				rb(slot);
			else
				rrb(slot);
		}
	}
}

t_bilist	*slot_target(t_bilist *slot_out, t_bilist *slot_in, bool a_b)
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
		if (a_b && slot_in->value < slot_out->value
			&& slot_in->value > best_match)
		{
			best_match = slot_in->value;
			best_node = slot_in;
		}
		if (!a_b && slot_in->value > slot_out->value
			&& slot_in->value < best_match)
		{
			best_match = slot_in->value;
			best_node = slot_in;
		}
		slot_in = slot_in->next;
	}
	return (best_node);
}
