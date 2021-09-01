/* zzdskbsr.f -- translated by f2c (version 19991025).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "__cspice_state.h"


extern zzdskbsr_init_t __zzdskbsr_init;
static zzdskbsr_state_t* get_zzdskbsr_state(cspice_t* state) {
	if (!state->zzdskbsr)
		state->zzdskbsr = __cspice_allocate_module(sizeof(
	zzdskbsr_state_t), &__zzdskbsr_init, sizeof(__zzdskbsr_init));
	return state->zzdskbsr;

}

/* $Procedure      ZZDSKBSR ( DSK, buffer segments for readers ) */
/* Subroutine */ int zzdskbsr_0_(cspice_t* __global_state, int n__, char *
	fname, integer *bodyid, integer *handle, L_fp cmpfun, integer *usrctr,
	 logical *update, integer *dladsc, doublereal *dskdsc, logical *found,
	 ftnlen fname_len)
{
    /* Initialized data */


    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    /* Subroutine */ int s_copy(f2c_state_t*, char *, char *, ftnlen, ftnlen);
    integer s_rnge(f2c_state_t*, char *, integer, char *, integer), s_cmp(
	    f2c_state_t*, char *, char *, ftnlen, ftnlen), i_dnnt(f2c_state_t*
	    , doublereal *);

    /* Local variables */
    integer head;
    integer node;
    integer tail;
    integer cost;
    extern /* Subroutine */ int zzctrchk_(cspice_t*, integer *, integer *, 
	    logical *);
    extern /* Subroutine */ int zzctrinc_(cspice_t*, integer *);
    extern /* Subroutine */ int zzctrsin_(cspice_t*, integer *);
    integer i__;
    integer j;
    integer cheap;
    integer p;
    extern /* Subroutine */ int chkin_(cspice_t*, char *, ftnlen);
    extern /* Subroutine */ int dskgd_(cspice_t*, integer *, integer *, 
	    doublereal *);
    char doing[40];
    extern /* Subroutine */ int lnkan_(cspice_t*, integer *, integer *);
    char stack[40*2];
    extern /* Subroutine */ int moved_(cspice_t*, doublereal *, integer *, 
	    doublereal *);
    extern /* Subroutine */ int movei_(cspice_t*, integer *, integer *, 
	    integer *);
    extern logical failed_(cspice_t*);
    extern /* Subroutine */ int dlabbs_(cspice_t*, integer *, integer *, 
	    logical *);
    extern /* Subroutine */ int dlabfs_(cspice_t*, integer *, integer *, 
	    logical *);
    integer dlalds[8];
    extern /* Subroutine */ int dlafns_(cspice_t*, integer *, integer *, 
	    integer *, logical *);
    extern integer intmax_(cspice_t*);
    extern integer isrchi_(cspice_t*, integer *, integer *, integer *);
    extern integer lnknfn_(cspice_t*, integer *);
    extern integer lnknxt_(cspice_t*, integer *, integer *);
    extern integer lnkprv_(cspice_t*, integer *, integer *);
    extern logical return_(cspice_t*);
    char urgent[40];
    doublereal dsklds[24];
    integer dlanxt[8];
    integer dlaprv[8];
    integer minexp;
    integer nxtseg;
    integer prvnod;
    extern /* Subroutine */ int sigerr_(cspice_t*, char *, ftnlen);
    extern /* Subroutine */ int chkout_(cspice_t*, char *, ftnlen);
    extern /* Subroutine */ int lnkini_(cspice_t*, integer *, integer *);
    extern /* Subroutine */ int dasopr_(cspice_t*, char *, integer *, ftnlen);
    extern /* Subroutine */ int dascls_(cspice_t*, integer *);
    extern /* Subroutine */ int lnkfsl_(cspice_t*, integer *, integer *, 
	    integer *);
    extern /* Subroutine */ int setmsg_(cspice_t*, char *, ftnlen);
    extern /* Subroutine */ int errint_(cspice_t*, char *, integer *, ftnlen);
    extern /* Subroutine */ int dlafps_(cspice_t*, integer *, integer *, 
	    integer *, logical *);
    extern /* Subroutine */ int lnkilb_(cspice_t*, integer *, integer *, 
	    integer *);
    extern /* Subroutine */ int lnkila_(cspice_t*, integer *, integer *, 
	    integer *);
    integer new__;

    /* Module state */
    zzdskbsr_state_t* __state = get_zzdskbsr_state(__global_state);
/* $ Abstract */

/*     Load and unload DSK files for use by the readers. Buffer segments */
/*     for readers. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     DSK */
/*     DAS */

/* $ Keywords */

/*     TOPOGRAPHY */

/* $ Declarations */

/*     Include file dla.inc */

/*     This include file declares parameters for DLA format */
/*     version zero. */

/*        Version 3.0.1 17-OCT-2016 (NJB) */

/*           Corrected comment: VERIDX is now described as a DAS */
/*           integer address rather than a d.p. address. */

/*        Version 3.0.0 20-JUN-2006 (NJB) */

/*           Changed name of parameter DSCSIZ to DLADSZ. */

/*        Version 2.0.0 09-FEB-2005 (NJB) */

/*           Changed descriptor layout to make backward pointer */
/*           first element.  Updated DLA format version code to 1. */

/*           Added parameters for format version and number of bytes per */
/*           DAS comment record. */

/*        Version 1.0.0 28-JAN-2004 (NJB) */


/*     DAS integer address of DLA version code. */


/*     Linked list parameters */

/*     Logical arrays (aka "segments") in a DAS linked array (DLA) file */
/*     are organized as a doubly linked list.  Each logical array may */
/*     actually consist of character, double precision, and integer */
/*     components.  A component of a given data type occupies a */
/*     contiguous range of DAS addresses of that type.  Any or all */
/*     array components may be empty. */

/*     The segment descriptors in a SPICE DLA (DAS linked array) file */
/*     are connected by a doubly linked list.  Each node of the list is */
/*     represented by a pair of integers acting as forward and backward */
/*     pointers.  Each pointer pair occupies the first two integers of a */
/*     segment descriptor in DAS integer address space.  The DLA file */
/*     contains pointers to the first integers of both the first and */
/*     last segment descriptors. */

/*     At the DLA level of a file format implementation, there is */
/*     no knowledge of the data contents.  Hence segment descriptors */
/*     provide information only about file layout (in contrast with */
/*     the DAF system).  Metadata giving specifics of segment contents */
/*     are stored within the segments themselves in DLA-based file */
/*     formats. */


/*     Parameter declarations follow. */

/*     DAS integer addresses of first and last segment linked list */
/*     pointer pairs.  The contents of these pointers */
/*     are the DAS addresses of the first integers belonging */
/*     to the first and last link pairs, respectively. */

/*     The acronyms "LLB" and "LLE" denote "linked list begin" */
/*     and "linked list end" respectively. */


/*     Null pointer parameter. */


/*     Segment descriptor parameters */

/*     Each segment descriptor occupies a contiguous */
/*     range of DAS integer addresses. */

/*        The segment descriptor layout is: */

/*           +---------------+ */
/*           | BACKWARD PTR  | Linked list backward pointer */
/*           +---------------+ */
/*           | FORWARD PTR   | Linked list forward pointer */
/*           +---------------+ */
/*           | BASE INT ADDR | Base DAS integer address */
/*           +---------------+ */
/*           | INT COMP SIZE | Size of integer segment component */
/*           +---------------+ */
/*           | BASE DP ADDR  | Base DAS d.p. address */
/*           +---------------+ */
/*           | DP COMP SIZE  | Size of d.p. segment component */
/*           +---------------+ */
/*           | BASE CHR ADDR | Base DAS character address */
/*           +---------------+ */
/*           | CHR COMP SIZE | Size of character segment component */
/*           +---------------+ */

/*     Parameters defining offsets for segment descriptor elements */
/*     follow. */


/*     Descriptor size: */


/*     Other DLA parameters: */


/*     DLA format version.  (This number is expected to occur very */
/*     rarely at integer address VERIDX in uninitialized DLA files.) */


/*     Characters per DAS comment record. */


/*     End of include file dla.inc */


/*     Include file dskdsc.inc */

/*     This include file declares parameters for DSK segment descriptors. */

/* -       SPICELIB Version 1.0.0 08-FEB-2017 (NJB) */

/*           Updated version info. */

/*           22-JAN-2016 (NJB) */

/*              Added parameter for data class 2. Changed name of data */
/*              class 1 parameter. Corrected data class descriptions. */

/*           13-MAY-2010 (NJB) */

/*              Descriptor now contains two ID codes, one for the */
/*              surface, one for the associated ephemeris object. This */
/*              supports association of multiple surfaces with one */
/*              ephemeris object without creating file management */
/*              issues. */

/*              Room was added for coordinate system definition */
/*              parameters. */

/*               Flag arrays and model ID/component entries were deleted. */

/*            11-SEP-2008 (NJB) */


/*     DSK segment descriptors are implemented as an array of d.p. */
/*     numbers.  Note that each integer descriptor datum occupies one */
/*     d.p. value. */




/*     Segment descriptor parameters */

/*     Each segment descriptor occupies a contiguous */
/*     range of DAS d.p. addresses. */

/*        The DSK segment descriptor layout is: */

/*           +---------------------+ */
/*           | Surface ID code     | */
/*           +---------------------+ */
/*           | Center ID code      | */
/*           +---------------------+ */
/*           | Data class code     | */
/*           +---------------------+ */
/*           | Data type           | */
/*           +---------------------+ */
/*           | Ref frame code      | */
/*           +---------------------+ */
/*           | Coord sys code      | */
/*           +---------------------+ */
/*           | Coord sys parameters|  {10 elements} */
/*           +---------------------+ */
/*           | Min coord 1         | */
/*           +---------------------+ */
/*           | Max coord 1         | */
/*           +---------------------+ */
/*           | Min coord 2         | */
/*           +---------------------+ */
/*           | Max coord 2         | */
/*           +---------------------+ */
/*           | Min coord 3         | */
/*           +---------------------+ */
/*           | Max coord 3         | */
/*           +---------------------+ */
/*           | Start time          | */
/*           +---------------------+ */
/*           | Stop time           | */
/*           +---------------------+ */

/*     Parameters defining offsets for segment descriptor elements */
/*     follow. */


/*     Surface ID code: */


/*     Central ephemeris object NAIF ID: */


/*     Data class: */

/*     The "data class" is a code indicating the category of */
/*     data contained in the segment. */


/*     Data type: */


/*     Frame ID: */


/*     Coordinate system code: */


/*     Coordinate system parameter start index: */


/*     Number of coordinate system parameters: */


/*     Ranges for coordinate bounds: */


/*     Coverage time bounds: */


/*     Descriptor size (24): */


/*     Data class values: */

/*        Class 1 indicates a surface that can be represented as a */
/*                single-valued function of its domain coordinates. */

/*                An example is a surface defined by a function that */
/*                maps each planetodetic longitude and latitude pair to */
/*                a unique altitude. */


/*        Class 2 indicates a general surface. Surfaces that */
/*                have multiple points for a given pair of domain */
/*                coordinates---for example, multiple radii for a given */
/*                latitude and longitude---belong to class 2. */



/*     Coordinate system values: */

/*        The coordinate system code indicates the system to which the */
/*        tangential coordinate bounds belong. */

/*        Code 1 refers to the planetocentric latitudinal system. */

/*        In this system, the first tangential coordinate is longitude */
/*        and the second tangential coordinate is latitude. The third */
/*        coordinate is radius. */



/*        Code 2 refers to the cylindrical system. */

/*        In this system, the first tangential coordinate is radius and */
/*        the second tangential coordinate is longitude. The third, */
/*        orthogonal coordinate is Z. */



/*        Code 3 refers to the rectangular system. */

/*        In this system, the first tangential coordinate is X and */
/*        the second tangential coordinate is Y. The third, */
/*        orthogonal coordinate is Z. */



/*        Code 4 refers to the planetodetic/geodetic system. */

/*        In this system, the first tangential coordinate is longitude */
/*        and the second tangential coordinate is planetodetic */
/*        latitude. The third, orthogonal coordinate is altitude. */



/*     End of include file dskdsc.inc */

/* $ Abstract */

/*     This include file defines the dimension of the counter */
/*     array used by various SPICE subsystems to uniquely identify */
/*     changes in their states. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Parameters */

/*     CTRSIZ      is the dimension of the counter array used by */
/*                 various SPICE subsystems to uniquely identify */
/*                 changes in their states. */

/* $ Author_and_Institution */

/*     B.V. Semenov    (JPL) */

/* $ Literature_References */

/*     None. */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 29-JUL-2013 (BVS) */

/* -& */

/*     End of include file. */

/* $ Brief_I/O */

/*     Variable  I/O  Entry points */
/*     --------  ---  -------------------------------------------------- */
/*     FNAME      I   ZZDSKLSF */
/*     BODYID     I   ZZDSKBSS */
/*     HANDLE    I,O  ZZDSKLSF, ZZDSKUPF, ZZDSKSNS */
/*     USRCTR    I,O  ZZDSKCHK */
/*     UPDATE     O   ZZDSKCHK */
/*     DESCR      O   ZZDSKSNS */
/*     FOUND      O   ZZDSKSNS */

/* $ Detailed_Input */

/*     FNAME      is the name of a binary DSK file to be loaded. */

/*     HANDLE     on input is the handle of a binary DSK file to be */
/*                unloaded. */


/*     The purpose of entry points ZZDSKBSS and ZZDSKSNS is to search for */
/*     segments in DSK files matching certain criteria. */

/*     USRCTR     on input is the value of a DSK loaded kernel counter */
/*                maintained by a DSK routine or subsystem. */


/* $ Detailed_Output */

/*     HANDLE     on output is the handle of the DSK file */
/*                containing a located segment. */

/*     USRCTR     on output is the value of a DSK loaded kernel counter */
/*                maintained by the ZZDSKBSR subsystem. */

/*     UPDATE     is a logical flag indicating whether the state of */
/*                the loaded DSK set has changed since the ZZDSKBSR */
/*                state counter was equal to a given user counter. */

/*     DESCR      is the packed descriptor of a located segment. */

/*     FOUND      indicates whether a requested segment was found or not. */

/* $ Parameters */

/*     FTSIZE     is the maximum number of shape files that can */
/*                be loaded by ZZDSKLSF at any given time for use by the */
/*                readers. */

/*     BTSIZE     is the maximum number of bodies whose segments */
/*                are buffered by ZZDSKSNS. */

/*     STSIZE     is the maximum number of segments that can be buffered */
/*                at any given time by ZZDSKSNS. */

/* $ Exceptions */

/*     1) If ZZDSKBSR is called directly, the error SPICE(DSKBOGUSENTRY) */
/*        is signaled. */

/*     2) See entry points ZZDSKLSF, ZZDSKUPF, ZZDSKBSS, and ZZDSKSNS */
/*        for exceptions specific to them. */

/* $ Files */

/*     DSK shape files are indicated by filename before loading */
/*     (see ZZDSKLSF) and handle after loading (all other places). */

/* $ Particulars */

/*     ZZDSKBSR serves as an umbrella, allowing data to be shared by its */
/*     entry points: */

/*        ZZDSKLSF       Load shape file. */
/*        ZZDSKUPF       Unload shape file. */
/*        ZZDSKBSS       Begin search for segment. */
/*        ZZDSKSNS       Select next segment. */
/*        ZZDSKCHK       Check for change in loaded kernel set. */

/*     Before a file can be read by the DSK readers, it must be */
/*     loaded by ZZDSKLSF, which among other things load the file into */
/*     the DAS subsystem. */

/*     Up to FTSIZE files may be loaded for use simultaneously, and a */
/*     file only has to be loaded once to become a potential search */
/*     target for any number of subsequent reads. */

/*     Once a DSK has been loaded, it is assigned a file */
/*     handle, which is used to keep track of the file internally, and */
/*     which is used by the calling program to refer to the file in all */
/*     subsequent calls to DSK routines. */

/*     A file may be removed from the list of files for potential */
/*     searching by unloading it via a call to ZZDSKUPF. */

/*     ZZDSKBSS and ZZDSKSNS are used together to search through loaded */
/*     files for segments. */

/*     ZZDSKBSS sets up the search. */

/*     ZZDSKSNS finds segments matching the search criteria set up by */
/*     ZZDSKBSS. Last-loaded files get searched first, and individual */
/*     files are searched backwards. */

/*     When an applicable segment is found, ZZDSKSNS returns that */
/*     segment's descriptor and identifier, along with the handle of the */
/*     file containing the segment. */

/*     Subsequent calls to ZZDSKSNS continue the search, picking up */
/*     where the previous call to this routine left off. */

/*     ZZDSKSNS uses information on loaded files to manage a buffer of */
/*     saved segment descriptors and identifiers. The buffer is used to */
/*     speed up access time by minimizing file reads. */

/* $ Examples */

/*     None. */

/* $ Restrictions */

/*     1) If Fortran I/O errors occur while searching a loaded DSK */
/*        file, the internal state of this suite of routines may */
/*        be corrupted.  It may be possible to correct the state */
/*        by unloading the pertinent DSK files and then re-loading */
/*        them. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     R.E. Thurman   (JPL) */
/*     I.M. Underwood (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 08-FEB-2017 (NJB) */

/*        Updated version info. */

/*        31-MAR-2016 (NJB) */

/*           Deleted unused variable references. */
/*           Added header for ZZDSKCHK. */

/*           Cleaned up in-line comments. */

/*        19-SEP-2014 (NJB) */

/*           Specification change: now treats the target body as the */
/*           primary search key. Segments lists are associated with */
/*           bodies rather than surfaces. */

/*           The input argument SURFID has been replaced with BODYID. */

/*           A counter system has been implemented to enable SPICE */
/*           routines to detect changes in the state of the loaded */
/*           kernel set. The user interface entry point for checking for */
/*           state updates in ZZDSKCHK. */

/*        21-MAY-2013 (NJB) */

/*           Removed debugging WRITE statement from entry point */
/*           ZZDSKSNS. Edited headers to remove long lines. */

/*        02-APR-2010 (NJB) (RET) (IMU) */

/*           Original version. */

/* -& */
/* $ Index_Entries */

/*     buffer dsk segments for readers */

/* -& */
/* $ Revisions */

/*     None. */

/* -& */

/*     SPICELIB functions */


/*     Local parameters */

/*     Constants used in the doubly linked list structure: */


/*     Local variables */


/*     DSK loaded kernel set state change counter: */


/*     The file table contains the handle and file number of each file */
/*     that has been loaded for use with the DSK readers. File */
/*     numbers begin at one, and are incremented until they reach a */
/*     value of INTMAX() - 1, at which point they are mapped to the */
/*     range 1:NFT, where NFT is the number of loaded DSK files. */

/*     A file number is similar to a file handle, but it is assigned */
/*     and used exclusively by this module. The purpose of file numbers */
/*     is to keep track of the order in which files are loaded and the */
/*     order in which they are searched. */

/*     All names begin with FT. */

/*        HAN      Handle */
/*        NUM      File number */

/*     NFT is the number of currently loaded DSK files. NEXT is */
/*     incremented whenever a new file is loaded to give the file */
/*     number for that file. FINDEX is the index of whatever file is */
/*     of current interest. */

/*     New files are added at the end of the table. As files are */
/*     removed, succeeding files are moved forward to take up the */
/*     slack. This keeps the table ordered by file number. */


/*     The body table contains the beginning of the list of the */
/*     stored segments for each body and the */
/*     expense at which that list was constructed. (The expense of an */
/*     body list is the number of segment descriptors examined */
/*     during the construction of the list.) It also contains the */
/*     highest and lowest file numbers searched during the construction */
/*     of the list. */

/*     All names begin with BT. */

/*        INS      Body number */
/*        EXP      Expense */
/*        HFS      Highest file (number) searched */
/*        LFS      Lowest  file (number) searched */
/*        BEG      Beginning of segment list */

/*     NIT is the number of bodies for which segments are currently */
/*     being stored in the table. BINDEX is the index of whatever */
/*     body is of current interest at any given time. */

/*     New bodies are added at the end of the table. As bodies */
/*     are removed, the last body is moved forward to take up the */
/*     slack. This keeps the entries in the table contiguous. */


/*     The segment table contains the handle, descriptor, and identifier */
/*     for each segment that has been found so far. */

/*     The segment table is implemented as a set of arrays indexed by */
/*     a SPICE doubly linked list structure.  For each body */
/*     in the body table, there is a segment table list; each */
/*     node of a list points to data associated with a segment.  In */
/*     each list, the head node corresponds to the highest-priority */
/*     segment in that list, and segment priority decreases in the */
/*     forward direction. */

/*     All names begin with ST. */

/*        DLAD     DLA segment descriptor */
/*        DSKD     DSK segment descriptor */
/*        HAN      Handle */
/*        POOL     Doubly linked list pool. */

/*     New segments are added to the front or end of an body list */
/*     as appropriate, according to the rules spelled out under */
/*     entry point ZZDSKSNS. */


/*     Other local variables */


/*     Saved variables */


/*     Initial values */

    /* Parameter adjustments */
    if (usrctr) {
	}
    if (dladsc) {
	}
    if (dskdsc) {
	}

    /* Function Body */
    switch(n__) {
	case 1: goto L_zzdsklsf;
	case 2: goto L_zzdskusf;
	case 3: goto L_zzdskbss;
	case 4: goto L_zzdsksns;
	case 5: goto L_zzdskchk;
	}


/*     Nobody has any business calling ZZDSKBSR directly. */

    if (return_(__global_state)) {
	return 0;
    }
    chkin_(__global_state, "ZZDSKBSR", (ftnlen)8);
    sigerr_(__global_state, "SPICE(DSKBOGUSENTRY)", (ftnlen)20);
    chkout_(__global_state, "ZZDSKBSR", (ftnlen)8);
    return 0;
/* $Procedure ZZDSKLSF ( DSK, load shape file ) */

L_zzdsklsf:
/* $ Abstract */

/*     Load a DSK shape file for use by the DSK readers.  Return that */
/*     file's handle, to be used by other DSK routines to refer to the */
/*     file. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     DSK */
/*     DAS */

/* $ Keywords */

/*     TOPOGRAPHY */

/* $ Declarations */

/*     CHARACTER*(*)         FNAME */
/*     INTEGER               HANDLE */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     FNAME      I   Name of the DSK file to be loaded. */
/*     HANDLE     O   Loaded file's handle. */
/*     FTSIZE     P   Maximum number of loaded DSK files. */

/* $ Detailed_Input */

/*     FNAME      is the name of a DSK file to be loaded. */

/* $ Detailed_Output */

/*     HANDLE     is an integer handle assigned to the file upon loading. */
/*                Almost every other DSK routine will subsequently use */
/*                this number to refer to the file. */

/* $ Parameters */

/*     FTSIZE     is the maximum number of DSK files that may */
/*                be loaded simultaneously under any circumstances. */
/*                FTSIZE is currently set to match the maximum number */
/*                of DAS files that may be loaded simultaneously. */

/* $ Exceptions */

/*     1) If an attempt is made to open more DAS files than is specified */
/*        by the parameter FTSIZE in DASAH, an error is signaled by a */
/*        routine in the call tree of this routine. */

/*     2) If an attempt is made to load more files than is specified */
/*        by the local parameter FTSIZE, and if the DAS system has */
/*        room to load another file, the error SPICE(DSKTOOMANYFILES) */
/*        signaled. The current setting of FTSIZE does not allow this */
/*        situation to arise:  the DAS system will trap the error */
/*        before this routine has the chance. */

/*     3) If the file specified by FNAME can not be opened, an error */
/*        is signaled by a routine that this routine calls. */

/*     4) If the file specified by FNAME has already been loaded, */
/*        it will become the "last-loaded" file.  The readers */
/*        search the last-loaded file first. */

/* $ Files */

/*     The DSK file specified by FNAME is loaded. The file is assigned */
/*     an integer handle by ZZDSKLSF. Other DSK routines will refer to */
/*     this file by its handle. */

/* $ Particulars */

/*     See Particulars above, in ZZDSKBSR. */

/*     If there is room for a new file, ZZDSKLSF opens the file for */
/*     reading. */

/*     DSK readers search files loaded with ZZDSKLSF in the reverse order */
/*     in which they were loaded.  That is, last-loaded files are */
/*     searched first. */

/* $ Examples */

/*     See the Example above, in ZZDSKBSR. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     R.E. Thurman   (JPL) */
/*     I.M. Underwood (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 08-FEB-2017 (NJB) */

/*        Updated version info. */

/*        19-SEP-2014 (NJB) */

/*           Specification change: now treats the target body as the */
/*           primary search key. Segments lists are associated with */
/*           bodies rather than surfaces. */

/*           Now initializes the DSK state change counter on the first */
/*           pass and updates it on every subsequent call. */
/*       21-MAY-2013 (NJB) */

/*           Edited headers to remove long lines. */

/*       02-APR-2010 (NJB) (RET) (IMU) */

/* -& */
/* $ Index_Entries */

/*     load dsk shape file */

/* -& */
/* $ Revisions */

/*     None. */
/* -& */

/*     Standard SPICE error handling. */

    if (return_(__global_state)) {
	return 0;
    }
    chkin_(__global_state, "ZZDSKLSF", (ftnlen)8);
    if (__state->pass1) {

/*        Initialize the BSR counter. */

	zzctrsin_(__global_state, __state->dskctr);
	__state->pass1 = FALSE_;
    }

/*     Increment the BSR counter regardless of whether */
/*     the load operation is successful. */

    zzctrinc_(__global_state, __state->dskctr);

/*     Don't allow a search to continue after loading a file; a new */
/*     search should be re-started. */

    s_copy(&__global_state->f2c, __state->status, "BOGUS ENTRY", (ftnlen)40, (
	    ftnlen)11);

/*     Nothing works unless at least one file has been loaded, so */
/*     this is as good a place as any to initialize the free list */
/*     whenever the body table is empty. */

    if (__state->nbt == 0) {
	lnkini_(__global_state, &__state->c__10000, __state->stpool);
    }

/*     To load a new file, first try to open it for reading. */

    dasopr_(__global_state, fname, handle, fname_len);
    if (failed_(__global_state)) {
	chkout_(__global_state, "ZZDSKLSF", (ftnlen)8);
	return 0;
    }

/*     Determine if the file is already in the table. */

    __state->findex = isrchi_(__global_state, handle, &__state->nft, 
	    __state->fthan);
    if (__state->findex > 0) {

/*        The last call we made to DASOPR added another DAS link to */
/*        the DSK file.  Remove this link. */

	dascls_(__global_state, handle);

/*        Handle is already in the table.  Remove it. */

	--__state->nft;
	i__1 = __state->nft;
	for (i__ = __state->findex; i__ <= i__1; ++i__) {
	    __state->fthan[(i__2 = i__ - 1) < 5000 && 0 <= i__2 ? i__2 : 
		    s_rnge(&__global_state->f2c, "fthan", i__2, "zzdskbsr_", (
		    ftnlen)720)] = __state->fthan[(i__3 = i__) < 5000 && 0 <= 
		    i__3 ? i__3 : s_rnge(&__global_state->f2c, "fthan", i__3, 
		    "zzdskbsr_", (ftnlen)720)];
	    __state->ftnum[(i__2 = i__ - 1) < 5000 && 0 <= i__2 ? i__2 : 
		    s_rnge(&__global_state->f2c, "ftnum", i__2, "zzdskbsr_", (
		    ftnlen)721)] = __state->ftnum[(i__3 = i__) < 5000 && 0 <= 
		    i__3 ? i__3 : s_rnge(&__global_state->f2c, "ftnum", i__3, 
		    "zzdskbsr_", (ftnlen)721)];
	}

/*        Unlink any segments that came from this file. */

	i__ = 1;
	while(i__ <= __state->nbt) {
	    p = __state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbsr_", (
		    ftnlen)731)];
	    while(p > 0) {

/*              Find the successor of P, if any. */

		nxtseg = lnknxt_(__global_state, &p, __state->stpool);
		if (__state->sthan[(i__1 = p - 1) < 10000 && 0 <= i__1 ? i__1 
			: s_rnge(&__global_state->f2c, "sthan", i__1, "zzdsk"
			"bsr_", (ftnlen)739)] == *handle) {

/*                 The segment corresponding to node P came from */
/*                 the file we're unloading.  Delete the node for */
/*                 P from the segment list for body I; if P happens */
/*                 to be the head node for body I's segment list, */
/*                 make the successor of P the head of the list. */

		    lnkfsl_(__global_state, &p, &p, __state->stpool);
		    if (p == __state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= 
			    i__1 ? i__1 : s_rnge(&__global_state->f2c, "btbeg"
			    , i__1, "zzdskbsr_", (ftnlen)749)]) {
			__state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? 
				i__1 : s_rnge(&__global_state->f2c, "btbeg", 
				i__1, "zzdskbsr_", (ftnlen)750)] = nxtseg;
		    }
		}

