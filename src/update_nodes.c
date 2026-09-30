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
	int	median_a;
	int	median_b;
	int	j;

	median_a = slot_len(slot_a) / 2;
	j = 0;
	while (slot_a)
	{
		slot_a->index = j;
		slot_a->ra = (j <= median_a);
		slot_a = slot_a->next;
		j++;
	}
	median_b = slot_len(slot_b) / 2;
	j = 0;
	while (slot_b)
	{
		slot_b->index = j;
		slot_b->ra = (j <= median_b);
		slot_b = slot_b->next;
		j++;
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

static int	calc_cost(int idx, int is_ra, int len)
{
	if (is_ra)
		return (idx);
	return (len - idx);
}

static void	update_cost(t_bilist *slot_a, t_bilist *slot_b)
{
	int	len_a;
	int	len_b;
	int	cost_a;
	int	cost_b;

	len_a = slot_len(slot_a);
	len_b = slot_len(slot_b);
	while (slot_a)
	{
		cost_a = calc_cost(slot_a->index, slot_a->ra, len_a);
		cost_b = calc_cost(slot_a->target->index,
				slot_a->target->ra, len_b);
		if (slot_a->ra == slot_a->target->ra)
		{
			if (cost_a > cost_b)
				slot_a->cost = cost_a;
			else
				slot_a->cost = cost_b;
		}
		else
			slot_a->cost = cost_a + cost_b;
		slot_a = slot_a->next;
	}
}

void	update_nodes(t_bilist *a, t_bilist *b, char slot)
{
	t_bilist	*cheapest;
	t_bilist	*temp;

	update_indexs(a, b);
	if (slot == 'b')
	{
		update_targets(b, a, 0);
		return ;
	}
	update_targets(a, b, 1);
	update_cost(a, b);
	temp = a;
	cheapest = a;
	while (temp)
	{
		temp->cheapest = false;
		if (temp->cost < cheapest->cost)
			cheapest = temp;
		temp = temp->next;
	}
	cheapest->cheapest = true;
}
