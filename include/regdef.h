// SPDX-License-Identifier: GPL-3.0-or-later
// This was taken from newlib, but I don't think there's anything actually copyrightable here.

#ifndef REGDEF_H
#define REGDEF_H

// MIPS registers.
#define zero	$0
#define at	$at
#define v0	$2
#define v1	$3
#define a0	$4
#define a1	$5
#define a2	$6
#define a3	$7
#define t0	$8
#define t1	$9
#define t2	$10
#define t3	$11
#define t4	$12
#define t5	$13
#define t6	$14
#define t7	$15
#define s0	$16
#define s1	$17
#define s2	$18
#define s3	$19
#define s4	$20
#define s5	$21
#define s6	$22
#define s7	$23
#define t8	$24
#define t9	$25
#define k0	$26
#define k1	$27
#define gp	$gp
#define sp	$sp
#define fp	$fp
#define ra	$ra
#define pc	$pc

// MIPS Coprocessor 0 registers.
#define BadVAddr $8
#define Status	 $12
#define Cause	 $13
#define EPC	 $14
#define	PRid	 $15

#endif // REGDEF_H
