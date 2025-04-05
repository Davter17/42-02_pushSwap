/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_utils_advance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:39:42 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:39:46 by event            ###   ########.fr       */
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

t_bilist	*slot_cheapest(t_bilist *slot)
{
	while (slot)
	{
		if (slot->cheapest)
			return (slot);
		slot = slot->next;
	}
	return (NULL);
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
