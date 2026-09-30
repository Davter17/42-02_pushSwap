/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:37:40 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:37:43 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_bilist **slot)
{
	t_bilist	*first_node;
	t_bilist	*last_node;

	first_node = *slot;
	last_node = slot_last(first_node);
	*slot = first_node->next;
	first_node->next->pre = NULL;
	last_node->next = first_node;
	first_node->pre = last_node;
	first_node->next = NULL;
}

void	ra(t_bilist **slot)
{
	rotate(slot);
	write(1, "ra\n", 3);
}

void	rb(t_bilist **slot)
{
	rotate(slot);
	write(1, "rb\n", 3);
}

void	rr(t_bilist **slot_a, t_bilist **slot_b)
{
	rotate(slot_a);
	rotate(slot_b);
	write(1, "rr\n", 3);
}
