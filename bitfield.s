	.text
	.file	"bitfield.c"
	.globl	bitfield_set                    # -- Begin function bitfield_set
	.p2align	4, 0x90
	.type	bitfield_set,@function
bitfield_set:                           # @bitfield_set
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %rbp, -16
	movl	%edx, %ebp
	movq	%rsi, %rax
	movq	%rdi, %rbx
	movl	$64, %esi
	movq	%rax, %rdi
	callq	lldiv
	movq	%rdx, %rcx
	movl	$1, %edx
                                        # kill: def $cl killed $cl killed $rcx
	shlq	%cl, %rdx
	testb	%bpl, %bpl
	je	.LBB0_2
# %bb.1:
	orq	%rdx, (%rbx,%rax,8)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.LBB0_2:
	.cfi_def_cfa_offset 32
	notq	%rdx
	andq	%rdx, (%rbx,%rax,8)
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	bitfield_set, .Lfunc_end0-bitfield_set
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_get                    # -- Begin function bitfield_get
	.p2align	4, 0x90
	.type	bitfield_get,@function
bitfield_get:                           # @bitfield_get
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movq	%rsi, %rax
	movq	%rdi, %rbx
	movl	$64, %esi
	movq	%rax, %rdi
	callq	lldiv
	movq	(%rbx,%rax,8), %rax
	btq	%rdx, %rax
	setb	%al
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end1:
	.size	bitfield_get, .Lfunc_end1-bitfield_get
	.cfi_endproc
                                        # -- End function
	.section	.rodata.cst16,"aM",@progbits,16
	.p2align	4                               # -- Begin function bitfield_count
.LCPI2_0:
	.zero	16,85
.LCPI2_1:
	.zero	16,51
.LCPI2_2:
	.zero	16,15
	.text
	.globl	bitfield_count
	.p2align	4, 0x90
	.type	bitfield_count,@function
bitfield_count:                         # @bitfield_count
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	testq	%rsi, %rsi
	je	.LBB2_1
# %bb.2:
	cmpq	$4, %rsi
	jae	.LBB2_4
# %bb.3:
	xorl	%ecx, %ecx
	xorl	%eax, %eax
	jmp	.LBB2_7
.LBB2_1:
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB2_4:
	.cfi_def_cfa_offset 16
	movq	%rsi, %rcx
	andq	$-4, %rcx
	pxor	%xmm8, %xmm8
	xorl	%eax, %eax
	movdqa	.LCPI2_0(%rip), %xmm2           # xmm2 = [85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85]
	movdqa	.LCPI2_1(%rip), %xmm3           # xmm3 = [51,51,51,51,51,51,51,51,51,51,51,51,51,51,51,51]
	movdqa	.LCPI2_2(%rip), %xmm5           # xmm5 = [15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15]
	pxor	%xmm4, %xmm4
	pxor	%xmm1, %xmm1
	.p2align	4, 0x90
.LBB2_5:                                # =>This Inner Loop Header: Depth=1
	movdqu	(%rdi,%rax,8), %xmm0
	movdqu	16(%rdi,%rax,8), %xmm6
	movdqa	%xmm0, %xmm7
	psrlw	$1, %xmm7
	pand	%xmm2, %xmm7
	psubb	%xmm7, %xmm0
	movdqa	%xmm0, %xmm7
	pand	%xmm3, %xmm7
	psrlw	$2, %xmm0
	pand	%xmm3, %xmm0
	paddb	%xmm7, %xmm0
	movdqa	%xmm0, %xmm7
	psrlw	$4, %xmm7
	paddb	%xmm0, %xmm7
	pand	%xmm5, %xmm7
	psadbw	%xmm8, %xmm7
	paddq	%xmm7, %xmm4
	movdqa	%xmm6, %xmm0
	psrlw	$1, %xmm0
	pand	%xmm2, %xmm0
	psubb	%xmm0, %xmm6
	movdqa	%xmm6, %xmm0
	pand	%xmm3, %xmm0
	psrlw	$2, %xmm6
	pand	%xmm3, %xmm6
	paddb	%xmm0, %xmm6
	movdqa	%xmm6, %xmm0
	psrlw	$4, %xmm0
	paddb	%xmm6, %xmm0
	pand	%xmm5, %xmm0
	psadbw	%xmm8, %xmm0
	paddq	%xmm0, %xmm1
	addq	$4, %rax
	cmpq	%rax, %rcx
	jne	.LBB2_5
