/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byjeon <byjeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 18:52:47 by byjeon            #+#    #+#             */
/*   Updated: 2022/12/14 19:14:14 by byjeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**ft_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) && envp[i])
		i++;
	if (envp[i] == NULL)
		ft_error("PATH", 1);
	path = envp[i] + 5;
	return (ft_split(path, ':'));
}

void	ft_fd(int to_close, int std_in, int std_out)
{
	close(to_close);
	if (dup2(std_in, STDIN_FILENO) == -1)
		ft_error("dup2", 1);
	if (dup2(std_out, STDOUT_FILENO) == -1)
		ft_error("dup2", 1);
	close(std_in);
	close(std_out);
}

char	*ft_cmd(char **path, char *cmd)
{
	char	*path_cmd;
	char	*tmp;
	int		fd;
	int		i;

	fd = access(cmd, X_OK);
	if (fd != -1)
		return (cmd);
	path_cmd = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], path_cmd);
		fd = access(tmp, X_OK);
		if (fd != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		free(tmp);
		close(fd);
	}
	free(path_cmd);
	return (NULL);
}

int	ft_arg(t_pipex *px, char **av, char **envp)
{
	px->fd_infile = open(av[1], O_RDONLY);
	if (px->fd_infile == -1)
		ft_error("infile", 1);
	px->fd_outfile = open(av[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (px->fd_outfile == -1)
		ft_error("outfile", 1);
	px->path = ft_path(envp);
	px->cmd1_bf = ft_split(av[2], ' ');
	px->cmd1_af = ft_cmd(px->path, px->cmd1_bf[0]);
	px->cmd2_bf = ft_split(av[3], ' ');
	px->cmd2_af = ft_cmd(px->path, px->cmd2_bf[0]);
	if (px->cmd1_af == NULL || px->cmd2_af == NULL)
	{
		ft_error("command", 127);
		return (127);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	px;
	int		result;

	if (ac != 5)
		ft_error("arg", 1);
	result = ft_arg(&px, av, envp);
	if (pipe(px.fd_pipe) < 0)
		ft_error("pipe", 1);
	px.pid = fork();
	if (px.pid == -1)
		ft_error("fork", 1);
	else if (px.pid == 0)
	{
		ft_fd(px.fd_pipe[0], px.fd_infile, px.fd_pipe[1]);
		if (execve(px.cmd1_af, px.cmd1_bf, envp) == -1)
			ft_error("execve", result);
	}
	else
	{
		ft_fd(px.fd_pipe[1], px.fd_pipe[0], px.fd_outfile);
		waitpid(px.pid, NULL, WNOHANG);
		if (execve(px.cmd2_af, px.cmd2_bf, envp) == -1)
			ft_error("execve", result);
	}
	return (0);
}
