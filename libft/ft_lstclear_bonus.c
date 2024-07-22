/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:40:00 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/16 10:30:04 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp1;
	t_list	*temp2;

	if (lst)
	{
		temp1 = *lst;
		if (*lst)
		{
			while (temp1)
			{
				temp2 = temp1->next;
				del(temp1->content);
				free(temp1);
				temp1 = temp2;
			}
			*lst = NULL;
		}
	}
}
