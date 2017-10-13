#include "SpinLock.h"
#include "Thread.h"

VOID SpinLock(SPIN_LOCK * SpinLock)
{
	ArchGetSpinLock(&SpinLock->SpinLock);
}

VOID SpinUnlock(SPIN_LOCK * SpinLock)
{
	ArchReleaseSpinLock(&SpinLock->SpinLock);
}

VOID SpinLockIrqSave(SPIN_LOCK * SpinLock)
{
	UINT64 IrqStatus = ArchGetIrqStatus();
	ArchDisableCpuIrq();

	//�˴������ȵõ����Ժ��ٱ����жϵ�״̬�����򱣴�Ŀ��ܲ��ǵõ���CPU���ж�״̬
	ArchGetSpinLock(&SpinLock->SpinLock);	
	SpinLock->LocalIrqStatus = IrqStatus;

	THREAD_CONTROL_BLOCK * Current = GetCurrentThread();
	if (Current)
	{
		Current->PreemptEnable++;
	}
}

VOID SpinUnlockIrqRestore(SPIN_LOCK * SpinLock)
{		
	UINT64 IrqStatus = SpinLock->LocalIrqStatus;
	//Ҫ���ͷ�ǰ��ȡ�жϵ�״̬��������ܱ�����CPU��ռ���¶��������״̬

	THREAD_CONTROL_BLOCK * Current = GetCurrentThread();
	if (Current)
	{
		Current->PreemptEnable--;
	}

	ArchReleaseSpinLock(&SpinLock->SpinLock);

	if (IrqStatus)
		ArchEnableCpuIrq();
}

VOID SpinUnlockIrqEnable(SPIN_LOCK * SpinLock)
{
	ArchReleaseSpinLock(&SpinLock->SpinLock);
	ArchEnableCpuIrq();
}