/**
 * @file intellivue_utils.h
 *
 * Reference:
 * 	Data Export Interface Programming Guide
 * 	IntelliVue Patient Monitor
 * 	MP70
 *
 * 	Philips Reorder Part Number: 451261001426
 *
 * @author Michael Szwaja
 */
//=============================================================================
#ifndef INTELLIVUE_MP70_SRC_INTELLIVUE_UTILS_H_
#define INTELLIVUE_MP70_SRC_INTELLIVUE_UTILS_H_

#include <stdio.h>

/**
 * Converts two byte array to a signed 16 bit integer.
 * @param [in] bytes Pointer to array of bytes
 * @return Returns signed 16 bit integer
 */
int16_t bytes216(uint8_t* bytes);

/**
 * Converts two byte array to a unsigned 16 bit integer.
 * @param [in] bytes Pointer to array of bytes
 * @return Returns unsigned 16 bit integer
 */
uint16_t bytes2u16(uint8_t* bytes);

/**
 * Converts four byte array to a unsigned 32 bit integer.
 * @param [in] bytes Pointer to array of bytes
 * @return Returns unsigned 32 bit integer
 */
uint32_t bytes2u32(uint8_t* bytes);

/**
 * Converts int into two byte array. Byte swap to big endian
 * @param [in] lx to be converted into byte array.
 * @param [in, out] rbuf Pointer to two bytes that represent the int value.
 */
void int22bytes(uint8_t* rbuf, int sx);

/**
 * Converts int into four byte array. Byte swap to big endian.
 * @param [in] lx int to be converted into byte array.
 * @param [in, out] rbuf Pointer to four bytes that represent the int value.
 */
void int24bytes(uint8_t* rbuf, int lx);

/**
 * Merges two byte arrays together into one byte array.
 * array a precedes b in the result array. size of the result is 
 * size of a + the size of b (sa + sb).
 * @param [in, out] pdest Pointer to destination byte array where merge result
 *   is stored.
 * @param [in] arrA Pointer to first byte array 
 * @param [in] size of array a.
 * @param [in] arrB Pointer to second byte array
 * @param [in] size of array b.
 * @return Returns zero for success.
 */
int merge(uint8_t* pdest, uint8_t* arrA, size_t sa, uint8_t* arrB, size_t sb);

#endif
