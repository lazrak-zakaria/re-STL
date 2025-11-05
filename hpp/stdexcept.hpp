#ifndef FT__STDEXCEPT_HPP
# define FT__STDEXCEPT_HPP
# include "exception.hpp"
#include <string>
namespace ft {
	class logic_error : public exception {
	private:
		std::string str;

	public:
		logic_error( const std::string& what_arg ) : str(what_arg) {}
		logic_error( const char* what_arg ) : str(what_arg) {}
		logic_error( const logic_error& oth ) : ft::exception(), str(oth.str) {
		}
		virtual ~logic_error()
		{
		}
		logic_error& operator=( const logic_error& oth )
		{
			if (&oth == this) return *this;
			str = oth.str;
			return *this;
		}
		virtual const char *what() const throw() {
			return str.c_str();
		}
	};

	class out_of_range : public logic_error {
	public:
		out_of_range( const std::string& what_arg ) : logic_error(what_arg) {}
		out_of_range( const char* what_arg ) : logic_error(what_arg) {}
		out_of_range( const out_of_range& other ) : logic_error(other) {}
	};
}
#endif