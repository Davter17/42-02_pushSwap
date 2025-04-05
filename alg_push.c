/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:37:15 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:37:22 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_bilist **slot_in, t_bilist **slot_out)
{
	t_bilist	*slot_in_first;
	t_bilist	*slot_out_first;

	slot_in_first = *slot_in;
	slot_out_first = *slot_out;
	*slot_out = NULL;
	if (slot_out_first && slot_out_first->next)
	{
		*slot_out = slot_out_first->next;
		slot_out_first->next->pre = NULL;
	}
	slot_out_first->next = slot_in_first;
	*slot_in = slot_out_first;
	if (slot_in_first)
		slot_in_first->pre = slot_out_first;
}

void	pa(t_bilist **slot_a, t_bilist **slot_b)
{
	push(slot_a, slot_b);
	write(1, "pa\n", 3);
}

void	pb(t_bilist **slot_a, t_bilist **slot_b)
{
	push(slot_b, slot_a);
	write(1, "pb\n", 3);
}
