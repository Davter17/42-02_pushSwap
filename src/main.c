/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpico-bu <mpico-bu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 20:38:30 by event             #+#    #+#             */
/*   Updated: 2025/04/06 23:50:36 by mpico-bu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	free_split(char **split_argv)
{
	int	i;

	i = 0;
	while (split_argv[i])
		free(split_argv[i++]);
	free(split_argv);
}

static char	**parse_args(int argc, char **argv, char ***split_ref)
{
	*split_ref = NULL;
	if (argc == 2)
	{
		*split_ref = ft_split(argv[1], ' ');
		return (*split_ref);
	}
	return (argv + 1);
}

int	main(int argc, char **argv)
{
	t_bilist	*slot_a;
	t_bilist	*slot_b;
	char		**split_argv;
	char		**args;

	slot_b = NULL;
	args = parse_args(argc, argv, &split_argv);
	if (check_errors(args))
	{
		if (split_argv)
			free_split(split_argv);
		exit(1);
	}
	generate_slot(&slot_a, args);
	if (!slot_sorted(slot_a))
		slot_a = turk_algorithm(&slot_a, &slot_b);
	slot_free(&slot_a);
	if (split_argv)
		free_split(split_argv);
	return (0);
}
