/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:40:04 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:40:11 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bilist	*solve_three(t_bilist *slot)
{
	int	num_1;
	int	num_2;
	int	num_3;

	num_1 = slot->value;
	if (slot->next)
	{
		num_2 = slot->next->value;
		if (slot->next->next)
		{
			num_3 = slot->next->next->value;
			if (num_1 > num_2 && num_2 > num_3)
				ra(&slot);
			else if (num_1 > num_3 && num_3 > num_2)
				ra(&slot);
			else if (num_2 > num_1 && num_1 > num_3)
				rra(&slot);
			else if (num_2 > num_3 && num_3 > num_1)
				rra(&slot);
		}
		if (slot->value > slot->next->value)
			sa(&slot);
	}
	return (slot_first(slot));
}
