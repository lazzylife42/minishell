/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:56:22 by nreichel          #+#    #+#             */
/*   Updated: 2023/10/17 14:56:53 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;

	if (!lst || !f || !del)
		return (NULL);
	new = ft_lstnew(f(lst->content));
	if (!new)
		return (NULL);
	lst = lst->next;
	res = new;
	while (lst)
	{
		new->next = ft_lstnew(f(lst->content));
		if (!new->next)
		{
			ft_lstclear(&res, (*del));
			return (NULL);
		}
		lst = lst->next;
		new = new->next;
	}
	new->next = NULL;
	return (res);
}
