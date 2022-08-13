/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabimich <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:21:19 by mabimich          #+#    #+#             */
/*   Updated: 2022/08/13 17:45:08 by mabimich         ###   ########.fr       */
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

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = -1;
	while (envp && envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	if (!envp || !envp[i] || ft_strncmp(envp[i], "PATH=", 5))
		return (NULL);
	cmd = ft_pick(cmd, ' ', 0);
	tmp = ft_pick(envp[i], '=', 1);
	paths = ft_split(tmp, ':');
	free(tmp);
	i = -1;
	while (paths && paths[++i])
	{
		paths[i] = ft_3strjoin_with_free(paths[i], "/", cmd, 100);
		if (!paths[i])
			free_tab_with_1blank(paths, cmd);
	}
	return (verif_paths(paths, cmd));
}