/*              Update P. */

		p = nxtseg;
	    }

/*           If the list for this body is now empty, shorten the */
/*           current table by one: put all the entries for the last */
/*           body in the table into the space occupied by the */
/*           one we've deleted. */

	    if (__state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbsr_", (
		    ftnlen)767)] <= 0) {
		__state->btbod[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btbod", i__1, "zzdskbs"
			"r_", (ftnlen)769)] = __state->btbod[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btbod", i__2, "zzdskbsr_", (
			ftnlen)769)];
		__state->btexp[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btexp", i__1, "zzdskbs"
			"r_", (ftnlen)770)] = __state->btexp[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btexp", i__2, "zzdskbsr_", (
			ftnlen)770)];
		__state->bthfs[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "bthfs", i__1, "zzdskbs"
			"r_", (ftnlen)771)] = __state->bthfs[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "bthfs", i__2, "zzdskbsr_", (
			ftnlen)771)];
		__state->btlfs[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btlfs", i__1, "zzdskbs"
			"r_", (ftnlen)772)] = __state->btlfs[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btlfs", i__2, "zzdskbsr_", (
			ftnlen)772)];
		__state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbs"
			"r_", (ftnlen)773)] = __state->btbeg[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btbeg", i__2, "zzdskbsr_", (
			ftnlen)773)];
		--__state->nbt;
	    } else {
		++i__;
	    }
	}
    } else {

/*        This is a new file.  Make sure that there are unused slots */
/*        in the file table. */

	if (__state->nft == 5000) {
	    dascls_(__global_state, handle);
	    setmsg_(__global_state, "Number of files loaded is at a maximum,"
		    " as specified by the parameter FTSIZE, the value of whic"
		    "h is #. You will need to load fewer files. Consider unlo"
		    "ading any files that are not needed.", (ftnlen)187);
	    errint_(__global_state, "#", &__state->c__5000, (ftnlen)1);
	    sigerr_(__global_state, "SPICE(DSKTOOMANYFILES)", (ftnlen)22);
	    chkout_(__global_state, "ZZDSKLSF", (ftnlen)8);
	    return 0;
	}
    }

