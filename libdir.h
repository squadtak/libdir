/**
 * \file		libdir.h
 * \brief		snippets library for directory
 * \author		squad
 * \version		Ver 1.0
 * \date		2026-07-01
 * \copyright	Copyright 2026 squad
 * \license		This library is released under the MIT license.
 */

/**
 * @mainpage libdir
 * snippets library for directory
 *
 * \copyright	Copyright 2026 squad
 * \license		This library is released under the MIT license.
 *
 *
 * Headers
 * =======
 * including:
 * @code
 * #include "libdir.h"
 * @endcode
 *
 *
 * Functions
 * =========
 * \sa isDir() is directory?
 * \sa mkdir_rec() make directory recursively
 * \sa dcopy() copy directory
 */


#ifndef LIBDIR_H_INCLUDED
#define LIBDIR_H_INCLUDED

#include <stdio.h>

/**
 * \brief	is directory?
 *
 * \param 	[in]	*path	directory path
 *
 * \return	0				success
 * \return	-1				error
 */
int isDir(char *path);

/**
 * \brief	make directory recursively
 *
 * \param 	[in]	*path	directory path
 *
 * \return	0				success
 * \return	-1 to -3		error
 */
int mkdir_rec(char *path);

/**
 * \brief	copy directory
 *
 * \param 	[in]	*dst	destination directory path
 * \param 	[in]	*src	destination directory path
 *
 * \return	0				success
 * \return	-1 to -5		error
 */
int dcopy(char *dst, char *src);

#endif // LIBDIR_H_INCLUDED
