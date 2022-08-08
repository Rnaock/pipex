/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 17:28:34 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/07 19:27:08 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	open_files(t_data *data)
{
	int	i;

	i = -1;
	if (data->here_doc)
	{
		data->hd_file = ft_create_fname(NAME_TMP_FILE);
		data->file[0] = open(data->hd_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->file[0] == -1)
			dispatch_exit(data, 5);
		here_doc(data);
		close(data->file[0]);
		data->file[0] = open(data->hd_file, O_RDONLY);
	}
	else
		data->file[0] = open(data->argv[1], O_RDONLY);
	if (data->file[0] == -1)
		dispatch_exit(data, 5);
	data->file[1] = open(data->argv[data->n_child + 2 + data->here_doc],
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->file[1] == -1)
		dispatch_exit(data, 6);
	while (i + 2 < data->n_child)
		if (pipe(&data->vanne[(++i) * 2]) == -1)
			dispatch_exit(data, 10 * i);
}

void	child(t_data *data, char **envp, int i)
{
	char	**argv;

	if (i == 0)
	{
		dup2(data->file[0], STDIN_FILENO);
		dup2(data->vanne[(i * 2) + 1], STDOUT_FILENO);
	}
	else if (i == data->n_child - 1)
	{
		dup2(data->vanne[(i * 2) - 2], STDIN_FILENO);
		dup2(data->file[1], STDOUT_FILENO);
	}
	else
	{
		dup2(data->vanne[(i * 2) - 2], STDIN_FILENO);
		dup2(data->vanne[(i * 2) + 1], STDOUT_FILENO);
	}
	close_pipes(data, -1);
	argv = ft_split(data->argv[i + 2 + data->here_doc], ' ');
	if (data->path[i] && argv)
		execve(data->path[i], argv, envp);
	ft_putendl_fd("Error: command not found", 2);
	if (argv)
		ft_free_tab_str(argv, -1);
}

t_data	*init(int argc, char **argv, char **envp)
{
	int		i;
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	if (!data)
		dispatch_exit(data, 1);
	data->argv = argv;
	data->here_doc = 0;
	if (!ft_strcmp(argv[1], "here_doc"))
		data->here_doc = 1;
	data->n_child = argc - 3 - data->here_doc;
	data->pid = ft_calloc_full(sizeof(pid_t), data->n_child);
	if (!data->pid)
		dispatch_exit(data, 2);
	data->path = ft_calloc(sizeof(char **), data->n_child);
	if (!data->path)
		dispatch_exit(data, 3);
	i = -1;
	while (++i < data->n_child)
	{
		if (!argv[i + 2 + data->here_doc])
			dispatch_exit(data, 3);
		data->path[i] = get_path(argv[i + 2 + data->here_doc], envp, data);
	}
	return (open_files(data), data);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_data	*data;

	data = NULL;
	if (ac <= 4 || ac >= 517 || (ac == 5 && !ft_strcmp(av[1], "here_doc")))
		return (ft_putendl_fd("Error: Nombre d'arguments", 2), 1);
	data = init(ac, av, envp);
	i = 0;
	while (i < data->n_child && data->pid[i])
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			dispatch_exit(data, 8);
		if (!data->pid[i])
		{
			child(data, envp, i);
			dispatch_exit(data, 127);
		}
		i++;
	}
	dispatch_exit(data, 777);
	return (0);
}