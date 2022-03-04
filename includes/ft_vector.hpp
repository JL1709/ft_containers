/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jludt <jludt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:25:51 by julian            #+#    #+#             */
/*   Updated: 2022/03/04 14:54:57 by jludt            ###   ########.fr       */
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
			/* -------------------- MEMBER FUNCTIONS -------------------- */

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
				size_type n = 0;
				for (InputIterator it = first; it != last && n <= this->max_size(); ++it)
					n++;
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

			/* -------------------- Iterators -------------------- */

			iterator				begin() {return iterator(_first);}
			iterator				end() {return iterator(_last);}
			const_iterator			begin() const {return const_iterator(_first);}
			const_iterator			end() const {return const_iterator(_last);}
			reverse_iterator		rbegin() {return reverse_iterator(iterator(_last));}
			reverse_iterator		rend() {return reverse_iterator(_first);}
			const_reverse_iterator	rbegin() const {return _last;}
			const_reverse_iterator	rend() const {return _first;}

			/* -------------------- Capacity -------------------- */
		
			size_type size() const {return (_last - _first);}
			size_type max_size() const {return _alloc.max_size();}
			
			void resize(size_type n, value_type val = value_type())
			{
				if (n > max_size())
					throw std::out_of_range("ft::vector");
				else if (n < size())
				{
					size_type stop = size() - n;
					for (size_type i = 0; i < stop; ++i)
						_alloc.destroy(--_last);
				}
				else if (n > size())
				{
					size_type stop = n - size();
					for (size_type i = 0; i < stop; ++i)
						push_back(val);
				}
			}

			size_type capacity() const {return (_capacity);}
			bool empty() const {return (_first == _last);}
			
			void reserve (size_type n)
			{
				if (n > max_size())
					throw std::length_error("ft::vector");
				else if (n > _capacity)
				{
					ft::vector<T> tmp(*this);
					size_type sizeVector = this->size();
					this->clear();
					this->~vector();
					_alloc = tmp._alloc;
					_capacity = n;
					_first = _alloc.allocate(_capacity);
					_last = _first;
					for (size_type i = 0; i < sizeVector; i++)
						_alloc.construct(_last++, tmp._first[i]);
				}
			}

			/* -------------------- Element access -------------------- */

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

			/* -------------------- Modifiers -------------------- */
			
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
				size_type n = 0;
				for (InputIterator it = first; it != last && n <= this->max_size(); ++it)
					n++;
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
				size_type pos = 0;
				for (iterator it = _first; it != position; ++it)
					pos++;
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
				size_type pos = 0;
				for (iterator it = _first; it != position; ++it)
					pos++;
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
				size_type pos = 0;
				for (iterator it = _first; it != position; ++it)
					pos++;
				size_type n = (pos > size()) ? pos : size();
				size_type count = 0;
				for (InputIterator it = first; it != last && count <= this->max_size(); ++it)
					count++;
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
					size_type pos = 0;
					for (iterator it = _first; it != position; ++it)
						pos++;
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
					size_type start = 0;
					for (iterator it = _first; it != first; ++it)
						start++;
					size_type end = 0;
					for (iterator it = _first; it != last; ++it)
						end++;
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

			void swap(vector& x)
			{
				if (this == &x)
					return ;
				ft::swap(_first, x._first);
				ft::swap(_last, x._last);
				ft::swap(_capacity, x._capacity);
				ft::swap(_alloc, x._alloc);
			}

			void clear()
			{
				while (_first != _last)
					_alloc.destroy(--_last);
			}

			/* -------------------- Allocator -------------------- */
			
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

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
