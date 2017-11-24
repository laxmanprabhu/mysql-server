/*****************************************************************************

Copyright (c) 2016, 2017 Oracle and/or its affiliates. All Rights Reserved.

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Suite 500, Boston, MA 02110-1335 USA

*****************************************************************************/
#ifndef lob0inf_h
#define lob0inf_h

#include "fut0lst.h"
#include "lob0lob.h"
#include "mtr0mtr.h"
#include "trx0trx.h"

namespace lob {

/** Insert a large object (LOB) into the system.
@param[in]	ctx	the B-tree context for this LOB operation.
@param[in]	trx	transaction doing the insertion.
@param[in,out]	ref	the LOB reference.
@param[in]	field	the LOB field.
@param[in]	field_j	the LOB field index in big rec vector.
@return DB_SUCCESS on success, error code on failure.*/
dberr_t
insert(
	InsertContext*		ctx,
	trx_t*			trx,
	ref_t&			ref,
	big_rec_field_t*	field,
	ulint			field_j);

/** Insert a compressed large object (LOB) into the system.
@param[in]	ctx	the B-tree context for this LOB operation.
@param[in]	trx	transaction doing the insertion.
@param[in,out]	ref	the LOB reference.
@param[in]	field	the LOB field.
@param[in]	field_j	the LOB field index in big rec vector.
@return DB_SUCCESS on success, error code on failure.*/
dberr_t
z_insert(
	InsertContext*		ctx,
	trx_t*			trx,
	ref_t&			ref,
	big_rec_field_t*	field,
	ulint			field_j);

/** Fetch a large object (LOB) from the system.
@param[in]  ctx    the read context information.
@param[in]  ref    the LOB reference identifying the LOB.
@param[in]  offset read the LOB from the given offset.
@param[in]  len    the length of LOB data that needs to be fetched.
@param[out] buf    the output buffer (owned by caller) of minimum len bytes.
@return the amount of data (in bytes) that was actually read. */
ulint read(
	ReadContext*	ctx,
	ref_t		ref,
	ulint		offset,
	ulint		len,
	byte*		buf);

/** Fetch a compressed large object (ZLOB) from the system.
@param[in] ctx    the read context information.
@param[in] ref    the LOB reference identifying the LOB.
@param[in] offset read the LOB from the given offset.
@param[in] len    the length of LOB data that needs to be fetched.
@param[out] buf   the output buffer (owned by caller) of minimum len bytes.
@return the amount of data (in bytes) that was actually read. */
ulint z_read(
	lob::ReadContext*	ctx,
	lob::ref_t		ref,
	ulint			offset,
	ulint			len,
	byte*			buf);

/** Purge an LOB (either of compressed or uncompressed).
@param[in]	ctx		the delete operation context information.
@param[in]	index		clustered index in which LOB is present
@param[in]	trxid		the transaction that is being purged.
@param[in]	undo_no		during rollback to savepoint, purge only upto
				this undo number.
@param[in]	ref		reference to LOB that is purged.
@param[in]	rec_type	undo record type.*/
void
purge(
	lob::DeleteContext*	ctx,
	dict_index_t*		index,
	trx_id_t		trxid,
	undo_no_t		undo_no,
	lob::ref_t		ref,
	ulint			rec_type);

/** Print information about the given LOB.
@param[in]  trx  the current transaction.
@param[in]  index  the clust index that contains the LOB.
@param[in]  out    the output stream into which LOB info is printed.
@param[in]  ref    the LOB reference
@param[in]  fatal  if true assert at end of function. */
void
print(
	trx_t*		trx,
	dict_index_t*	index,
	std::ostream&	out,
	ref_t		ref,
	bool		fatal);

/** Print information about the given compressed lob. */
dberr_t
z_print_info(
	const dict_index_t*	index,
	const lob::ref_t&	ref,
	std::ostream&		out);

/** Update a portion of the given LOB.
@param[in] trx       the transaction that is doing the modification.
@param[in] index     the clustered index containing the LOB.
@param[in] upd       update vector
@param[in] field_no  the LOB field number
@return DB_SUCCESS on success, error code on failure. */
dberr_t update(trx_t* trx, dict_index_t* index, const upd_t* upd,
               ulint field_no);

/** Update a portion of the given LOB.
@param[in] trx       the transaction that is doing the modification.
@param[in] index     the clustered index containing the LOB.
@param[in] upd       update vector
@param[in] field_no  the LOB field number
@return DB_SUCCESS on success, error code on failure. */
dberr_t z_update(trx_t* trx, dict_index_t* index, const upd_t* upd,
                 ulint field_no);

}  // namespace lob

#endif  // lob0inf_h
