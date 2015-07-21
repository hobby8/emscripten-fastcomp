//===- MCNaClExpander.h -----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the MCNaClExpander class. This is an abstract
// class that encapsulates the expansion logic for MCInsts, and holds
// state such as available scratch registers.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_MC_MCNACLEXPANDER_H
#define LLVM_MC_MCNACLEXPANDER_H

#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"

namespace llvm {
class MCInst;
class MCSubtargetInfo;
class MCStreamer;

class MCNaClExpander {
protected:
  std::unique_ptr<MCInstrInfo> InstInfo;
  std::unique_ptr<MCRegisterInfo> RegInfo;

public:
  MCNaClExpander(std::unique_ptr<MCRegisterInfo> &&RI,
                 std::unique_ptr<MCInstrInfo> &&II)
      : InstInfo(std::move(II)), RegInfo(std::move(RI)) {}
  bool isReturn(const MCInst &Inst);

  virtual ~MCNaClExpander() = default;
  virtual bool expandInst(const MCInst &Inst, MCStreamer &Out,
                          const MCSubtargetInfo &STI) = 0;
};

}
#endif
