/*
 This file is part of vedgTools/TemplateUtilities.
 Copyright (C) 2014 Igor Kushnir <igorkuo AT Google mail>

 vedgTools/TemplateUtilities is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 vedgTools/TemplateUtilities is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License along with
 vedgTools/TemplateUtilities.  If not, see <http://www.gnu.org/licenses/>.
*/

# ifndef TEMPLATE_UTILITIES_MISCELLANEOUS_HPP
# define TEMPLATE_UTILITIES_MISCELLANEOUS_HPP


namespace TemplateUtilities
{
inline int safeCtypeCast(unsigned char c) { return c; }

template<int (& F)(int)>
inline int safeCtype(unsigned char c) { return F(c); }
}

# endif // TEMPLATE_UTILITIES_MISCELLANEOUS_HPP
