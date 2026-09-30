/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alg_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:37:51 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:37:55 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_bilist **slot)
{
	t_bilist	*first_node;
	t_bilist	*second_node;

	first_node = *slot;
	second_node = first_node->next;
	first_node->pre = second_node;
	first_node->next = second_node->next;
	if (first_node->next)
		first_node->next->pre = first_node;
	second_node->pre = NULL;
	second_node->next = first_node;
	*slot = second_node;
}

void	sa(t_bilist **slot)
{
	swap(slot);
	write(1, "sa\n", 3);
}

void	sb(t_bilist **slot)
{
	swap(slot);
	write(1, "sb\n", 3);
}

void	ss(t_bilist **slot_a, t_bilist **slot_b)
{
	swap(slot_a);
	swap(slot_b);
	write(1, "ss\n", 3);
}
