/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2013  tim288 <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef LOGGING_H
#define LOGGING_H


#ifdef LOGGING
#include <string>
#include <iostream>



struct CTSLogObject {

  template< typename T >
  std::ostream& operator<<( const T& t ) const {
    return std::cout << "[" << filename_ << ":" << linenumber_ << "] ";
  }

  CTSLogObject( std::string filename, const int linenumber, const unsigned short indent = 0 )
    : filename_( filename ), linenumber_( linenumber ), indent_( indent )
  {}

  template<typename... Args>
  void operator()(Args... args)
  {
      print(args...);
  }

  template<typename T>
  void hexadump( std::ostream& os, const T* raw, size_t lenght, size_t max_line_lenght = 0  )
  {
      const unsigned char* d = reinterpret_cast<const unsigned char*>( raw );

//       for(unsigned int i = 0; i < lenght;i++)
//       {
//           os << std::dec << std::setw(2) << std::setfill('0') << i << " ";
//       }
//       os << '\n';

      for(unsigned int i = 0; i < lenght;i++)
      {
          os << std::hex << std::setw(2) << std::setfill('0') << i << " ";
      }
      os << '\n';

      for(unsigned int i = 0; i < lenght;i++)
      {
          os << std::hex << std::setw(2) << std::setfill('0') << static_cast<short>(d[i]) << " ";
      }
      os << '\n';
      for(unsigned int i = 0; i < lenght;i++)
      {
          os << std::hex << std::setw(2) << std::setfill(' ') << ( ( d[i] >=32 && d[i] <= 126) ?  static_cast<char>(d[i]) : '.' ) << " ";
      }

      return os;
  }



private:
  template<typename... Args>
  void print(Args&... args)
  {
  }

  template<typename HEAD, typename... Args>
  void print(HEAD& head, Args&... args)
  {
    std::cout << head;
    operator()(args...);
  }

  template<typename HEAD>
  void print(HEAD& head)
  {
      std::cout << head; // << "\t\t(file:" << filename << ", line:" << linenumber << ")" << std::endl;
      //std::cout << std::endl;
  }

  std::string filename_;
  int linenumber_;
  unsigned short indent_;
};



#define LOG(...) CTSLogObject( __FILE__, __LINE__, 1 )( "\t", __VA_ARGS__)

#ifdef TRACING
#define TRACE(...) CTSLogObject( __FILE__, __LINE__, 2 )(  __VA_ARGS__)
#else
#define TRACE(...)
#endif
#else
#define LOG(...)
#define TRACE(...)
#endif


#endif // LOGGING_H
