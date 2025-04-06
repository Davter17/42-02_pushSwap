/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_slot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:38:19 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:39:49 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_bilist	*bilst_new(t_bilist *prev, int value)
{
	t_bilist	*new_node;

	new_node = malloc(sizeof(t_bilist));
	if (!new_node)
		return (NULL);
	new_node->pre = prev;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

void	generate_slot(t_bilist **slot_ini, char **argv)
{
	int			i;
	t_bilist	*slot_act;
	t_bilist	*next_slot;

	*slot_ini = bilst_new(NULL, ft_atoi(argv[0]));
	if (!slot_ini)
	{
		ft_printf("Error\nMemory allocation failed.\n");
		exit(1);
	}
	slot_act = *slot_ini;
	i = 1;
	while (argv[i])
	{
		next_slot = bilst_new(slot_act, ft_atoi(argv[i]));
		if (!next_slot)
		{
			ft_printf("Error\nMemory allocation failed.\n");
			slot_free(slot_ini);
			exit(1);
		}
		slot_act->next = next_slot;
		slot_act = next_slot;
		i++;
	}
}