# %bb.6:
	paddq	%xmm4, %xmm1
	pshufd	$238, %xmm1, %xmm0              # xmm0 = xmm1[2,3,2,3]
	paddq	%xmm1, %xmm0
	movq	%xmm0, %rax
	cmpq	%rsi, %rcx
	je	.LBB2_9
.LBB2_7:
	movabsq	$6148914691236517205, %r8       # imm = 0x5555555555555555
	movabsq	$3689348814741910323, %r11      # imm = 0x3333333333333333
	movabsq	$1085102592571150095, %r9       # imm = 0xF0F0F0F0F0F0F0F
	movabsq	$72340172838076673, %r10        # imm = 0x101010101010101
	.p2align	4, 0x90
.LBB2_8:                                # =>This Inner Loop Header: Depth=1
	movq	(%rdi,%rcx,8), %rdx
	movq	%rdx, %rbx
	shrq	%rbx
	andq	%r8, %rbx
	subq	%rbx, %rdx
	movq	%rdx, %rbx
	andq	%r11, %rbx
	shrq	$2, %rdx
	andq	%r11, %rdx
	addq	%rbx, %rdx
	movq	%rdx, %rbx
	shrq	$4, %rbx
	addq	%rdx, %rbx
	andq	%r9, %rbx
	imulq	%r10, %rbx
	shrq	$56, %rbx
	addq	%rbx, %rax
	addq	$1, %rcx
	cmpq	%rcx, %rsi
	jne	.LBB2_8
.LBB2_9:
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end2:
	.size	bitfield_count, .Lfunc_end2-bitfield_count
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_create                 # -- Begin function bitfield_create
	.p2align	4, 0x90
	.type	bitfield_create,@function
bitfield_create:                        # @bitfield_create
	.cfi_startproc
# %bb.0:
	pushq	%r14
	.cfi_def_cfa_offset 16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	pushq	%rax
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -24
	.cfi_offset %r14, -16
	addq	$-1, %rdi
	shrq	$6, %rdi
	leaq	8(,%rdi,8), %r14
	movq	%r14, %rdi
	callq	malloc
	movq	%rax, %rbx
	movq	%rax, %rdi
	xorl	%esi, %esi
	movq	%r14, %rdx
	callq	memset@PLT
	movq	%rbx, %rax
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end3:
	.size	bitfield_create, .Lfunc_end3-bitfield_create
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_free                   # -- Begin function bitfield_free
	.p2align	4, 0x90
	.type	bitfield_free,@function
bitfield_free:                          # @bitfield_free
	.cfi_startproc
# %bb.0:
	jmp	free                            # TAILCALL
.Lfunc_end4:
	.size	bitfield_free, .Lfunc_end4-bitfield_free
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_or                     # -- Begin function bitfield_or
	.p2align	4, 0x90
	.type	bitfield_or,@function
bitfield_or:                            # @bitfield_or
	.cfi_startproc
# %bb.0:
	testq	%rdx, %rdx
	je	.LBB5_16
# %bb.1:
	cmpq	$4, %rdx
	jb	.LBB5_2
# %bb.3:
	leaq	(%rsi,%rdx,8), %rax
	cmpq	%rdi, %rax
	jbe	.LBB5_6
# %bb.4:
	leaq	(%rdi,%rdx,8), %rax
	cmpq	%rsi, %rax
	jbe	.LBB5_6
.LBB5_2:
	xorl	%r10d, %r10d
.LBB5_12:
	movq	%r10, %r8
	notq	%r8
	addq	%rdx, %r8
	movq	%rdx, %rcx
	andq	$3, %rcx
	je	.LBB5_14
	.p2align	4, 0x90
