/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:20:52 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/07 18:04:17 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_data *data)
{
	char	*ret;
	int		len;
	char	*tmp;

	len = 1;
	while (len && len != -1)
	{
		ret = get_next_line(STDIN_FILENO);
		tmp = ft_strdup(ret);
		if (tmp == NULL)
			break ;
		tmp[strlen(tmp) - 1] = '\0';
		if (!ft_strcmp(tmp, data->argv[2]))
			break ;
		len = write(data->file[0], ret, ft_strlen(ret));
		free(tmp);
		free(ret);
	}
	if (tmp)
		free(tmp);
	if (ret)
		free(ret);
	if (len == -1)
		dispatch_exit(data, 5);
}