/*     Determine the next file number. */

/*     Programmer's note: this section is normally not reached. */
/*     It should be tested by temporarily setting the comparison */
/*     value to a smaller number, for example 2*FTSIZE. */

    if (__state->next < intmax_(__global_state) - 1) {
	++__state->next;
    } else {

/*        The user is to be congratulated:  we've run out of file */
/*        numbers. */

/*        Re-set the valid file numbers so they lie in the range 1:NFT, */
/*        with the Ith file in the file table having file number I. */
/*        First update the LFS and HFS components of the body table */
/*        according to this mapping. */

/*        Set any body table entries that are lower than FTNUM(1) */
/*        to zero. */

	i__1 = __state->nbt;
	for (i__ = 1; i__ <= i__1; ++i__) {

/*           Re-map the HFS table for the Ith body. */

	    j = isrchi_(__global_state, &__state->bthfs[(i__2 = i__ - 1) < 
		    100 && 0 <= i__2 ? i__2 : s_rnge(&__global_state->f2c, 
		    "bthfs", i__2, "zzdskbsr_", (ftnlen)836)], &__state->nft, 
		    __state->ftnum);

/*           Either the highest file searched for body I is the Jth */
/*           file in the file table, or the file is not in the table. */
/*           In both cases, J is the correct value to assign to */
/*           BTHFS(I). */

	    __state->bthfs[(i__2 = i__ - 1) < 100 && 0 <= i__2 ? i__2 : 
		    s_rnge(&__global_state->f2c, "bthfs", i__2, "zzdskbsr_", (
		    ftnlen)844)] = j;

/*           When the highest file searched for body I is not in the */
/*           file table, the highest file searched has been unloaded. */
/*           Note that this assignment makes all files appear to be */
/*           "new" when a lookup for body I is performed. */

/*           Re-map the LFS table for the Ith body. */

	    j = isrchi_(__global_state, &__state->btlfs[(i__2 = i__ - 1) < 
		    100 && 0 <= i__2 ? i__2 : s_rnge(&__global_state->f2c, 
		    "btlfs", i__2, "zzdskbsr_", (ftnlen)854)], &__state->nft, 
		    __state->ftnum);
	    if (j > 0) {

/*              The lowest file searched for body I is the Jth file */
/*              in the file table. */

		__state->btlfs[(i__2 = i__ - 1) < 100 && 0 <= i__2 ? i__2 : 
			s_rnge(&__global_state->f2c, "btlfs", i__2, "zzdskbs"
			"r_", (ftnlen)861)] = j;
	    } else {

/*              The lowest file searched for body I is not in the */
/*              file table.  This occurs when the lowest file searched */
/*              has been unloaded.  Zero out both the lowest and */
/*              highest file searched to force reconstruction of the */
/*              list. */

		__state->btlfs[(i__2 = i__ - 1) < 100 && 0 <= i__2 ? i__2 : 
			s_rnge(&__global_state->f2c, "btlfs", i__2, "zzdskbs"
			"r_", (ftnlen)871)] = 0;
		__state->bthfs[(i__2 = i__ - 1) < 100 && 0 <= i__2 ? i__2 : 
			s_rnge(&__global_state->f2c, "bthfs", i__2, "zzdskbs"
			"r_", (ftnlen)872)] = 0;
	    }
	}

/*        Re-map the file number table itself. */

	i__1 = __state->nft;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    __state->ftnum[(i__2 = i__ - 1) < 5000 && 0 <= i__2 ? i__2 : 
		    s_rnge(&__global_state->f2c, "ftnum", i__2, "zzdskbsr_", (
		    ftnlen)883)] = i__;
	}

/*        Assign a new file number. */

	__state->next = __state->nft + 1;
    }

/*     Now add this file to file table. */

    ++__state->nft;
    __state->fthan[(i__1 = __state->nft - 1) < 5000 && 0 <= i__1 ? i__1 : 
	    s_rnge(&__global_state->f2c, "fthan", i__1, "zzdskbsr_", (ftnlen)
	    898)] = *handle;
    __state->ftnum[(i__1 = __state->nft - 1) < 5000 && 0 <= i__1 ? i__1 : 
	    s_rnge(&__global_state->f2c, "ftnum", i__1, "zzdskbsr_", (ftnlen)
	    899)] = __state->next;
    chkout_(__global_state, "ZZDSKLSF", (ftnlen)8);
    return 0;
/* $Procedure ZZDSKUSF ( DSK, Unload shape file ) */

L_zzdskusf:
/* $ Abstract */

/*     Unload a DSK shape file so that it will no longer be searched */
/*     by the readers. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     DSK */
/*     DAS */

/* $ Keywords */

/*     TOPOGRAPHY */

/* $ Declarations */

/*     INTEGER               HANDLE */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     HANDLE     I   Handle of DSK file to be unloaded */

/* $ Detailed_Input */

/*     HANDLE     Integer handle assigned to the file upon loading. */

/* $ Detailed_Output */

/*     None. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1) Unloading a file that has not been loaded is a no-op. */
/*        No error is signaled. */

/* $ Files */

/*     The file referred to by HANDLE is unloaded. */

/* $ Particulars */

/*     See Particulars section above, in ZZDSKBSR. */

/*     Unloading a file with ZZDSKUSF removes that file from */
/*     consideration by the DSK readers. In doing so, it frees up space */
/*     for another file to be loaded. */

/* $ Examples */

/*     See the Example above, in ZZDSKBSR. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     R.E. Thurman   (JPL) */
/*     I.M. Underwood (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 08-FEB-2017 (NJB) */

/*        Updated version info. */

/*        19-SEP-2014 (NJB) */

/*           Specification change: now treats the target body as the */
/*           primary search key. Segments lists are associated with */
/*           bodies rather than surfaces. */

/*           Now initializes the DSK state change counter on the first */
/*           pass and updates it on every subsequent call. */
/*        21-MAY-2013 (NJB) */

/*           Edited headers to remove long lines. */
/*           Removed debugging output. */

/*        02-APR-2010 (NJB) (RET) (IMU) */

/* -& */
/* $ Index_Entries */

/*     unload ck shape file */

/* -& */
/* $ Revisions */

/*     None. */

/* -& */
    if (return_(__global_state)) {
	return 0;
    }
    chkin_(__global_state, "ZZDSKUSF", (ftnlen)8);
    if (__state->pass1) {

/*        Initialize the BSR counter. */

	zzctrsin_(__global_state, __state->dskctr);
	__state->pass1 = FALSE_;
    }

/*     Increment the BSR counter regardless of whether */
/*     the load operation is successful. */

    zzctrinc_(__global_state, __state->dskctr);

/*     Don't allow a search to continue after unloading a file; a new */
/*     search should be re-started. */

    s_copy(&__global_state->f2c, __state->status, "BOGUS ENTRY", (ftnlen)40, (
	    ftnlen)11);

/*     All of the stored segments from the file must be removed */
/*     from the segment table (by returning the corresponding nodes */
/*     to the segment table pool.) */

/*     Don't do anything if the given handle is not in the file table. */

    __state->findex = isrchi_(__global_state, handle, &__state->nft, 
	    __state->fthan);
    if (__state->findex == 0) {
	chkout_(__global_state, "ZZDSKUSF", (ftnlen)8);
	return 0;
    }