.LBB5_13:                               # =>This Inner Loop Header: Depth=1
	movq	(%rsi,%r10,8), %rax
	orq	%rax, (%rdi,%r10,8)
	addq	$1, %r10
	addq	$-1, %rcx
	jne	.LBB5_13
.LBB5_14:
	cmpq	$3, %r8
	jb	.LBB5_16
	.p2align	4, 0x90
.LBB5_15:                               # =>This Inner Loop Header: Depth=1
	movq	(%rsi,%r10,8), %rax
	orq	%rax, (%rdi,%r10,8)
	movq	8(%rsi,%r10,8), %rax
	orq	%rax, 8(%rdi,%r10,8)
	movq	16(%rsi,%r10,8), %rax
	orq	%rax, 16(%rdi,%r10,8)
	movq	24(%rsi,%r10,8), %rax
	orq	%rax, 24(%rdi,%r10,8)
	addq	$4, %r10
	cmpq	%r10, %rdx
	jne	.LBB5_15
	jmp	.LBB5_16
.LBB5_6:
	movq	%rdx, %r10
	andq	$-4, %r10
	leaq	-4(%r10), %rcx
	movq	%rcx, %r8
	shrq	$2, %r8
	addq	$1, %r8
	testq	%rcx, %rcx
	je	.LBB5_17
# %bb.7:
	movq	%r8, %r9
	andq	$-2, %r9
	negq	%r9
	xorl	%ecx, %ecx
	.p2align	4, 0x90
.LBB5_8:                                # =>This Inner Loop Header: Depth=1
	movups	(%rsi,%rcx,8), %xmm0
	movups	16(%rsi,%rcx,8), %xmm1
	movups	(%rdi,%rcx,8), %xmm2
	orps	%xmm0, %xmm2
	movups	16(%rdi,%rcx,8), %xmm0
	orps	%xmm1, %xmm0
	movups	32(%rdi,%rcx,8), %xmm1
	movups	48(%rdi,%rcx,8), %xmm3
	movups	%xmm2, (%rdi,%rcx,8)
	movups	%xmm0, 16(%rdi,%rcx,8)
	movups	32(%rsi,%rcx,8), %xmm0
	orps	%xmm1, %xmm0
	movups	48(%rsi,%rcx,8), %xmm1
	orps	%xmm3, %xmm1
	movups	%xmm0, 32(%rdi,%rcx,8)
	movups	%xmm1, 48(%rdi,%rcx,8)
	addq	$8, %rcx
	addq	$2, %r9
	jne	.LBB5_8
# %bb.9:
	testb	$1, %r8b
	je	.LBB5_11
.LBB5_10:
	movups	(%rsi,%rcx,8), %xmm0
	movups	16(%rsi,%rcx,8), %xmm1
	movups	(%rdi,%rcx,8), %xmm2
	orps	%xmm0, %xmm2
	movups	16(%rdi,%rcx,8), %xmm0
	orps	%xmm1, %xmm0
	movups	%xmm2, (%rdi,%rcx,8)
	movups	%xmm0, 16(%rdi,%rcx,8)
.LBB5_11:
	cmpq	%rdx, %r10
	jne	.LBB5_12
.LBB5_16:
	retq
.LBB5_17:
	xorl	%ecx, %ecx
	testb	$1, %r8b
	jne	.LBB5_10
	jmp	.LBB5_11
.Lfunc_end5:
	.size	bitfield_or, .Lfunc_end5-bitfield_or
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_and                    # -- Begin function bitfield_and
	.p2align	4, 0x90
	.type	bitfield_and,@function
bitfield_and:                           # @bitfield_and
	.cfi_startproc
# %bb.0:
	testq	%rdx, %rdx
	je	.LBB6_16
# %bb.1:
	cmpq	$4, %rdx
	jb	.LBB6_2
# %bb.3:
	leaq	(%rsi,%rdx,8), %rax
	cmpq	%rdi, %rax
	jbe	.LBB6_6
# %bb.4:
	leaq	(%rdi,%rdx,8), %rax
	cmpq	%rsi, %rax
	jbe	.LBB6_6
.LBB6_2:
	xorl	%r10d, %r10d
