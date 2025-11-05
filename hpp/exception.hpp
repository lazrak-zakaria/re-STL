#ifndef FT__EXCEPTION_HPP
#define FT__EXCEPTION_HPP
namespace ft
{
	class exception
	{
	public:
		exception() throw()
		{
		}

		exception(const exception &oth) throw()
		{
			*this = oth;
		}

		virtual ~exception() {};

		exception &operator=(const exception &) throw()
		{
			return *this;
		};

		virtual const char *what() const throw()
		{
			return "ft::except";
		}
	};
}
#endif