/*     First get rid of the entry in the file table. Close the file */
/*     before wiping out the handle. */

    dascls_(__global_state, &__state->fthan[(i__1 = __state->findex - 1) < 
	    5000 && 0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c, "fthan", 
	    i__1, "zzdskbsr_", (ftnlen)1091)]);
    --__state->nft;
    i__1 = __state->nft;
    for (i__ = __state->findex; i__ <= i__1; ++i__) {
	__state->fthan[(i__2 = i__ - 1) < 5000 && 0 <= i__2 ? i__2 : s_rnge(&
		__global_state->f2c, "fthan", i__2, "zzdskbsr_", (ftnlen)1097)
		] = __state->fthan[(i__3 = i__) < 5000 && 0 <= i__3 ? i__3 : 
		s_rnge(&__global_state->f2c, "fthan", i__3, "zzdskbsr_", (
		ftnlen)1097)];
	__state->ftnum[(i__2 = i__ - 1) < 5000 && 0 <= i__2 ? i__2 : s_rnge(&
		__global_state->f2c, "ftnum", i__2, "zzdskbsr_", (ftnlen)1098)
		] = __state->ftnum[(i__3 = i__) < 5000 && 0 <= i__3 ? i__3 : 
		s_rnge(&__global_state->f2c, "ftnum", i__3, "zzdskbsr_", (
		ftnlen)1098)];
    }

/*     Check each body list individually. Note that the first */
/*     node on each list, having no predecessor, must be handled */
/*     specially. */

    i__ = 1;
    while(i__ <= __state->nbt) {
	p = __state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
		s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbsr_", (
		ftnlen)1110)];
	while(p > 0) {
	    nxtseg = lnknxt_(__global_state, &p, __state->stpool);
	    if (__state->sthan[(i__1 = p - 1) < 10000 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "sthan", i__1, "zzdskbsr_", (
		    ftnlen)1116)] == *handle) {
		if (p == __state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? 
			i__1 : s_rnge(&__global_state->f2c, "btbeg", i__1, 
			"zzdskbsr_", (ftnlen)1118)]) {
		    __state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 
			    : s_rnge(&__global_state->f2c, "btbeg", i__1, 
			    "zzdskbsr_", (ftnlen)1119)] = nxtseg;
		}

/*              Free this segment table entry. */

		lnkfsl_(__global_state, &p, &p, __state->stpool);
	    }
	    p = nxtseg;
	}

/*        If the list for this body is now empty, shorten the */
/*        current table by one: put all the entries for the last */
/*        body in the table into the space occupied by the */
/*        one we've deleted. */

	if (__state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
		s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbsr_", (
		ftnlen)1138)] <= 0) {
	    if (i__ != __state->nbt) {
		__state->btbod[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btbod", i__1, "zzdskbs"
			"r_", (ftnlen)1142)] = __state->btbod[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btbod", i__2, "zzdskbsr_", (
			ftnlen)1142)];
		__state->btexp[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btexp", i__1, "zzdskbs"
			"r_", (ftnlen)1143)] = __state->btexp[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btexp", i__2, "zzdskbsr_", (
			ftnlen)1143)];
		__state->bthfs[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "bthfs", i__1, "zzdskbs"
			"r_", (ftnlen)1144)] = __state->bthfs[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "bthfs", i__2, "zzdskbsr_", (
			ftnlen)1144)];
		__state->btlfs[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btlfs", i__1, "zzdskbs"
			"r_", (ftnlen)1145)] = __state->btlfs[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btlfs", i__2, "zzdskbsr_", (
			ftnlen)1145)];
		__state->btbeg[(i__1 = i__ - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbs"
			"r_", (ftnlen)1146)] = __state->btbeg[(i__2 = 
			__state->nbt - 1) < 100 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "btbeg", i__2, "zzdskbsr_", (
			ftnlen)1146)];
	    }
	    --__state->nbt;
	} else {
	    ++i__;
	}
    }
    chkout_(__global_state, "ZZDSKUSF", (ftnlen)8);
    return 0;
/* $Procedure ZZDSKBSS ( DSK, begin search for segment ) */

L_zzdskbss:
/* $ Abstract */

/*     Initiate search through loaded files to find segments */
/*     satisfying search criteria. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     DSK */
/*     DAS */

/* $ Keywords */

/*     TOPOGRAPHY */

/* $ Declarations */

/*     INTEGER               BODYID */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */

/* $ Detailed_Input */

/*     ZZDSKBSS sets up a search for segments. The four quantities below */
/*     establish the search criteria. */


/* $ Detailed_Output */

/*     None. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1)  If no files have been loaded, the error */
/*         SPICE(NOLOADEDDSKFILES) is signaled. */

/* $ Files */

/*     All files loaded by ZZDSKLSF are potential search targets for */
/*     ZZDSKSNS. */

/* $ Particulars */

/*     ZZDSKBSS sets up a search for segments by ZZDSKSNS. It records the */
/*     body and time to be searched for, and whether to require */
/*     segments containing angular velocity data. If angular velocity */
/*     data are required, only segments containing angular velocity */
/*     data will be returned by ZZDSKSNS. If angular velocity data are */
/*     not required, segments returned by ZZDSKSNS may or may not contain */
/*     angular velocity data. */

/*     ZZDSKBSS determines the first task that ZZDSKSNS will have to */
/*     perform if it is called to get an applicable segment. */

/* $ Examples */

/*     See Examples in ZZDSKBSR. */

/* $ Restrictions */

/*     None. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     R.E. Thurman   (JPL) */
/*     I.M. Underwood (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 08-FEB-2017 (NJB) */

/*        Updated version info. */

/*        19-SEP-2014 (NJB) */

/*           Specification change: now treats the target body as the */
/*           primary search key. Segments lists are associated with */
/*           bodies rather than surfaces. */

/*           Now initializes the DSK state change counter on the first */
/*           pass. */

/*        21-MAY-2013 (NJB) */

/*           Edited headers to remove long lines. */

/*        02-APR-2010 (NJB) (RET) (IMU) */


/* -& */
/* $ Index_Entries */

/*     begin search for dsk segment */

/* -& */
/* $ Revisions */

/*     None. */

/* -& */

/*     Standard SPICE error handling. */

    if (return_(__global_state)) {
	return 0;
    }
    chkin_(__global_state, "ZZDSKBSS", (ftnlen)8);
    if (__state->pass1) {

/*        Initialize the BSR counter. */

	zzctrsin_(__global_state, __state->dskctr);
	__state->pass1 = FALSE_;
    }

/*     Make a saved copy of the body ID code. */

    __state->svbody = *bodyid;

/*     There must be at least one file loaded. */

    if (__state->nft == 0) {
	setmsg_(__global_state, "At least one DSK file needs must be loaded "
		"by ZZDSKLSF before beginning a search.", (ftnlen)81);
	sigerr_(__global_state, "SPICE(NOLOADEDDSKFILES)", (ftnlen)23);
	chkout_(__global_state, "ZZDSKBSS", (ftnlen)8);
	return 0;
    }

/*     The stack of suspended tasks is empty. */

    __state->top = 0;

/*     Is the body already in the body table?  The answer */
/*     determines what the first task for ZZDSKSNS will be. */

    __state->bindex = isrchi_(__global_state, &__state->svbody, &__state->nbt,
	     __state->btbod);
    if (__state->bindex == 0) {
	s_copy(&__global_state->f2c, __state->status, "NEW BODY", (ftnlen)40, 
		(ftnlen)8);
    } else {

/*        Set the status so that ZZDSKSNS will determine whether to check */
/*        the segment list or search new files. */

	s_copy(&__global_state->f2c, __state->status, "?", (ftnlen)40, (
		ftnlen)1);
    }

/*     The saved segment list pointer is no longer valid. */

    __state->savep = -1;
    chkout_(__global_state, "ZZDSKBSS", (ftnlen)8);
    return 0;
/* $Procedure ZZDSKSNS ( DSK, Select next segment ) */

L_zzdsksns:
/* $ Abstract */

/*     Search through loaded files to find a segment matching the */
/*     requested body, time, and need for angular velocity. */
/*     Buffer segment descriptors, identifiers, and handles in the */
/*     process to minimize file reads. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     DSK */
/*     DAS */

/* $ Keywords */

/*     TOPOGRAPHY */

/* $ Declarations */

/*     LOGICAL               CMPFUN */
/*     EXTERNAL              CMPFUN */
/*     INTEGER               HANDLE */
/*     INTEGER               DLADSC ( * ) */
/*     DOUBLE PRECISION      DSKDSC ( * ) */
/*     LOGICAL               FOUND */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     CMPFUN     I   Comparison function. */
/*     HANDLE     O   Handle of file containing the applicable segment. */
/*     DLSDSC     O   DLA descriptor of the applicable segment. */
/*     DSKDSC     O   DSK descriptor of the applicable segment. */
/*     FOUND      O   True if a segment was found. */

/* $ Detailed_Input */

/*     CMPFUN */

/* $ Detailed_Output */

/*     DLADSC */

/*     DSKDS */


/*     HANDLE     is an integer handle of the file containing the */
/*                segment matching the body and time */
/*                specifications made in the last call to ZZDSKBSS. */

/*     FOUND      is true if an applicable segment was found.  False */
/*                otherwise.  If FOUND is false, the values of the */
/*                other arguments are meaningless. */

/* $ Parameters */

/*     None. */

/* $ Exceptions */

/*     1) If ZZDSKSNS is called without ZZDSKBSS ever having been */
/*        called, the error 'SPICE(CALLZZDSKBSSFIRST)' is signaled. */

/*     2) If no segment is found that matches the search criteria, */
/*        FOUND is set to false, but the values of HANDLE, DESCR, */
/*        and SEGID will be meaningless. */

/* $ Files */

/*     All files loaded by ZZDSKLSF are potential search targets for */
/*     ZZDSKSNS. The files are all referred to by their integer handles. */

/* $ Particulars */

/*     ZZDSKSNS is used to locate segments based on the search criteria */
/*     established by the most recent call to ZZDSKBSS.  When a segment */
/*     is found it will have the following characteristics: */

/*        1) Its body will match the body specified in the */
/*           call to ZZDSKBSS. */

/*        2) Its time interval will intersect the time interval */

/*              [SCLKDP - TOL, SCLKDP + TOL], */

/*           where SCLKDP and TOL were specified in the call to ZZDSKBSS. */

/*        3) If there is a need for angular velocity data, as specified */
/*           by NEEDAV in the call to ZZDSKBSS, a returned segment */
/*           will contain angular velocity data. If there is no need */
/*           for such data, the returned segment may or may not contain */
/*           angular velocity data. */

/*     The first call to ZZDSKSNS following a call to ZZDSKBSS starts a */
/*     search through loaded files and either returns the first */
/*     applicable segment, or indicates that no segment was found. */

/*     ZZDSKSNS searches through last-loaded files first. Individual */
/*     files are searched backwards, so that segments that were inserted */
/*     last into the file get checked first. */

/*     Subsequent calls to ZZDSKSNS pick up the search exactly where the */
/*     previous calls left off. If a segment is not found, future calls */
/*     will also indicate that no segment could be found, until a new */
/*     search is begun. */

/*     ZZDSKSNS also buffers segment descriptors and identifiers, to */
/*     attempt to minimize file reads. */

/* $ Examples */

/*     See Examples in ZZDSKBSR. */

/* $ Restrictions */

/*     1) This subroutine assumes that a search has been initiated by */
/*        a call to ZZDSKBSS. */

/*     2) When a DSK file is loaded or unloaded, a new search must */
/*        be started via a call to ZZDSKBSS before this routine may */
/*        be called. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     R.E. Thurman   (JPL) */
/*     I.M. Underwood (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 08-FEB-2017 (NJB) */

/*        Updated version info. */

/*        31-MAR-2016 (NJB) */

/*           References to unneeded variables were removed. */

/*        19-SEP-2014 (NJB) */

/*           Specification change: now treats the target body as the */
/*           primary search key. Segment lists are associated with */
/*           bodies rather than surfaces. */

/*           Now initializes the DSK state change counter on the first */
/*           pass. */

/*        21-MAY-2013 (NJB) */

/*            Removed debugging WRITE statement. Edited headers to */
/*            remove long lines. */

/*        02-APR-2010 (NJB) (RET) (IMU) */

/* -& */
/* $ Index_Entries */

/*     select next dsk segment */

/* -& */
/* $ Revisions */

/*     None. */

/* -& */

/*     Standard SPICE error handling. */

    if (return_(__global_state)) {
	return 0;
    }
    chkin_(__global_state, "ZZDSKSNS", (ftnlen)8);
    if (__state->pass1) {

/*        Initialize the BSR counter. */

	zzctrsin_(__global_state, __state->dskctr);
	__state->pass1 = FALSE_;
    }

/*     Nothing's been found yet. */

    *found = FALSE_;

/*     Initialize the segment list pointer to the saved value from */
/*     the previous pass through this routine, if any. */

    p = __state->savep;

/*     ZZDSKSNS buffers segment descriptors and identifiers, to */
/*     attempt to minimize file reads. Buffering segments involves */
/*     maintaining three tables:  the file table, the body table, */
/*     and the segment table. ZZDSKSNS is broken down into various tasks, */
/*     described in the code below, which perform these manipulations. */

/*     A description of the components of each table is provided in */
/*     the declarations section of ZZDSKBSR. */

