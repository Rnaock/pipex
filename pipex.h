/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 02:15:16 by manuel            #+#    #+#             */
/*   Updated: 2022/08/10 23:55:00 by mabimich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/includes/libft.h"
# include <stdio.h> ////////////////////////////////////////////////////////////////
# include <errno.h>
# include <sys/wait.h>
# include <fcntl.h>

typedef struct s_data
{
	char	**argv;
	char	**path;
	int		here_doc;
	char	*hd_file;
	int		file[2];
	int		vanne[1024];
	int		n_child;
	pid_t	*pid;
	int		c_errno;
}			t_data;

void	dispatch_exit(t_data *data, int code);
void	close_pipes(t_data *data, int e);
char	*get_path(char *cmd, char **envp);
void	free_tab_with_1blank(char **tab, char *str);
char	*ft_3strjoin_free_s1(char *s1, char *s2, char *s3);
void	ft_msg(char *str);

#endif
