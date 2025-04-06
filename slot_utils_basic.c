/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slot_utils_basic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:39:54 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:50:17 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

t_bilist	*slot_first(t_bilist *slot)
{
	while (slot->pre)
		slot = slot->pre;
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

/*
void	slot_print(t_bilist *slot)
{
	while (slot)
	{
		printf("%i ", slot->value);
		slot = slot->next;
	}
	printf("\n");
}
*/