/*     Basically, the buffering is performed as follows: once a request */
/*     for a segment for a particular body is made, if there are */
/*     no adequate entries in the buffer already, a search is made */
/*     through loaded files for applicable segments.  Every segment */
/*     pertaining to that body in a searched file is buffered, */
/*     before a check of the current buffer is made.  If the search */
/*     doesn't turn up a segment matching the specified search criteria */
/*     the next file is searched and new segments are added to the list, */
/*     and so on. */

/*     The information in the segment table (ST) is stored in a */
/*     doubly-linked list. Each node in the list contains several */
/*     individual pieces of data, which are stored in parallel */
/*     arrays. */

/*     In the following loop, we will try to simplify things by */
/*     doing exactly one thing on each pass through the loop. */
/*     After each pass, the status of the loop (STATUS) will be */
/*     adjusted to reflect the next thing that needs to be done. */
/*     The first task is set by ZZDSKBSS. */

/*     Occasionally, the current task will have to be interrupted */
/*     until another task can be carried out. (For example, when */
/*     collecting new segments, an interrupt might place a segment */
/*     at the front or end of the current body list; when placing */
/*     the segment on the list, a second interrupt might free */
/*     room in the segment table in order to allow the addition */
/*     to proceed.) In this case, the current task will be saved and */
/*     restored after the more urgent task has been completed. */

/*     The loop can terminate in only one of two ways (unless an error */
/*     occurs). First, if an applicable segment is found in the segment */
/*     table, the handle, descriptor, and identifier for the segment */
/*     are returned immediately.  Second, if the table does not contain */
/*     an applicable segment, and if no files remain to be searched, */
/*     the loop terminates normally, and no data are returned. */

/*     The status is saved on exit, however, so that subsequent calls */
/*     will resume a search exactly where previous calls left off. */

/*     Each status is described below. */

/*     'NEW BODY' */

/*        This indicates that the specified body has */
/*        no segments stored for it at all. It must be added to the */
/*        body table.  (This is followed immediately by an */
/*        OLD FILES search, in which every file loaded is considered an */
/*        old file.) */

/*     'NEW FILES' */

/*        This indicates that at least one new file has been added */
/*        since the last time the segment list for the specified */
/*        body was searched. Find the oldest of these new files, */
/*        and begin a NEW SEGMENTS search in forward order for */
/*        segments to add to the front of the list. */

/*     'NEW SEGMENTS' */

/*        Continue a NEW FILES search, adding segments for the specified */
/*        body to the front of the list. */

/*     'OLD FILES' */

/*        This indicates that although the list has been searched */
/*        and found to contain no applicable segment, some of the */
/*        older files remain to be searched. Find the newest of these */
/*        old files, and begin an OLD SEGMENTS search in backward order. */

/*     'OLD SEGMENTS' */

/*        Continue an OLD FILES search, adding segments for the specified */
/*        body to the end of the list. */

/*     'CHECK LIST' */

/*        This indicates that the list is ready to be searched, */
/*        either because no new files have been added, or because */
/*        segments from a new file or an old file have recently */
/*        been added. */

/*        The list is never checked until all new files have been */
/*        searched. */

/*        If an applicable segment is found, it is returned. */

/*     'MAKE ROOM' (Interrupt) */

/*        This indicates that one of the bodies must be removed, */
/*        along with its stored segments, to make room for another */
/*        body or segment.  The body (other than the */
/*        specified body) with the smallest expense is selected */
/*        for this honor. */

/*     'ADD TO FRONT' (Interrupt) */

/*        This indicates that a segment has been found (during the */
/*        course of a NEW FILES search) and must be added to the front */
/*        of the list. */

/*     'ADD TO END' (Interrupt) */

/*        This indicates that a segment has been found (during the */
/*        course of an OLD FILES search) and must be added to the end */
/*        of the list. */

/*     'SUSPEND' */

/*        This indicates that the current task (DOING) should be */
/*        interrupted until a more urgent task (URGENT) can be */
/*        carried out. The current task is placed on a stack for */
/*        safekeeping. */

/*     'RESUME' */

/*        This indicates that the most recently interrupted task */
/*        should be resumed immediately. */

/*     '?' */

/*        This indicates that the next task is not immediately */
/*        apparent: if new files exist, they should be searched; */
/*        otherwise the list should be checked. */

/*     'HOPELESS' */

/*        This indicates that the table does not contain an applicable */
/*        segment, and no files remain to be searched. */

/*      'BOGUS ENTRY' */

/*        This is the initial value of STATUS and indicates that no */
/*        call to ZZDSKBSS was ever made. If this is the case then an */
/*        error will be signaled. */

    if (s_cmp(&__global_state->f2c, __state->status, "BOGUS ENTRY", (ftnlen)
	    40, (ftnlen)11) == 0) {
	setmsg_(__global_state, "Must begin a search by calling ZZDSKBSS fir"
		"st.", (ftnlen)46);
	sigerr_(__global_state, "SPICE(CALLZZDSKBSSFIRST)", (ftnlen)24);
	chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
	return 0;
    }
    while(s_cmp(&__global_state->f2c, __state->status, "HOPELESS", (ftnlen)40,
	     (ftnlen)8) != 0) {

/*        If new files have been added, they have to be searched. */
/*        Otherwise, go right to the list of stored segments. */

	if (s_cmp(&__global_state->f2c, __state->status, "?", (ftnlen)40, (
		ftnlen)1) == 0) {

/*           There are two ways to get to this point. */

/*           1)  Status may have been set to '?' by ZZDSKBSS. */

/*           2)  Status was set to '?' by the NEW SEGMENTS block */
/*               of code as the result of finishing the read of */
/*               a new file. */

	    if (__state->bthfs[(i__1 = __state->bindex - 1) < 100 && 0 <= 
		    i__1 ? i__1 : s_rnge(&__global_state->f2c, "bthfs", i__1, 
		    "zzdskbsr_", (ftnlen)1796)] < __state->ftnum[(i__2 = 
		    __state->nft - 1) < 5000 && 0 <= i__2 ? i__2 : s_rnge(&
		    __global_state->f2c, "ftnum", i__2, "zzdskbsr_", (ftnlen)
		    1796)]) {
		s_copy(&__global_state->f2c, __state->status, "NEW FILES", (
			ftnlen)40, (ftnlen)9);
	    } else {
/*              If the segment list for this body is empty, make */
/*              sure the expense is set to 0. */

		if (__state->btbeg[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btbeg", 
			i__1, "zzdskbsr_", (ftnlen)1805)] <= 0) {
		    __state->btexp[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			    i__1 ? i__1 : s_rnge(&__global_state->f2c, "btexp"
			    , i__1, "zzdskbsr_", (ftnlen)1806)] = 0;
		}

/*              Prepare to look at the first segment in the list for */
/*              this body. */

		p = __state->btbeg[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btbeg", 
			i__1, "zzdskbsr_", (ftnlen)1813)];
		s_copy(&__global_state->f2c, __state->status, "CHECK LIST", (
			ftnlen)40, (ftnlen)10);
	    }
	} else if (s_cmp(&__global_state->f2c, __state->status, "NEW BODY", (
		ftnlen)40, (ftnlen)8) == 0) {

/*           New bodies are added to the end of the body */
/*           table. If the table is full, one of the current occupants */
/*           must be removed to make room for the new one. */

/*           Setting LFS to one more than the highest current file */
/*           number means the 'OLD FILES' search that follows will */
/*           begin with the last-loaded file. */

/*           There is one way to get here: */

/*           1)  The variable STATUS was set to NEW BODY prior */
/*               in ZZDSKBSS. */

/*           Find the cheapest slot in the body table to store */
/*           the initial information about this body. */

/*           NOTE:  This used to be handled by the MAKE ROOM section. */
/*           However, trying to handle this special case there was */
/*           just more trouble than it was worth. */

	    if (__state->nbt < 100) {

/*              If the body table isn't full, the cheapest place is */
/*              just the next unused row of the table. */

		++__state->nbt;
		cheap = __state->nbt;
	    } else {

/*              The body table is full.  Find the least */
/*              expensive body in the table and remove it. */

		cheap = 1;
		minexp = __state->btexp[0];
		i__1 = __state->nbt;
		for (i__ = 2; i__ <= i__1; ++i__) {
		    if (__state->btexp[(i__2 = i__ - 1) < 100 && 0 <= i__2 ? 
			    i__2 : s_rnge(&__global_state->f2c, "btexp", i__2,
			     "zzdskbsr_", (ftnlen)1859)] < minexp) {
			cheap = i__;
			minexp = __state->btexp[(i__2 = i__ - 1) < 100 && 0 <=
				 i__2 ? i__2 : s_rnge(&__global_state->f2c, 
				"btexp", i__2, "zzdskbsr_", (ftnlen)1861)];
		    }
		}

/*              If there are any segments associated with the */
/*              least expensive body, we put them back on the free */
/*              list. */

		head = __state->btbeg[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? 
			i__1 : s_rnge(&__global_state->f2c, "btbeg", i__1, 
			"zzdskbsr_", (ftnlen)1871)];
		if (head > 0) {
		    tail = -lnkprv_(__global_state, &head, __state->stpool);
		    lnkfsl_(__global_state, &head, &tail, __state->stpool);
		}
	    }

/*           Set up a table entry for the new body. */

	    __state->btbod[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "btbod", i__1, "zzdskbsr_", (
		    ftnlen)1885)] = __state->svbody;
	    __state->btexp[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "btexp", i__1, "zzdskbsr_", (
		    ftnlen)1886)] = 0;
	    __state->bthfs[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "bthfs", i__1, "zzdskbsr_", (
		    ftnlen)1887)] = __state->ftnum[(i__2 = __state->nft - 1) <
		     5000 && 0 <= i__2 ? i__2 : s_rnge(&__global_state->f2c, 
		    "ftnum", i__2, "zzdskbsr_", (ftnlen)1887)];
	    __state->btlfs[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "btlfs", i__1, "zzdskbsr_", (
		    ftnlen)1888)] = __state->ftnum[(i__2 = __state->nft - 1) <
		     5000 && 0 <= i__2 ? i__2 : s_rnge(&__global_state->f2c, 
		    "ftnum", i__2, "zzdskbsr_", (ftnlen)1888)] + 1;
	    __state->btbeg[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? i__1 : 
		    s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbsr_", (
		    ftnlen)1889)] = 0;
	    __state->bindex = cheap;

