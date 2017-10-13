extern TSS

global ArchTaskSchedule
global ArchThreadStart
extern PickNextThread
extern GetCurrentThread


ArchThreadStart:

	xor rcx, rcx
	str	cx							; ���浱ǰTSS��������cx
	shr cx, 4
	sub cx, 64						; TSS��������GDT��65�ʼ
	imul rdx, rcx, 104
	mov r8, TSS
	lea rbx, [r8 + rdx]
	mov rax, [rdi + 0x10000]		; ����Ŀ���߳��ں�ջָ��
	mov rsp, rax
	add rax, 192
	mov [rbx + 4], rax				; �ı�TSS.RSP0ʹ�´��жϷ���ʱʹ��Ŀ���߳��ں�ջ

	pop rax
	mov gs, ax
	pop rax
	mov fs, ax
	pop rax
	mov es, ax
	pop rax
	mov ds, ax

	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rdi
	pop rsi
	pop rbp
	;pop rsp
	pop rdx
	pop rcx
	pop rbx
	pop rax

	iretq

ArchTaskSchedule:
		
		mov rax, GetCurrentThread
		call rax
		test rax, rax
		jz PickThread

		mov rbx, rax					;rbxΪ��ǰ�߳�ָ��
		
		mov rax, [rbx + 0x10008]		;������µ��ȱ��
		test rax, rax
		jz NoSchedule

		mov rax, [rbx + 0x10010]		;�����ռ����
		test rax, rax
		jnz NoSchedule
		
		mov [rbx + 0x10000], rbp		;����֮ǰջָ�뵽�߳��������У�rsp->rbp���жϴ������б�����

PickThread:
		
		mov rax, PickNextThread
		call rax
		
		mov rdi, rax
		mov rax, ArchThreadStart
		call rax

		; Cannot reach here
		jmp $

NoSchedule:
		ret