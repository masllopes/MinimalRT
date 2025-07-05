#ifndef SCH_TI_DEVICE_H_
#define SCH_TI_DEVICE_H_

/*************************************************************************************
* @file    SCH_TI_Device.h
*
* @brief   Definition of device specific types and addresses required for the scheduler.
**************************************************************************************
*  Version  | Date       | Author     | Description       
**************************************************************************************
*  1.0      | 24/06/2025 | M. Lopes   | Initial revision. 
**************************************************************************************
*/

/*----------------------- Required interfaces -------------------*/
#include <stdint.h>
#include "SYSTEM.h"

/*----------------------- Provided interfaces -------------------*/
#include "SCH_TI_Device.h"


#ifndef __STATIC_FORCEINLINE
#define __STATIC_FORCEINLINE __attribute__((always_inline)) static inline
#endif

#ifndef __ASM
#define __ASM __asm
#endif

/* Interface barrries required to allow for CPU and memory  sync after some instructions */
__STATIC_FORCEINLINE void __ISB(void)
{
  __ASM volatile("isb 0xF" :: : "memory");
}

__STATIC_FORCEINLINE void __DSB(void)
{
  __ASM volatile("dsb 0xF" :: : "memory");
}


__STATIC_FORCEINLINE void __DMB(void)
{
  __ASM volatile("dmb 0xF" :: : "memory");
}

/* FPU registers */
typedef struct
{
  uint32_t RESERVED0[1U];
  volatile uint32_t FPCCR;  /*!< Offset: 0x004 (R/W)  Floating-Point Context Control Register */
  volatile uint32_t FPCAR;  /*!< Offset: 0x008 (R/W)  Floating-Point Context Address Register */
  volatile uint32_t FPDSCR; /*!< Offset: 0x00C (R/W)  Floating-Point Default Status Control Register */
  volatile uint32_t MVFR0;  /*!< Offset: 0x010 (R/ )  Media and FP Feature Register 0 */
  volatile uint32_t MVFR1;  /*!< Offset: 0x014 (R/ )  Media and FP Feature Register 1 */
  volatile uint32_t MVFR2;  /*!< Offset: 0x018 (R/ )  Media and FP Feature Register 2 */
} FPU_Type;

/* Floating-Point Context Control Register Definitions */
#define FPU_FPCCR_ASPEN_Pos 31U                          /*!< FPCCR: ASPEN bit Position */
#define FPU_FPCCR_ASPEN_Msk (1UL << FPU_FPCCR_ASPEN_Pos) /*!< FPCCR: ASPEN bit Mask */

#define FPU_FPCCR_LSPEN_Pos 30U                          /*!< FPCCR: LSPEN Position */
#define FPU_FPCCR_LSPEN_Msk (1UL << FPU_FPCCR_LSPEN_Pos) /*!< FPCCR: LSPEN bit Mask */

#define FPU_FPCCR_MONRDY_Pos 8U                            /*!< FPCCR: MONRDY Position */
#define FPU_FPCCR_MONRDY_Msk (1UL << FPU_FPCCR_MONRDY_Pos) /*!< FPCCR: MONRDY bit Mask */

#define FPU_FPCCR_BFRDY_Pos 6U                           /*!< FPCCR: BFRDY Position */
#define FPU_FPCCR_BFRDY_Msk (1UL << FPU_FPCCR_BFRDY_Pos) /*!< FPCCR: BFRDY bit Mask */

#define FPU_FPCCR_MMRDY_Pos 5U                           /*!< FPCCR: MMRDY Position */
#define FPU_FPCCR_MMRDY_Msk (1UL << FPU_FPCCR_MMRDY_Pos) /*!< FPCCR: MMRDY bit Mask */

#define FPU_FPCCR_HFRDY_Pos 4U                           /*!< FPCCR: HFRDY Position */
#define FPU_FPCCR_HFRDY_Msk (1UL << FPU_FPCCR_HFRDY_Pos) /*!< FPCCR: HFRDY bit Mask */

