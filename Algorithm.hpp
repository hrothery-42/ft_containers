/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Algorithm.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrothery <hrothery@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:17:23 by hrothery          #+#    #+#             */
/*   Updated: 2022/12/16 12:25:37 by hrothery         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGORITHM_HPP
# define ALGORITHM_HPP

namespace ft {
	
		/*lexicograpical compare checks if the first range is lexicographically (alphabetically) 
		less than the second range and returns true if the first element is smaller*/
		template<class InputIt1, class InputIt2>
		bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2 ) {
			for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
			{
				if (*first1 < *first2)
					return true;
				if (*first2 < *first1)
					return false;
			}
			return (first1 == last1) && (first2 != last2);
		};

		/*elements are compared using the given binary comparison function comp*/	
		template<class InputIt1, class InputIt2, class Compare>
		bool lexicographical_compare( InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
			for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
			{
				if (comp(*first1, *first2))
					return true;
				if (comp(*first2, *first1))
					return false;
			}
			return (first1 == last1) && (first2 != last2);
		};

		/*equal:
		returns true if the range [first1, last1] == [first2, first2 + (last1 - first1)]
		and otherwise false.*/
		template<class InputIt1, class InputIt2>
		bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2 ) {
			for (; first1 != last1; ++first1, (void) ++first2)
			{
				if (!(*first1 == *first2))
					return false;
			}
			return true;
		};

		template<class InputIt1, class InputIt2, class BinaryPredicate>
		bool equal( InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred) {
			for (; first1 != last1; ++first1, (void) ++first2)
			{
				if (pred(*first1, *first2) == false)
					return false;
			}
			return true;
		};

		template<class MapIt1, class MapIt2>
		bool pairs_are_equal( MapIt1 first1,MapIt1 last1, MapIt2 first2 )
		{
			for (; first1 != last1; ++first1, ++first2)
			{
				if (!((*first1).first == (*first2).first))
					return false;
				if (!((*first1).second == (*first2).second))
					return false;
			}
			return true;
		};

		template<class MapIt1, class MapIt2>
		bool compare_pairs( MapIt1 first1, MapIt1 last1, MapIt2 first2, MapIt2 last2 )
		{
			for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
			{
					if ((*first1).first < (*first2).first || ((*first1).first == (*first2).first && (*first1).second < (*first2).second))
						return true;
					if ((*first2).first < (*first1).first || ((*first1).first == (*first2).first && (*first2).second < (*first1).second))
						return false;
				}
				return (first1 == last1) && (first2 != last2);
		};

}

#endif