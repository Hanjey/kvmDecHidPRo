#ifndef KVM_UNIFDEF_H
#define KVM_UNIFDEF_H

#ifdef __i386__
#ifndef CONFIG_X86_32
#define CONFIG_X86_32 1
#endif
#endif

#ifdef __x86_64__
#ifndef CONFIG_X86_64
#define CONFIG_X86_64 1
#endif
#endif

#if defined(__i386__) || defined (__x86_64__)
#ifndef CONFIG_X86
#define CONFIG_X86 1
#endif
#endif

#ifdef __PPC__
#ifndef CONFIG_PPC
#define CONFIG_PPC 1
#endif
#endif

#ifdef __s390__
#ifndef CONFIG_S390
#define CONFIG_S390 1
#endif
#endif

#endif
#ifndef _UAPI__LINUX_KVM_PARA_H
#define _UAPI__LINUX_KVM_PARA_H

/*
 * This header file provides a method for making a hypercall to the host
 * Architectures should define:
 * - kvm_hypercall0, kvm_hypercall1...
 * - kvm_arch_para_features
 * - kvm_para_available
 */

/* Return values for hypercalls */
#define KVM_ENOSYS		1000
#define KVM_EFAULT		EFAULT
#define KVM_E2BIG		E2BIG
#define KVM_EPERM		EPERM
/*add by jack*/
#define JACK_OP_CODE 20
#define KVM_ENABLE_SECURITY 21
#define KVM_DISABLE_SECURITY 22
#define PROCDESS_QUERY_CODE 24
/*sub op code by jack*/
#define KVM_ADD_SE_PROCESS 1
#define KVM_REMOVE_SE_PROCESS 2





#define KVM_HC_VAPIC_POLL_IRQ		1
#define KVM_HC_MMU_OP			2
#define KVM_HC_FEATURES			3
#define KVM_HC_PPC_MAP_MAGIC_PAGE	4

/*
 * hypercalls use architecture specific
 */
#include <asm/kvm_para.h>

#endif /* _UAPI__LINUX_KVM_PARA_H */