.LBB6_12:
	movq	%r10, %r8
	notq	%r8
	addq	%rdx, %r8
	movq	%rdx, %rcx
	andq	$3, %rcx
	je	.LBB6_14
	.p2align	4, 0x90
.LBB6_13:                               # =>This Inner Loop Header: Depth=1
	movq	(%rsi,%r10,8), %rax
	andq	%rax, (%rdi,%r10,8)
	addq	$1, %r10
	addq	$-1, %rcx
	jne	.LBB6_13
.LBB6_14:
	cmpq	$3, %r8
	jb	.LBB6_16
	.p2align	4, 0x90
.LBB6_15:                               # =>This Inner Loop Header: Depth=1
	movq	(%rsi,%r10,8), %rax
	andq	%rax, (%rdi,%r10,8)
	movq	8(%rsi,%r10,8), %rax
	andq	%rax, 8(%rdi,%r10,8)
	movq	16(%rsi,%r10,8), %rax
	andq	%rax, 16(%rdi,%r10,8)
	movq	24(%rsi,%r10,8), %rax
	andq	%rax, 24(%rdi,%r10,8)
	addq	$4, %r10
	cmpq	%r10, %rdx
	jne	.LBB6_15
	jmp	.LBB6_16
.LBB6_6:
	movq	%rdx, %r10
	andq	$-4, %r10
	leaq	-4(%r10), %rcx
	movq	%rcx, %r8
	shrq	$2, %r8
	addq	$1, %r8
	testq	%rcx, %rcx
	je	.LBB6_17
# %bb.7:
	movq	%r8, %r9
	andq	$-2, %r9
	negq	%r9
	xorl	%ecx, %ecx
	.p2align	4, 0x90
.LBB6_8:                                # =>This Inner Loop Header: Depth=1
	movups	(%rsi,%rcx,8), %xmm0
	movups	16(%rsi,%rcx,8), %xmm1
	movups	(%rdi,%rcx,8), %xmm2
	andps	%xmm0, %xmm2
	movups	16(%rdi,%rcx,8), %xmm0
	andps	%xmm1, %xmm0
	movups	32(%rdi,%rcx,8), %xmm1
	movups	48(%rdi,%rcx,8), %xmm3
	movups	%xmm2, (%rdi,%rcx,8)
	movups	%xmm0, 16(%rdi,%rcx,8)
	movups	32(%rsi,%rcx,8), %xmm0
	andps	%xmm1, %xmm0
	movups	48(%rsi,%rcx,8), %xmm1
	andps	%xmm3, %xmm1
	movups	%xmm0, 32(%rdi,%rcx,8)
	movups	%xmm1, 48(%rdi,%rcx,8)
	addq	$8, %rcx
	addq	$2, %r9
	jne	.LBB6_8
# %bb.9:
	testb	$1, %r8b
	je	.LBB6_11
.LBB6_10:
	movups	(%rsi,%rcx,8), %xmm0
	movups	16(%rsi,%rcx,8), %xmm1
	movups	(%rdi,%rcx,8), %xmm2
	andps	%xmm0, %xmm2
	movups	16(%rdi,%rcx,8), %xmm0
	andps	%xmm1, %xmm0
	movups	%xmm2, (%rdi,%rcx,8)
	movups	%xmm0, 16(%rdi,%rcx,8)
.LBB6_11:
	cmpq	%rdx, %r10
	jne	.LBB6_12
.LBB6_16:
	retq
.LBB6_17:
	xorl	%ecx, %ecx
	testb	$1, %r8b
	jne	.LBB6_10
	jmp	.LBB6_11
.Lfunc_end6:
	.size	bitfield_and, .Lfunc_end6-bitfield_and
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_not                    # -- Begin function bitfield_not
	.p2align	4, 0x90
	.type	bitfield_not,@function
bitfield_not:                           # @bitfield_not
	.cfi_startproc
# %bb.0:
	movq	%rsi, %rcx
	leaq	-1(%rsi), %rax
	movq	%rax, %r8
	shrq	$6, %r8
	leaq	1(%r8), %r10
	cmpq	$192, %rax
	jae	.LBB7_3
