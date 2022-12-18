/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 19:26:05 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/14 19:24:09 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct s_pipex
{
	pid_t	pid;
	int		fd_infile;
	int		fd_outfile;
	int		fd_pipe[2];
	char	**path;
	char	**cmd1_bf;
	char	**cmd2_bf;
	char	*cmd1_af;
	char	*cmd2_af;
}	t_pipex;

//pipex.c
char	**ft_path(char **envp);
void	ft_fd(int to_close, int std_in, int std_out);
char	*ft_cmd(char **path, char *cmd);
int		ft_arg(t_pipex *px, char **av, char **envp);

// help_1.c & help_2.c
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_error(char *str, int num);

#endif