/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:21:19 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/08 21:50:42 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*verif_paths(char **paths, char *cmd)
{
	int		i;
	char	*out;

	out = NULL;
	i = -1;
	while (paths && paths[++i])
	{
		if (!access(paths[i], F_OK | X_OK) && !out)
			out = ft_strdup(paths[i]);
		free(paths[i]);
	}
	if (!out && !access(cmd, F_OK | X_OK))
		out = ft_strdup(cmd);
	if (paths)
		free(paths);
	if (cmd)
		free(cmd);
	return (out);
}

char	*get_path(char *cmd, char **envp, t_data *data)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = -1;
	while (envp && envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	if (!envp || !envp[i] || ft_strncmp(envp[i], "PATH=", 5))
		dispatch_exit(data, 4);
	cmd = ft_pick(cmd, ' ', 0);
	tmp = ft_pick(envp[i], '=', 1);
	paths = ft_split(tmp, ':');
	free(tmp);
	i = -1;
	while (paths && paths[++i])
	{
		paths[i] = ft_3strjoin_free_s1(paths[i], "/", cmd);
		if (!paths[i])
			free_tab_with_1blank(data, paths, cmd);
	}
	return (verif_paths(paths, cmd));
}
