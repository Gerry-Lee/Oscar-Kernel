#include "Task.h"

RETURN_STATUS ArchFrameIpSet(VOID * StackFrame, UINT64 Ip)
{
	X86_64_STACK_FRAME * X64StackPtr = (VOID *)((UINT64)StackFrame + MAX_STACK_FRAME_SIZE - sizeof(X86_64_STACK_FRAME));
	X64StackPtr->RIP = Ip;
	return RETURN_SUCCESS;
}

RETURN_STATUS ArchFrameSpSet(VOID * StackFrame, UINT64 Sp)
{
	X86_64_STACK_FRAME * X64StackPtr = (VOID *)((UINT64)StackFrame + MAX_STACK_FRAME_SIZE - sizeof(X86_64_STACK_FRAME));
	X64StackPtr->RSP = Sp;
	return RETURN_SUCCESS;
}

RETURN_STATUS ArchFrameKernelModeSet(VOID * StackFrame)
{
	X86_64_STACK_FRAME * X64StackPtr = (VOID *)((UINT64)StackFrame + MAX_STACK_FRAME_SIZE - sizeof(X86_64_STACK_FRAME));
	X64StackPtr->CS = SELECTOR_KERNEL_CODE;
	X64StackPtr->DS = SELECTOR_KERNEL_DATA;
	X64StackPtr->ES = SELECTOR_KERNEL_DATA;
	X64StackPtr->FS = SELECTOR_KERNEL_DATA;
	X64StackPtr->GS = SELECTOR_KERNEL_DATA;
	X64StackPtr->SS = SELECTOR_KERNEL_DATA;
	X64StackPtr->RFLAGS = 0x1202;
	return RETURN_SUCCESS;
}

RETURN_STATUS ArchFrameUserModeSet(VOID * StackFrame)
{
	X86_64_STACK_FRAME * X64StackPtr = (VOID *)((UINT64)StackFrame + MAX_STACK_FRAME_SIZE - sizeof(X86_64_STACK_FRAME));
	X64StackPtr->CS = SELECTOR_USER_CODE | 0x3;
	X64StackPtr->DS = SELECTOR_USER_DATA | 0x3;
	X64StackPtr->ES = SELECTOR_USER_DATA | 0x3;
	X64StackPtr->FS = SELECTOR_USER_DATA | 0x3;
	X64StackPtr->GS = SELECTOR_USER_DATA | 0x3;
	X64StackPtr->SS = SELECTOR_USER_DATA | 0x3;
	X64StackPtr->RFLAGS = 0x1202;
	return RETURN_SUCCESS;
}

RETURN_STATUS ArchFrameParaRegSet(
	VOID * StackFrame, 
	UINT64 Para1, 
	UINT64 Para2, 
	UINT64 Para3, 
	UINT64 Para4, 
	UINT64 Para5, 
	UINT64 Para6)
{
	X86_64_STACK_FRAME * X64StackPtr = (VOID *)((UINT64)StackFrame + MAX_STACK_FRAME_SIZE - sizeof(X86_64_STACK_FRAME));
	X64StackPtr->RDI = Para1;
	X64StackPtr->RSI = Para2;
	X64StackPtr->RDX = Para3;
	X64StackPtr->RCX = Para4;
	X64StackPtr->R8 = Para5;
	X64StackPtr->R9 = Para6;
	return RETURN_SUCCESS;
}
