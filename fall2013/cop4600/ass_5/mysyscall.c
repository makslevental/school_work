/*

Name: Maksim Levental

UF ID: 3186-7826

Gator ID: mlevental86


*/


#include <linux/kernel_stat.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/mman.h>
#include <linux/swap.h>
#include <linux/highmem.h>
#include <linux/pagemap.h>
#include <linux/ksm.h>
#include <linux/rmap.h>
#include <linux/export.h>
#include <linux/delayacct.h>
#include <linux/init.h>
#include <linux/writeback.h>
#include <linux/memcontrol.h>
#include <linux/mmu_notifier.h>
#include <linux/kallsyms.h>
#include <linux/swapops.h>
#include <linux/elf.h>
#include <linux/gfp.h>

#include <asm/io.h>
#include <asm/pgalloc.h>
#include <asm/uaccess.h>
#include <asm/tlb.h>
#include <asm/tlbflush.h>
#include <asm/pgtable.h>

#include "internal.h"
/*#ifndef is_zero_pfn
static inline int is_zero_pfn(unsigned long pfn)
{
	return pfn == zero_pfn;
}
#endif*/
long sys_mysyscall(unsigned long address)
{


	pgd_t *pgd;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *ptep;
	spinlock_t *ptl;
	// new
	struct mm_struct *mm = current->mm;
	// replacing vma passed in
	struct vm_area_struct *vma = find_vma(mm, address);
	// vma = find_vma(mm, ksm_scan.address);
	pgd = pgd_offset(mm, address);

	pud = pud_offset(pgd, address);

	pmd = pmd_offset(pud, address);

	ptep = pte_offset_map_lock(mm, pmd, address, &ptl);

	// HEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEre
	// printk("%d .. %d .. %d .. %d ",vma->vm_page_prot, VM_WRITE, (vma->vm_flags & VM_WRITE), !pte_write(*ptep));
	return ((vma->vm_flags & VM_WRITE) && !pte_write(*ptep));
	

}
