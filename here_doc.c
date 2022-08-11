/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:20:52 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/11 16:30:55 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_data *data)
{
	char	*ret;
	int		len;
	char	*tmp;

	len = 1;
	data->hd_file = ft_create_fname(NAME_TMP_FILE);
	data->file[0] = open(data->hd_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (data->file[0] != -1 && len != -1)
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
	close(data->file[0]);
}