# %bb.1:
	xorl	%esi, %esi
	jmp	.LBB7_2
.LBB7_3:
	movq	%r10, %rsi
	andq	$-4, %rsi
	leaq	-4(%rsi), %rax
	movq	%rax, %r9
	shrq	$2, %r9
	addq	$1, %r9
	testq	%rax, %rax
	je	.LBB7_4
# %bb.5:
	movq	%r9, %rdx
	andq	$-2, %rdx
	negq	%rdx
	xorl	%eax, %eax
	pcmpeqd	%xmm0, %xmm0
	.p2align	4, 0x90
.LBB7_6:                                # =>This Inner Loop Header: Depth=1
	movdqu	(%rdi,%rax,8), %xmm1
	movdqu	16(%rdi,%rax,8), %xmm2
	movdqu	32(%rdi,%rax,8), %xmm3
	movdqu	48(%rdi,%rax,8), %xmm4
	pxor	%xmm0, %xmm1
	pxor	%xmm0, %xmm2
	movdqu	%xmm1, (%rdi,%rax,8)
	movdqu	%xmm2, 16(%rdi,%rax,8)
	pxor	%xmm0, %xmm3
	pxor	%xmm0, %xmm4
	movdqu	%xmm3, 32(%rdi,%rax,8)
	movdqu	%xmm4, 48(%rdi,%rax,8)
	addq	$8, %rax
	addq	$2, %rdx
	jne	.LBB7_6
# %bb.7:
	testb	$1, %r9b
	jne	.LBB7_8
	jmp	.LBB7_9
.LBB7_4:
	xorl	%eax, %eax
	testb	$1, %r9b
	je	.LBB7_9
.LBB7_8:
	movdqu	(%rdi,%rax,8), %xmm0
	movdqu	16(%rdi,%rax,8), %xmm1
	pcmpeqd	%xmm2, %xmm2
	pxor	%xmm2, %xmm0
	pxor	%xmm2, %xmm1
	movdqu	%xmm0, (%rdi,%rax,8)
	movdqu	%xmm1, 16(%rdi,%rax,8)
	jmp	.LBB7_9
.LBB7_2:
	notq	(%rdi,%rsi,8)
	addq	$1, %rsi
.LBB7_9:
	cmpq	%rsi, %r10
	jne	.LBB7_2
# %bb.10:
	movq	$-1, %rax
                                        # kill: def $cl killed $cl killed $rcx
	shlq	%cl, %rax
	notq	%rax
	andq	%rax, (%rdi,%r8,8)
	retq
.Lfunc_end7:
	.size	bitfield_not, .Lfunc_end7-bitfield_not
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_xor                    # -- Begin function bitfield_xor
	.p2align	4, 0x90
	.type	bitfield_xor,@function
bitfield_xor:                           # @bitfield_xor
	.cfi_startproc
# %bb.0:
	testq	%rdx, %rdx
	je	.LBB8_16
# %bb.1:
	cmpq	$4, %rdx
	jb	.LBB8_2
# %bb.3:
	leaq	(%rsi,%rdx,8), %rax
	cmpq	%rdi, %rax
	jbe	.LBB8_6
# %bb.4:
	leaq	(%rdi,%rdx,8), %rax
	cmpq	%rsi, %rax
	jbe	.LBB8_6
.LBB8_2:
	xorl	%r10d, %r10d
.LBB8_12:
	movq	%r10, %r8
	notq	%r8
	addq	%rdx, %r8
	movq	%rdx, %rcx
	andq	$3, %rcx
	je	.LBB8_14
	.p2align	4, 0x90
.LBB8_13:                               # =>This Inner Loop Header: Depth=1
	movq	(%rsi,%r10,8), %rax
	xorq	%rax, (%rdi,%r10,8)
	addq	$1, %r10
	addq	$-1, %rcx
	jne	.LBB8_13
.LBB8_14:
	cmpq	$3, %r8
	jb	.LBB8_16
	.p2align	4, 0x90
