/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:57:43 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/13 18:08:56 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_msg(char *s1, char *s2)
{	
	char	*tmp;
	char	*out;

	tmp = ft_3strjoin_with_free("Error: ", s1, ": ", 0);
	if (!tmp)
		return ;
	out = ft_3strjoin_with_free(tmp, s2, "\n", 100);
	ft_putendl_fd(out, 2);
	free(out);
}

void	close_pipes(t_data *data, int e)
{
	int	i;

	i = 0;
	while (i < (data->n_child - 1) * 2 && i != e)
		close(data->vanne[i++]);
}

void	dispatch_exit2(t_data *data, int code, int status)
{
	if (code > 6 && data->file[1] != -1)
		close(data->file[1]);
	if (code > 5 && data->file[0] != -1)
		close(data->file[0]);
	if (code > 3)
		ft_free_tab_str(data->path, data->n_child);
	if (code > 2)
		free(data->pid);
	if (code > 1)
		free(data);
	data = NULL;
	close(0);
	close(1);
	close(2);
	if (code == 127)
		exit(code);
	if (code == 666)
		exit(1);
	exit(WEXITSTATUS(status));
}

void	dispatch_exit(t_data *data, int code)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	if (code == 0)
		code = 7;
	if (code >= 10 && !(code % 10))
		close_pipes(data, code / 5);
	if (data->hd_file && waitpid(data->pid[0], NULL, 0))
		unlink(data->hd_file);
	if (data->hd_file)
		free(data->hd_file);
	if (!(code % 111))
	{
		close_pipes(data, -1);
		while (code == 777 && ++i < data->n_child && data->pid[i])
			if (data->pid[i] != -1)
				waitpid(data->pid[i], &status, 0);
	}
	if (code == 555)
		ft_msg(strerror(errno), data->argv[1 + data->here_doc]);
	if (code == 666)
		ft_msg(strerror(errno), data->argv[data->n_child + 2 + data->here_doc]);
	dispatch_exit2(data, code, status);
}
