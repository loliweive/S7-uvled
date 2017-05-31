;**********************************************************
;KEYɨ�裬���ڲ���:key_byte
;ʹ��ϸ��Ŀǰֻ�õ�������������ʶ��������ʶ�����������ĳ����̰���
;�˴�δ�漰���������������ܸ���
;������־�ڰ�������ʶ�𵽺�ֱ����һ���̰���־���ͷŰ����ĺ�������һ
;************************m_key_scan_proc*****************

get_key_value:

	btfss	S1
	bsf	f_key0

	movf	key_byte,w
	btfsc	Z
	goto	key_release		;�ް���
	movwf	current_key		;�а��������浱ǰ�İ���ֵ
	xorwf	last_key,f		;����һ�ΰ���ֵ���бȽ�
	btfss	Z
	clrf	cnt_key_press		;ǰ�󰴼�ֵ����ȣ����¿�ʼ����
	incf	cnt_key_press,f		;ǰ�󰴼�ֵ��ȣ�������1
	movwf	last_key		;����ǰ����ֵ��ֵ����һ�ΰ���ֵ
	
key_debounce:

	btfsc	f_keylock
	goto	get_key_value_end
	movlw	KEY_DEBOUNCE_TICK
	subwf	cnt_key_press,w
	btfss	C
	goto	get_key_value_end	
	clrf	cnt_key_press		;�������
	bsf	f_keylock		;�̰����������߰���������ɱ�־
	bsf	f_short_press
	goto	get_key_value_end
	
key_release:

	incf	cnt_key_release,f
	movlw	CONST_KEY_RELEASE
	subwf	cnt_key_release,w
	btfss	C
	goto	get_key_value_end
	clrf	cnt_key_release		;�����ͷ�����
	btfss	f_status_on		;��ֹ˯�ߺ󰴼����ɿ������ϵͳ�����̱�����
	bsf	f_sleep
	btfss	f_keylock
	goto	get_key_value_end
	bcf	f_keylock
	
	movf	last_key,w
	iorwf	key_byte,f		;����last_key�ļ�ֵ
	goto	get_key_value_end
	
get_key_value_end:

	return
;----------------------------------------------------------

;**********************************************************
;KEY�������������ڲ���:mode��f_status_on
;	      ��ڲ���:key_byte
;ʹ��ϸ��	
;************************m_key_scan_proc*****************	
key_proc:

	btfsc	f_key0
	goto	key0_proc
	goto	key_proc_end
	
;---key0����	
key0_proc:
	
	;��λ����
	btfss	f_short_press
	goto	key_proc_end
	
power_on_off_judge:

	btfss	f_status_on
	goto	power_on
	
power_off:
	
	bcf	f_status_on
	OFFLED
	goto	key_proc_end
	
power_on:

	bsf	f_status_on
	ONLED	
	
key_proc_end:

	clrf	key_byte		;��������������㰴��ֵ
	return	
;-------------------------------------------------