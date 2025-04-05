/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:39:30 by event             #+#    #+#             */
/*   Updated: 2025/04/05 20:39:34 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"

typedef struct s_bilist
{
	int				value;
	struct s_bilist	*pre;
	struct s_bilist	*next;
	int				index;
	bool			ra;
	struct s_bilist	*target;
	int				cost;
	bool			cheapest;
}	t_bilist;

//Algorithms
void		sa(t_bilist **slot);
void		sb(t_bilist **slot);
void		ss(t_bilist **slot_a, t_bilist **slot_b);
void		ra(t_bilist **slot);
void		rb(t_bilist **slot);
void		rr(t_bilist **slot_a, t_bilist **slot_b);
void		rra(t_bilist **slot);
void		rrb(t_bilist **slot);
void		rrr(t_bilist **slot_a, t_bilist **slot_b);
void		pa(t_bilist **slot_a, t_bilist **slot_b);
void		pb(t_bilist **slot_a, t_bilist **slot_b);

//Initialization
bool		check_errors(char **argv);
void		generate_slot(t_bilist **slot_ini, char **argv);

//***Slot utils
int			slot_sorted(t_bilist *slot);
int			slot_len(t_bilist *slot);
t_bilist	*slot_first(t_bilist *slot);
t_bilist	*slot_last(t_bilist *slot);
void		slot_print(t_bilist *slot);
t_bilist	*slot_min(t_bilist *slot);
t_bilist	*slot_max(t_bilist *slot);
t_bilist	*slot_cheapest(t_bilist *stack);
void		slot_free(t_bilist **slot);

//***Nodes initiation
void		update_nodes(t_bilist *a, t_bilist *b, char node);
void		update_indexs(t_bilist *slot_a, t_bilist *slot_b);
void		set_cheapest(t_bilist *stack);

//***Algorithm
t_bilist	*solve_three(t_bilist *slot);
t_bilist	*turk_algorithm(t_bilist **a, t_bilist **b);



#endif