#define FPU_FPCCR_THREAD_Pos 3U                            /*!< FPCCR: processor mode bit Position */
#define FPU_FPCCR_THREAD_Msk (1UL << FPU_FPCCR_THREAD_Pos) /*!< FPCCR: processor mode active bit Mask */

#define FPU_FPCCR_USER_Pos 1U                          /*!< FPCCR: privilege level bit Position */
#define FPU_FPCCR_USER_Msk (1UL << FPU_FPCCR_USER_Pos) /*!< FPCCR: privilege level bit Mask */

#define FPU_FPCCR_LSPACT_Pos 0U                                /*!< FPCCR: Lazy state preservation active bit Position */
#define FPU_FPCCR_LSPACT_Msk (1UL /*<< FPU_FPCCR_LSPACT_Pos*/) /*!< FPCCR: Lazy state preservation active bit Mask */

/* Floating-Point Context Address Register Definitions */
#define FPU_FPCAR_ADDRESS_Pos 3U                                      /*!< FPCAR: ADDRESS bit Position */
#define FPU_FPCAR_ADDRESS_Msk (0x1FFFFFFFUL << FPU_FPCAR_ADDRESS_Pos) /*!< FPCAR: ADDRESS bit Mask */

/* Floating-Point Default Status Control Register Definitions */
#define FPU_FPDSCR_AHP_Pos 26U                         /*!< FPDSCR: AHP bit Position */
#define FPU_FPDSCR_AHP_Msk (1UL << FPU_FPDSCR_AHP_Pos) /*!< FPDSCR: AHP bit Mask */

#define FPU_FPDSCR_DN_Pos 25U                        /*!< FPDSCR: DN bit Position */
#define FPU_FPDSCR_DN_Msk (1UL << FPU_FPDSCR_DN_Pos) /*!< FPDSCR: DN bit Mask */

#define FPU_FPDSCR_FZ_Pos 24U                        /*!< FPDSCR: FZ bit Position */
#define FPU_FPDSCR_FZ_Msk (1UL << FPU_FPDSCR_FZ_Pos) /*!< FPDSCR: FZ bit Mask */

#define FPU_FPDSCR_RMode_Pos 22U                           /*!< FPDSCR: RMode bit Position */
#define FPU_FPDSCR_RMode_Msk (3UL << FPU_FPDSCR_RMode_Pos) /*!< FPDSCR: RMode bit Mask */

/* Media and FP Feature Register 0 Definitions */
#define FPU_MVFR0_FP_rounding_modes_Pos 28U                                        /*!< MVFR0: FP rounding modes bits Position */
#define FPU_MVFR0_FP_rounding_modes_Msk (0xFUL << FPU_MVFR0_FP_rounding_modes_Pos) /*!< MVFR0: FP rounding modes bits Mask */

#define FPU_MVFR0_Short_vectors_Pos 24U                                    /*!< MVFR0: Short vectors bits Position */
#define FPU_MVFR0_Short_vectors_Msk (0xFUL << FPU_MVFR0_Short_vectors_Pos) /*!< MVFR0: Short vectors bits Mask */

#define FPU_MVFR0_Square_root_Pos 20U                                  /*!< MVFR0: Square root bits Position */
#define FPU_MVFR0_Square_root_Msk (0xFUL << FPU_MVFR0_Square_root_Pos) /*!< MVFR0: Square root bits Mask */

#define FPU_MVFR0_Divide_Pos 16U                             /*!< MVFR0: Divide bits Position */
#define FPU_MVFR0_Divide_Msk (0xFUL << FPU_MVFR0_Divide_Pos) /*!< MVFR0: Divide bits Mask */

#define FPU_MVFR0_FP_excep_trapping_Pos 12U                                        /*!< MVFR0: FP exception trapping bits Position */
#define FPU_MVFR0_FP_excep_trapping_Msk (0xFUL << FPU_MVFR0_FP_excep_trapping_Pos) /*!< MVFR0: FP exception trapping bits Mask */