.LBB8_15:                               # =>This Inner Loop Header: Depth=1
	movq	(%rsi,%r10,8), %rax
	xorq	%rax, (%rdi,%r10,8)
	movq	8(%rsi,%r10,8), %rax
	xorq	%rax, 8(%rdi,%r10,8)
	movq	16(%rsi,%r10,8), %rax
	xorq	%rax, 16(%rdi,%r10,8)
	movq	24(%rsi,%r10,8), %rax
	xorq	%rax, 24(%rdi,%r10,8)
	addq	$4, %r10
	cmpq	%r10, %rdx
	jne	.LBB8_15
	jmp	.LBB8_16
.LBB8_6:
	movq	%rdx, %r10
	andq	$-4, %r10
	leaq	-4(%r10), %rcx
	movq	%rcx, %r8
	shrq	$2, %r8
	addq	$1, %r8
	testq	%rcx, %rcx
	je	.LBB8_17
# %bb.7:
	movq	%r8, %r9
	andq	$-2, %r9
	negq	%r9
	xorl	%ecx, %ecx
	.p2align	4, 0x90
.LBB8_8:                                # =>This Inner Loop Header: Depth=1
	movups	(%rsi,%rcx,8), %xmm0
	movups	16(%rsi,%rcx,8), %xmm1
	movups	(%rdi,%rcx,8), %xmm2
	xorps	%xmm0, %xmm2
	movups	16(%rdi,%rcx,8), %xmm0
	xorps	%xmm1, %xmm0
	movups	32(%rdi,%rcx,8), %xmm1
	movups	48(%rdi,%rcx,8), %xmm3
	movups	%xmm2, (%rdi,%rcx,8)
	movups	%xmm0, 16(%rdi,%rcx,8)
	movups	32(%rsi,%rcx,8), %xmm0
	xorps	%xmm1, %xmm0
	movups	48(%rsi,%rcx,8), %xmm1
	xorps	%xmm3, %xmm1
	movups	%xmm0, 32(%rdi,%rcx,8)
	movups	%xmm1, 48(%rdi,%rcx,8)
	addq	$8, %rcx
	addq	$2, %r9
	jne	.LBB8_8
# %bb.9:
	testb	$1, %r8b
	je	.LBB8_11
.LBB8_10:
	movups	(%rsi,%rcx,8), %xmm0
	movups	16(%rsi,%rcx,8), %xmm1
	movups	(%rdi,%rcx,8), %xmm2
	xorps	%xmm0, %xmm2
	movups	16(%rdi,%rcx,8), %xmm0
	xorps	%xmm1, %xmm0
	movups	%xmm2, (%rdi,%rcx,8)
	movups	%xmm0, 16(%rdi,%rcx,8)
.LBB8_11:
	cmpq	%rdx, %r10
	jne	.LBB8_12
.LBB8_16:
	retq
.LBB8_17:
	xorl	%ecx, %ecx
	testb	$1, %r8b
	jne	.LBB8_10
	jmp	.LBB8_11
.Lfunc_end8:
	.size	bitfield_xor, .Lfunc_end8-bitfield_xor
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_findfirst_true         # -- Begin function bitfield_findfirst_true
	.p2align	4, 0x90
	.type	bitfield_findfirst_true,@function
bitfield_findfirst_true:                # @bitfield_findfirst_true
	.cfi_startproc
# %bb.0:
	movq	$-1, %rax
	testq	%rsi, %rsi
	je	.LBB9_10
# %bb.1:
	xorl	%r8d, %r8d
	xorl	%r10d, %r10d
	xorl	%edx, %edx
	jmp	.LBB9_2
	.p2align	4, 0x90
.LBB9_9:                                #   in Loop: Header=BB9_2 Depth=1
	addq	$1, %rdx
	addq	$64, %r10
	cmpq	%rdx, %rsi
	je	.LBB9_10
.LBB9_2:                                # =>This Inner Loop Header: Depth=1
	movq	(%rdi,%rdx,8), %r9
	testq	%r9, %r9
	je	.LBB9_9
# %bb.3:                                #   in Loop: Header=BB9_2 Depth=1
	movl	%r9d, %ecx
	testl	%r9d, %r9d
	jne	.LBB9_5
