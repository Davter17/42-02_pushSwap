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

int	slot_sorted(t_bilist *slot)
{
	while (slot->next)
	{
		if (slot->value > slot->next->value)
			return (0);
		slot = slot->next;
	}
	return (1);
}

int	slot_len(t_bilist *slot)
{
	int	len;

	len = 0;
	while (slot)
	{
		slot = slot->next;
		len++;
	}
	return (len);
}

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

t_bilist	*slot_first(t_bilist *slot)
{
	while (slot->prev)
		slot = slot->prev;
	return (slot);
}

t_bilist	*slot_last(t_bilist *slot)
{
	while (slot->next)
		slot = slot->next;
	return (slot);
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

void	slot_print(t_bilist *slot)
{
	while (slot)
	{
		printf("%i ", slot->value);
		slot = slot->next;
	}
	printf("\n");
}

void	prep_for_push(t_bilist **slot, t_bilist *top_node, char slot_name)
{
	while (*slot != top_node)
	{
		if (slot_name == 'a')
		{
			if (top_node->above_median)
				ra(slot);
			else
				rra(slot);
		}
		else if (slot_name == 'b')
		{
			if (top_node->above_median)
				rb(slot);
			else
				rrb(slot);
		}
	}
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
