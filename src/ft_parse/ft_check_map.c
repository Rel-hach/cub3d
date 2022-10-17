/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-hach <rel-hach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 21:06:31 by rel-hach          #+#    #+#             */
/*   Updated: 2022/10/17 13:56:56 by rel-hach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"


bool	valid_index(int j, char *prev_line, char *next_line)
{
	return (prev_line && j < (int) ft_strlen(prev_line) 
			&& next_line && j < (int) ft_strlen(next_line));
}

bool	check_circumference(int j, char *line, char *prev_line, char *next_line)
{
	char	*str;

	str = "01NWSE";
	if (!ft_strchr(str, line[j - 1]) || !ft_strchr(str, line[j + 1]))
		return (false);
	else if (!prev_line || !ft_strchr(str, prev_line[j]))
		return (false);
	else if(!next_line || !ft_strchr(str, next_line[j]))
		return (false);
	return (true);
}

void	check_map_validity(t_var *g, char **map, int nb_line)
{
	int		i;
	int		j;
	
	i = -1;
	(void)nb_line;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '0' || map[i][j] == 'N'
				|| map[i][j] == 'W' || map[i][j] == 'E'
				|| map[i][j] == 'S')
			{
				if (i == 0 || !valid_index(j, map[i - 1], map[i + 1]))
					ft_put_error("invalid index");
				if (!check_circumference(j, map[i], map[i - 1], map[i + 1]))
					ft_put_error("cirumference error");
				save_player_position(g, map[i][j], i, j);
			}
		}
	}
	if (g->nb_player != 1)
		ft_put_error("Wrong number of players");
}

void	store_check_map_validity(t_var *g, t_game *head, int count)
{
	t_game	*temp;
	int		i;

	temp = head;
	i = 0;
	g->map = ft_calloc(sizeof (char *), count + 1);
	while (temp && ft_strncmp(temp->line, "\n", 1) != 0)
	{
		g->map[i] = temp->line;
		temp = temp->next;
		i++;
	}
	check_map_validity(g, g->map, i);
}

int		count_map_lines(t_game *head)
{
	int		count;
	t_game	*temp;

	temp = head;
	count = 0;
	while (temp && ft_strncmp(temp->line, "\n", 1) != 0)
	{
		temp = temp->next;
		count++;
	}
	return (count);
}

int		ft_check_map(t_var *g, t_game *head)
{
	t_game	*temp;
	int		count;

	temp = head;
	count = 0;
	while (temp->next && ft_strncmp(temp->line, "\n", 1) == 0)
		temp = temp->next;
	count = count_map_lines(temp);
	store_check_map_validity(g, temp, count);
	return (1);
}