/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "places.h"

bool_t
xdr_location (XDR *xdrs, location *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->state, 4,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->city, 50,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->latitude))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->longitude))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_clientArg (XDR *xdrs, clientArg *objp)
{
	register int32_t *buf;

	 if (!xdr_string (xdrs, &objp->city, ~0))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->state, ~0))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_airportInfo (XDR *xdrs, airportInfo *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->code, 4,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->name, 50,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->latitude))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->longitude))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->distance))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_placesResults (XDR *xdrs, placesResults *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_location (xdrs, &objp->location))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->airports, 5,
		sizeof (airportInfo), (xdrproc_t) xdr_airportInfo))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_placesRet (XDR *xdrs, placesRet *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->err))
		 return FALSE;
	switch (objp->err) {
	case 0:
		 if (!xdr_placesResults (xdrs, &objp->placesRet_u.results))
			 return FALSE;
		break;
	default:
		break;
	}
	return TRUE;
}
