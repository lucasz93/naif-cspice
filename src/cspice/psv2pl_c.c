/*

-Procedure psv2pl_c ( Point and spanning vectors to plane )

-Abstract
 
   Make a CSPICE plane from a point and two spanning vectors. 
 
-Disclaimer

   THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE
   CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S.
   GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE
   ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE
   PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS"
   TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY
   WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A
   PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC
   SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE
   SOFTWARE AND RELATED MATERIALS, HOWEVER USED.

   IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA
   BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT
   LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND,
   INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS,
   REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE
   REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY.

   RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF
   THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY
   CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE
   ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE.

-Required_Reading
 
   PLANES 
 
-Keywords
 
   GEOMETRY 
   MATH 
   PLANE 
 
*/

   #include "SpiceUsr.h"
   #undef    psv2pl_c


   void psv2pl_c ( void              * naif_state,
                   ConstSpiceDouble    point[3],
                   ConstSpiceDouble    span1[3],
                   ConstSpiceDouble    span2[3],
                   SpicePlane        * plane    ) 
/*

-Brief_I/O
 
   Variable  I/O  Description 
   --------  ---  -------------------------------------------------- 
   point, 
   span1, 
   span2      I   A point and two spanning vectors defining a plane. 
   plane      O   A CSPICE plane representing the plane. 
 
-Detailed_Input
 
   point, 
   span1, 
   span2          are, respectively, a point and two spanning vectors 
                  that define a geometric plane in three-dimensional 
                  space. The plane is the set of vectors 
 
                     point   +   s * span1   +   t * span2 
 
                  where s and t are real numbers.  The spanning 
                  vectors span1 and span2 must be linearly 
                  independent, but they need not be orthogonal or 
                  unitized. 
 
-Detailed_Output
 
   plane          is a CSPICE plane that represents the geometric 
                  plane defined by point, span1, and span2. 
 
-Parameters
 
   None. 
 
-Exceptions
 
   1)  If span1 and span2 are linearly dependent, then the vectors 
       point, span1, and span2 do not define a plane.  The error 
       SPICE(DEGENERATECASE) is signaled. 
 
-Files
 
   None. 
 
-Particulars
 
   CSPICE geometry routines that deal with planes use the `plane' 
   data type to represent input and output planes.  This data type 
   makes the subroutine interfaces simpler and more uniform. 
 
   The CSPICE routines that produce CSPICE planes from data that 
   define a plane are: 
 
      nvc2pl_c ( Normal vector and constant to plane ) 
      nvp2pl_c ( Normal vector and point to plane    ) 
      psv2pl_c ( Point and spanning vectors to plane ) 
 
   The CSPICE routines that convert CSPICE planes to data that 
   define a plane are: 
 
      pl2nvc_c ( Plane to normal vector and constant ) 
      pl2nvp_c ( Plane to normal vector and point    ) 
      pl2psv_c ( Plane to point and spanning vectors ) 
 
   Any of these last three routines may be used to convert this 
   routine's output, plane, to another representation of a 
   geometric plane. 
 
-Examples
 
   1)  Project a vector v orthogonally onto a plane defined by 
       point, span1, and span2.  proj is the projection we want; it 
       is the closest vector in the plane to v. 
 
          psv2pl_c ( point,  span1,   span2,  &plane ); 
          vprjp_c  ( v,      &plane,  proj           );
 
 
   2)  Find the plane determined by a spacecraft's position vector 
       relative to a central body and the spacecraft's velocity 
       vector.  We assume that all vectors are given in the same 
       coordinate system. 
 
          /.
          pos is the spacecraft's position, relative to 
          the central body.  vel is the spacecraft's velocity 
          vector.  pos is a point (vector, if you like) in 
          the orbit plane, and it is also one of the spanning 
          vectors of the plane. 
          ./
          psv2pl_c ( pos, pos, vel, &plane );
           
 
-Restrictions
 
   None. 
 
-Literature_References
 
   [1] `Calculus and Analytic Geometry', Thomas and Finney. 
 
-Author_and_Institution
 
   N.J. Bachman   (JPL) 
 
-Version
 
   -CSPICE Version 1.0.0, 05-MAR-1999 (NJB)

-Index_Entries
 
   point and spanning vectors to plane 
 
-&
*/

{ /* Begin psv2pl_c */



   /*
   This routine checks in only if an error is discovered.
   */

   if ( return_c(naif_state) ) 
   {
      return;
   }

   /*
   Find the unitized cross product of SPAN1 and SPAN2; this is our
   unit normal vector, or possibly its inverse.
   */
   ucrss_c (  naif_state, span1,  span2,  plane->normal  );

   if (  vzero_c ( naif_state, plane->normal )  )
   {
      chkin_c  ( naif_state, "psv2pl_c"                       );
      setmsg_c ( naif_state, "Spanning vectors are parallel." );
      sigerr_c ( naif_state, "SPICE(DEGENERATECASE)"          );
      chkout_c ( naif_state, "psv2pl_c"                       );
      return;
   }
 
 
   /*
   Find the plane constant corresponding to the unit normal
   vector we've found.
   */
   plane->constant  =  vdot_c ( naif_state, plane->normal, point );
 
 
   /*
   The constant should be the distance of the plane from the
   origin.  If the constant is negative, negate both it and the
   normal vector.
   */
      
   if ( plane->constant  <  0. ) 
   {
      plane->constant  =   - (plane->constant);
      
      vminus_c ( naif_state, plane->normal, plane->normal );
   }


} /* End psv2pl_c */

