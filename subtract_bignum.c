/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtract_bignum.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scamargo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/13 12:33:18 by scamargo          #+#    #+#             */
/*   Updated: 2018/01/13 14:01:56 by scamargo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft.h"

static int	second_is_bigger(char **p_n2, int *p_len2, char **p_n1, int *p_len1)
{
	int		is_sec_bigger;
	int		temp_len;
	char	*temp_str;

	is_sec_bigger = (*p_len2 != *p_len1) ? (*p_len2 > *p_len1) : 0;
	if (*p_len2 == *p_len1)
	{
		temp_len = *p_len2;
		while (--temp_len >= 0)
		{
			if ((*p_n2)[temp_len] != (*p_n1)[temp_len])
				is_sec_bigger = ((*p_n2)[temp_len] > (*p_n1)[temp_len]);
		}
	}
	if (is_sec_bigger)
	{
		temp_str = *p_n1;
		*p_n1 = *p_n2;
		*p_n2 = temp_str;
		temp_len = *p_len1;
		*p_len1 = *p_len2;
		*p_len2 = temp_len;
	}
	return (is_sec_bigger);
}

static void	trim_trailing_zeroes(char *num)
{
	int len;
	int is_neg;

	len = ft_strlen(num);
	is_neg = (num[len - 1] == '-') ? 1 : 0;
	while (--len >= 0)
	{
		if (num[len] != '0' && num[len] != '-')
		{
			if (is_neg)
				num[++len] = '-';
			break ;
		}
	}
	if (len < 0)
		++len;
	num[++len] = '\0';
}

static int	carry_the_one(char *num, int initial_index, int factor)
{
	int index;

	index = initial_index;
	while (index > 0)
	{
		if (num[index - 1] != '0')
		{
			num[index - 1] -= 1;
			while (index < initial_index)
				num[index++] = '9';
			return (factor + 10);
		}
		index--;
	}
	ft_putendl("you screwed you up big time!! carry_the_one() not working");
	return (0);
}

char		*subtract_bignum(char *num1, int len1, char *num2, int len2)
{
	char	*result;
	t_array *char_arr;
	int		is_second_bigger;
	int		fac1;
	int		fac2;

	if (num1[0] == '-' && num2[0] == '-')
		return (subtract_bignum(++num1, --len1, ++num2, --len2));
	else if (num1[0] == '-' && num2[0] != '-') // TODO: protect call to convert_to_neg
		return (add_bignum(num1, len1, convert_to_neg(num2, len2), len2 + 1));
	else if (num2[0] == '-' && num1[0] != '-')
		return (add_bignum(++num2, --len2, num1, len1));
	if (!(char_arr = init_bignum("", len1)))
		return (0);
	is_second_bigger = second_is_bigger(&num2, &len2, &num1, &len1);
	len1--;
	len2--;
	while (len1 >= 0 || len2 >= 0)
	{
		fac1 = (len1 < 0) ? 0 : num1[len1] - '0';
		fac2 = (len2 < 0) ? 0 : num2[len2] - '0';
		fac1 = (fac1 < fac2) ? carry_the_one(num1, len1, fac1) : fac1;
		fac1 -= fac2;
		arr_insert(char_arr, fac1 + '0');
		len1--;
		len2--;
	}
	if (is_second_bigger)
		arr_insert(char_arr, '-');
	arr_insert(char_arr, '\0');
	trim_trailing_zeroes(char_arr->str);
	ft_strrev(char_arr->str);
	result = char_arr->str;
	free(char_arr);
	return (result);
}
