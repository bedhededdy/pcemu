#include "cpu.h"

#include <stdbool.h>

#include "bus.h"

void cpu_ctor(cpu_t *cpu, bus_t *bus) {
    cpu->bus = bus;
}

void cpu_reset(cpu_t *cpu) {
    cpu->pc = 0x3000;
    cpu->ctrl = 0;
    cpu->cond = 0;
}

void cpu_dtor(cpu_t *cpu) {
}

void cpu_clock(cpu_t *cpu) {
    cpu->ir = bus_read(cpu->bus, cpu->pc);
    cpu->pc += 4;
    cpu->ir |= bus_read(cpu->bus, cpu->pc) << 32;
    cpu->pc += 4;

    cpu_decode(cpu);
}

static void cpu_decode(cpu_t *cpu) {
    uint8_t opcode = cpu->ir >> 56;
}

static void cpu_set_cond(cpu_t *cpu, bool zero, bool negative, bool overflow, bool carry) {
    cpu->cond = (carry << 3) | (overflow << 2) | (negative << 1) | zero;
}

static void cpu_decode_reg_offsets(cpu_t *cpu, uint32_t *dr, uint32_t *sr1, uint32_t *sr2) {
    *dr =  (cpu->ir & 0x00f00000) >> 40;
    *sr1 = (cpu->ir & 0x000f0000) >> 32;
    *sr2 = (cpu->ir & 0x0000f000) >> 24;
}

static void cpu_and(cpu_t *cpu) {
    uint32_t dr, sr1, sr2;
    cpu_decode_reg_offsets(cpu, &dr, &sr1, &sr2);

    uint32_t res = cpu->r[sr1] & cpu->r[sr2];
    cpu->r[dr] = res;

    cpu_set_cond(cpu, res == 0, false, false, false);
}

static void cpu_add(cpu_t *cpu) {
    uint32_t dr, sr1, sr2;
    cpu_decode_reg_offsets(cpu, &dr, &sr1, &sr2);

    int32_t lhs = cpu->r[sr1];
    int32_t rhs = cpu->r[sr2];
    int32_t res = lhs + rhs;
    cpu->r[dr] = res;

    bool ovr = (lhs > 0 & rhs > 0 && res < 0) || (lhs < 0 && rhs < 0 && res > 0);

    cpu_set_cond(cpu, res == 0, res < 0, ovr, false);
}

static void cpu_addu(cpu_t *cpu) {
    uint32_t dr, sr1, sr2;
    cpu_decode_reg_offsets(cpu, &dr, &sr1, &sr2);

    uint32_t lhs = cpu->r[sr1];
    uint32_t rhs = cpu->r[sr2];
    uint32_t res = lhs + rhs;
    cpu->r[dr] = res;

    bool carry = (lhs & 0x80000000) || (rhs & 0x80000000) && !(res & 0x80000000);

    cpu_set_cond(cpu, res == 0, false, false, carry);
}

static void cpu_fadd(cpu_t *cpu) {
    uint32_t dr, sr1, sr2;
    cpu_decode_reg_offsets(cpu, &dr, &sr1, &sr2);

    float lhs = cpu->r[sr1];
    float rhs = cpu->r[sr2];
    float res = lhs + rhs;
    cpu->r[dr] = res;

    bool ovr = (lhs > 0.0f && rhs > 0.0f && res < 0.0f) || (lhs < 0.0f && rhs < 0.0f && res > 0.0f);

    cpu_set_cond(cpu, res == 0.0f, res < 0.0f, ovr, false);
}

static void cpu_brz(cpu_t *cpu) {
    uint32_t reg = (cpu->ir & 0x00f00000) >> 40;
    cpu->pc = (cpu->cond & 0x01) ? cpu->r[reg] : cpu->pc;
}

static void cpu_brn(cpu_t *cpu) {
    uint32_t reg = (cpu->ir & 0x00f00000) >> 40;
    cpu->pc = (cpu->cond & 0x02) ? cpu->r[reg] : cpu->pc;
}

static void cpu_call(cpu_t *cmp) {
    // call function
    // push regs to stack
    // set pc
}

static void cpu_div(cpu_t *cpu) {

}

static void cpu_divu(cpu_t *cpu) {

}

static void cpu_fdiv(cpu_t *cpu) {

}

static void cpu_hlt(cpu_t *cpu) {
    // halt CPU
}

static void cpu_in(cpu_t *cpu) {
    // IO IN
}

static void cpu_jmp(cpu_t *cpu) {
    uint32_t reg = (cpu->ir & 0x00f00000) >> 40;
    cpu->pc = cpu->r[reg];
}

static void cpu_ld(cpu_t *cpu) {
    // load dr,0x01
    // load dr,*(sr)
}

static void cpu_mul(cpu_t *cpu) {

}

static void cpu_mulu(cpu_t *cpu) {

}

static void cpu_fmul(cpu_t *cpu) {

}

static void cpu_nop(cpu_t *cpu) {

}

static void cpu_not(cpu_t *cpu) {

}

static void cpu_out(cpu_t *cpu) {
    // IO OUT
}

static void cpu_or(cpu_t *cpu) {

}

static void cpu_ret(cpu_t *cpu) {
    // return from call
}

static void cpu_rctl(cpu_t *cpu) {
    // read control register
}

static void cpu_sctl(cpu_t *cpu) {
    // write control register
}

static void cpu_shl(cpu_t *cpu) {
    // shift left
}

static void cpu_shr(cpu_t *cpu) {
    // shift right
}

static void cpu_st(cpu_t *cpu) {
    // store sr1,0x01
    // store sr1,*(sr2)
}

static void cpu_sub(cpu_t *cpu) {

}

static void cpu_subu(cpu_t *cpu) {

}

static void cpu_fsub(cpu_t *cpu) {

}

static void cpu_trap(cpu_t *cpu) {
    // interrupt
}

static void cpu_tret(cpu_t *cpu) {
    // return from interrupt
}