/*           Now search all of the files for segments relating to */
/*           this body. */

	    s_copy(&__global_state->f2c, __state->status, "OLD FILES", (
		    ftnlen)40, (ftnlen)9);
	} else if (s_cmp(&__global_state->f2c, __state->status, "NEW FILES", (
		ftnlen)40, (ftnlen)9) == 0) {

/*           When new files exist, they should be searched in forward */
/*           order, beginning with the oldest new file not yet searched. */
/*           All new files must be searched before the list can be */
/*           checked, to ensure that the best (newest) segments are */
/*           being used. */

/*           Begin a forward search, and prepare to look for individual */
/*           segments from the file. */

/*           The only way to get here is to have STATUS set to */
/*           the value NEW FILES in the STATUS .EQ. '?' block */
/*           of the IF structure. */

/*           Find the next file to search; set FINDEX to the */
/*           corresponding file table entry. */
	    __state->findex = 1;
	    while(__state->bthfs[(i__1 = __state->bindex - 1) < 100 && 0 <= 
		    i__1 ? i__1 : s_rnge(&__global_state->f2c, "bthfs", i__1, 
		    "zzdskbsr_", (ftnlen)1919)] >= __state->ftnum[(i__2 = 
		    __state->findex - 1) < 5000 && 0 <= i__2 ? i__2 : s_rnge(&
		    __global_state->f2c, "ftnum", i__2, "zzdskbsr_", (ftnlen)
		    1919)]) {
		++__state->findex;
	    }
	    __state->bthfs[(i__1 = __state->bindex - 1) < 100 && 0 <= i__1 ? 
		    i__1 : s_rnge(&__global_state->f2c, "bthfs", i__1, "zzds"
		    "kbsr_", (ftnlen)1925)] = __state->ftnum[(i__2 = 
		    __state->findex - 1) < 5000 && 0 <= i__2 ? i__2 : s_rnge(&
		    __global_state->f2c, "ftnum", i__2, "zzdskbsr_", (ftnlen)
		    1925)];

/*           Start a forward search through the current file. */

	    __state->begsch = TRUE_;
	    dlabfs_(__global_state, &__state->fthan[(i__1 = __state->findex - 
		    1) < 5000 && 0 <= i__1 ? i__1 : s_rnge(&
		    __global_state->f2c, "fthan", i__1, "zzdskbsr_", (ftnlen)
		    1931)], dlalds, &__state->fnd);
	    if (failed_(__global_state)) {
		chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		return 0;
	    }
	    s_copy(&__global_state->f2c, __state->status, "NEW SEGMENTS", (
		    ftnlen)40, (ftnlen)12);

/*           The cost of the list contributed by the new file is */
/*           zero so far. */

	    cost = 0;
	} else if (s_cmp(&__global_state->f2c, __state->status, "NEW SEGMENTS"
		, (ftnlen)40, (ftnlen)12) == 0) {

/*           New files are searched in forward order. Segments, when */
/*           found, are inserted at the front of the list. */

/*           Each segment examined, whether applicable or not, adds to */
/*           the expense of the list. */

/*           The only ways to get here are: */

/*               1) Enter from the NEW FILES block of the IF structure. */
/*               2) Re-enter from this block if there are more segments */
/*                  to examine in the current file and the last segment */
/*                  seen wasn't for the body of interest. */
/*               3) Enter from the RESUME state after adding a segment */
/*                  to the front of the list for the current body. */

	    if (__state->begsch) {

/*              We already have a FND value, and if FND is true, a */
/*              DLA descriptor. */

		__state->begsch = FALSE_;
	    } else {

/*              Use the current DLA descriptor to look up the next one. */

		dlafns_(__global_state, &__state->fthan[(i__1 = 
			__state->findex - 1) < 5000 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "fthan", i__1, "zzdskbs"
			"r_", (ftnlen)1975)], dlalds, dlanxt, &__state->fnd);
		if (__state->fnd) {
		    movei_(__global_state, dlanxt, &__state->c__8, dlalds);
		}
	    }
	    if (failed_(__global_state)) {
		chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		return 0;
	    }
	    if (! __state->fnd) {

/*              We're out of segments in the current file.  Decide */
/*              whether we need to examine another new file, or */
/*              whether we're ready to check the list. */

		s_copy(&__global_state->f2c, __state->status, "?", (ftnlen)40,
			 (ftnlen)1);
		__state->btexp[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btexp", 
			i__1, "zzdskbsr_", (ftnlen)1995)] = __state->btexp[(
			i__2 = __state->bindex - 1) < 100 && 0 <= i__2 ? i__2 
			: s_rnge(&__global_state->f2c, "btexp", i__2, "zzdsk"
			"bsr_", (ftnlen)1995)] + cost;
	    } else {

/*              Get the DSK segment descriptor for the current */
/*              segment. */

		dskgd_(__global_state, &__state->fthan[(i__1 = 
			__state->findex - 1) < 5000 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "fthan", i__1, "zzdskbs"
			"r_", (ftnlen)2002)], dlalds, dsklds);
		if (i_dnnt(&__global_state->f2c, &dsklds[1]) == 
			__state->svbody) {

/*                 The segment is for the body of interest. Add this */
/*                 segment to the front of the list. */

		    s_copy(&__global_state->f2c, doing, "NEW SEGMENTS", (
			    ftnlen)40, (ftnlen)12);
		    s_copy(&__global_state->f2c, urgent, "ADD TO FRONT", (
			    ftnlen)40, (ftnlen)12);
		    s_copy(&__global_state->f2c, __state->status, "SUSPEND", (
			    ftnlen)40, (ftnlen)7);
		}
		++cost;
	    }

/*           If we haven't reset the status, we'll return for another */
/*           'NEW SEGMENTS' pass. */

	} else if (s_cmp(&__global_state->f2c, __state->status, "OLD FILES", (
		ftnlen)40, (ftnlen)9) == 0) {

/*           When old files must be searched (because the segments in */
/*           the list are inadequate), they should be searched in */
/*           backward order, beginning with the newest old file not */
/*           yet searched.  The segment list will be re-checked */
/*           after each file is searched.  If a match is found, */
/*           the search terminates, so some old files may not be */
/*           searched. */

/*           Begin a backwards search, and prepare to look for */
/*           individual segments from the file. */

/*           You can get to this block in two ways. */

/*           1) We can have a NEW BODY. */

/*           2) We have checked the current list (CHECK LIST) for */
/*              this body, didn't find an applicable segment and */
/*              have some files left that have not been searched. */
	    __state->findex = __state->nft;
	    while(__state->btlfs[(i__1 = __state->bindex - 1) < 100 && 0 <= 
		    i__1 ? i__1 : s_rnge(&__global_state->f2c, "btlfs", i__1, 
		    "zzdskbsr_", (ftnlen)2046)] <= __state->ftnum[(i__2 = 
		    __state->findex - 1) < 5000 && 0 <= i__2 ? i__2 : s_rnge(&
		    __global_state->f2c, "ftnum", i__2, "zzdskbsr_", (ftnlen)
		    2046)]) {
		--__state->findex;
	    }
	    __state->begsch = TRUE_;
	    dlabbs_(__global_state, &__state->fthan[(i__1 = __state->findex - 
		    1) < 5000 && 0 <= i__1 ? i__1 : s_rnge(&
		    __global_state->f2c, "fthan", i__1, "zzdskbsr_", (ftnlen)
		    2051)], dlalds, &__state->fnd);
	    if (failed_(__global_state)) {
		chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		return 0;
	    }
	    s_copy(&__global_state->f2c, __state->status, "OLD SEGMENTS", (
		    ftnlen)40, (ftnlen)12);

/*           The next thing we'll do is search through all the segments */
/*           of this file for those that applicable to this body. */
/*           The cost of the list contributed by the current file is */
/*           zero so far. */

	    cost = 0;

/*        Old files are searched in backward order. Segments, when */
/*        found, are inserted at the end of the list. */

/*        Each segment examined, whether applicable or not, adds to */
/*        the expense of the list. */

	} else if (s_cmp(&__global_state->f2c, __state->status, "OLD SEGMENTS"
		, (ftnlen)40, (ftnlen)12) == 0) {

/*           There is only one way to get here---from the */
/*           block 'OLD FILES'.  Note we do not add to the */
/*           expense of the list for this body until we've */
/*           completely searched this file. */

	    if (__state->begsch) {

/*              We already have a value of FND, and if FND is true, */
/*              a DLA segment from the current file. */

		__state->begsch = FALSE_;
	    } else {

/*              Look up the previous segment from this file. */

		dlafps_(__global_state, &__state->fthan[(i__1 = 
			__state->findex - 1) < 5000 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "fthan", i__1, "zzdskbs"
			"r_", (ftnlen)2093)], dlalds, dlaprv, &__state->fnd);
		if (__state->fnd) {
		    movei_(__global_state, dlaprv, &__state->c__8, dlalds);
		}
	    }
	    if (failed_(__global_state)) {
		chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		return 0;
	    }
	    if (! __state->fnd) {

/*              All of the segments in this file have been exhausted. */
/*              Change the lowest file searched indicator for this */
/*              body to be the current file, and go check the */
/*              current list. */

		__state->btlfs[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btlfs", 
			i__1, "zzdskbsr_", (ftnlen)2116)] = __state->ftnum[(
			i__2 = __state->findex - 1) < 5000 && 0 <= i__2 ? 
			i__2 : s_rnge(&__global_state->f2c, "ftnum", i__2, 
			"zzdskbsr_", (ftnlen)2116)];
		__state->btexp[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btexp", 
			i__1, "zzdskbsr_", (ftnlen)2117)] = __state->btexp[(
			i__2 = __state->bindex - 1) < 100 && 0 <= i__2 ? i__2 
			: s_rnge(&__global_state->f2c, "btexp", i__2, "zzdsk"
			"bsr_", (ftnlen)2117)] + cost;
		p = __state->btbeg[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btbeg", 
			i__1, "zzdskbsr_", (ftnlen)2118)];
		s_copy(&__global_state->f2c, __state->status, "CHECK LIST", (
			ftnlen)40, (ftnlen)10);
	    } else {

/*              Get the DSK descriptor for this segment. */

		dskgd_(__global_state, &__state->fthan[(i__1 = 
			__state->findex - 1) < 5000 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "fthan", i__1, "zzdskbs"
			"r_", (ftnlen)2125)], dlalds, dsklds);
		if (failed_(__global_state)) {
		    chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		    return 0;
		}
		if (i_dnnt(&__global_state->f2c, &dsklds[1]) == 
			__state->svbody) {

/*                 This is a segment for the body of interest. */

		    s_copy(&__global_state->f2c, doing, "OLD SEGMENTS", (
			    ftnlen)40, (ftnlen)12);
		    s_copy(&__global_state->f2c, urgent, "ADD TO END", (
			    ftnlen)40, (ftnlen)10);
		    s_copy(&__global_state->f2c, __state->status, "SUSPEND", (
			    ftnlen)40, (ftnlen)7);
		}
		++cost;
	    }
	} else if (s_cmp(&__global_state->f2c, __state->status, "CHECK LIST", 
		(ftnlen)40, (ftnlen)10) == 0) {

/*           Okay, all the new files (and maybe an old file or two) */
/*           have been searched. Time to look at the list of segments */
/*           stored for the body, to see if there is one applicable */
/*           to the specified epoch and need for angular velocity data. */

/*           If so, return it.  If not, try another old file.  If there */
/*           are no more old files, give up the ghost. */

/*           There are two ways to get to this point. */

/*           1) From the '?' block. */
/*           2) From the 'OLD SEGMENTS' block. */

/*           For every segment examined, adjust the re-use interval */
/*           associated with the current body. */

/*           P always points to the current segment in the list. Reject */
/*           a segment if there is a need for angular velocity data and */
/*           the segment doesn't have it. */


	    while(p > 0) {
		if ((*cmpfun)(__global_state, &__state->sthan[(i__1 = p - 1) <
			 10000 && 0 <= i__1 ? i__1 : s_rnge(&
			__global_state->f2c, "sthan", i__1, "zzdskbsr_", (
			ftnlen)2171)], &__state->stdlad[(i__2 = (p << 3) - 8) 
			< 80000 && 0 <= i__2 ? i__2 : s_rnge(&
			__global_state->f2c, "stdlad", i__2, "zzdskbsr_", (
			ftnlen)2171)], &__state->stdskd[(i__3 = p * 24 - 24) <
			 240000 && 0 <= i__3 ? i__3 : s_rnge(&
			__global_state->f2c, "stdskd", i__3, "zzdskbsr_", (
			ftnlen)2171)])) {
		    movei_(__global_state, &__state->stdlad[(i__1 = (p << 3) 
			    - 8) < 80000 && 0 <= i__1 ? i__1 : s_rnge(&
			    __global_state->f2c, "stdlad", i__1, "zzdskbsr_", 
			    (ftnlen)2173)], &__state->c__8, dladsc);
		    moved_(__global_state, &__state->stdskd[(i__1 = p * 24 - 
			    24) < 240000 && 0 <= i__1 ? i__1 : s_rnge(&
			    __global_state->f2c, "stdskd", i__1, "zzdskbsr_", 
			    (ftnlen)2175)], &__state->c__24, dskdsc);
		    *handle = __state->sthan[(i__1 = p - 1) < 10000 && 0 <= 
			    i__1 ? i__1 : s_rnge(&__global_state->f2c, "sthan"
			    , i__1, "zzdskbsr_", (ftnlen)2177)];
		    *found = TRUE_;

/*                 Go ahead and move the pointer up before returning */
/*                 so that the search for the next applicable segment */
/*                 will start at the right place. */

		    __state->savep = __state->stpool[(i__1 = (p << 1) + 10) < 
			    20012 && 0 <= i__1 ? i__1 : s_rnge(&
			    __global_state->f2c, "stpool", i__1, "zzdskbsr_", 
			    (ftnlen)2184)];
		    chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		    return 0;
		}

/*              Get the next node.  We avoid LNKNXT here in order */
/*              to speed up the operation. */

		p = __state->stpool[(i__1 = (p << 1) + 10) < 20012 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "stpool", 
			i__1, "zzdskbsr_", (ftnlen)2196)];
	    }

/*           If we're still here we didn't have information for this */
/*           body in the segment list. */

