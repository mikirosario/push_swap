/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_removeone.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:33:02 by mrosario          #+#    #+#             */
/*   Updated: 2021/05/12 19:42:09 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*find_preceding_member(t_list *lst, t_list *member)
{
	if (lst == member)
		return (NULL);
	while (lst && lst->next != member)
		lst = lst->next;
	return (lst);
}

/*
** This function removes a single member pointed to by the argument passed as
** *remove from a list pointed to by a pointer pointed to by another pointer
** passed as **alst. If there is no such member in the list, nothing is done.
*/

void	ft_lst_removeone(t_list **alst, t_list *remove)
{
	t_list	*subsequent_member;
	t_list	*preceding_member;
	t_list	*tmp;

	tmp = *alst;
	while (tmp && tmp != remove)
		tmp = tmp->next;
	if (!tmp)
		return ;
	subsequent_member = remove->next;
	preceding_member = find_preceding_member(*alst, remove);
	if (preceding_member == NULL)
	{
		ft_lstdelone(remove, free);
		*alst = subsequent_member;
	}
	else
	{
		ft_lstdelone(remove, free);
		preceding_member->next = subsequent_member;
	}
}
