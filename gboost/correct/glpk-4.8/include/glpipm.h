/* glpipm.h (primal-dual interior-point method) */

/*----------------------------------------------------------------------
-- Copyright (C) 2000, 2001, 2002, 2003, 2004, 2005 Andrew Makhorin,
-- Department for Applied Informatics, Moscow Aviation Institute,
-- Moscow, Russia. All rights reserved. E-mail: <mao@mai2.rcnet.ru>.
--
-- This file is part of GLPK (GNU Linear Programming Kit).
--
-- GLPK is free software; you can redistribute it and/or modify it
-- under the terms of the GNU General Public License as published by
-- the Free Software Foundation; either version 2, or (at your option)
-- any later version.
--
-- GLPK is distributed in the hope that it will be useful, but WITHOUT
-- ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
-- or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
-- License for more details.
--
-- You should have received a copy of the GNU General Public License
-- along with GLPK; see the file COPYING. If not, write to the Free
-- Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
-- 02111-1307, USA.
----------------------------------------------------------------------*/

#ifndef _GLPIPM_H
#define _GLPIPM_H

#define ipm_main              glp_ipm_main

int ipm_main(int m, int n, int A_ptr[], int A_ind[], double A_val[],
      double b[], double c[], double x[], double y[], double z[]);
/* solve LP with primal-dual interior-point method */

#endif

/* eof */
