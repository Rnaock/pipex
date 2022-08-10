/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/10 23:17:13 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup(t_data *data, int i)
{
	if (i == 0)
	{
		if (data->file[0] == -1)
		{
			ft_msg(data->argv[1]);
			dispatch_exit(data, 555);
		}
		dup2(data->file[0], STDIN_FILENO);
		dup2(data->vanne[(i * 2) + 1], STDOUT_FILENO);
	}
	else if (i == data->n_child - 1)
	{
		if (data->file[1] == -1)
		{
			ft_msg(data->argv[data->n_child + i + 1]);
			dispatch_exit(data, 666);
		}
		dup2(data->vanne[(i * 2) - 2], STDIN_FILENO);
		dup2(data->file[1], STDOUT_FILENO);
	}
	else
	{
		dup2(data->vanne[(i * 2) - 2], STDIN_FILENO);
		dup2(data->vanne[(i * 2) + 1], STDOUT_FILENO);
	}
}

void	open_files(t_data *data)
{
	int	i;

	i = -1;
	data->file[0] = open(data->argv[1], O_RDONLY);
	data->file[1] = open(data->argv[data->n_child + 2],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (i + 2 < data->n_child)
		if (pipe(&data->vanne[(++i) * 2]) == -1)
			dispatch_exit(data, 10 * i);
}

void	child(t_data *data, char **envp, int i)
{
	char	**argv;

	ft_dup(data, i);
	if (data->file[0] != -1)
		close(data->file[0]);
	if (data->file[1] != -1)
		close(data->file[1]);
	close_pipes(data, -1);
	argv = ft_split(data->argv[i + 2], ' ');
	if (data->path[i] && argv)
		execve(data->path[i], argv, envp);
	ft_putendl_fd("Error: command not found", 2);
	ft_msg(argv[0]);
	if (argv)
		ft_free_tab_str(argv, -1);
	dispatch_exit(data, 127);
}

t_data	*init(char **argv, char **envp)
{
	int		i;
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		dispatch_exit(data, 1);
	data->argv = argv;
	data->here_doc = 0;
	data->n_child = 2;
	data->pid = ft_calloc_full(sizeof(pid_t), data->n_child);
	if (!data->pid)
		dispatch_exit(data, 2);
	data->path = ft_calloc(sizeof(char **), data->n_child);
	if (!data->path)
		dispatch_exit(data, 3);
	i = -1;
	while (++i < data->n_child)
	{
		if (!argv[i + 2])
			dispatch_exit(data, 3);
		data->path[i] = get_path(argv[i + 2], envp, data);
	}
	return (open_files(data), data);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_data	*data;

	data = NULL;
	if (ac != 5)
		return (ft_putendl_fd("Error: Nombre d'arguments", 2), 1);
	data = init(av, envp);
	i = 0;
	while (i < data->n_child && data->pid[i])
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			dispatch_exit(data, 8);
		if (!data->pid[i])
			child(data, envp, i);
		i++;
	}
	dispatch_exit(data, 777);
	return (0);
}
