/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_instructions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 19:50:35 by mrosario          #+#    #+#             */
/*   Updated: 2021/06/15 20:31:18 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

/*
** Find an exact match for a null-terminated string 'match' in a string 'str'
** separated by a separator 'sep'. The separator 'sep' must be standard ASCII
** and may not be NUL and both string pointers must be valid.
**
** In case of an error, -1 is returned. In case of a match, 1 is returned. In
** case of no match, 0 is returned.
*/

static int	ft_str_match(char *match, char *str, char sep)
{
	size_t	i;
	size_t	matchlen;
	size_t	toklen;

	if (sep == '\0' || !ft_isascii(sep) || str == NULL || match == NULL)
		return (-1);
	matchlen = ft_strlen(match);
	while (*str)
	{
		i = 0;
		if (*str == sep)
			while (*str == sep)
				str++;
		while (str[i] && str[i] != sep)
			i++;
		toklen = &str[i] - str;
		if (matchlen == toklen && !ft_strncmp(match, str, toklen))
			return (1);
		str = &str[i];
	}
	return (0);
}

/*
** This function retrieves all instructions from STDIN and places them in a
** linked list called lst.
**
** In piped mode, the last instruction read will cause return get_next_line to
** return 0, while in tty mode the last instruction read will be the EOF command
** sent via CTRL+D, which seems to be converted into a single NULL char.
*/

void	get_instructions(t_checker *checker)
{
	int		ret;
	char	*buf;
	char	*content;
	t_list	*new;

	buf = NULL;
	ret = ft_get_next_line(STDIN_FILENO, &buf);
	while (ret > 0 || *buf)
	{
		if (ret == -1)
			exit_failure("GNL Error", checker);
		if (ft_str_match(buf, INSTRUCTIONS, ':') < 1)
			exit_failure("Error", checker);
		content = ft_strdup(buf);
		new = ft_lstnew(content);
		if (checker->lst)
			ft_lstadd_back(&checker->lst, new);
		else
			checker->lst = new;
		buf = ft_del(buf);
		ret = ft_get_next_line(STDIN_FILENO, &buf);
	}
	if (buf)
		buf = ft_del(buf);
}