# %bb.4:                                #   in Loop: Header=BB9_2 Depth=1
	movl	4(%rdi,%rdx,8), %ecx
.LBB9_5:                                #   in Loop: Header=BB9_2 Depth=1
	testb	$1, %cl
	jne	.LBB9_8
# %bb.6:                                #   in Loop: Header=BB9_2 Depth=1
	testb	$2, %cl
	jne	.LBB9_7
# %bb.11:                               #   in Loop: Header=BB9_2 Depth=1
	testb	$4, %cl
	jne	.LBB9_12
# %bb.13:                               #   in Loop: Header=BB9_2 Depth=1
	testb	$8, %cl
	jne	.LBB9_14
# %bb.15:                               #   in Loop: Header=BB9_2 Depth=1
	testb	$16, %cl
	jne	.LBB9_16
# %bb.17:                               #   in Loop: Header=BB9_2 Depth=1
	testb	$32, %cl
	jne	.LBB9_18
# %bb.19:                               #   in Loop: Header=BB9_2 Depth=1
	testb	$64, %cl
	jne	.LBB9_20
# %bb.21:                               #   in Loop: Header=BB9_2 Depth=1
	testb	%cl, %cl
	js	.LBB9_22
# %bb.23:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$256, %ecx                      # imm = 0x100
	jne	.LBB9_24
# %bb.25:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$512, %ecx                      # imm = 0x200
	jne	.LBB9_26
# %bb.27:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$1024, %ecx                     # imm = 0x400
	jne	.LBB9_28
# %bb.29:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$2048, %ecx                     # imm = 0x800
	jne	.LBB9_30
# %bb.31:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$4096, %ecx                     # imm = 0x1000
	jne	.LBB9_32
# %bb.33:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$8192, %ecx                     # imm = 0x2000
	jne	.LBB9_34
# %bb.35:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$16384, %ecx                    # imm = 0x4000
	jne	.LBB9_36
# %bb.37:                               #   in Loop: Header=BB9_2 Depth=1
	testw	%cx, %cx
	js	.LBB9_38
# %bb.39:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$65536, %ecx                    # imm = 0x10000
	jne	.LBB9_40
# %bb.41:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$131072, %ecx                   # imm = 0x20000
	jne	.LBB9_42
# %bb.43:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$262144, %ecx                   # imm = 0x40000
	jne	.LBB9_44
# %bb.45:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$524288, %ecx                   # imm = 0x80000
	jne	.LBB9_46
# %bb.47:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$1048576, %ecx                  # imm = 0x100000
	jne	.LBB9_48
# %bb.49:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$2097152, %ecx                  # imm = 0x200000
	jne	.LBB9_50
# %bb.51:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$4194304, %ecx                  # imm = 0x400000
	jne	.LBB9_52
# %bb.53:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$8388608, %ecx                  # imm = 0x800000
	jne	.LBB9_54
# %bb.55:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$16777216, %ecx                 # imm = 0x1000000
	jne	.LBB9_56
# %bb.57:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$33554432, %ecx                 # imm = 0x2000000
	jne	.LBB9_58
# %bb.59:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$67108864, %ecx                 # imm = 0x4000000
	jne	.LBB9_60
# %bb.61:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$134217728, %ecx                # imm = 0x8000000
	jne	.LBB9_62
# %bb.63:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$268435456, %ecx                # imm = 0x10000000
	jne	.LBB9_64
# %bb.65:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$536870912, %ecx                # imm = 0x20000000
	jne	.LBB9_66
# %bb.67:                               #   in Loop: Header=BB9_2 Depth=1
	testl	$1073741824, %ecx               # imm = 0x40000000
	jne	.LBB9_68
# %bb.69:                               #   in Loop: Header=BB9_2 Depth=1
	testl	%ecx, %ecx
	jns	.LBB9_9
# %bb.70:
	movl	$31, %r8d
	jmp	.LBB9_8
.LBB9_10:
	retq
.LBB9_7:
	movl	$1, %r8d
	jmp	.LBB9_8
.LBB9_12:
	movl	$2, %r8d
	jmp	.LBB9_8
