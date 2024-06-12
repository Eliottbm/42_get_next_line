/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebengtss <ebengtss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:02:04 by ebengtss          #+#    #+#             */
/*   Updated: 2024/06/12 11:58:53 by ebengtss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_free(char **str, char *buff)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	if (buff)
		free(buff);
	return (1);
}

static char	*trim_line(char **tab)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	while (tab[0][i] && tab[0][i] != '\n')
		i++;
	tmp = malloc(sizeof(char) * (i + 2));
	if (!tmp)
		return (NULL);
	ft_strlcpy(tmp, tab[0], (i + 1));
	if (tab[0] && tab[0][i] == '\n' && tab[0][i + 1])
	{
		tmp2 = ft_strdup(&(tab[0][++i]));
		ft_free(&tab[0], ft_strdup(""));
		tab[0] = tmp2;
	}
	else
		ft_free(&tab[0], ft_strdup(""));
	return (tmp);
}

static int	read_line(char **tab, int fd)
{
	char	*buff;
	int		rbytes;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (1);
	rbytes = 1;
	while (rbytes > 0)
	{
		rbytes = read(fd, buff, BUFFER_SIZE);
		if ((rbytes < 0) || (rbytes == 0 && !tab[0]))
			return (ft_free(&tab[0], buff));
		buff[rbytes] = '\0';
		tab[0] = ft_strjoin(tab[0], buff);
		if (!tab[0])
			return (1);
		if (is_nl(tab[0]) == 0)
			break ;
	}
	if (buff)
		free(buff);
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*tab[1];
	char		*str;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE < 0)
		return (NULL);
	if (read_line(tab, fd))
		return (NULL);
	str = trim_line(tab);
	if (!str)
		return (NULL);
	return (str);
}