/*           If there are more files, search them. */
/*           Otherwise, things are hopeless, set the status that way. */

	    if (__state->btlfs[(i__1 = __state->bindex - 1) < 100 && 0 <= 
		    i__1 ? i__1 : s_rnge(&__global_state->f2c, "btlfs", i__1, 
		    "zzdskbsr_", (ftnlen)2207)] > __state->ftnum[0]) {
		s_copy(&__global_state->f2c, __state->status, "OLD FILES", (
			ftnlen)40, (ftnlen)9);
	    } else {
		s_copy(&__global_state->f2c, __state->status, "HOPELESS", (
			ftnlen)40, (ftnlen)8);
	    }
	} else if (s_cmp(&__global_state->f2c, __state->status, "MAKE ROOM", (
		ftnlen)40, (ftnlen)9) == 0) {

/*           When adding a new segment to a full table, one of the */
/*           current bodies must be dropped.  The ideal */
/*           candidate is the one whose list was constructed at the */
/*           lowest expense.  The candidate should be removed from */
/*           the body table, and its list transferred to the */
/*           segment table pool. */

/*           There is ``room'' if the segment table pool contains at */
/*           least one free node. */

/*           It is possible that a single body requires more than the */
/*           entire segment table for its own segments. Two things might */
/*           happen in such a case: */

/*              1) If the list under consideration was being added to at */
/*                 the end, then a search is continued without buffering */
/*                 any segments. */

/*              2) If the list was being added to at the beginning, then */
/*                 that means there was a NEW FILES search going on, and */
/*                 so a brand new list is constructed for the body, */
/*                 much as in a 'NEW BODY' task. */

/*           There are two different ways to get to this point. */

/*              1) From 'ADD TO FRONT' if the segment table pool is full. */
/*              2) From 'ADD TO END' if the segment table pool is full. */

/*           Try to make room by deleting a segment list.  CHEAP will */
/*           be the index of the "cheapest" segment list in the */
/*           body table. */

	    minexp = intmax_(__global_state);
	    cheap = 0;
	    i__1 = __state->nbt;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (i__ != __state->bindex) {
		    if (__state->btexp[(i__2 = i__ - 1) < 100 && 0 <= i__2 ? 
			    i__2 : s_rnge(&__global_state->f2c, "btexp", i__2,
			     "zzdskbsr_", (ftnlen)2257)] < minexp || cheap == 
			    0) {

/*                    This list is the cheapest seen so far, */
/*                    possibly because it's the first one */
/*                    considered.  At the moment, it's as good */
/*                    a candidate for removal as any. */

			cheap = i__;
			minexp = __state->btexp[(i__2 = i__ - 1) < 100 && 0 <=
				 i__2 ? i__2 : s_rnge(&__global_state->f2c, 
				"btexp", i__2, "zzdskbsr_", (ftnlen)2266)];
		    }
		}
	    }
	    if (cheap == 0) {

/*              If there are no deletable segments, the Thing To */
/*              Do depends on the task that was suspended before */
/*              entering MAKE ROOM. */

		if (s_cmp(&__global_state->f2c, stack + ((i__1 = __state->top 
			- 1) < 2 && 0 <= i__1 ? i__1 : s_rnge(&
			__global_state->f2c, "stack", i__1, "zzdskbsr_", (
			ftnlen)2281)) * 40, "ADD TO END", (ftnlen)40, (ftnlen)
			10) == 0) {

/*                 The segment meta-data from the current file cannot */
/*                 be buffered. */

/*                 In the corresponding SPK and CK cases, we would */
/*                 search the partial list of segments from this file, */
/*                 then proceed to search the rest of the file and any */
/*                 other old files. In this case, we don't support */
/*                 searching unbuffered segments, so this is the */
/*                 end of the line. */

/*                 We must clean up the segment list for the current */
/*                 body before we signal an error. All segments from the */
/*                 file we're currently searching must be deleted from */
/*                 the list. If we delete the head node of the list, the */
/*                 body table pointer to the list must be updated. If */
/*                 the segment list becomes empty, the body must be */
/*                 deleted from the body table. */

		    head = __state->btbeg[(i__1 = __state->bindex - 1) < 100 
			    && 0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c,
			     "btbeg", i__1, "zzdskbsr_", (ftnlen)2301)];
		    tail = -lnkprv_(__global_state, &head, __state->stpool);
		    node = tail;
		    while(node > 0) {

/*                    Let PRVNOD be the predecessor of NODE. PRVNOD may */
/*                    be negative (actually, a pointer to the list tail). */

			prvnod = lnkprv_(__global_state, &node, 
				__state->stpool);
			if (__state->sthan[(i__1 = node - 1) < 10000 && 0 <= 
				i__1 ? i__1 : s_rnge(&__global_state->f2c, 
				"sthan", i__1, "zzdskbsr_", (ftnlen)2313)] == 
				__state->fthan[(i__2 = __state->findex - 1) < 
				5000 && 0 <= i__2 ? i__2 : s_rnge(&
				__global_state->f2c, "fthan", i__2, "zzdskbs"
				"r_", (ftnlen)2313)]) {

/*                       This segment is from the file we were */
/*                       searching when we ran out of room. Free */
/*                       the segment list entry at index NODE. */
			    lnkfsl_(__global_state, &node, &node, 
				    __state->stpool);
			    if (node == head) {

/*                          We just deleted the last remaining node in */
/*                          the list for the current body. We can delete */
/*                          this body from the body table. However, the */
/*                          body table contains no other bodies at this */
/*                          point, since we would have deleted them in */
/*                          the attempt to make room for the current */
/*                          body. So we don't need to compress the body */
/*                          table; we just indicate that it's empty. */

				__state->nbt = 0;
			    }

/*                       This is the end of the block that handles the */
/*                       head node case. */

			}

/*                    This is the end of the block that handles the */
/*                    matching file case. */

/*                    Process the previous node. If the node is */
/*                    non-positive, the loop will terminate. */

			node = prvnod;
		    }

/*                 The segment table entries for the current body that */
/*                 are associated with the current file have been */
/*                 deleted. */

/*                 Make sure that a new search is started before this */
/*                 routine is called again. */

		    s_copy(&__global_state->f2c, __state->status, "HOPELESS", 
			    (ftnlen)40, (ftnlen)8);
		    __state->top = 0;

/*                 It's finally time to signal the error. */

		    setmsg_(__global_state, "ZZDSKSNS ran out of segment tab"
			    "le room while trying to append to the tail of th"
			    "e segment list for body #. Current state is ADD "
			    "TO END.", (ftnlen)134);
		    errint_(__global_state, "#", &__state->svbody, (ftnlen)1);
		    sigerr_(__global_state, "SPICE(BUFFEROVERFLOW)", (ftnlen)
			    21);
		    chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		    return 0;
		} else {

/*                 STACK(TOP) is set to 'ADD TO FRONT'. */

/*                 If there is no room left in the table in the middle */
/*                 of an attempt to add to the front of the list, just */
/*                 start from scratch by effectively initiating a 'NEW */
/*                 BODY' task. */

/*                 Return the current list to the segment table pool. */
/*                 Note this list is non-empty. */

		    p = __state->btbeg[(i__1 = __state->bindex - 1) < 100 && 
			    0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c, 
			    "btbeg", i__1, "zzdskbsr_", (ftnlen)2384)];
		    tail = -lnkprv_(__global_state, &p, __state->stpool);
		    lnkfsl_(__global_state, &p, &tail, __state->stpool);

/*                 Re-initialize the table for this body, and */
/*                 initiate an 'OLD FILES' search, just as in 'NEW */
/*                 BODY'. */

		    __state->btexp[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			    i__1 ? i__1 : s_rnge(&__global_state->f2c, "btexp"
			    , i__1, "zzdskbsr_", (ftnlen)2393)] = 0;
		    __state->bthfs[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			    i__1 ? i__1 : s_rnge(&__global_state->f2c, "bthfs"
			    , i__1, "zzdskbsr_", (ftnlen)2394)] = 
			    __state->ftnum[(i__2 = __state->nft - 1) < 5000 &&
			     0 <= i__2 ? i__2 : s_rnge(&__global_state->f2c, 
			    "ftnum", i__2, "zzdskbsr_", (ftnlen)2394)];
		    __state->btlfs[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			    i__1 ? i__1 : s_rnge(&__global_state->f2c, "btlfs"
			    , i__1, "zzdskbsr_", (ftnlen)2395)] = 
			    __state->ftnum[(i__2 = __state->nft - 1) < 5000 &&
			     0 <= i__2 ? i__2 : s_rnge(&__global_state->f2c, 
			    "ftnum", i__2, "zzdskbsr_", (ftnlen)2395)] + 1;
		    s_copy(&__global_state->f2c, __state->status, "OLD FILES",
			     (ftnlen)40, (ftnlen)9);
		}

/*              Unwind the stack; we've set the target states already. */

		__state->top = 0;
	    } else {

/*              Return this cheapest list to the segment pool.  This */
/*              list could be empty. */

		head = __state->btbeg[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? 
			i__1 : s_rnge(&__global_state->f2c, "btbeg", i__1, 
			"zzdskbsr_", (ftnlen)2411)];
		if (head > 0) {
		    tail = -lnkprv_(__global_state, &head, __state->stpool);
		    lnkfsl_(__global_state, &head, &tail, __state->stpool);
		}

/*              Fill the deleted body's space in the table with */
/*              the final entry in the table. */

		if (cheap != __state->nbt) {
		    __state->btbod[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? 
			    i__1 : s_rnge(&__global_state->f2c, "btbod", i__1,
			     "zzdskbsr_", (ftnlen)2427)] = __state->btbod[(
			    i__2 = __state->nbt - 1) < 100 && 0 <= i__2 ? 
			    i__2 : s_rnge(&__global_state->f2c, "btbod", i__2,
			     "zzdskbsr_", (ftnlen)2427)];
		    __state->btexp[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? 
			    i__1 : s_rnge(&__global_state->f2c, "btexp", i__1,
			     "zzdskbsr_", (ftnlen)2428)] = __state->btexp[(
			    i__2 = __state->nbt - 1) < 100 && 0 <= i__2 ? 
			    i__2 : s_rnge(&__global_state->f2c, "btexp", i__2,
			     "zzdskbsr_", (ftnlen)2428)];
		    __state->bthfs[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? 
			    i__1 : s_rnge(&__global_state->f2c, "bthfs", i__1,
			     "zzdskbsr_", (ftnlen)2429)] = __state->bthfs[(
			    i__2 = __state->nbt - 1) < 100 && 0 <= i__2 ? 
			    i__2 : s_rnge(&__global_state->f2c, "bthfs", i__2,
			     "zzdskbsr_", (ftnlen)2429)];
		    __state->btlfs[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? 
			    i__1 : s_rnge(&__global_state->f2c, "btlfs", i__1,
			     "zzdskbsr_", (ftnlen)2430)] = __state->btlfs[(
			    i__2 = __state->nbt - 1) < 100 && 0 <= i__2 ? 
			    i__2 : s_rnge(&__global_state->f2c, "btlfs", i__2,
			     "zzdskbsr_", (ftnlen)2430)];
		    __state->btbeg[(i__1 = cheap - 1) < 100 && 0 <= i__1 ? 
			    i__1 : s_rnge(&__global_state->f2c, "btbeg", i__1,
			     "zzdskbsr_", (ftnlen)2431)] = __state->btbeg[(
			    i__2 = __state->nbt - 1) < 100 && 0 <= i__2 ? 
			    i__2 : s_rnge(&__global_state->f2c, "btbeg", i__2,
			     "zzdskbsr_", (ftnlen)2431)];
		}
		if (__state->bindex == __state->nbt) {
		    __state->bindex = cheap;
		}

/*              One less body now. */

		--__state->nbt;
		s_copy(&__global_state->f2c, __state->status, "RESUME", (
			ftnlen)40, (ftnlen)6);
	    }

/*           At this point, we either made room by freeing a non-empty */
/*           segment list, or we're going to re-build the list for the */
/*           current body, starting with the highest-priority segments. */
/*           In the former case, the state is 'RESUME'; in the latter, */
/*           it's 'OLD FILES'. */

	} else if (s_cmp(&__global_state->f2c, __state->status, "ADD TO FRONT"
		, (ftnlen)40, (ftnlen)12) == 0) {

/*           The current segment information should be linked in at */
/*           the head of the segment list for the current body, */
/*           and the pertinent body table entry should point */
/*           to the new head of the list. */

/*           The only way to get here is from the block NEW SEGMENTS */
/*           after suspending that task. */
	    if (lnknfn_(__global_state, __state->stpool) == 0) {
		s_copy(&__global_state->f2c, doing, "ADD TO FRONT", (ftnlen)
			40, (ftnlen)12);
		s_copy(&__global_state->f2c, urgent, "MAKE ROOM", (ftnlen)40, 
			(ftnlen)9);
		s_copy(&__global_state->f2c, __state->status, "SUSPEND", (
			ftnlen)40, (ftnlen)7);
	    } else {

/*              Allocate a node and link it to the front of the list */
/*              for the current body. */

		lnkan_(__global_state, __state->stpool, &new__);
		__state->sthan[(i__1 = new__ - 1) < 10000 && 0 <= i__1 ? i__1 
			: s_rnge(&__global_state->f2c, "sthan", i__1, "zzdsk"
			"bsr_", (ftnlen)2478)] = __state->fthan[(i__2 = 
			__state->findex - 1) < 5000 && 0 <= i__2 ? i__2 : 
			s_rnge(&__global_state->f2c, "fthan", i__2, "zzdskbs"
			"r_", (ftnlen)2478)];

/*              Store the DLA and DSK descriptors for this segment in */
/*              the segment table. */

		movei_(__global_state, dlalds, &__state->c__8, &
			__state->stdlad[(i__1 = (new__ << 3) - 8) < 80000 && 
			0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c, "std"
			"lad", i__1, "zzdskbsr_", (ftnlen)2483)]);
		moved_(__global_state, dsklds, &__state->c__24, &
			__state->stdskd[(i__1 = new__ * 24 - 24) < 240000 && 
			0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c, "std"
			"skd", i__1, "zzdskbsr_", (ftnlen)2484)]);
		if (failed_(__global_state)) {
		    chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		    return 0;
		}

