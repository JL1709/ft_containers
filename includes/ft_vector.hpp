/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:25:51 by julian            #+#    #+#             */
/*   Updated: 2022/01/19 15:44:32 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include "ft_algorithm.hpp"
#include "ft_iterator.hpp"
#include "ft_random_access_iterator.hpp"
#include "ft_type_traits.hpp"
#include "ft_utility.hpp"
#include <string>
#include <memory>
#include <stdexcept>

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			/* -------------------- MEMBER TYPES -------------------- */

			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef std::ptrdiff_t									difference_type;
			typedef	std::size_t										size_type;
			typedef typename allocator_type::reference				reference;
			typedef typename allocator_type::const_reference		const_reference;
			typedef typename allocator_type::pointer				pointer;
			typedef typename allocator_type::const_pointer			const_pointer;
			typedef ft::random_access_iterator<value_type>			iterator;
			typedef ft::random_access_iterator<const value_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

		public:
			/* -------------------- MEMBER FUNCTIONS -------------------- */ // DONE

			// empty container constructor (default constructor)
			// constructs an empty container, with no elements
			explicit vector(const allocator_type& alloc = allocator_type()) : _first(0), _last(0), _capacity(0), _alloc(alloc) {}

			// fill constructor
			// Constructs a container with n elements. Each element is a copy of val.
			explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc)
			{
				_capacity = _getCapacity(n);
				_first = _alloc.allocate(_capacity);
				_last = _first;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_last++, val);
			}

			// range constructor
			// Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element in that range, in the same order.
			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), \
					typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) : _alloc(alloc)
			{
				size_type n = last - first;
				_capacity = _getCapacity(n);
				_first = _alloc.allocate(_capacity);
				_last = _first;
				for (size_type i = 0; i < n; i++)
					_alloc.construct(_last++, *first++);
			}
			
			// copy constructor
			// Constructs a container with a copy of each of the elements in x, in the same order.
			vector(const vector& x) : _alloc(x._alloc)
			{
				_first = _alloc.allocate(x._capacity);
				_last = _first;
				_capacity = x._capacity;
				for (size_type i = 0; i < x.size(); i++)
					_alloc.construct(_last++, x._first[i]);
			}
			
			~vector() {_alloc.deallocate(_first, this->size());}

			vector& operator=(const vector& x) 
			{
				if (this != &x)
				{
					this->~vector();
					_alloc = x._alloc;
					_first = _alloc.allocate(x._capacity);
					_last = _first;
					for (size_type i = 0; i < x.size(); i++)
						_alloc.construct(_last++, x._first[i]);
					_capacity = x._capacity;
				}
				return *this;
			}

			/* -------------------- Iterators -------------------- */ //DONE

			iterator				begin() {return iterator(_first);}
			iterator				end() {return iterator(_last);}
			const_iterator			cbegin() const {return const_iterator(_first);}
			const_iterator			cend() const {return const_iterator(_last);}
			reverse_iterator		rbegin() {return reverse_iterator(_first);}
			reverse_iterator		rend() {return reverse_iterator(_last);}
			const_reverse_iterator	crbegin() {return const_reverse_iterator(_first);}
			const_reverse_iterator	crend() {return const_reverse_iterator(_last);}

			/* -------------------- Capacity -------------------- */
		
			size_type size() const {return (_last - _first);}
			size_type max_size() const {return _alloc.max_size();}
			
			// void resize(size_type n, value_type val = value_type())
			// {
			// 	(void) val;
			// 	if (n < size())
			// 	{
			// 		// content is reduced to first n elements
			// 		// removing and destroying those beyoned
			// 		_alloc.destroy(_first + n);
			// 		_last = _first + n;
			// 	}
			// 	// if (n > _capacity)
			// 	// {
					
			// 	// }
			// 	// if (n > size())
			// 	// {
			// 	// 	//  expand content by inserting at the end as many elements as needed to reach the size of n
			// 	// 	// if val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
 
			// 	// }
			// }

			size_type capacity() const {return (_capacity);}
			bool empty() const {return (_first == _last);}

			/* -------------------- Element access -------------------- */ //DONE

			reference operator[](size_type n) {return (_first[n]);}
			const_reference	operator[](size_type n) const {return (_first[n]);}
			
			reference  at(size_type n)
			{
				if (n >= size())
					throw std::out_of_range("ft::vector");
				else
					return (_first[n]);
			}
			
			const_reference at(size_type n) const
			{
				if (n >= size())
					throw std::out_of_range("ft::vector");
				else
					return (_first[n]);
			}

			reference front() {return reference(*_first);}
			const_reference front() const {return const_reference(*_first);}
			reference back() {return reference(*(_last - 1));}
			const_reference back() const {return const_reference(*(_last - 1));}
			value_type* data() {return (_first);}
			const value_type* data() const {return (_first);}

			/* -------------------- Modifiers -------------------- */ // DONE
			
			void assign(size_type n, const value_type& val)
			{
				this->clear();
				if (_capacity >= n)
				{
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_last++, val);
				}
				else
				{
					_capacity = _getCapacity(n);
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_last++, val);
				}
			}
			
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last, \
						typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				this->clear();
				size_type n = last - first;
				if (_capacity >= n)
				{
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_last++, *first++);	
				}
				else
				{
					_capacity = _getCapacity(n);
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_last++, *first++);
				}
			}

			void push_back(const value_type& val)
			{
				if (size() == _capacity)
				{
					ft::vector<T> tmp(*this);
					size_type n = this->size();
					this->clear();
					this->~vector();
					_alloc = tmp._alloc;
					_capacity = _getCapacity(tmp._capacity + 1);
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (size_type i = 0; i < n; i++)
						_alloc.construct(_last++, tmp._first[i]);
				}
				_alloc.construct(_last++, val);
			}

			void pop_back() {_alloc.destroy(--_last);}

			iterator insert(iterator position, const value_type& val)
			{
				ft::vector<T> tmp(*this);
				size_type pos = position - _first;
				size_type n = (pos > size()) ? pos : size();
				
				this->clear();
				this->~vector();
				_alloc = tmp._alloc;
				_capacity =  (pos > tmp.size()) ? _getCapacity(n) : _getCapacity(n + 1);
				_first = _alloc.allocate(_capacity);
				_last = _first;
				size_type i = 0;
				size_type j = 0;
				int insert = 0;
				while (j <= n)
				{
					if (j == pos && insert == 0)
					{
						_alloc.construct(_last++, val);
						insert = 1;
					}
					else
						_alloc.construct(_last++, tmp._first[i++]);
					++j;
				}
				return (_first + pos);
			}

			void insert(iterator position, size_type count, const value_type& val)
			{
				ft::vector<T> tmp(*this);
				size_type pos = position - _first;
				size_type n = (pos > size()) ? pos : size();
				
				this->clear();
				this->~vector();
				_alloc = tmp._alloc;
				_capacity = _getCapacity(n + count);
				_first = _alloc.allocate(_capacity);
				_last = _first;
				size_type i = 0;
				size_type j = 0;
				int insert = 0;
				while (j <= n)
				{
					if (j == pos && insert == 0)
					{
						while (count)
						{
							_alloc.construct(_last++, val);
							--count;
						}
						insert = 1;
					}
					else
						_alloc.construct(_last++, tmp._first[i++]);
					++j;
				}
			}

			template <class InputIterator>
			void insert(iterator position, InputIterator first, InputIterator last, \
				typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type* = 0)
			{
				ft::vector<T> tmp(*this);
				size_type pos = position - _first;
				size_type n = (pos > size()) ? pos : size();
				size_type count = last - first;
				
				this->clear();
				this->~vector();
				_alloc = tmp._alloc;
				_capacity = _getCapacity(n + count);
				_first = _alloc.allocate(_capacity);
				_last = _first;
				size_type i = 0;
				size_type j = 0;
				int insert = 0;
				while (j <= n)
				{
					if (j == pos && insert == 0)
					{
						while (count)
						{
							_alloc.construct(_last++, *first++);
							--count;
						}
						insert = 1;
					}
					else
						_alloc.construct(_last++, tmp._first[i++]);
					++j;
				}
			}

			iterator erase(iterator position)
			{
				if (position >= end())
					return (end());
				if ((position == end() - 1))
				{
					_alloc.destroy(--_last);
					return (end());
				}
				else
				{
					size_type size = this->size();
					size_type pos = position - _first;
					if (pos < 0 || pos > size)
						pos = 0;
					size_type i = 0;
					int found = 0;
					while (i < size - 1)
					{
						if (i == pos || found == 1)
						{
							_first[i] = _first[i + 1];
							found = 1;
						}
						else
							_first[i] = _first[i];
						i++;
					}
					_alloc.destroy(--_last);
					return (position);
				}
			}
			
			iterator erase(iterator first, iterator last)
			{
				if ((last - first) == 0)
					return (_last);
				else
				{
					size_type size = this->size();
					size_type start = first - _first;
					size_type end = last - _first;
					size_type range = end - start;
					size_type i = 0;
					int found = 0;
					while (i < (size - range))
					{
						if (i == start || found == 1)
						{
							_first[i] = _first[i + range];
							found = 1;
						}
						else
							_first[i] = _first[i];
						i++;
					}
					while (range--)
						_alloc.destroy(--_last);
					return (this->end() - 1);
				}
			}

			void swap (vector& x)
			{
				if (this == &x)
					return ;
					
				pointer			tmp_first;
				pointer			tmp_last;
				size_type		tmp_capacity;
				allocator_type	tmp_alloc;

				tmp_first = _first;
				tmp_last = _last;
				tmp_capacity = _capacity;
				tmp_alloc = _alloc;
				_first = x._first;
				_last = x._last;
				_capacity = x._capacity;
				_alloc = x._alloc;
				x._first = tmp_first;
				x._last = tmp_last;
				x._capacity = tmp_capacity;
				x._alloc = tmp_alloc;
			}

			void clear()
			{
				while (_first != _last)
					_alloc.destroy(--_last);
			}

			/* -------------------- Allocator -------------------- */ //DONE
			
			allocator_type get_allocator() const {return (_alloc);}
			
		protected:
			pointer			_first;
			pointer			_last;
			size_type		_capacity;
			allocator_type 	_alloc;
			
			size_type		_getCapacity(size_type n)
			{
				size_type i = 1;
				size_type max = _alloc.max_size();
				while (i < max)
				{
					if (i >= n)
						return i;
					i *= 2;
				}
				return (max);
			}
	};
}
#endif