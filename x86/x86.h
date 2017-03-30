#ifndef ARCH_X86_KVM_X86_H
#define ARCH_X86_KVM_X86_H

#include <linux/kvm_host.h>
#include "kvm_cache_regs.h"

static inline void kvm_clear_exception_queue(struct kvm_vcpu *vcpu)
{
	vcpu->arch.exception.pending = false;
}

static inline void kvm_queue_interrupt(struct kvm_vcpu *vcpu, u8 vector,
	bool soft)
{
	vcpu->arch.interrupt.pending = true;
	vcpu->arch.interrupt.soft = soft;
	vcpu->arch.interrupt.nr = vector;
}

static inline void kvm_clear_interrupt_queue(struct kvm_vcpu *vcpu)
{
	vcpu->arch.interrupt.pending = false;
}

static inline bool kvm_event_needs_reinjection(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.exception.pending || vcpu->arch.interrupt.pending ||
		vcpu->arch.nmi_injected;
}

static inline bool kvm_exception_is_soft(unsigned int nr)
{
	return (nr == BP_VECTOR) || (nr == OF_VECTOR);
}

static inline bool is_protmode(struct kvm_vcpu *vcpu)
{
	return kvm_read_cr0_bits(vcpu, X86_CR0_PE);
}

static inline int is_long_mode(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_X86_64
	return vcpu->arch.efer & EFER_LMA;
#else
	return 0;
#endif
}

static inline bool mmu_is_nested(struct kvm_vcpu *vcpu)
{
	return vcpu->arch.walk_mmu == &vcpu->arch.nested_mmu;
}

static inline int is_pae(struct kvm_vcpu *vcpu)
{
	return kvm_read_cr4_bits(vcpu, X86_CR4_PAE);
}

static inline int is_pse(struct kvm_vcpu *vcpu)
{
	return kvm_read_cr4_bits(vcpu, X86_CR4_PSE);
}

static inline int is_paging(struct kvm_vcpu *vcpu)
{
	return likely(kvm_read_cr0_bits(vcpu, X86_CR0_PG));
}

static inline u32 bit(int bitno)
{
	return 1 << (bitno & 31);
}

static inline void vcpu_cache_mmio_info(struct kvm_vcpu *vcpu,
					gva_t gva, gfn_t gfn, unsigned access)
{
	vcpu->arch.mmio_gva = gva & PAGE_MASK;
	vcpu->arch.access = access;
	vcpu->arch.mmio_gfn = gfn;
}

/*
 * Clear the mmio cache info for the given gva,
 * specially, if gva is ~0ul, we clear all mmio cache info.
 */
static inline void vcpu_clear_mmio_info(struct kvm_vcpu *vcpu, gva_t gva)
{
	if (gva != (~0ul) && vcpu->arch.mmio_gva != (gva & PAGE_MASK))
		return;

	vcpu->arch.mmio_gva = 0;
}

static inline bool vcpu_match_mmio_gva(struct kvm_vcpu *vcpu, unsigned long gva)
{
	if (vcpu->arch.mmio_gva && vcpu->arch.mmio_gva == (gva & PAGE_MASK))
		return true;

	return false;
}

static inline bool vcpu_match_mmio_gpa(struct kvm_vcpu *vcpu, gpa_t gpa)
{
	if (vcpu->arch.mmio_gfn && vcpu->arch.mmio_gfn == gpa >> PAGE_SHIFT)
		return true;

	return false;
}

void kvm_before_handle_nmi(struct kvm_vcpu *vcpu);
void kvm_after_handle_nmi(struct kvm_vcpu *vcpu);
int kvm_inject_realmode_interrupt(struct kvm_vcpu *vcpu, int irq, int inc_eip);

void kvm_write_tsc(struct kvm_vcpu *vcpu, struct msr_data *msr);
static int kvm_read_guest_virt_system(struct x86_emulate_ctxt *ctxt,
                gva_t addr, void *val, unsigned int bytes,
                struct x86_exception *exception);
int kvm_read_guest_virt(struct x86_emulate_ctxt *ctxt,
	gva_t addr, void *val, unsigned int bytes,
	struct x86_exception *exception);
/*jack code*/
static int add_process_to_list(struct kvm_vcpu *vcpu,u32 next_process,u32 targetpid);
static int get_proname_by_path(struct kvm_vcpu *vcpu,u32 next_process,hva_t *pro_name);
static int get_curr_apc_processName(struct kvm_vcpu *vcpu,u32 *curr_processadd,char *pname,u32 *apcadd,u32 *belongprocess);
 int get_process_list_by_handletable(struct kvm_vcpu *vcpu,u32 targetpid);
static int get_curr_processName(struct kvm_vcpu *vcpu,char *pname,u32 *processadd);
static int foreach_process_list(struct list_head *head);
static int insert_list(struct list_head *head,struct list_head *node);
static int del_list(struct list_head *head,struct list_head *node);
static struct  list_head* find_se_process_by_pname(struct list_head *head,char *pname);
static struct  list_head* find_se_process_by_pid(struct list_head *head,int pid);
void *vmx_alloc(unsigned long size);
void vmx_free(const void *addr);
/*
unsigned int kvm_get_guest_last_spte(struct kvm_vcpu *vcpu,gva_t addr,u64 *last_spte);
int kvm_alloc_vm_page1(gva_t ssdt_base,gva_t nonpagedpoolstart,struct kvm_vcpu *vcpu,u32 mmpfn);
 int kvm_alloc_vm_page(gva_t ssdt_base,struct kvm_vcpu *vcpu,u64 *last_spte,int *flag);*/
int kvm_write_guest_virt_system(struct x86_emulate_ctxt *ctxt,
	gva_t addr, void *val, unsigned int bytes,
	struct x86_exception *exception);

extern u64 host_xcr0;

extern struct kvm_static_key kvm_no_apic_vcpu;
#endif