.LBB9_14:
	movl	$3, %r8d
	jmp	.LBB9_8
.LBB9_16:
	movl	$4, %r8d
	jmp	.LBB9_8
.LBB9_18:
	movl	$5, %r8d
	jmp	.LBB9_8
.LBB9_20:
	movl	$6, %r8d
	jmp	.LBB9_8
.LBB9_22:
	movl	$7, %r8d
	jmp	.LBB9_8
.LBB9_24:
	movl	$8, %r8d
	jmp	.LBB9_8
.LBB9_26:
	movl	$9, %r8d
	jmp	.LBB9_8
.LBB9_28:
	movl	$10, %r8d
	jmp	.LBB9_8
.LBB9_30:
	movl	$11, %r8d
	jmp	.LBB9_8
.LBB9_32:
	movl	$12, %r8d
	jmp	.LBB9_8
.LBB9_34:
	movl	$13, %r8d
	jmp	.LBB9_8
.LBB9_36:
	movl	$14, %r8d
	jmp	.LBB9_8
.LBB9_38:
	movl	$15, %r8d
	jmp	.LBB9_8
.LBB9_40:
	movl	$16, %r8d
	jmp	.LBB9_8
.LBB9_42:
	movl	$17, %r8d
	jmp	.LBB9_8
.LBB9_44:
	movl	$18, %r8d
	jmp	.LBB9_8
.LBB9_46:
	movl	$19, %r8d
	jmp	.LBB9_8
.LBB9_48:
	movl	$20, %r8d
	jmp	.LBB9_8
.LBB9_50:
	movl	$21, %r8d
	jmp	.LBB9_8
.LBB9_52:
	movl	$22, %r8d
	jmp	.LBB9_8
.LBB9_54:
	movl	$23, %r8d
	jmp	.LBB9_8
.LBB9_56:
	movl	$24, %r8d
	jmp	.LBB9_8
.LBB9_58:
	movl	$25, %r8d
	jmp	.LBB9_8
.LBB9_60:
	movl	$26, %r8d
	jmp	.LBB9_8
.LBB9_62:
	movl	$27, %r8d
	jmp	.LBB9_8
.LBB9_64:
	movl	$28, %r8d
	jmp	.LBB9_8
.LBB9_66:
	movl	$29, %r8d
	jmp	.LBB9_8
.LBB9_68:
	movl	$30, %r8d
.LBB9_8:
	movl	%r9d, %ecx
	xorl	%eax, %eax
	addq	%rcx, %r10
	sete	%al
	shlq	$5, %rax
	orq	%r8, %rax
	retq
.Lfunc_end9:
	.size	bitfield_findfirst_true, .Lfunc_end9-bitfield_findfirst_true
	.cfi_endproc
                                        # -- End function
	.globl	bitfield_show                   # -- Begin function bitfield_show
	.p2align	4, 0x90
	.type	bitfield_show,@function
bitfield_show:                          # @bitfield_show
	.cfi_startproc
# %bb.0:
	pushq	%r15
	.cfi_def_cfa_offset 16
	pushq	%r14
	.cfi_def_cfa_offset 24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	.cfi_offset %r15, -16
	testq	%rsi, %rsi
	je	.LBB10_3
# %bb.1:
	movq	%rsi, %r15
	movq	%rdi, %r14
	xorl	%ebx, %ebx
	.p2align	4, 0x90
.LBB10_2:                               # =>This Inner Loop Header: Depth=1
	movl	$64, %esi
	movq	%rbx, %rdi
	callq	lldiv
	movq	(%r14,%rax,8), %rax
	btq	%rdx, %rax
	movl	$49, %edi
	adcl	$-1, %edi
	callq	putchar@PLT
	addq	$1, %rbx
	cmpq	%rbx, %r15
	jne	.LBB10_2
.LBB10_3:
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end10:
	.size	bitfield_show, .Lfunc_end10-bitfield_show
	.cfi_endproc
                                        # -- End function
	.ident	"Ubuntu clang version 12.0.0-3ubuntu1~20.04.4"
	.section	".note.GNU-stack","",@progbits
	.addrsig
