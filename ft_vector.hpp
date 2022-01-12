/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:25:51 by julian            #+#    #+#             */
/*   Updated: 2022/01/12 16:02:02 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "ft_iterator.hpp"
#include <iterator>
#include <memory>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			/* -------------------- MEMBER TYPES -------------------- */

			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef std::ptrdiff_t								difference_type;
			typedef	std::size_t									size_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ft::iterator<value_type>					iterator;
			typedef ft::iterator<const value_type>				const_iterator;
			typedef ft::reverse_iterator<value_type>			reverse_iterator;
			typedef ft::reverse_iterator<const value_type>		const_reverse_iterator;

		public:
			/* -------------------- MEMBER FUNCTIONS -------------------- */

			// empty container constructor (default constructor)
			// constructs an empty container, with no elements
			explicit vector (const allocator_type& alloc = allocator_type()) : _start(0), _finish(0), _endOfStorage(0), _alloc(alloc) {}

			// fill constructor
			// Constructs a container with n elements. Each element is a copy of val.
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				_start = _alloc.allocate(n);
				_finish = _start;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_finish++, val);
				_endOfStorage = _finish;
			}

			// range constructor
			// Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				// size_type n = 0;
				// std::distance(first, last, n);
				_start = _alloc.allocate(last - first);
				_finish = _start;
				for (int i = 0; i < (last - first); i++)
				{
					// std::cout << "i = " << i << std::endl;
					// std::cout << "last - first = " << last - first << std::endl;
					_alloc.construct(_finish++, first++);
				}
				_endOfStorage = _finish;
			}
			
			// copy constructor
			// Constructs a container with a copy of each of the elements in x, in the same order.
			vector (const vector& x) : _alloc(x._alloc)
			{
				_start = _alloc.allocate(x.size());
				_finish = _start;
				for (size_type i = 0; i < x.size(); i++)
					_alloc.construct(_finish++, x._start[i]);
				_endOfStorage = _finish;
			}
			
			~vector() {_alloc.deallocate(_start, this->size());}

			/* -------------------- Iterators -------------------- */

			iterator				begin() {return (_start);}
			iterator				end() {return (_finish);}
			const_iterator			cbegin() const {return (_start);}
			const_iterator			cend() const {return (_finish);}
			reverse_iterator		rbegin() {return (_finish - 1);}
			reverse_iterator		rend() {return (_start - 1);}
			const_reverse_iterator	crbegin() {return (_finish - 1);}
			const_reverse_iterator	crend() {return (_start - 1);}

			/* -------------------- Capacity -------------------- */
		
			size_type size() const {return (_finish - _start);}

			/* -------------------- Element access -------------------- */

			reference		operator[] (size_type n) {return (_start[n]);}
			const_reference	operator[] (size_type n) const {return (_start[n]);}

			/* -------------------- Modifiers -------------------- */

			/* -------------------- Allocator -------------------- */

		private:
			pointer			_start;
			pointer			_finish;
			pointer			_endOfStorage;
			allocator_type 	_alloc;
	};
}
#endif