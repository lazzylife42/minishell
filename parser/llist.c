/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreichel <nreichel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:38:28 by smonte-e          #+#    #+#             */
/*   Updated: 2024/01/31 09:59:52 by nreichel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_rdin(char **input, t_sep *sep, int pos)
{
	int	i;

	i = pos;
	sep->rd_in = NULL;
	sep->file_in = NULL;
	while (input[i] && ft_strncmp(input[i], "|", 1) != 0)
	{
		if (ft_strncmp(input[i], "<", 1) == 0 && input[i + 1])
		{
			sep->rd_in = input[i];
			sep->file_in = input[i + 1];
		}
		i++;
	}
}

void	get_rdout(char **input, t_sep *sep, int pos)
{
	int	i;

	i = pos;
	sep->rd_out = NULL;
	sep->file_out = NULL;
	while (input[i] && ft_strncmp(input[i], "|", 1) != 0)
	{
		if (ft_strncmp(input[i], ">", 1) == 0 && input[i + 1])
		{
			sep->rd_out = input[i];
			sep->file_out = input[i + 1];
		}
		i++;
	}
}

t_sep	*create_sep_node(char **arg, char **input, char *pipe, int pos)
{
	t_sep	*new_node;

	new_node = (t_sep *)malloc(sizeof(t_sep));
	if (new_node)
	{
		check_heredoc(arg);
		new_node->arg = arg;
		get_rdin(input, new_node, pos);
		get_rdout(input, new_node, pos);
		new_node->pipe = pipe;
	}
	return (new_node);
}

t_exec	*add_to_exec_list(t_exec *head, t_sep *new_node)
{
	t_exec	*temp;
	t_exec	*current;

	temp = (t_exec *)malloc(sizeof(t_exec));
	if (temp)
	{
		temp->separator = new_node;
		temp->next = NULL;
		if (head == NULL)
			head = temp;
		else
		{
			current = head;
			while (current->next != NULL)
				current = current->next;
			current->next = temp;
		}
	}
	return (head);
}

void	free_exec_list(t_exec *head)
{
	int		i;
	t_exec	*temp;
	t_sep	*current_sep;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->separator)
		{
			current_sep = temp->separator;
			if (current_sep->arg)
			{
				i = -1;
				while (current_sep->arg[++i])
					free(current_sep->arg[i]);
				free(current_sep->arg);
			}
			free(current_sep);
		}
		free(temp);
	}
}

/*oid	print_to_run(t_exec *to_run)
{
	t_sep	*current_sep;
	int		i;
	char	**args;

	if (to_run == NULL)
	{
		printf("Nothing to execute...\n");
		return ;
	}
	while (to_run != NULL)
	{
		current_sep = to_run->separator;
		if (current_sep != NULL)
		{
			i = 0;
			args = current_sep->arg;
			while (args && args[i] != NULL)
			{
				printf("Argument: [%s]\n", args[i]);
				i++;
			}
			printf("Input Redirect: ");
			if (current_sep->rd_in != NULL)
				printf("[%s]\n", current_sep->rd_in);
			else
				printf("[None]\n");
			printf("Output Redirect: ");
			if (current_sep->rd_out != NULL)
				printf("[%s]\n", current_sep->rd_out);
			else
				printf("[None]\n");
			printf("Input File: ");
			if (current_sep->file_in != NULL)
				printf("[%s]\n", current_sep->file_in);
			else
				printf("[None]\n");
			printf("Output File: ");
			if (current_sep->file_out != NULL)
				printf("[%s]\n", current_sep->file_out);
			else
				printf("[None]\n");
			printf("Pipe Operator: ");
			if (current_sep->pipe != NULL)
				printf("[%s]\n", current_sep->pipe);
			else
				printf("[None]\n");
			printf("---------\n");
		}
		to_run = to_run->next;
	}
}*/