/*              If the current list is empty, this append operation */
/*              is a no-op. */

		lnkilb_(__global_state, &new__, &__state->btbeg[(i__1 = 
			__state->bindex - 1) < 100 && 0 <= i__1 ? i__1 : 
			s_rnge(&__global_state->f2c, "btbeg", i__1, "zzdskbs"
			"r_", (ftnlen)2495)], __state->stpool);
		__state->btbeg[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btbeg", 
			i__1, "zzdskbsr_", (ftnlen)2496)] = new__;
		s_copy(&__global_state->f2c, __state->status, "RESUME", (
			ftnlen)40, (ftnlen)6);
	    }
	} else if (s_cmp(&__global_state->f2c, __state->status, "ADD TO END", 
		(ftnlen)40, (ftnlen)10) == 0) {

/*           The current segment information should be linked in at */
/*           the tail of the segment list for the current body. */

/*           The only way to get to this task is from the OLD SEGMENTS */
/*           block after suspending that task. */

	    if (lnknfn_(__global_state, __state->stpool) == 0) {
		s_copy(&__global_state->f2c, doing, "ADD TO END", (ftnlen)40, 
			(ftnlen)10);
		s_copy(&__global_state->f2c, urgent, "MAKE ROOM", (ftnlen)40, 
			(ftnlen)9);
		s_copy(&__global_state->f2c, __state->status, "SUSPEND", (
			ftnlen)40, (ftnlen)7);
	    } else {

/*              Allocate a new node in the segment table pool. */

		lnkan_(__global_state, __state->stpool, &new__);
		__state->sthan[(i__1 = new__ - 1) < 10000 && 0 <= i__1 ? i__1 
			: s_rnge(&__global_state->f2c, "sthan", i__1, "zzdsk"
			"bsr_", (ftnlen)2523)] = __state->fthan[(i__2 = 
			__state->findex - 1) < 5000 && 0 <= i__2 ? i__2 : 
			s_rnge(&__global_state->f2c, "fthan", i__2, "zzdskbs"
			"r_", (ftnlen)2523)];

/*              Store the DLA and DSK descriptors for this segment in */
/*              the segment table. */

		movei_(__global_state, dlalds, &__state->c__8, &
			__state->stdlad[(i__1 = (new__ << 3) - 8) < 80000 && 
			0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c, "std"
			"lad", i__1, "zzdskbsr_", (ftnlen)2529)]);
		moved_(__global_state, dsklds, &__state->c__24, &
			__state->stdskd[(i__1 = new__ * 24 - 24) < 240000 && 
			0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c, "std"
			"skd", i__1, "zzdskbsr_", (ftnlen)2530)]);
		if (failed_(__global_state)) {
		    chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
		    return 0;
		}
		if (__state->btbeg[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			i__1 ? i__1 : s_rnge(&__global_state->f2c, "btbeg", 
			i__1, "zzdskbsr_", (ftnlen)2537)] <= 0) {

/*                 This is the first node in the list for this */
/*                 body. */

		    __state->btbeg[(i__1 = __state->bindex - 1) < 100 && 0 <= 
			    i__1 ? i__1 : s_rnge(&__global_state->f2c, "btbeg"
			    , i__1, "zzdskbsr_", (ftnlen)2542)] = new__;
		} else {

/*                 Link the new node to the tail of the list. */

		    tail = -lnkprv_(__global_state, &__state->btbeg[(i__1 = 
			    __state->bindex - 1) < 100 && 0 <= i__1 ? i__1 : 
			    s_rnge(&__global_state->f2c, "btbeg", i__1, "zzd"
			    "skbsr_", (ftnlen)2548)], __state->stpool);
		    lnkila_(__global_state, &tail, &new__, __state->stpool);
		}
		s_copy(&__global_state->f2c, __state->status, "RESUME", (
			ftnlen)40, (ftnlen)6);
	    }
	} else if (s_cmp(&__global_state->f2c, __state->status, "SUSPEND", (
		ftnlen)40, (ftnlen)7) == 0) {

/*           When a task is suspended, the current activity is placed on */
/*           a stack, to be restored later. Two levels are provided, */
/*           since some interrupts can be interrupted by others. */

	    ++__state->top;
	    s_copy(&__global_state->f2c, stack + ((i__1 = __state->top - 1) < 
		    2 && 0 <= i__1 ? i__1 : s_rnge(&__global_state->f2c, 
		    "stack", i__1, "zzdskbsr_", (ftnlen)2565)) * 40, doing, (
		    ftnlen)40, (ftnlen)40);
	    s_copy(&__global_state->f2c, __state->status, urgent, (ftnlen)40, 
		    (ftnlen)40);
	} else if (s_cmp(&__global_state->f2c, __state->status, "RESUME", (
		ftnlen)40, (ftnlen)6) == 0) {
	    s_copy(&__global_state->f2c, __state->status, stack + ((i__1 = 
		    __state->top - 1) < 2 && 0 <= i__1 ? i__1 : s_rnge(&
		    __global_state->f2c, "stack", i__1, "zzdskbsr_", (ftnlen)
		    2570)) * 40, (ftnlen)40, (ftnlen)40);
	    --__state->top;
	}
    }

/*     Can only get here if status is 'HOPELESS', in which case a */
/*     segment was not found. */

    *found = FALSE_;
    chkout_(__global_state, "ZZDSKSNS", (ftnlen)8);
    return 0;
/* $Procedure ZZDSKCHK ( DSK, check for file updates ) */

L_zzdskchk:
/* $ Abstract */

/*     Indicate to a calling routine whether any DSK load or unload */
/*     operations have occurred since the local state counter had */
/*     a particular, caller-supplied value. */

/* $ Disclaimer */

/*     THIS SOFTWARE AND ANY RELATED MATERIALS WERE CREATED BY THE */
/*     CALIFORNIA INSTITUTE OF TECHNOLOGY (CALTECH) UNDER A U.S. */
/*     GOVERNMENT CONTRACT WITH THE NATIONAL AERONAUTICS AND SPACE */
/*     ADMINISTRATION (NASA). THE SOFTWARE IS TECHNOLOGY AND SOFTWARE */
/*     PUBLICLY AVAILABLE UNDER U.S. EXPORT LAWS AND IS PROVIDED "AS-IS" */
/*     TO THE RECIPIENT WITHOUT WARRANTY OF ANY KIND, INCLUDING ANY */
/*     WARRANTIES OF PERFORMANCE OR MERCHANTABILITY OR FITNESS FOR A */
/*     PARTICULAR USE OR PURPOSE (AS SET FORTH IN UNITED STATES UCC */
/*     SECTIONS 2312-2313) OR FOR ANY PURPOSE WHATSOEVER, FOR THE */
/*     SOFTWARE AND RELATED MATERIALS, HOWEVER USED. */

/*     IN NO EVENT SHALL CALTECH, ITS JET PROPULSION LABORATORY, OR NASA */
/*     BE LIABLE FOR ANY DAMAGES AND/OR COSTS, INCLUDING, BUT NOT */
/*     LIMITED TO, INCIDENTAL OR CONSEQUENTIAL DAMAGES OF ANY KIND, */
/*     INCLUDING ECONOMIC DAMAGE OR INJURY TO PROPERTY AND LOST PROFITS, */
/*     REGARDLESS OF WHETHER CALTECH, JPL, OR NASA BE ADVISED, HAVE */
/*     REASON TO KNOW, OR, IN FACT, SHALL KNOW OF THE POSSIBILITY. */

/*     RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF */
/*     THE SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY */
/*     CALTECH AND NASA FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE */
/*     ACTIONS OF RECIPIENT IN THE USE OF THE SOFTWARE. */

/* $ Required_Reading */

/*     DSK */
/*     DAS */

/* $ Keywords */

/*     TOPOGRAPHY */

/* $ Declarations */

/*     INTEGER               USRCTR ( * ) */
/*     LOGICAL               UPDATE */

/* $ Brief_I/O */

/*     Variable  I/O  Description */
/*     --------  ---  -------------------------------------------------- */
/*     USRCTR    I-O  User counter. */
/*     UPDATE     O   Update flag. */

/* $ Detailed_Input */

/*     USRCTR    is, on input, the value of a counter maintained by */
/*               a calling routine. This counter is to be compared to */
/*               a local counter. */

/* $ Detailed_Output */

/*     USRCTR    is, on output, the value of the local DSK load/unload */
/*               counter. */

/*     UPDATE    is a logical flag that is .TRUE. if and only if the */
/*               local DSK load/unload counter differs from the input */
/*               value of USRCTR. If the counters differ, a DSK load or */
/*               unload call has been made since the local counter last */
/*               had the value provided in USRCTR on input. */

/* $ Parameters */

/*     See zzctr.inc. */

/* $ Exceptions */

/*     1)  This routine will fail if the total count of DSK load and */
/*         unload operations exceeds the maximum accommodated by a */
/*         two-integer counter. The maximum count is about 4e19, */
/*         presuming a two-integer counter. */

/* $ Files */

/*     This routine does not access DSK files, but all DSK file */
/*     load and unload operations affect the local counter used */
/*     by this routine. */

/* $ Particulars */

/*     This set of routines maintains a local counter that indicates */
/*     the kernel load status. When a call is made to ZZDSKLSF or */
/*     ZZDSKUSF, the local counter is incremented. Applications can */
/*     compare counter values they save to the current count by */
/*     calling this routine. A mismatch indicates that DSK load or */
/*     unload calls have been made since an application's counter */
/*     was set. */

/*     This type of check presumes the caller's counter is initialized */
/*     by a call to */

/*        ZZCTRUIN */

/*     and is updated only by calls to this routine. */

/*     This routine is used by much of the DSK subsystem to determine */
/*     whether locally buffered information about DSK segments remains */
/*     up to date. */

/* $ Examples */

/*     See usage in ZZDSKBBL. */

/* $ Restrictions */

/*     This routine assumes the number of DSK load and unload operations */
/*     does not exceed the maximum value of a two-integer counter. */

/* $ Literature_References */

/*     None. */

/* $ Author_and_Institution */

/*     N.J. Bachman   (JPL) */
/*     B.V. Semenov   (JPL) */
/*     R.E. Thurman   (JPL) */
/*     I.M. Underwood (JPL) */

/* $ Version */

/* -    SPICELIB Version 1.0.0, 08-FEB-2017 (NJB) */

/*        Updated version info. */

/* -& */
/* $ Index_Entries */

/*     check for changes to set of loaded dsk files */

/* -& */
/* $ Revisions */

/*     None. */

/* -& */
    if (return_(__global_state)) {
	return 0;
    }
    chkin_(__global_state, "ZZDSKCHK", (ftnlen)8);
    zzctrchk_(__global_state, __state->dskctr, usrctr, update);
    chkout_(__global_state, "ZZDSKCHK", (ftnlen)8);
    return 0;
} /* zzdskbsr_ */

/* Subroutine */ int zzdskbsr_(cspice_t* __global_state, char *fname, integer 
	*bodyid, integer *handle, L_fp cmpfun, integer *usrctr, logical *
	update, integer *dladsc, doublereal *dskdsc, logical *found, ftnlen 
	fname_len)
{
    return zzdskbsr_0_(__global_state, 0, fname, bodyid, handle, cmpfun, 
	    usrctr, update, dladsc, dskdsc, found, fname_len);
    }

/* Subroutine */ int zzdsklsf_(cspice_t* __global_state, char *fname, integer 
	*handle, ftnlen fname_len)
{
    return zzdskbsr_0_(__global_state, 1, fname, (integer *)0, handle, (L_fp)
	    0, (integer *)0, (logical *)0, (integer *)0, (doublereal *)0, (
	    logical *)0, fname_len);
    }

/* Subroutine */ int zzdskusf_(cspice_t* __global_state, integer *handle)
{
    return zzdskbsr_0_(__global_state, 2, (char *)0, (integer *)0, handle, (
	    L_fp)0, (integer *)0, (logical *)0, (integer *)0, (doublereal *)0,
	     (logical *)0, (ftnint)0);
    }

/* Subroutine */ int zzdskbss_(cspice_t* __global_state, integer *bodyid)
{
    return zzdskbsr_0_(__global_state, 3, (char *)0, bodyid, (integer *)0, (
	    L_fp)0, (integer *)0, (logical *)0, (integer *)0, (doublereal *)0,
	     (logical *)0, (ftnint)0);
    }

/* Subroutine */ int zzdsksns_(cspice_t* __global_state, L_fp cmpfun, integer 
	*handle, integer *dladsc, doublereal *dskdsc, logical *found)
{
    return zzdskbsr_0_(__global_state, 4, (char *)0, (integer *)0, handle, 
	    cmpfun, (integer *)0, (logical *)0, dladsc, dskdsc, found, (
	    ftnint)0);
    }

/* Subroutine */ int zzdskchk_(cspice_t* __global_state, integer *usrctr, 
	logical *update)
{
    return zzdskbsr_0_(__global_state, 5, (char *)0, (integer *)0, (integer *)
	    0, (L_fp)0, usrctr, update, (integer *)0, (doublereal *)0, (
	    logical *)0, (ftnint)0);
    }

