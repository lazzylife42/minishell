/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:51:38 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/16 09:55:22 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *nw)
{
	t_list	*temp;

	if (lst)
	{
		if (*lst == NULL)
			*lst = nw;
		else
		{
			temp = ft_lstlast(*lst);
			temp->next = nw;
		}
	}
}