#define FPU_MVFR0_Double_precision_Pos 8U                                        /*!< MVFR0: Double-precision bits Position */
#define FPU_MVFR0_Double_precision_Msk (0xFUL << FPU_MVFR0_Double_precision_Pos) /*!< MVFR0: Double-precision bits Mask */

#define FPU_MVFR0_Single_precision_Pos 4U                                        /*!< MVFR0: Single-precision bits Position */
#define FPU_MVFR0_Single_precision_Msk (0xFUL << FPU_MVFR0_Single_precision_Pos) /*!< MVFR0: Single-precision bits Mask */

#define FPU_MVFR0_A_SIMD_registers_Pos 0U                                            /*!< MVFR0: A_SIMD registers bits Position */
#define FPU_MVFR0_A_SIMD_registers_Msk (0xFUL /*<< FPU_MVFR0_A_SIMD_registers_Pos*/) /*!< MVFR0: A_SIMD registers bits Mask */

/* Media and FP Feature Register 1 Definitions */
#define FPU_MVFR1_FP_fused_MAC_Pos 28U                                   /*!< MVFR1: FP fused MAC bits Position */
#define FPU_MVFR1_FP_fused_MAC_Msk (0xFUL << FPU_MVFR1_FP_fused_MAC_Pos) /*!< MVFR1: FP fused MAC bits Mask */

#define FPU_MVFR1_FP_HPFP_Pos 24U                              /*!< MVFR1: FP HPFP bits Position */
#define FPU_MVFR1_FP_HPFP_Msk (0xFUL << FPU_MVFR1_FP_HPFP_Pos) /*!< MVFR1: FP HPFP bits Mask */

#define FPU_MVFR1_D_NaN_mode_Pos 4U                                  /*!< MVFR1: D_NaN mode bits Position */
#define FPU_MVFR1_D_NaN_mode_Msk (0xFUL << FPU_MVFR1_D_NaN_mode_Pos) /*!< MVFR1: D_NaN mode bits Mask */

#define FPU_MVFR1_FtZ_mode_Pos 0U                                    /*!< MVFR1: FtZ mode bits Position */
#define FPU_MVFR1_FtZ_mode_Msk (0xFUL /*<< FPU_MVFR1_FtZ_mode_Pos*/) /*!< MVFR1: FtZ mode bits Mask */

/* Media and FP Feature Register 2 Definitions */

#define FPU_MVFR2_VFP_Misc_Pos 4U                                /*!< MVFR2: VFP Misc bits Position */
#define FPU_MVFR2_VFP_Misc_Msk (0xFUL << FPU_MVFR2_VFP_Misc_Pos) /*!< MVFR2: VFP Misc bits Mask */

/* System control block (SCB) registers */
typedef struct
{
  volatile uint32_t CPUID;    /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;     /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;     /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;    /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;      /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;      /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t SHP[12U];  /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;    /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;     /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;     /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;     /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;    /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;     /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;     /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
  volatile uint32_t PFR[2U];  /*!< Offset: 0x040 (R/ )  Processor Feature Register */
  volatile uint32_t DFR;      /*!< Offset: 0x048 (R/ )  Debug Feature Register */
  volatile uint32_t ADR;      /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
  volatile uint32_t MMFR[4U]; /*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
  volatile uint32_t ISAR[5U]; /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
  uint32_t RESERVED0[5U];
  volatile uint32_t CPACR; /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} SCB_Type;

#define SCB_ICSR_PENDSVSET_Pos 28U                             /*!< SCB ICSR: PENDSVSET Position */
#define SCB_ICSR_PENDSVSET_Msk (1UL << SCB_ICSR_PENDSVSET_Pos) /*!< SCB ICSR: PENDSVSET Mask */

#endif /* SCH_TI_DEVICE_H_ */